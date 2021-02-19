//--------------------------------------------------------------------------------
//
//	タイトルの処理 [title.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "title.h"				// タイトル
#include "fade.h"				// フェード
#include "sound.h"				// BGM
#include "keyboard.h"			// キーボード
#include "Xcontroller.h"		// Xinput

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define MAX_POLYGON	(1)		// テクスチャ枚数

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;
LPDIRECT3DTEXTURE9 g_pTexTitle = NULL;				// タイトル

//-------------------------------------------------------------------------------
//	タイトル画面初期化処理
//-------------------------------------------------------------------------------
HRESULT InitTitle(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 変数宣言
	VERTEX_2D *pVtx;

	// BGMの読み込み
	PlaySound(SOUND_LABEL_TITLE);		// タイトルBGM

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title.jpg", &g_pTexTitle);		// タイトル画像

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

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
	g_pVtxBuffTitle->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	タイトル画面の終了処理
//-------------------------------------------------------------------------------
void UninitTitle(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	// テクスチャの開放(タイトル画面)
	if (g_pTexTitle != NULL)
	{
		g_pTexTitle->Release();
		g_pTexTitle = NULL;
	}
}

//-------------------------------------------------------------------------------
//	タイトル画面の更新処理
//-------------------------------------------------------------------------------
void UpdateTitle(void)
{
	int nFade = GetFade();

	if (nFade == FADE_NONE)
	{//　フェード中は動けない
		if (GetkeyboardTrgger(DIK_RETURN) == true)
		{//　エンターキーを押した
			// チュートリアル画面に移動
			SetFade(FADE_OUT, MODE_TUTORIAL);

			//音止める
			StopSound();
		}
	}
}

//-------------------------------------------------------------------------------
//	タイトル画面の描画処理
//-------------------------------------------------------------------------------
void DrawTitle(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストーリに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定(タイトル)
	pDevice->SetTexture(0, g_pTexTitle);

	// タイトル画面の描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
		0,						// 描画を開始する頂点インデックス
		2);						// 描画するプリミティブ数
}