//--------------------------------------------------------------------------------
//
//	プレイヤーの処理 [player.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "player.h"					// プレイヤー
#include "keyboard.h"				// キーボード
#include "camera.h"					// カメラ
#include "Goal.h"					// ゴール
#include "meshfild.h"				// 地面
#include "shadow.h"					// 影

//--------------------------------------------------------------------------------
//	マクロ定義
//--------------------------------------------------------------------------------
#define MAX_MOVE		(0.3f)		// 移動量
#define MAX_ROT			(0.1f)		// 向き

#define MAX_FLAME		(40)		// 再生フレーム数
#define MAX_COUNTER		(10)		// モーションカウンター

#define MAX_JUMP		(2)		// ジャンプ

#define MAX_PLAYER		(20)		// モデル数

//--------------------------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------------------------
Player g_player;					// プレイヤーの情報	
Model g_Model;						// プレイヤーの情報
											
//--------------------------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------------------------
HRESULT InitPlayer(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// プレイヤーの最初のモーション
	g_player.motionType = MOTION_NONE;

	// プレイヤー構造体の初期化
	g_player.pos =D3DXVECTOR3 (0.0f,0.0f,0.0f);						// 今の位置
	g_player.posOld =D3DXVECTOR3 (0.0f,0.0f,0.0f);					// 昔の位置
	g_player.rot = D3DXVECTOR3 (0.0f,0.0f,0.0f);					// 向き
	g_player.rotDest = D3DXVECTOR3(0.0f,0.0f,0.0f) ;				// 目的の向き
	g_player.move =  D3DXVECTOR3(0.0f,0.0f,0.0f) ;					// 移動量
	g_player.bJump = false;											// ジャンプ中かどうか
	g_player.bGetKey = false;										// 鍵を持っているか
	g_player.nIdx = SetShadow(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		// 影
	g_player.oldmotionType = MOTION_NONE;


	// モデルの読み込み
	// テキストファイル読み込み
	FILE *pfile = fopen("data/TEXT/motion.txt", "r");
	char string[255][255];

	// モデル数の読み込み(パーツ)
	while (fgets(string[0], 255, pfile) != NULL)
	{// NULLじゃなかったら
		fscanf(pfile, "%s", string[0]);

		if (strcmp(string[0], "NUM_MODEL") == 0)
		{//　strcmp文字列は一致したら
			fscanf(pfile, "%s %d", &string[0], &g_player.nNumModel);
			break;
		}
	}

	// Xファイル文の読み込み
	for (int nCntNumModel = 0; nCntNumModel < g_player.nNumModel; nCntNumModel++)
	{
		while (fgets(string[0], 255, pfile) != NULL)
		{
			if (strstr(string[0], "MODEL_FILENAME"))
			{
				sscanf(string[0], "%s %s %s %*s %*s\n", string[1], string[2], &g_player.aModel[nCntNumModel].sModelFailName);
				break;
			}
		}
		// Xファィルの読み込み
		D3DXLoadMeshFromX(g_player.aModel[nCntNumModel].sModelFailName,			// 読み込むXファイル名
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[nCntNumModel].pBuffMat,							// マテリアル(頂点情報)
			NULL,
			&g_player.aModel[nCntNumModel].nNumMat,								// マテリアル数
			&g_player.aModel[nCntNumModel].pMesh);								// メッシュ(頂点情報)
	}
	for (int nCntNumModel = 0; nCntNumModel < g_player.nNumModel; nCntNumModel++)
	{
		// 階層構造
		while (fgets(string[0], 255, pfile) != NULL)
		{
			if (strstr(string[0], "INDEX"))
			{
				sscanf(string[0], "%s %s %d", string[0], string[1], &g_player.aModel[nCntNumModel].nIdxModelNum);		// インデックス情報
				fscanf(pfile, "%s%s%d%*s%*s", string[1], string[2], &g_player.aModel[nCntNumModel].nIdModelParent);
				fscanf(pfile, "%s%s%f%f%f", string[3], string[4], &g_player.aModel[nCntNumModel].pos.x, &g_player.aModel[nCntNumModel].pos.y, &g_player.aModel[nCntNumModel].pos.z);
				fscanf(pfile, "%s%s%f%f%f", string[5], string[6], &g_player.aModel[nCntNumModel].rot.x, &g_player.aModel[nCntNumModel].rot.y, &g_player.aModel[nCntNumModel].rot.z);
				break;
			}
		}

		// マテリアルデータを取得する
		g_player.aModel[nCntNumModel].pMat = (D3DXMATERIAL*)g_player.aModel[nCntNumModel].pBuffMat->GetBufferPointer();
		g_player.aModel[nCntNumModel].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 初期化

																				// 頂点数を取得する
		g_player.aModel[nCntNumModel].nNumVtx = g_player.aModel[nCntNumModel].pMesh->GetNumVertices();

		// 頂点フォーマットのサイズを取得
		g_player.aModel[nCntNumModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_player.aModel[nCntNumModel].pVtxBuff);

		for (int nCntvtx = 0; nCntvtx < g_player.aModel[nCntNumModel].nNumVtx; nCntvtx++)
		{
			g_player.aModel[nCntNumModel].vtx = *(D3DXVECTOR3*)g_player.aModel[nCntNumModel].pVtxBuff;		// 頂点座標の代入

																											// xの最大値の比較
			if (g_player.aModel[nCntNumModel].vtx.x >= g_player.aModel[nCntNumModel].vtxMax.x)
			{
				g_player.aModel[nCntNumModel].vtxMax.x = g_player.aModel[nCntNumModel].vtx.x;
			}

			// yの最大値の比較
			if (g_player.aModel[nCntNumModel].vtx.y >= g_player.aModel[nCntNumModel].vtxMax.y)
			{
				g_player.aModel[nCntNumModel].vtxMax.y = g_player.aModel[nCntNumModel].vtx.y;
			}

			// zの最大値の比較
			if (g_player.aModel[nCntNumModel].vtx.z >= g_player.aModel[nCntNumModel].vtxMax.z)
			{
				g_player.aModel[nCntNumModel].vtxMax.z = g_player.aModel[nCntNumModel].vtx.z;
			}

			// xの最小値の比較
			if (g_player.aModel[nCntNumModel].vtx.x <= g_player.aModel[nCntNumModel].vtxMax.x)
			{
				g_player.aModel[nCntNumModel].vtxMax.x = g_player.aModel[nCntNumModel].vtx.x;
			}

			// yの最小値の比較
			if (g_player.aModel[nCntNumModel].vtx.y <= g_player.aModel[nCntNumModel].vtxMax.y)
			{
				g_player.aModel[nCntNumModel].vtxMax.y = g_player.aModel[nCntNumModel].vtx.y;
			}

			// zの最小値の比較
			if (g_player.aModel[nCntNumModel].vtx.z <= g_player.aModel[nCntNumModel].vtxMax.z)
			{
				g_player.aModel[nCntNumModel].vtxMax.z = g_player.aModel[nCntNumModel].vtx.z;
			}
			// 頂点フォーマットのサイズ分ポインタを進める
			g_player.aModel[nCntNumModel].pVtxBuff += g_player.aModel[nCntNumModel].sizeFVF;
		}
		//頂点バッファをアンロック
		g_player.aModel[nCntNumModel].pMesh->UnlockVertexBuffer();
	}

	//キー情報
	for (int nCnt1 = 0; nCnt1 < MOTION_MAX; nCnt1++)
	{// モーション読み込み
	 // キー数の取得
		while (fgets(string[0], 255, pfile) != NULL)
		{
			if (strstr(string[0], "MOTIONSET"))
			{
				fscanf(pfile, "%s%s%d%*s%*s%*s%*s", string[1], string[2], &g_player.aMotionInfo[nCnt1].nLoop);
				fscanf(pfile, "%s%s%d", string[3], string[4], &g_player.aMotionInfo[nCnt1].nMaxKey);
				break;
			}
		}
		for (int nCnt2 = 0; nCnt2 < g_player.aMotionInfo[nCnt1].nMaxKey; nCnt2++)
		{
			while (fgets(string[0], 255, pfile) != NULL)
			{
				if (strstr(string[0], "KEYSET"))
				{
					fscanf(pfile, "%s%s%d", string[1], string[2], &g_player.aMotionInfo[nCnt1].aKeyInfo[nCnt2].nFrame);
					break;
				}
			}
			for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
			{
				while (fgets(string[0], 255, pfile) != NULL)
				{
					if (strstr(string[0], "KEY"))
					{
						fscanf(pfile, "%s%s%f%f%f", string[1], string[2], &g_player.aMotionInfo[nCnt1].aKeyInfo[nCnt2].aKey[nCnt].fPosKeyX,
							&g_player.aMotionInfo[nCnt1].aKeyInfo[nCnt2].aKey[nCnt].fPosKeyY,
							&g_player.aMotionInfo[nCnt1].aKeyInfo[nCnt2].aKey[nCnt].fPosKeyZ);

						fscanf(pfile, "%s%s%f%f%f%*s", string[3], string[4], &g_player.aMotionInfo[nCnt1].aKeyInfo[nCnt2].aKey[nCnt].fRotKeyX,
							&g_player.aMotionInfo[nCnt1].aKeyInfo[nCnt2].aKey[nCnt].fRotKeyY,
							&g_player.aMotionInfo[nCnt1].aKeyInfo[nCnt2].aKey[nCnt].fRotKeyZ);
						break;
					}
				}
			}

			while (fgets(string[0], 255, pfile) != NULL)
			{
				if (strstr(string[0], "END_KEYSET"))
				{
					break;
				}
			}
		}
		while (fgets(string[0], 255, pfile) != NULL)
		{
			if (strstr(string[0], "END_MOTIONSET"))
			{
				break;
			}
		}
	}
	// 原点にあるposとモデルごとにあるposをいい感じに合体させる
	for (int nCntMotion = 0; nCntMotion < MOTION_MAX; nCntMotion++)
	{
		for (int nCntKey = 0; nCntKey < g_player.aMotionInfo[nCntMotion].nMaxKey; nCntKey++)
		{
			for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
			{
				g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fPosKeyX += g_player.aModel[nCnt].pos.x;
				g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fPosKeyY += g_player.aModel[nCnt].pos.y;
				g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fPosKeyZ += g_player.aModel[nCnt].pos.z;

				g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fRotKeyX += g_player.aModel[nCnt].rot.x;
				g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fRotKeyY += g_player.aModel[nCnt].rot.y;
				g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fRotKeyZ += g_player.aModel[nCnt].rot.z;
			}
		}
	}
	fclose(pfile);
	return S_OK;
}

//--------------------------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------------------------
void UninitPlayer(void)
{
	for (int nCutModel = 0; nCutModel < g_player.nNumModel; nCutModel++)
	{
		// メッシュの開放
		if (g_player.aModel[nCutModel].pMesh != NULL)
		{
			g_player.aModel[nCutModel].pMesh->Release();
			g_player.aModel[nCutModel].pMesh = NULL;
		}

		// マテリアルの開放
		if (g_player.aModel[nCutModel].pBuffMat != NULL)
		{
			g_player.aModel[nCutModel].pBuffMat->Release();
			g_player.aModel[nCutModel].pBuffMat = NULL;
		}
	}
}

//--------------------------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------------------------
void UpdatePlayer(void)
{
	// カメラの情報をもらう
	Camera * pCamera;
	pCamera = GetCamera();

	// ゴールの情報
	Goal *pGoal = GetGoal();




	// プレイヤーの移動処理
	if (GetkeyboardPress(DIK_W) == true)
	{// Wキーを押した

		g_player.motionType = MOTION_WORK;

		if (GetkeyboardPress(DIK_D) == true)
		{// Dキーを押した
			g_player.move.x += sinf(pCamera->rot.y + D3DX_PI * 3 / 4) * MAX_MOVE;
			g_player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 3 / 4) * MAX_MOVE;
			g_player.rotDest.y = -D3DX_PI * 3 / 4 - pCamera->rot.y;

		}
		else if (GetkeyboardPress(DIK_A) == true)
		{// Aキーを押した
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 3 / 4) * MAX_MOVE;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 3 / 4) * MAX_MOVE;
			g_player.rotDest.y = D3DX_PI * 3 / 4 - pCamera->rot.y;

		}
		else
		{
			g_player.move.x += sinf(pCamera->rot.y + D3DX_PI) * MAX_MOVE;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI) * MAX_MOVE;
			g_player.rotDest.y = D3DX_PI - pCamera->rot.y;
		}
	}
	else if (GetkeyboardPress(DIK_S) == true)
	{
		g_player.motionType = MOTION_WORK;

		if (GetkeyboardPress(DIK_A) == true)
		{
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 1 / 4) * MAX_MOVE;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 1 / 4) * MAX_MOVE;
			g_player.rotDest.y = D3DX_PI * 1 / 4 - pCamera->rot.y;

		}
		else if (GetkeyboardPress(DIK_D) == true)
		{
			g_player.move.x += sinf(pCamera->rot.y + D3DX_PI * 1 / 4) * MAX_MOVE;
			g_player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 1 / 4) * MAX_MOVE;
			g_player.rotDest.y = -D3DX_PI * 1 / 4 - pCamera->rot.y;
		}
		else
		{
			g_player.move.x -= sinf(pCamera->rot.y + D3DX_PI) * MAX_MOVE;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI) * MAX_MOVE;
			g_player.rotDest.y = 0.0f - pCamera->rot.y;
		}
	}
	else if (GetkeyboardPress(DIK_A) == true)		// 右移動・左移動
	{// Aキーを押した
		g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 2 / 4) * MAX_MOVE;
		g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 2 / 4) * MAX_MOVE;
		g_player.rotDest.y = D3DX_PI * 2 / 4 - pCamera->rot.y;

		g_player.motionType = MOTION_WORK;
	}
	else if (GetkeyboardPress(DIK_D) == true)
	{// Dキーを押した
		g_player.move.x += sinf(pCamera->rot.y + D3DX_PI * 2 / 4) * MAX_MOVE;
		g_player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 2 / 4) * MAX_MOVE;
		g_player.rotDest.y = -D3DX_PI * 2 / 4 - pCamera->rot.y;

		g_player.motionType = MOTION_WORK;
	}
	else if (GetkeyboardPress(DIK_W) == false)
	{// キー入力されてなかったら
		g_player.motionType = MOTION_NONE;
	}
	else if (GetkeyboardPress(DIK_A) == false)
	{
		g_player.motionType = MOTION_NONE;
	}
	else if (GetkeyboardPress(DIK_S) == false)
	{
		g_player.motionType = MOTION_NONE;
	}
	else if (GetkeyboardPress(DIK_D) == false)
	{
		g_player.motionType = MOTION_NONE;
	}

	// モーション
	MotionPlayer(g_player.motionType);

	// 左シフトを押した
	if (GetkeyboardPress(DIK_LSHIFT) == true)
	{// 左回転
		g_player.rot.y -= MAX_ROT;
	}

	// 右シフトを押した
	if (GetkeyboardPress(DIK_RSHIFT) == true)
	{// 右回転
		g_player.rot.y += MAX_ROT;
	}


	// 重力
