#if 0

//--------------------------------------------------------------------------------
//
//	モデルの処理 [model.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "model.h"
#include "keyboard.h"
#include "camera.h"

//--------------------------------------------------------------------------------
//	マクロ定義
//--------------------------------------------------------------------------------
#define MAX_MOVE	(3)			// 移動量
#define MAX_ROT		(0.1f)		// 向き

//--------------------------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------------------------
LPD3DXMESH g_pMeshModel = NULL;							// メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatModel = NULL;					// マテリアル(頂点情報)へのポインタ
LPDIRECT3DTEXTURE9 g_apTexture[10] = {};				// テクスチャへのポインタ
DWORD g_nNumMatModel = 0;								// マテリアル数

MODEL g_Model;											// プレイヤーの情報	
														
D3DXMATRIX g_mtxWorldModel;								// ワールドマトリックス

int g_nCountersAnimationCun;							// カウント制御(カウンタ更新を遅くする)

//--------------------------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------------------------
void InitModel(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATERIAL *pMat;									// マテリアルへのポインタ

	// Xファイルの読み込み
	D3DXLoadMeshFromX("data/MODEL/01_head.x",			// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,								// マテリアル(頂点情報)
		NULL,
		&g_nNumMatModel,								// マテリアル数
		&g_pMeshModel);									// メッシュ(頂点情報)

	int nNumVtx;										// 頂点数
	DWORD sizeFVF;										// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;										// 頂点バッファへのポインタ

	// 頂点数を取得
	nNumVtx = g_pMeshModel->GetNumVertices();

	// 頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());

	// 頂点バッファをロック
	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntMat = 0; nCntMat < nNumVtx; nCntMat++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		// 頂点座標の代入

		// 全ての頂点を比較してモデルの最小値・最大値を抜き出す



		pVtxBuff += sizeFVF;		// 頂点フォーマットのサイズ分ポインタを進める
	}






	// マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{// ファイル読み込みをする
			
		}
	}


	// ポリゴンの情報初期化
	g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	g_Model.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
	g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
}

//--------------------------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------------------------
void UninitModel(void)
{
	// メッシュの開放
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	// マテリアルの開放
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//--------------------------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------------------------
void UpdateModel(void)
{
	// カメラの情報をもらう
	Camera * pCamer;
	pCamer = GetCamera();

	// モデルの移動処理
	// 上キーを押した
	if (GetkeyboardPress(DIK_UP) == true)
	{// バック
		g_Model.pos.x += sinf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.x += sinf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.z += cosf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.z += cosf(pCamer->rot.y) * MAX_MOVE;
	}

	// 下キーを押した
	if (GetkeyboardPress(DIK_DOWN) == true)
	{// 前進
		g_Model.pos.x -= sinf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.x -= sinf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.z -= cosf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.z -= cosf(pCamer->rot.y) * MAX_MOVE;
	}

	// 左キーを押した
	if (GetkeyboardPress(DIK_LEFT) == true)
	{// 左移動
		g_Model.pos.x -= cosf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.x -= cosf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.z += sinf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.z += sinf(pCamer->rot.y) * MAX_MOVE;
	}

	// 右キーを押した
	if (GetkeyboardPress(DIK_RIGHT) == true)
	{// 右移動
		g_Model.pos.x += cosf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.x += cosf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.z -= sinf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.z -= sinf(pCamer->rot.y) * MAX_MOVE;
	}

	// 左シフトを押した
	if (GetkeyboardPress(DIK_LSHIFT) == true)
	{// 左回転
		g_Model.rot.y -= MAX_ROT;
	}

	// 右シフトを押した
	if (GetkeyboardPress(DIK_RSHIFT) == true)
	{// 右回転
		g_Model.rot.y += MAX_ROT;
	}

	// エンターキーを押した
	if (GetkeyboardPress(DIK_RETURN) == true)
	{// 位置を戻す
		g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//--------------------------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------------------------
void DrawModel(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;		// 計算用のマトリックス
	D3DMATERIAL9 matDef;				// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;					// マテリアルデータへのポインタ

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldModel);

	// 向きを反映(y,x,z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.rot.y, g_Model.rot.x, g_Model.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Model.pos.x, g_Model.pos.y, g_Model.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCnyMat = 0; nCnyMat < (int)g_nNumMatModel; nCnyMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCnyMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, NULL);

		// モデル(パーツ)の描画
		g_pMeshModel->DrawSubset(nCnyMat);
	}
	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//--------------------------------------------------------------------------------
//	プレイヤーの取得
//--------------------------------------------------------------------------------
MODEL *GetModel(void)
{
	return &g_Model;			// プレイヤーの情報の先頭アドレスを返す
}

#endif