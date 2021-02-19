//--------------------------------------------------------------------------------
//
//	ハートの処理 [heart.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "heart.h"
#include "keyboard.h"		// キーボード

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define MAX_X					(75*2)			// 画像の幅
#define MAX_Y					(60*2)			// 画像の高さ
#define MAX_COUNTER				(5)				// スピード
#define MAX_PATTERN				(10)			// 画像コマ数
#define DIVISION				(0.1f)			// 割り算
#define RED						(255)			// カラー(赤)
//#define 

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHeart = NULL;

LPDIRECT3DTEXTURE9 g_pTextureHeart = NULL;		// テクスチャ
D3DXVECTOR3 g_posHeart;							// 位置
int g_nCountersHeart;							// コマ数の切り替え
int g_nCountersHeartCnt;						// カウンタ更新

//-------------------------------------------------------------------------------
//	タイトル画面初期化処理
//-------------------------------------------------------------------------------
HRESULT InitHeart(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 変数宣言
	VERTEX_2D *pVtx;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/heart.png", &g_pTextureHeart);				// ハート

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4,		// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffHeart,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHeart->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_posHeart.x + 0    ,g_posHeart.y +  MAX_Y, g_posHeart.z + 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posHeart.x + 0    ,g_posHeart.y +  0    , g_posHeart.z + 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posHeart.x + MAX_X,g_posHeart.y +  MAX_Y, g_posHeart.z + 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posHeart.x + MAX_X,g_posHeart.y +  0    , g_posHeart.z + 0.0f);

	// 頂点情報の設定
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
	g_pVtxBuffHeart->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	タイトル画面の終了処理
//-------------------------------------------------------------------------------
void UninitHeart(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffHeart != NULL)
	{
		g_pVtxBuffHeart->Release();
		g_pVtxBuffHeart = NULL;
	}

	// タイトル画面の開放
	if (g_pTextureHeart != NULL)
	{
		g_pTextureHeart->Release();
		g_pTextureHeart = NULL;
	}
}

//-------------------------------------------------------------------------------
//	タイトル画面の更新処理
//-------------------------------------------------------------------------------
void UpdateHeart(void)
{
	// 変数宣言
	VERTEX_2D *pVtx;

	g_nCountersHeartCnt++;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHeart->Lock(0, 0, (void**)&pVtx, 0);



	// アニメーション
	if ((g_nCountersHeartCnt %MAX_COUNTER) == 0)	// アニメーションのカウント
	{
		g_nCountersHeart = (g_nCountersHeart + 1) % MAX_PATTERN;	// アニメーションのコマ数

		// アニメーションの頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + g_nCountersHeart * DIVISION, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f + g_nCountersHeart * DIVISION, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(DIVISION + g_nCountersHeart * DIVISION, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(DIVISION + g_nCountersHeart * DIVISION, 0.0f);
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffHeart->Unlock();
}

//-------------------------------------------------------------------------------
//	アニメーションの描画処理
//-------------------------------------------------------------------------------
void DrawHeart(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 頂点バッファをデータストーリに設定
	pDevice->SetStreamSource(0, g_pVtxBuffHeart, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureHeart);

	//タイトルの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
		0,						// 描画を開始する頂点インデックス
		NUM_POLYGON);			// 描画するプリミティブ数
}