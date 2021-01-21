//--------------------------------------------------------------------------------
//
//	フェードの処理 tTitle.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "fade.h"

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define SPEEDTIME	(0.05f)		//フェードのスピード

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
FADE g_fade;			//フェードの状態
MODE g_modeNext;		//次のモード(画面)
D3DXCOLOR g_cdorFade;	//フェード色

LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxFade = NULL;

//-------------------------------------------------------------------------------
//	初期化処理
//-------------------------------------------------------------------------------
HRESULT InitFade(MODE modeNext)
{
	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_cdorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4,		//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxFade,
		NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxFade->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);				//左上
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);							//左下
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);	//右下
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);				//右上

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー設定
	pVtx[0].col = g_cdorFade;
	pVtx[1].col = g_cdorFade;
	pVtx[2].col = g_cdorFade;
	pVtx[3].col = g_cdorFade;

	//頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);	//左上
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);	//左下
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);	//右下
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);	//右上

	//頂点バッファをアンロックする
	g_pVtxFade->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	終了処理
//-------------------------------------------------------------------------------
void UninitFade(void)
{
	//頂点バッファの開放
	if (g_pVtxFade != NULL)
	{
		g_pVtxFade->Release();
		g_pVtxFade = NULL;
	}

	//テクスチャの開放
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}
}

//-------------------------------------------------------------------------------
//	更新処理
//-------------------------------------------------------------------------------
void UpdateFade(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxFade->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラー設定
	pVtx[0].col = g_cdorFade;
	pVtx[1].col = g_cdorFade;
	pVtx[2].col = g_cdorFade;
	pVtx[3].col = g_cdorFade;

	//頂点バッファをアンロックする
	g_pVtxFade->Unlock();

	if (g_fade == FADE_IN)
	{//フェードイン
		g_cdorFade.a -= SPEEDTIME;		//フェードスピード
		
		if (g_cdorFade.a <= 0.0f)
		{
			g_fade = FADE_NONE;
			g_cdorFade.a = 0.0f;
		}
	}
	else if(g_fade == FADE_OUT)
	{//フェードアウト
		g_cdorFade.a += SPEEDTIME;		//フェードスピード

		if (g_cdorFade.a >= 1.0f)
		{
			g_fade = FADE_IN;
			SetMode(g_modeNext);
		}
	}
}

//-------------------------------------------------------------------------------
//	描画処理
//-------------------------------------------------------------------------------
void DrawFade(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファをデータストーリに設定
	pDevice->SetStreamSource(0, g_pVtxFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureFade);

	//ポリゴンの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,						//描画を開始する頂点インデックス
		2);						//描画するプリミティブ数
}

//-------------------------------------------------------------------------------
//	画面状態の保存
//-------------------------------------------------------------------------------
void SetFade(FADE fade, MODE modeNext)
{
	g_fade = fade;
	g_modeNext = modeNext;
}

//-------------------------------------------------------------------------------
//	フェード状態の取得
//-------------------------------------------------------------------------------
FADE GetFade(void)
{
	return g_fade;
}