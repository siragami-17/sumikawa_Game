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
LPD3DXMESH g_pMesh = NULL;				// メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMat = NULL;			// マテリアルへのポインタ
D3DXMATRIX g_mtxWorld;					// ワールドマトリックス
DWORD g_nNumMat = 0;					// マテリアル数

Block g_block;							// ブロックの情報	
												
//--------------------------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------------------------
HRESULT InitBlock(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// block構造体の初期化
	g_block.pos = D3DXVECTOR3(0.0f, 0.0f, 500.0f);			// 位置
	g_block.blockVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	g_block.fWidth = 0.0f;									// 幅
	g_block.fHeight = 0.0f;									// 高さ
	g_block.fLength = 0.0f;									// 長さ
	g_block.fRadius = (float)10;							// 半径
	g_block.bUse = true;									// 使用しているかどうか

	// Xファイルの読み込み
	// ブロック
	D3DXLoadMeshFromX("data/MODEL/Block_1.x",				// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMat,										// マテリアル(頂点情報)
		NULL,	
		&g_nNumMat,											// マテリアル数
		&g_pMesh);											// メッシュ(頂点情報)

	return S_OK;
}

//--------------------------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------------------------
void UninitBlock(void)
{

	// メッシュの開放
	if (g_pMesh != NULL)
	{		 
		g_pMesh->Release();
		g_pMesh = NULL;
	}				  

	// マテリアルの開放
	if (g_pBuffMat != NULL)
	{	
		g_pBuffMat->Release();
		g_pBuffMat = NULL;
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

	 //ブロックとプレイヤーの当たり判定
	if (g_block.bUse == true)
	{// ブロックがあるとき
		g_block.blockVec = pPlayer->pos - g_block.pos;		// 鍵のベクトルを求める
		g_block.fLength = sqrtf((g_block.blockVec.x*g_block.blockVec.x) + (g_block.blockVec.z*g_block.blockVec.z));		// 鍵とプレイヤーの距離

		// ブロックとプレイヤーが当たった
		if (g_block.fLength < g_block.fRadius)
		{// 長さが半径より小さくなった



			if (pPlayer->bGetKey == true)
			{// プレイヤーが鍵を持っていたら

			 //鍵を消す
				g_block.bUse = false;

				// リザルトに飛ぶ
				SetResult(true);					// クリア画面
				SetFade(FADE_OUT, MODE_RESULT);
			}
		
		
			

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

	if (g_block.bUse == true)
	{


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


		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMat->GetBufferPointer();

		for (int nCutMat = 0; nCutMat < g_nNumMat; nCutMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, NULL);

			// モデル(パーツ)の描画
			g_pMesh->DrawSubset(nCutMat);
		}

		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//--------------------------------------------------------------------------------
//	ブロック情報の取得
//--------------------------------------------------------------------------------
Block *GetBlock(void)
{
	return &g_block;			// ブロック情報の先頭アドレスを返す
}