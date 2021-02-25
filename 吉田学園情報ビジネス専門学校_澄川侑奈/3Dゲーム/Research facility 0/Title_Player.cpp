//--------------------------------------------------------------------------------
//
//	タイトルキャラの処理 [Title_Player.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Title_Player.h"

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define MAN_X					(501)					// 画像の幅
#define MAN_Y					(535)					// 画像の高さ
#define POS_X					(2)						// Xの位置
#define POS_Y					(200)					// Yの位置
#define MAX_ANIMATION_COUNTER	(7)						// スピード
#define MAX_ANIMATION_PATTERN	(16)					// 画像コマ数
#define DIVISION				(0.0625f)				// 割り算

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle_Player = NULL;

LPDIRECT3DTEXTURE9 g_pTextureTitle_Player = NULL;		// テクスチャ
D3DXVECTOR3 g_posTitle_Player;							// 位置
int g_nCountersTitle_Player;							// コマ数の切り替え
int g_nCountersTitle_PlayerCnt;							// カウンタ更新

//-------------------------------------------------------------------------------
//	タイトル画面初期化処理
//-------------------------------------------------------------------------------
HRESULT InitTitle_PLayer(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 変数宣言
	VERTEX_2D *pVtx;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/1.png", &g_pTextureTitle_Player);		// アニメーション画像

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4,		// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle_Player,
		NULL)))
	{
		return E_FAIL;
	}


	

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle_Player->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0      -POS_X	   , MAN_Y+POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0      -POS_X	   , 0    +POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(MAN_X  -POS_X, MAN_Y+POS_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(MAN_X  -POS_X, 0    +POS_Y, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(DIVISION, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(DIVISION, 0.0f);

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

	// 頂点バッファをアンロックする
	g_pVtxBuffTitle_Player->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	タイトル画面の終了処理
//-------------------------------------------------------------------------------
void UninitTitle_PLayer(void)
{

	// 頂点バッファの開放
	if (g_pVtxBuffTitle_Player != NULL)
	{
		g_pVtxBuffTitle_Player->Release();
		g_pVtxBuffTitle_Player = NULL;
	}

	// タイトル画面の開放
	if (g_pTextureTitle_Player != NULL)
	{
		g_pTextureTitle_Player->Release();
		g_pTextureTitle_Player = NULL;
	}
}

//-------------------------------------------------------------------------------
//	タイトル画面の更新処理
//-------------------------------------------------------------------------------
void UpdateTitle_PLayer(void)
{
	// 変数宣言
	VERTEX_2D *pVtx;

	g_nCountersTitle_PlayerCnt++;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle_Player->Lock(0, 0, (void**)&pVtx, 0);


	// アニメーション
	if ((g_nCountersTitle_PlayerCnt %MAX_ANIMATION_COUNTER) == 0)	// アニメーションのカウント
	{
		g_nCountersTitle_Player = (g_nCountersTitle_Player + 1) % MAX_ANIMATION_PATTERN;	// アニメーションのコマ数

		// アニメーションの頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + g_nCountersTitle_Player * DIVISION, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f + g_nCountersTitle_Player * DIVISION, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(DIVISION + g_nCountersTitle_Player * DIVISION, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(DIVISION + g_nCountersTitle_Player * DIVISION, 0.0f);
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTitle_Player->Unlock();
}

//-------------------------------------------------------------------------------
//	アニメーションの描画処理
//-------------------------------------------------------------------------------
void DrawTitle_PLayer(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 頂点バッファをデータストーリに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle_Player, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitle_Player);

	//タイトルの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
		0,						// 描画を開始する頂点インデックス
		NUM_POLYGON);			// 描画するプリミティブ数
}