//	g_player.pos.y--;

	//// プレイヤーの位置が0以下の時
	//if (g_player.pos.y <= 0)
	//{
	//	if (GetkeyboardTrgger(DIK_SPACE) == true && g_player.bJump == false)
	//	{//ジャンプの処理(2段ジャンプの制御)
	//		g_player.move.y = MAX_JUMP;
	//		g_player.bJump = true;

	//		g_player.motionType = MOTION_JUMP;
	//	}
	//}




	// 位置の更新
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;
	g_player.pos.z += g_player.move.z;

	// 目的回転制限
	if ((g_player.rotDest.y - g_player.rot.y) > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}
	if ((g_player.rotDest.y - g_player.rot.y) < (-D3DX_PI))
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}

	// 向いてる方向
	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.1f;

	// 回転制限
	if (g_player.rot.y < (-D3DX_PI))
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}
	if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}

	// 移動・回転量の減衰　割合で移動量を０まで減らす
	g_player.move.x += (0 - g_player.move.x) * 0.08f;		
	g_player.move.y += (0 - g_player.move.y) * 0.05f;
	g_player.move.z += (0 - g_player.move.z) * 0.08f;


	// 影をセットする
	SetPositionShadow(g_player.nIdx, D3DXVECTOR3(g_player.pos.x, 0.0f, g_player.pos.z));


}

