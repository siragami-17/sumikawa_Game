//--------------------------------------------------------------------------------
//
//	ステージ1の背景処理 [background_00.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "title.h"
#include "keyboard.h"
#include "fade.h"

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define MAX_POLYGON	(3)					//ポリゴン数

//#define MAX_PLAY_X			(55)		//再生マークX
//#define MAX_PLAY_Y			(100)		//再生マークY

#define MAX_PLAY_X			(0)			//再生マークX
#define MAX_PLAY_Y			(00)		//再生マークY
#define MAX_PLAY_COUNTER	(8)			//再生マークのスピード
#define MAX_PLAY_PATTERN	(4)			//再生マークの個数

//#define MAX_STOP_X			(60)		//停止マークX
//#define MAX_STOP_Y			(100)		//停止マークY

#define MAX_STOP_X			(0)			//停止マークX
#define MAX_STOP_Y			(00)		//停止マークY
#define MAX_STOP_COUNTER	(8)			//停止マークのスピード
#define MAX_STOP_PATTERN	(4)			//停止マークの個数

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBackground_00 = NULL;

LPDIRECT3DTEXTURE9 g_pTexturebackground_00 = NULL;				//ステージ1

LPDIRECT3DTEXTURE9 g_pTexturePlay = NULL;						//再生マーク
int g_nCountersAnimationPlay;									//再生マークのコマ数切り替え
int g_nCountersAnimationCntPlay;								//再生マークのカウンタ更新

LPDIRECT3DTEXTURE9 g_pTextureStop = NULL;						//停止マーク
int g_nCountersAnimationStop;									//停止マークのコマ数切り替え
int g_nCountersAnimationCntStop;								//停止マークのカウンタ更新

//-------------------------------------------------------------------------------
//	ステージ1初期化処理
//-------------------------------------------------------------------------------
HRESULT Initbackground_00(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//変数宣言
	VERTEX_2D *pVtx;


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/background.png", &g_pTexturebackground_00);		//ステージ1
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Plye.png", &g_pTexturePlay);						//再生マーク
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Stop.png", &g_pTextureStop);						//停止マーク

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffBackground_00,
		NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBackground_00->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCunBG = 0; nCunBG < MAX_POLYGON; nCunBG++)
	{
		switch (nCunBG)		//ポジションの設定(頂点座標.pos)
		{
		case 0:					//背景

			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
			break;

		case 1:					//再生マーク

			pVtx[0].pos = D3DXVECTOR3(0			 + 1210, MAX_PLAY_Y + 10, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0			 + 1210, 0          + 10, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(MAX_PLAY_X + 1210, MAX_PLAY_Y + 10, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(MAX_PLAY_X + 1210, 0          + 10, 0.0f);
			break;

		case 2:					//停止マーク

			pVtx[0].pos = D3DXVECTOR3(0 + 500, MAX_STOP_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0 + 500, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(MAX_STOP_X + 500, MAX_STOP_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(MAX_STOP_X + 500, 0, 0.0f);
			break;
		}

		switch (nCunBG)		//アニメーション用のswitch(頂点情報.tex)
		{//アニメーションする
		case 1:					//再生マーク

			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0);
			pVtx[2].tex = D3DXVECTOR2(0.25f, 1.0);
			pVtx[3].tex = D3DXVECTOR2(0.25f, 0.0);
			break;

		case 2:					//停止マーク

			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0);
			pVtx[2].tex = D3DXVECTOR2(0.25f, 1.0);
			pVtx[3].tex = D3DXVECTOR2(0.25f, 0.0);
			break;

		default:				//アニメーションしない

			pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
			pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
			pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
			pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);
			break;
		}

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBackground_00->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	ステージ1の終了処理
//-------------------------------------------------------------------------------
void Uninitbackground_00(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffBackground_00 != NULL)
	{
		g_pVtxBuffBackground_00->Release();
		g_pVtxBuffBackground_00 = NULL;
	}

	//背景の開放
	if (g_pTexturebackground_00 != NULL)
	{
		g_pTexturebackground_00->Release();
		g_pTexturebackground_00 = NULL;
	}

	//再生マークの開放
	if (g_pTexturePlay != NULL)
	{
		g_pTexturePlay->Release();
		g_pTexturePlay = NULL;
	}

	//停止マークの開放
	if (g_pTextureStop != NULL)
	{
		g_pTextureStop->Release();
		g_pTextureStop = NULL;
	}
}

//-------------------------------------------------------------------------------
//	ステージ1の更新処理
//-------------------------------------------------------------------------------
void Updatebackground_00(void)
{
	VERTEX_2D *pVtx;

	g_nCountersAnimationCntPlay++;
	g_nCountersAnimationCntStop++;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBackground_00->Lock(0, 0, (void**)&pVtx, 0);

	//アニメーション再生マーク
	if ((g_nCountersAnimationCntPlay %MAX_PLAY_COUNTER) == 0)							//アニメーションのカウント
	{
		g_nCountersAnimationPlay = (g_nCountersAnimationPlay + 1) % MAX_PLAY_PATTERN;	//アニメーションのコマ数

		//アニメーションの頂点情報の設定
		pVtx[4].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationPlay * 0.25f, 1.0f);
		pVtx[5].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationPlay * 0.25f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.25f + g_nCountersAnimationPlay * 0.25f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(0.25f + g_nCountersAnimationPlay * 0.25f, 0.0f);
	}

	//アニメーション停止マーク
	if ((g_nCountersAnimationCntStop %MAX_STOP_COUNTER) == 0)							//アニメーションのカウント
	{
		g_nCountersAnimationStop = (g_nCountersAnimationStop + 1) % MAX_STOP_PATTERN;	//アニメーションのコマ数

		//アニメーションの頂点情報の設定
		pVtx[8].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationStop * 0.25f, 1.0f);
		pVtx[9].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationStop * 0.25f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.25f + g_nCountersAnimationStop * 0.25f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(0.25f + g_nCountersAnimationStop * 0.25f, 0.0f);
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBackground_00->Unlock();
}

//-------------------------------------------------------------------------------
//	ステージ1の描画処理
//-------------------------------------------------------------------------------
void Drawbackground_00(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファをデータストーリに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBackground_00, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCunBG = 0; nCunBG < MAX_POLYGON; nCunBG++)
	{
		switch (nCunBG)
		{
		case 0:
			//背景の設定
			pDevice->SetTexture(0, g_pTexturebackground_00);
			break;

		case 1:
			//再生マークの設定
			pDevice->SetTexture(0, g_pTexturePlay);
			break;

		case 2:
			//再生マークの設定
			pDevice->SetTexture(0, g_pTextureStop);
			break;
		}
		//ステージ背景の描画
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
			nCunBG * 4,			//描画を開始する頂点インデックス
			NUM_POLYGON);			//描画するプリミティブ数
	}
}