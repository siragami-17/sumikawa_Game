//--------------------------------------------------------------------------------
//
//	タイムの処理 [time.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "time.h"
#include "fade.h"
#include "result.h"

//--------------------------------------------------------------------------------
//	マクロ定義
//--------------------------------------------------------------------------------
#define MAX_TIME			(3)				//タイムの最大表示数
#define MAX_TIME_SIZE_X		(35.0f)			//タイムの幅
#define MAX_TIME_SIZE_Y		(70.0f)			//タイムの高さ
#define TIME_X				(1000.0f)		//タイムのU位置
#define TIME_Y				(10.0f)			//タイムのV位置
#define TIME				(900)			//表示する秒数
#define COUNT_TIME			(60)			//減っていく感覚

//--------------------------------------------------------------------------------
//	グローバル変数
//--------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;			//テクスチへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		//頂点バッファのポインタ
D3DXVECTOR3 g_aTimepos[MAX_TIME];					//タイムの画像
int g_nTime;										//現在のタイム
int g_nCountTime;									//カウントタイム

Time g_time;										// タイマーの情報	

//-------------------------------------------------------------------------------
//	タイムの初期化処理
//-------------------------------------------------------------------------------
HRESULT InitTime(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	g_nTime = TIME;					//タイム
	g_nCountTime = COUNT_TIME;		//カウントタイム

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_pTextureTime);	//タイムのテクスチャ

	//頂点情報の設定
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL)))
	{
		return E_FAIL;
	}

	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//タイムの位置
		g_aTimepos[nCntTime] = D3DXVECTOR3(nCntTime *MAX_TIME_SIZE_X + 600, TIME_Y, 0.0f);

		////タイムの頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aTimepos[nCntTime].x - 0.0f, g_aTimepos[nCntTime].y + MAX_TIME_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTimepos[nCntTime].x - 0.0f, g_aTimepos[nCntTime].y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTimepos[nCntTime].x + MAX_TIME_SIZE_X, g_aTimepos[nCntTime].y + MAX_TIME_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTimepos[nCntTime].x + MAX_TIME_SIZE_X, g_aTimepos[nCntTime].y - 0.0f, 0.0f);

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

		//頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);	//左上
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);	//左下
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);	//右下
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);	//右上

		pVtx += NUM_VERTEX;

	}
	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	終了処理
//-------------------------------------------------------------------------------
void UninitTime(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}

	//テクスチャの開放(かたす)
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}
}

//-------------------------------------------------------------------------------
//	更新処理
//-------------------------------------------------------------------------------
void UpdateTime(void)
{
	//変数宣言
	VERTEX_2D *pVtx;
	int aNumber[8];

	if (g_nTime != 0)
	{//タイムが0の時カウントをSTOP
		g_nCountTime -= 1;
	}

	if (g_nCountTime == 0)
	{
		g_nTime -= 1;
		g_nCountTime = COUNT_TIME;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//タイムの格納
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++, pVtx += 4)
	{
		aNumber[nCntTime] = (g_nTime / (int)powf(10.0f, (float)(MAX_TIME - (nCntTime + 1))));	//タイムを1桁ずつに分ける

		//テクスチャ座標更新//頂点座標
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aNumber[nCntTime] * 0.1f), 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f + (aNumber[nCntTime] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / 10.0f + (aNumber[nCntTime] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f / 10.0f + (aNumber[nCntTime] * 0.1f), 0.0f);
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();

	if (g_nTime == 0)
	{//秒数が0になったらリザルト画面へ
		SetResult(false);					//クリア画面
		SetFade(FADE_OUT, MODE_RESULT);
	}
}

//-------------------------------------------------------------------------------
//	タイムの描画処理
//-------------------------------------------------------------------------------
void DrawTime(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTime);

		//ポリゴンの描画
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
			nCntTime * NUM_VERTEX,		//描画を開始する頂点インデックス
			NUM_POLYGON);				//描画するプリミティブ数
	}
	//変数宣言
	D3DXVECTOR3*pTime;
	pTime = &g_aTimepos[0];
}


//-------------------------------------------------------------------------------
//	タイムテクスチャ座標の更新
//-------------------------------------------------------------------------------
void SetVertexTime(int nIdx,int nNumber)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f*nNumber), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (0.1f*nNumber), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f + (0.1f*nNumber), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f*nNumber), 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();
}

//--------------------------------------------------------------------------------
//	タイマーの取得
//--------------------------------------------------------------------------------
Time *GetTime(void)
{
	return &g_time;			// プレイヤーの情報の先頭アドレスを返す
}