//--------------------------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------------------------
void DrawPlayer(void)
{
	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得:
	D3DXMATRIX mtxRot, mtxTrans;					// 計算用のマトリックス
	D3DMATERIAL9 matDef;							// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;								// マテリアルデータへのポインタ

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_player.mtxWorld);

	// 向きを反映(y,x,z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	for (int nCutModel = 0; nCutModel < g_player.nNumModel; nCutModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;		// 計算用マトリックス

		D3DXMATRIX mtxParent;						// 親のマトリックス

		// 各パーツのワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_player.aModel[nCutModel].mtxWorld);

		// 向きを反映(y,x,z)
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCutModel].rot.y, g_player.aModel[nCutModel].rot.x, g_player.aModel[nCutModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCutModel].mtxWorld, &g_player.aModel[nCutModel].mtxWorld, &mtxRotModel);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCutModel].pos.x, g_player.aModel[nCutModel].pos.y, g_player.aModel[nCutModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCutModel].mtxWorld, &g_player.aModel[nCutModel].mtxWorld, &mtxTransModel);
		
		// 各パーツの親のマトリックスを設定
		if (g_player.aModel[nCutModel].nIdModelParent != -1)		// p:プレイヤー m:モデル nld:番号
		{
			mtxParent = g_player.aModel[g_player.aModel[nCutModel].nIdModelParent].mtxWorld;
		}
		else
		{// 親以外
			// プレイヤーのマトリックスを設定
			mtxParent = g_player.mtxWorld;
		}

		//親読み込み
		D3DXMatrixMultiply(&g_player.aModel[nCutModel].mtxWorld,
						   &g_player.aModel[nCutModel].mtxWorld,
						   &mtxParent);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCutModel].mtxWorld);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_player.aModel[nCutModel].pBuffMat->GetBufferPointer();

		for (int nCutMat = 0; nCutMat < (int)g_player.aModel[nCutModel].nNumMat; nCutMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, NULL);

			// モデル(パーツ)の描画
			g_player.aModel[nCutModel].pMesh->DrawSubset(nCutMat);
		}
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//--------------------------------------------------------------------------------
//	プレイヤーの取得
//--------------------------------------------------------------------------------
Player *GetPlayer(void)
{
	return &g_player;			// プレイヤーの情報の先頭アドレスを返す
}

