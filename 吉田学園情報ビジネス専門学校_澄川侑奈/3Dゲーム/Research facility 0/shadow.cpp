//--------------------------------------------------------------------------------
//
//	影の処理 [shadow.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "shadow.h"			// 影
#include "keyboard.h"		//キーボード

//--------------------------------------------------------------------------------
// マクロ定義
//--------------------------------------------------------------------------------
#define MAX_SHADOW		(15.0f)		// 影の大きさ

//--------------------------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;		// ポリゴンの頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;				// ポリゴンの頂点バッファのポインタ

D3DXVECTOR3 g_posShadow;								// 位置
D3DXVECTOR3 g_rotShadow;								// 法線ベクトル(向き)
D3DXMATRIX g_mtxWorldShadow;							// ワールドマトリックス

//--------------------------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------------------------
HRESULT InitShadow(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 変数宣言
	VERTEX_3D *pVtx;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/shadow000.jpg", &g_pTextureShadow);		// 影のテクスチャ

	// ポリゴンの情報初期化
	g_posShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	g_rotShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き


	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * 4,					// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,							// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標(X.Y.Z)
	pVtx[0].pos = D3DXVECTOR3(g_posShadow.x - MAX_SHADOW, g_posShadow.y + 0.0f, g_posShadow.z + MAX_SHADOW);
	pVtx[1].pos = D3DXVECTOR3(g_posShadow.x + MAX_SHADOW, g_posShadow.y + 0.0f, g_posShadow.z + MAX_SHADOW);
	pVtx[2].pos = D3DXVECTOR3(g_posShadow.x - MAX_SHADOW, g_posShadow.y + 0.0f, g_posShadow.z - MAX_SHADOW);
	pVtx[3].pos = D3DXVECTOR3(g_posShadow.x + MAX_SHADOW, g_posShadow.y + 0.0f, g_posShadow.z - MAX_SHADOW);

	// 法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラー設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 150);

	// 頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(0.0, 1.0);

	// 頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();

	return S_OK;
}

//--------------------------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------------------------
void UninitShadow(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

	// テクスチャの開放(ポリゴン)
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}

//--------------------------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------------------------
void UpdateShadow(void)
{

}

//--------------------------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------------------------
void DrawShadow(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;		// 計算用のマトリックス

	//減算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldShadow);

	// 向きを反映(y,x,z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotShadow.y, g_rotShadow.x, g_rotShadow.z);
	D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posShadow.x, g_posShadow.y, g_posShadow.z);
	D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンのテクスチャの設定
	pDevice->SetTexture(0, g_pTextureShadow);
	
	// ポリゴンの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
		0,						// 描画を開始する頂点インデックス
		2);						// 描画するプリミティブ数

	// 通常合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}