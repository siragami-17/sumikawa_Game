//--------------------------------------------------------------------------------
//
//	タイトル画面の処理 [title.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "title.h"
#include "keyboard.h"
#include "fade.h"
#include "Select.h"
#include "sound.h"

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define MAX_POLYGON				(3)		//ポリゴン数

#define PRESSENTER_X			(490)	//プレスエンターの幅
#define PRESSENTER_Y			(90)	//プレスエンターの高さ

#define GIRL_X					(320)	//少女の幅
#define GIRL_Y					(700)	//少女の高さ
#define MAX_ANIMATION_COUNTER	(6)		//少女(スピード)
#define MAX_ANIMATION_PATTERN	(10)	//少女(個数)

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;

LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;			// タイトル画面
													   
LPDIRECT3DTEXTURE9 g_pPressEnter = NULL;			// プレスエンター
D3DCOLOR g_col;										// カラー
int g_nCount;										// カウント
bool g_bPressEnter;									// キーを押した

int nPressEnter;									// プレスエンターをかくす
													   
LPDIRECT3DTEXTURE9 g_pGirl = NULL;					// 少女
D3DXVECTOR3 g_posAnimationGirl;						// X,Y,Zを決める
int g_nCountersAnimationGirl;						// 少女(コマ数の切り替え)
int g_nCountersAnimationCntGirl;					// 少女(カウンタ更新)
													   
bool g_bSelect = false;								// セレクト中かどうか
//-------------------------------------------------------------------------------
//	タイトル画面初期化処理
//-------------------------------------------------------------------------------
HRESULT InitTitle(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//変数宣言
	VERTEX_2D *pVtx;

	//BGMの追加
	PlaySound(SOUND_LABEL_BGM000);	//タイトルBGM

	// 初期化
	nPressEnter = 0;
	


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Title.png", &g_pTextureTitle);				//タイトル画面
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/press_enter.png", &g_pPressEnter);			//プレスエンター
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Girl.png", &g_pGirl);						//少女

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCunTitle = 0; nCunTitle < MAX_POLYGON; nCunTitle++)
	{

		switch (nCunTitle)		//ポジションの設定(頂点座標.pos)
		{
		case 0:					//背景

			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
			break;


		case 1:					//プレスエンター

			pVtx[0].pos = D3DXVECTOR3(0			   + 200, PRESSENTER_Y + 500, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0			   + 200,			 0 + 500, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(PRESSENTER_X + 200, PRESSENTER_Y + 500, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(PRESSENTER_X + 200,			 0 + 500, 0.0f);
			break;

		case 2:					//少女

			pVtx[0].pos = D3DXVECTOR3(0      + 850, GIRL_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0      + 850, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(GIRL_X + 850, GIRL_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(GIRL_X + 850, 0, 0.0f);
			break;
		}

		switch (nCunTitle)		//アニメーション用のswitch(頂点情報.tex)
		{//アニメーションする
		case 2:					//少女

			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);
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
	g_pVtxBuffTitle->Unlock();

	//セレクトの初期化処理
	InitSelect();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	タイトル画面の終了処理
//-------------------------------------------------------------------------------
void UninitTitle(void)
{
	g_bSelect = false;		//セレクト終了

	//頂点バッファの開放
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	//タイトル画面の開放
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	//プレスエンターの開放
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	//少女の開放
	if (g_pGirl != NULL)
	{
		g_pGirl->Release();
		g_pGirl = NULL;
	}

	//音止める
	StopSound();

	//セレクトの終了処理
	UninitSelect();
}

//-------------------------------------------------------------------------------
//	タイトル画面の更新処理
//-------------------------------------------------------------------------------
void UpdateTitle(void)
{
	VERTEX_2D *pVtx;

	int nFade = GetFade();

	g_nCountersAnimationCntGirl++;

	g_nCount++;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	if (nFade == FADE_NONE)
	{//フェード中は動けない

		// カウンタを更新
		if (0 == g_nCount % 70)
		{
			pVtx[4].col = D3DCOLOR_RGBA(255,255,255, 0);
			pVtx[5].col = D3DCOLOR_RGBA(255,255,255, 0);
			pVtx[6].col = D3DCOLOR_RGBA(255,255,255, 0);
			pVtx[7].col = D3DCOLOR_RGBA(255,255,255, 0);
		}
		else if (g_nCount  %100  )
		{
			pVtx[4].col = D3DCOLOR_RGBA(255,255,255, 255);
			pVtx[5].col = D3DCOLOR_RGBA(255,255,255, 255);
			pVtx[6].col = D3DCOLOR_RGBA(255,255,255, 255);
			pVtx[7].col = D3DCOLOR_RGBA(255,255,255, 255);
		}


		if (g_bSelect == true)
		{//セレクトを表示

		 //セレクト
			UpdateSelect();

			//プッシュエンターを見えなくする
			pVtx[4].col = D3DCOLOR_RGBA(0, 0, 0, 0);
			pVtx[5].col = D3DCOLOR_RGBA(0, 0, 0, 0);
			pVtx[6].col = D3DCOLOR_RGBA(0, 0, 0, 0);
			pVtx[7].col = D3DCOLOR_RGBA(0, 0, 0, 0);
		}
		else if (g_bSelect == false)
		{//セレクトが表示されてないとき
			if (GetkeyboardTrgger(DIK_RETURN) == true)
			{//ENTERキーを押した
				g_bSelect = true;

				//SEの追加
				PlaySound(SOUND_LABEL_SE_ON);	//オン
			}
		}
	}

	//アニメーション(少女)
	if ((g_nCountersAnimationCntGirl %MAX_ANIMATION_COUNTER) == 0)	//アニメーションのカウント
	{
		g_nCountersAnimationGirl = (g_nCountersAnimationGirl + 1) % MAX_ANIMATION_PATTERN;	//アニメーションのコマ数

		//アニメーションの頂点情報の設定
		pVtx[8].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationGirl * 0.1f, 1.0f);
		pVtx[9].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationGirl * 0.1f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.1f + g_nCountersAnimationGirl * 0.1f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(0.1f + g_nCountersAnimationGirl * 0.1f, 0.0f);
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}

//-------------------------------------------------------------------------------
//	タイトル画面の描画処理
//-------------------------------------------------------------------------------
void DrawTitle(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファをデータストーリに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < MAX_POLYGON; nCntTitle++)
	{
		switch (nCntTitle)
		{
		case 0:
			//タイトル画面の設定
			pDevice->SetTexture(0, g_pTextureTitle);
			break;

		case 1:
			//プレスエンターの設定
			pDevice->SetTexture(0, g_pPressEnter);
			break;

		case 2:
			//少女の設定
			pDevice->SetTexture(0, g_pGirl);
			break;
		}
		//タイトルの描画
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
			nCntTitle * 4,			//描画を開始する頂点インデックス
			NUM_POLYGON);			//描画するプリミティブ数
	}

	if (g_bSelect == true)
	{//g_bSelectがオンの時描画する
	 //セレクト
		DrawSelect();
	}
}