//--------------------------------------------------------------------------------
//
//	プレイヤーの処理 [player.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "player.h"			// プレイヤー
#include "keyboard.h"		// キーボード
#include "camera.h"			// カメラ
#include "block.h"			// ブロック
#include "meshfild.h"		// 地面

//--------------------------------------------------------------------------------
//	マクロ定義
//--------------------------------------------------------------------------------
#define MAX_MOVE		(5)			// 移動量
#define MAX_ROT			(0.1f)		// 向き

#define MAX_FLAME		(40)		// 再生フレーム数
#define MAX_COUNTER		(10)		// モーションカウンター

#define MAX_JUMP		(-20)		//ジャンプ


//--------------------------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------------------------
Player g_player;					// プレイヤーの情報	

int nDifference;					// 差分
											
//--------------------------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------------------------
HRESULT InitPlayer(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// パーツ数の初期化
	g_player.nNumModel = 14;										

	// Xファイルの読み込み
	// 体
	D3DXLoadMeshFromX("data/MODEL/00_body.x",						// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[0].pBuffMat,								// マテリアル(頂点情報)
		NULL,
		&g_player.aModel[0].nNumMat,								// マテリアル数
		&g_player.aModel[0].pMesh);									// メッシュ(頂点情報)

	// 顔
	D3DXLoadMeshFromX("data/MODEL/01_head.x",						// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[1].pBuffMat,								// マテリアル(頂点情報)
		NULL,
		&g_player.aModel[1].nNumMat,								// マテリアル数
		&g_player.aModel[1].pMesh);									// メッシュ(頂点情報)

	// 右腕_0
	D3DXLoadMeshFromX("data/MODEL/02_armR_0.x",						// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[2].pBuffMat,								// マテリアル(頂点情報)
		NULL,
		&g_player.aModel[2].nNumMat,								// マテリアル数
		&g_player.aModel[2].pMesh);									// メッシュ(頂点情報)

	// 右腕_1
	D3DXLoadMeshFromX("data/MODEL/02_armR_1.x",						// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[3].pBuffMat,								// マテリアル(頂点情報)
		NULL,
		&g_player.aModel[3].nNumMat,								// マテリアル数
		&g_player.aModel[3].pMesh);									// メッシュ(頂点情報)

	// 右手
	D3DXLoadMeshFromX("data/MODEL/03_handR.x",						// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[4].pBuffMat,								// マテリアル(頂点情報)
		NULL,
		&g_player.aModel[4].nNumMat,								// マテリアル数
		&g_player.aModel[4].pMesh);									// メッシュ(頂点情報)

	// 左腕_0
	D3DXLoadMeshFromX("data/MODEL/04_armL_0.x",						// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[5].pBuffMat,								// マテリアル(頂点情報)
		NULL,
		&g_player.aModel[5].nNumMat,								// マテリアル数
		&g_player.aModel[5].pMesh);									// メッシュ(頂点情報)

	// 左腕_1
	D3DXLoadMeshFromX("data/MODEL/04_armL_1.x",						// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[6].pBuffMat,								// マテリアル(頂点情報)
		NULL,
		&g_player.aModel[6].nNumMat,								// マテリアル数
		&g_player.aModel[6].pMesh);									// メッシュ(頂点情報)

	// 左手
	D3DXLoadMeshFromX("data/MODEL/05_handL.x",						// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[7].pBuffMat,								// マテリアル(頂点情報)
		NULL,
		&g_player.aModel[7].nNumMat,								// マテリアル数
		&g_player.aModel[7].pMesh);									// メッシュ(頂点情報)

	// 右腿_0
	D3DXLoadMeshFromX("data/MODEL/06_legR_0.x",						// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[8].pBuffMat,								// マテリアル(頂点情報)
		NULL,
		&g_player.aModel[8].nNumMat,								// マテリアル数
		&g_player.aModel[8].pMesh);									// メッシュ(頂点情報)

	// 右腿_1
	D3DXLoadMeshFromX("data/MODEL/06_legR_1.x",						// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[9].pBuffMat,								// マテリアル(頂点情報)
		NULL,
		&g_player.aModel[9].nNumMat,								// マテリアル数
		&g_player.aModel[9].pMesh);									// メッシュ(頂点情報)

	// 右足
	D3DXLoadMeshFromX("data/MODEL/07_footR.x",						// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[10].pBuffMat,								// マテリアル(頂点情報)
		NULL,
		&g_player.aModel[10].nNumMat,								// マテリアル数
		&g_player.aModel[10].pMesh);								// メッシュ(頂点情報)

	// 左腿_0
	D3DXLoadMeshFromX("data/MODEL/08_legL_0.x",						// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[11].pBuffMat,								// マテリアル(頂点情報)
		NULL,
		&g_player.aModel[11].nNumMat,								// マテリアル数
		&g_player.aModel[11].pMesh);								// メッシュ(頂点情報)

	// 左腿_1
	D3DXLoadMeshFromX("data/MODEL/08_legL_1.x",						// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[12].pBuffMat,								// マテリアル(頂点情報)
		NULL,
		&g_player.aModel[12].nNumMat,								// マテリアル数
		&g_player.aModel[12].pMesh);								// メッシュ(頂点情報)

	// 左足
	D3DXLoadMeshFromX("data/MODEL/09_footL.x",						// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[13].pBuffMat,								// マテリアル(頂点情報)
		NULL,
		&g_player.aModel[13].nNumMat,								// マテリアル数
		&g_player.aModel[13].pMesh);								// メッシュ(頂点情報)


	// 各パーツの階層構造設定
	// 体
	g_player.aModel[0].nIdModelParent = -1;							// 親モデルのインデックスを設定
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 23.0f, 0.0f);		// 位置(オフセット)の初期設定
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定

	// 顔
	g_player.aModel[1].nIdModelParent = 0;							// 親モデルのインデックスを設定
	g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 22.0f, 0.0f);		// 位置(オフセット)の初期設定
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定

	// 右腕_0
	g_player.aModel[2].nIdModelParent = 0;							// 親モデルのインデックスを設定
	g_player.aModel[2].pos = D3DXVECTOR3(-3.0f, 20.0f, 0.0f);		// 位置(オフセット)の初期設定
	g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定

	// 右腕_1
	g_player.aModel[3].nIdModelParent = 2;							// 親モデルのインデックスを設定
	g_player.aModel[3].pos = D3DXVECTOR3(-9.0f, 0.0f, 0.0f);		// 位置(オフセット)の初期設定
	g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定

	// 右手
	g_player.aModel[4].nIdModelParent = 3;							// 親モデルのインデックスを設定
	g_player.aModel[4].pos = D3DXVECTOR3(-9.0f, 0.0f, 0.0f);		// 位置(オフセット)の初期設定
	g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定

	// 左腕_0
	g_player.aModel[5].nIdModelParent = 0;							// 親モデルのインデックスを設定
	g_player.aModel[5].pos = D3DXVECTOR3(3.0f, 20.0f, 0.0f);		// 位置(オフセット)の初期設定
	g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定

	// 左腕_1
	g_player.aModel[6].nIdModelParent = 5;							// 親モデルのインデックスを設定
	g_player.aModel[6].pos = D3DXVECTOR3(9.0f, 0.0f, 0.0f);			// 位置(オフセット)の初期設定
	g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定

	// 左手
	g_player.aModel[7].nIdModelParent = 6;							// 親モデルのインデックスを設定
	g_player.aModel[7].pos = D3DXVECTOR3(9.0f, 0.0f, 0.0f);			// 位置(オフセット)の初期設定
	g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定

	// 右腿_0
	g_player.aModel[8].nIdModelParent = 0;							// 親モデルのインデックスを設定
	g_player.aModel[8].pos = D3DXVECTOR3(-3.5f, 0.0f, 0.0f);			// 位置(オフセット)の初期設定
	g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定

	// 右腿_1
	g_player.aModel[9].nIdModelParent = 8;							// 親モデルのインデックスを設定
	g_player.aModel[9].pos = D3DXVECTOR3(0.0f, -9.5f, 0.0f);		// 位置(オフセット)の初期設定
	g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定

	// 右足
	g_player.aModel[10].nIdModelParent = 9;							// 親モデルのインデックスを設定
	g_player.aModel[10].pos = D3DXVECTOR3(0.0f, -10.0f, 0.0f);		// 位置(オフセット)の初期設定
	g_player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向きの初期設定

	// 左腿_0
	g_player.aModel[11].nIdModelParent = 0;							// 親モデルのインデックスを設定
	g_player.aModel[11].pos = D3DXVECTOR3(3.5f, 0.0f, 0.0f);		// 位置(オフセット)の初期設定
	g_player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向きの初期設定

	// 左腿_1
	g_player.aModel[12].nIdModelParent = 11;						// 親モデルのインデックスを設定
	g_player.aModel[12].pos = D3DXVECTOR3(0.0f, -9.5f, 0.0f);		// 位置(オフセット)の初期設定
	g_player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向きの初期設定

	// 左足
	g_player.aModel[13].nIdModelParent = 12;						// 親モデルのインデックスを設定
	g_player.aModel[13].pos = D3DXVECTOR3(0.0f, -10.0f, 0.0f);		// 位置(オフセット)の初期設定
	g_player.aModel[13].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向きの初期設定

	//初期設定
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 位置
	g_player.rot = D3DXVECTOR3(0.0f, -3.14f, 0.0f);					// 向き

	//変数宣言
	int nNumVtx;													// 頂点数
	DWORD sizeFVF;													// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;													// 頂点バッファへのポインタ



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

	// ブロック情報
	Block *pBlock = GetBlock();

	// モデルの移動処理
	// 上キーを押した
	if (GetkeyboardPress(DIK_W) == true)
	{// バック
		g_player.pos.x += sinf(pCamera->rot.y) * MAX_MOVE;		// +=はずっと押してる反応
		g_player.pos.z += cosf(pCamera->rot.y) * MAX_MOVE;

		g_player.rot.y = pCamera->rot.y - D3DX_PI;				// プレイヤーの向きを前にする

	}

	// 下キーを押した
	if (GetkeyboardPress(DIK_S) == true)
	{// 前進
		g_player.pos.x -= sinf(pCamera->rot.y) * MAX_MOVE;
		g_player.pos.z -= cosf(pCamera->rot.y) * MAX_MOVE;

		g_player.rot.y = pCamera->rot.y;						// プレイヤーの向きを後ろにする
	}

	// 左キーを押した
	if (GetkeyboardPress(DIK_A) == true)
	{// 左移動
		g_player.pos.x -= cosf(pCamera->rot.y) * MAX_MOVE;
		g_player.pos.z += sinf(pCamera->rot.y) * MAX_MOVE;

		g_player.rot.y = +D3DX_PI / 2 + pCamera->rot.y;			// プレイヤーの向きを左向きにする
	}

	// 右キーを押した
	if (GetkeyboardPress(DIK_D) == true)
	{// 右移動
		g_player.pos.x += cosf(pCamera->rot.y) * MAX_MOVE;
		g_player.pos.z -= sinf(pCamera->rot.y) * MAX_MOVE;

		g_player.rot.y = -D3DX_PI / 2 + pCamera->rot.y;			// プレイヤーの向きを右向きに
	}

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

	// moveにposを加算
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	// 移動量の制限
	g_player.move.x += (0.0f - g_player.move.x)*0.25f;
	g_player.move.y += (0.0f - g_player.move.y)*0.25f;

	// エンターキーを押した
	if (GetkeyboardPress(DIK_RETURN) == true)
	{// 位置を戻す
		g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rot = D3DXVECTOR3(0.0f, -3.14f, 0.0f);
	}

	// モーション
	// ニュートラルモーション

	for (int nCuntPlayer = 0; nCuntPlayer < 2; nCuntPlayer++)
	{
		// 右腕



	}




	//重力
//	g_player.move.y += +2;
//
//	if (GetkeyboardTrgger(DIK_SPACE) == true && g_player.bJump == false)
//	{//ジャンプの処理(2段ジャンプの制御)
//		g_player.move.y = MAX_JUMP;
//		g_player.bJump = true;
//	}






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