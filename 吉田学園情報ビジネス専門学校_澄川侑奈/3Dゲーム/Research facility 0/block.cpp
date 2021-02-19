//--------------------------------------------------------------------------------
//
//	ブロックの処理 [block.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "block.h"			// ブロック
#include "keyboard.h"		// キー入力
#include "player.h"			// プレイヤー
#include "result.h"			// リザルト
#include "fade.h"			// フェード

//--------------------------------------------------------------------------------
//	マクロ定義
//--------------------------------------------------------------------------------
#define MAX_MOVE	(3)			// 移動量
#define MAX_ROT		(0.1f)		// 向き

//--------------------------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------------------------
Block g_block;										// ブロックの情報	
												
//--------------------------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------------------------
HRESULT InitBlock(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// パーツ数の初期化
	g_block.nNumModel = MAX_BLOCK;

	// Xファイルの読み込み
	// ブロック
	D3DXLoadMeshFromX("data/MODEL/block.x",						// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_block.aModel[0].pBuffMat,							// マテリアル(頂点情報)
		NULL,
		&g_block.aModel[0].nNumMat,								// マテリアル数
		&g_block.aModel[0].pMesh);								// メッシュ(頂点情報)

	// 各パーツの階層構造設定
	// 体
	g_block.aModel[0].nldModelParent = -1;						// 親モデルのインデックスを設定
	g_block.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 500.0f);	// 位置(オフセット)の初期設定
	g_block.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向きの初期設定



	// ブロックの構造体の初期化
	g_block.pos = D3DXVECTOR3(0.0f, 0.0f, 650.0f);				// 位置の初期設定
	g_block.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 向きの初期設定
	g_block.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 移動量の初期設定
	g_block.fHeight = 0.0f;										// 高さの初期設定
	g_block.fWidth = 0.0f;										// 幅の初期設定
	g_block.bUse = true;										// 使用しているか

	return S_OK;
}

//--------------------------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------------------------
void UninitBlock(void)
{
	for (int nCutModel = 0; nCutModel < g_block.nNumModel; nCutModel++)
	{
		// メッシュの開放
		if (g_block.aModel[nCutModel].pMesh != NULL)
		{
			g_block.aModel[nCutModel].pMesh->Release();
			g_block.aModel[nCutModel].pMesh = NULL;
		}

		// マテリアルの開放
		if (g_block.aModel[nCutModel].pBuffMat != NULL)
		{
			g_block.aModel[nCutModel].pBuffMat->Release();
			g_block.aModel[nCutModel].pBuffMat = NULL;
		}
	}
}

//--------------------------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------------------------
void UpdateBlock(void)
{
	// プレイヤーの情報
	Player * pPlayer;
	pPlayer = GetPlayer();

	// ブロックとプレイヤーの当たり判定
	if (g_block.bUse == true)
	{// ブロックがあるとき
		if (pPlayer->pos.x - (50) < g_block.pos.x + (10) &&
			pPlayer->pos.x + (50) > g_block.pos.x - (10) &&
			pPlayer->pos.z - (150) < g_block.pos.z + (50) &&
			pPlayer->pos.z + (150) > g_block.pos.z - (50))
		{// ブロックとプレイヤーが当たった
			// リザルトにとぶ
			SetResult(true);					//クリア画面
			SetFade(FADE_OUT, MODE_RESULT);
		}
	}
}

//--------------------------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------------------------
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;					// 計算用のマトリックス
	D3DMATERIAL9 matDef;							// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;								// マテリアルデータへのポインタ

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_block.mtxWorld);

	// 向きを反映(y,x,z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_block.rot.y, g_block.rot.x, g_block.rot.z);
	D3DXMatrixMultiply(&g_block.mtxWorld, &g_block.mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_block.pos.x, g_block.pos.y, g_block.pos.z);
	D3DXMatrixMultiply(&g_block.mtxWorld, &g_block.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_block.mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	for (int nCutModel = 0; nCutModel < g_block.nNumModel; nCutModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;		// 計算用マトリックス

		D3DXMATRIX mtxParent;						// 親のマトリックス

		// 各パーツのワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_block.aModel[nCutModel].mtxWorld);

		// 向きを反映(y,x,z)
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_block.aModel[nCutModel].rot.y, g_block.aModel[nCutModel].rot.x, g_block.aModel[nCutModel].rot.z);
		D3DXMatrixMultiply(&g_block.aModel[nCutModel].mtxWorld, &g_block.aModel[nCutModel].mtxWorld, &mtxRotModel);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTransModel, g_block.aModel[nCutModel].pos.x, g_block.aModel[nCutModel].pos.y, g_block.aModel[nCutModel].pos.z);
		D3DXMatrixMultiply(&g_block.aModel[nCutModel].mtxWorld, &g_block.aModel[nCutModel].mtxWorld, &mtxTransModel);
		
		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_block.aModel[nCutModel].mtxWorld);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_block.aModel[nCutModel].pBuffMat->GetBufferPointer();

		for (int nCutMat = 0; nCutMat < (int)g_block.aModel[nCutModel].nNumMat; nCutMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, NULL);

			// モデル(パーツ)の描画
			g_block.aModel[nCutModel].pMesh->DrawSubset(nCutMat);
		}
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//--------------------------------------------------------------------------------
//	ブロック情報の取得
//--------------------------------------------------------------------------------
Block *GetBlock(void)
{
	return &g_block;			// ブロック情報の先頭アドレスを返す
}