//--------------------------------------------------------------------------------
//	モーションの処理
//--------------------------------------------------------------------------------
void MotionPlayer(MOTION_STATE motionType)
{
	float fPosDiffX[MAX_PLAYER];		// 位置情報の差分
	float fPosDiffY[MAX_PLAYER];		// 位置情報の差分
	float fPosDiffZ[MAX_PLAYER];		// 位置情報の差分
	float fRotDiffX[MAX_PLAYER];		// 位置情報の差分
	float fRotDiffY[MAX_PLAYER];		// 位置情報の差分
	float fRotDiffZ[MAX_PLAYER];		// 位置情報の差分
	float fPosXAsk[MAX_PLAYER];			// 求める値位置X
	float fPosYAsk[MAX_PLAYER];			// 求める値位置Y
	float fPosZAsk[MAX_PLAYER];			// 求める値位置Z
	float fRotXAsk[MAX_PLAYER];			// 求める値位置X
	float fRotYAsk[MAX_PLAYER];			// 求める値位置Y
	float fRotZAsk[MAX_PLAYER];			// 求める値位置Z

	// 前回のモーションと現在のモーション比較
	if (g_player.oldmotionType != motionType)
	{
		g_player.nNumKey = 0;
	}

	// 現在のモーションを保存
	g_player.oldmotionType = motionType;

	// 最大キーに行くまでの処理
	if (g_player.nNumKey < g_player.aMotionInfo[motionType].nMaxKey - 1)
	{
		for (int nCntKey = 0; g_player.nNumKey < g_player.aMotionInfo[motionType].nMaxKey - 1; nCntKey++)
		{
			for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
			{
				// 差分を求める
				fPosDiffX[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey + 1].aKey[nCnt].fPosKeyX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyX;
				fPosDiffY[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey + 1].aKey[nCnt].fPosKeyY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyY;
				fPosDiffZ[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey + 1].aKey[nCnt].fPosKeyZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyZ;

				fRotDiffX[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey + 1].aKey[nCnt].fRotKeyX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyX;
				fRotDiffY[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey + 1].aKey[nCnt].fRotKeyY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyY;
				fRotDiffZ[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey + 1].aKey[nCnt].fRotKeyZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyZ;

				// 求める値(位置＋差分*モーション数/フレーム数)
				fPosXAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyX + fPosDiffX[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);
				fPosYAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyY + fPosDiffY[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);
				fPosZAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyZ + fPosDiffZ[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);

				fRotXAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyX + fRotDiffX[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);
				fRotYAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyY + fRotDiffY[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);
				fRotZAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyZ + fRotDiffZ[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);

				// モデルの位置に代入
				g_player.aModel[nCnt].pos.x = fPosXAsk[nCnt];
				g_player.aModel[nCnt].pos.z = fPosZAsk[nCnt];
				g_player.aModel[nCnt].pos.y = fPosYAsk[nCnt];

				g_player.aModel[nCnt].rot.x = fRotXAsk[nCnt];
				g_player.aModel[nCnt].rot.y = fRotYAsk[nCnt];
				g_player.aModel[nCnt].rot.z = fRotZAsk[nCnt];


			}
			// モーションカウンターを毎フレーム数ごとに増やす
			g_player.nNumMotion += 1;

			if (g_player.nNumMotion >= g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame)
			{// モーションカウンターがフレーム数を超えたら
				if (g_player.nNumKey < g_player.aMotionInfo[motionType].nMaxKey - 1)
				{// ループする
					g_player.nNumKey++;		// 次のキーに行く
				}
				g_player.nNumMotion = 0;		// モーションカウンターを初期化
			}
			else if (g_player.nNumMotion < g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame)
			{// ループしない
				break;
			}
		}
	}
	// 最大キーの時の処理
	if (g_player.nNumKey == g_player.aMotionInfo[motionType].nMaxKey - 1)
	{
		if (g_player.aMotionInfo[motionType].nLoop == 1)
		{// モーションループ
			for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
			{
				// 差分を求める
				fPosDiffX[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fPosKeyX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyX;
				fPosDiffY[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fPosKeyY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyY;
				fPosDiffZ[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fPosKeyZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyZ;
																		
				fRotDiffX[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fRotKeyX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyX;
				fRotDiffY[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fRotKeyY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyY;
				fRotDiffZ[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fRotKeyZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyZ;

				// 求める値(位置＋差分*モーション数/フレーム数)
				fPosXAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyX + fPosDiffX[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);
				fPosYAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyY + fPosDiffY[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);
				fPosZAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyZ + fPosDiffZ[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);

				fRotXAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyX + fRotDiffX[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);
				fRotYAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyY + fRotDiffY[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);
				fRotZAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyZ + fRotDiffZ[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);

				// モデルの位置に代入
				g_player.aModel[nCnt].pos.x = fPosXAsk[nCnt];
				g_player.aModel[nCnt].pos.z = fPosZAsk[nCnt];
				g_player.aModel[nCnt].pos.y = fPosYAsk[nCnt];

				g_player.aModel[nCnt].rot.x = fRotXAsk[nCnt];
				g_player.aModel[nCnt].rot.y = fRotYAsk[nCnt];
				g_player.aModel[nCnt].rot.z = fRotZAsk[nCnt];
			}
			// モーションカウンターを毎フレーム数ごとに増やす
			g_player.nNumMotion += 1;

			if (g_player.nNumMotion >= g_player.aMotionInfo[motionType].aKeyInfo[0].nFrame)
			{// モーションカウンターがフレーム数を超えたら
				g_player.nNumKey = 0;		// キーを固定	
				g_player.nNumMotion = 0;	// モーションカウンター最初に戻す
			}
		}
		else
		{// モデルをループさせない
			for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
			{
				// 差分を求める
				fPosDiffX[nCnt] = g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].aKey[nCnt].fPosKeyX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyX;
				fPosDiffY[nCnt] = g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].aKey[nCnt].fPosKeyY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyY;
				fPosDiffZ[nCnt] = g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].aKey[nCnt].fPosKeyZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyZ;

				fRotDiffX[nCnt] = g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].aKey[nCnt].fRotKeyX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyX;
				fRotDiffY[nCnt] = g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].aKey[nCnt].fRotKeyY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyY;
				fRotDiffZ[nCnt] = g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].aKey[nCnt].fRotKeyZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyZ;

				// 求める値(位置＋差分*モーション数/フレーム数)
				fPosXAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyX + fPosDiffX[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].nFrame);
				fPosYAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyY + fPosDiffY[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].nFrame);
				fPosZAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyZ + fPosDiffZ[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].nFrame);

				fRotXAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyX + fRotDiffX[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].nFrame);
				fRotYAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyY + fRotDiffY[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].nFrame);
				fRotZAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyZ + fRotDiffZ[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].nFrame);

				// モデルの位置に代入
				g_player.aModel[nCnt].pos.x = fPosXAsk[nCnt];
				g_player.aModel[nCnt].pos.z = fPosZAsk[nCnt];
				g_player.aModel[nCnt].pos.y = fPosYAsk[nCnt];

				g_player.aModel[nCnt].rot.x = fRotXAsk[nCnt];
				g_player.aModel[nCnt].rot.y = fRotYAsk[nCnt];
				g_player.aModel[nCnt].rot.z = fRotZAsk[nCnt];
			}
			// モーションカウンターを毎フレーム数ごとに増やす
			g_player.nNumMotion += 1;

			// モーションカウンターがフレーム数を超えたら
			if (g_player.nNumMotion >= g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].nFrame)
			{

				g_player.nNumMotion = 0;	// モーションカウンター最初に戻す

				g_player.motionType = MOTION_NONE;
			}
		}

	}

}