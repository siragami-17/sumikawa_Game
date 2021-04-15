//--------------------------------------------------------------------------------
//
//	ストップ背景の処理 [StopBG.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "StopBG.h"

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define MAX_POLYGON	(2)	//ポリゴン数

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStopBG = NULL;

LPDIRECT3DTEXTURE9 g_pTextureStopBG = NULL;							//点線

//-------------------------------------------------------------------------------
//	ストップ背景初期化処理
//-------------------------------------------------------------------------------
HRESULT InitStopBG(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//変数宣言
	VERTEX_2D *pVtx;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/aaaa.png", &g_pTextureStopBG);		//点線

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffStopBG,
		NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffStopBG->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);


	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

	//頂点バッファをアンロックする
	g_pVtxBuffStopBG->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	ストップ背景の終了処理
//-------------------------------------------------------------------------------
void UninitStopBG(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffStopBG != NULL)
	{
		g_pVtxBuffStopBG->Release();
		g_pVtxBuffStopBG = NULL;
	}



	//点線の開放
	if (g_pTextureStopBG != NULL)
	{
		g_pTextureStopBG->Release();
		g_pTextureStopBG = NULL;
	}
}

//-------------------------------------------------------------------------------
//	ストップ背景の更新処理
//-------------------------------------------------------------------------------
void UpdateStopBG(void)
{

}

//-------------------------------------------------------------------------------
//	ストップ背景の描画処理
//-------------------------------------------------------------------------------
void DrawStopBG(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファをデータストーリに設定
	pDevice->SetStreamSource(0, g_pVtxBuffStopBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//背景テクスチャの設定
	pDevice->SetTexture(0, g_pTextureStopBG);

	//点線の設定
	pDevice->SetTexture(0, g_pTextureStopBG);


	//ストップ背景の描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,			//描画を開始する頂点インデックス
		NUM_POLYGON);			//描画するプリミティブ数
}
