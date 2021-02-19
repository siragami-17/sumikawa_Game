//--------------------------------------------------------------------------------
//
//	ビルボードの処理 [billboard.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Billboard.h"

//--------------------------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------------------------
#define MAX_Billboard		(1)		// テクスチャの最大数

//--------------------------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;		// ビルボードの頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;			// テクスチャのポインタ

D3DXVECTOR3 g_posBillboard;								// 位置
D3DXMATRIX g_mtxWorldBillboard;							// ワールドマトリックス

//--------------------------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------------------------
HRESULT InitBillboard(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 変数宣言
	VERTEX_3D *pVtx;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Key.png", &g_pTextureBillboard);

	// ビルボードの情報初期化
	g_posBillboard = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * 4,								// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,									// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	//// 頂点座標(X.Y.Z)
	//pVtx[0].pos = D3DXVECTOR3(g_posBillboard.x - 100.0f, g_posBillboard.y + 100.0f, g_posBillboard.z + 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_posBillboard.x + 100.0f, g_posBillboard.y + 100.0f, g_posBillboard.z + 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_posBillboard.x - 100.0f, g_posBillboard.y - 0.0f, g_posBillboard.z + 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_posBillboard.x + 100.0f, g_posBillboard.y - 0.0f, g_posBillboard.z + 0.0f);

	// 頂点座標(X.Y.Z)
	pVtx[0].pos = D3DXVECTOR3(g_posBillboard.x - 25.0f, g_posBillboard.y + 50.0f, g_posBillboard.z + 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posBillboard.x + 25.0f, g_posBillboard.y + 50.0f, g_posBillboard.z + 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posBillboard.x - 25.0f, g_posBillboard.y - 0.0f, g_posBillboard.z + 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posBillboard.x + 25.0f, g_posBillboard.y - 0.0f, g_posBillboard.z + 0.0f);

	// 法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// 頂点カラー設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// 頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(0.0, 1.0);

	// 頂点バッファをアンロックする
	g_pVtxBuffBillboard->Unlock();

	return S_OK;
}

//--------------------------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------------------------
void UninitBillboard(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}

	// テクスチャの開放(ビルボード)
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
}

//--------------------------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------------------------
void UpdateBillboard(void)
{

}

//--------------------------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------------------------
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;			// デバイスへのポインタ
	D3DXMATRIX mtxView;					// ビューマトリックスの取得
	D3DXMATRIX mtxRot, mtxTrans;		// 計算用のマトリックス

	// デバイスの取得
	pDevice = GetDevice();

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldBillboard);

	// ビューマトリックスの取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);		// 逆行列を求める
	g_mtxWorldBillboard._41 = 0.0f;
	g_mtxWorldBillboard._42 = 0.0f;
	g_mtxWorldBillboard._43 = 0.0f;

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posBillboard.x, g_posBillboard.y, g_posBillboard.z);
	D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ビルボードのテクスチャの設定
	pDevice->SetTexture(0, g_pTextureBillboard);

	// ビルボードの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
		0,						// 描画を開始する頂点インデックス
		2);						// 描画するプリミティブ数

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//--------------------------------------------------------------------------------
// ビルボードの設定
//--------------------------------------------------------------------------------
void SetBillboard(D3DXVECTOR3 pos)
{

}
