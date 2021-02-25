//--------------------------------------------------------------------------------
//
//	プレスエンターの処理 [pressenter.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "PressEnter.h"			// ロゴ

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define MAX_LOGO		(1)			// テクスチャ数
#define MAX_LOGO_X		(425)		// ロゴの大きさ(x)
#define MAX_LOGO_Y		(131)		// ロゴの大きさ(y)
#define MAX_POS_X		(650)		// ロゴの位置(x)
#define MAX_POS_Y		(500)		// ロゴの位置(y)

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTexturePressEnter = NULL;			// テクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPressEnter = NULL;


//-------------------------------------------------------------------------------
//	ロゴの初期化処理
//-------------------------------------------------------------------------------
HRESULT InitPressEnter(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;	
	pDevice = GetDevice();

	// 変数宣言
	VERTEX_2D *pVtx;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title_PressEnter.png", &g_pTexturePressEnter);		// ロゴ

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4* MAX_LOGO,		// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,						// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffPressEnter,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(		   0+MAX_POS_X, MAX_LOGO_Y+MAX_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(		   0+MAX_POS_X,          0+MAX_POS_Y, 0.0f);							
	pVtx[2].pos = D3DXVECTOR3(MAX_LOGO_X+MAX_POS_X, MAX_LOGO_Y+MAX_POS_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(MAX_LOGO_X+MAX_POS_X,          0+MAX_POS_Y, 0.0f);				

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// 頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);	
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);	
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);	
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);	

	// 頂点バッファをアンロックする
	g_pVtxBuffPressEnter->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	ロゴの終了処理
//-------------------------------------------------------------------------------
void UninitPressEnter(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffPressEnter != NULL)
	{
		g_pVtxBuffPressEnter->Release();
		g_pVtxBuffPressEnter = NULL;
	}

	// テクスチャの開放
	if (g_pTexturePressEnter != NULL)
	{
		g_pTexturePressEnter->Release();
		g_pTexturePressEnter = NULL;
	}
}

//-------------------------------------------------------------------------------
//	ロゴの更新処理
//-------------------------------------------------------------------------------
void UpdatePressEnter(void)
{

}

//-------------------------------------------------------------------------------
//	ロゴの描画処理
//-------------------------------------------------------------------------------
void DrawPressEnter(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 頂点バッファをデータストーリに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPressEnter, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePressEnter);

	// ロゴの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
		0,						// 描画を開始する頂点インデックス
		2);						// 描画するプリミティブ数
}