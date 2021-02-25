//--------------------------------------------------------------------------------
//
//	タイトルロゴの処理 [logo.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Logo.h"			// ロゴ

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define MAX_LOGO		(1)			// テクスチャ数
#define MAX_LOGO_X		(810)		// ロゴの大きさ(x)
#define MAX_LOGO_Y		(320)		// ロゴの大きさ(y)
#define MAX_POS_X		(450.0f)		// ロゴの位置(x)
#define MAX_POS_Y		(30.0f)		// ロゴの位置(y)

//-------------------------------------------------------------------------------
//	構造体
//-------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;							// 位置
	D3DXVECTOR3 move;							// 移動量

}Logo;

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureLogo = NULL;			// テクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLogo = NULL;

Logo g_logo;										// ロゴの情報

//-------------------------------------------------------------------------------
//	ロゴの初期化処理
//-------------------------------------------------------------------------------
HRESULT InitLogo(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 変数宣言
	VERTEX_2D *pVtx;

	// 構造体の初期化
	g_logo.pos = D3DXVECTOR3(MAX_POS_X, MAX_POS_Y, 0.0f);
	g_logo.move = D3DXVECTOR3(0.0f, 5.0f, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Title_Logo.png", &g_pTextureLogo);		// ロゴ

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_LOGO,		// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,						// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffLogo,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLogo->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_logo.pos.x + 0, g_logo.pos.y + MAX_LOGO_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_logo.pos.x + 0, g_logo.pos.y + 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_logo.pos.x + MAX_LOGO_X, g_logo.pos.y + MAX_LOGO_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_logo.pos.x + MAX_LOGO_X, g_logo.pos.y + 0, 0.0f);

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
	g_pVtxBuffLogo->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	ロゴの終了処理
//-------------------------------------------------------------------------------
void UninitLogo(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffLogo != NULL)
	{
		g_pVtxBuffLogo->Release();
		g_pVtxBuffLogo = NULL;
	}

	// テクスチャの開放
	if (g_pTextureLogo != NULL)
	{
		g_pTextureLogo->Release();
		g_pTextureLogo = NULL;
	}
}

//-------------------------------------------------------------------------------
//	ロゴの更新処理
//-------------------------------------------------------------------------------
void UpdateLogo(void)
{
	g_logo.pos == g_logo.move;
}

//-------------------------------------------------------------------------------
//	ロゴの描画処理
//-------------------------------------------------------------------------------
void DrawLogo(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 頂点バッファをデータストーリに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLogo, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureLogo);

	// ロゴの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
		0,						// 描画を開始する頂点インデックス
		2);						// 描画するプリミティブ数
}