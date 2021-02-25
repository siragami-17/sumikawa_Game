//--------------------------------------------------------------------------------
//
//	ポリゴンの処理 [polygon.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "polygon.h"
#include "keyboard.h"

//--------------------------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolgon = NULL;		// ポリゴンの頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePolgon = NULL;				// テクスチャのポインタ

D3DXVECTOR3 g_posPolygon;								// 位置
D3DXVECTOR3 g_rotPolygon;								// 法線ベクトル(向き)
D3DXMATRIX g_mtxWorldPolygon;							// ワールドマトリックス

//--------------------------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------------------------
HRESULT InitPolgon(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 変数宣言
	VERTEX_3D *pVtx;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field000.jpg", &g_pTexturePolgon);

	// ポリゴンの情報初期化
	g_posPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	g_rotPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き


	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * 4,					// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,							// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolgon,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPolgon->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標(X.Y.Z)
	pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - 100.0f, g_posPolygon.y + 0.0f, g_posPolygon.z + 100.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x + 100.0f, g_posPolygon.y + 0.0f, g_posPolygon.z + 100.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x - 100.0f, g_posPolygon.y + 0.0f, g_posPolygon.z - 100.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + 100.0f, g_posPolygon.y + 0.0f, g_posPolygon.z - 100.0f);

	// 法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
	g_pVtxBuffPolgon->Unlock();

	return S_OK;
}

//--------------------------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------------------------
void UninitPolgon(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffPolgon != NULL)
	{
		g_pVtxBuffPolgon->Release();
		g_pVtxBuffPolgon = NULL;
	}

	// テクスチャの開放(ポリゴン)
	if (g_pTexturePolgon != NULL)
	{
		g_pTexturePolgon->Release();
		g_pTexturePolgon = NULL;
	}
}

//--------------------------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------------------------
void UpdatePolgon(void)
{

}

//--------------------------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------------------------
void DrawPolgon(void)
{
	LPDIRECT3DDEVICE9 pDevice;			// デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;		// 計算用のマトリックス

	// デバイスの取得
	pDevice = GetDevice();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	// 向きを反映(y,x,z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPolgon, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンのテクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolgon);
	
	// ポリゴンの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
		0,						// 描画を開始する頂点インデックス
		2);						// 描画するプリミティブ数
}