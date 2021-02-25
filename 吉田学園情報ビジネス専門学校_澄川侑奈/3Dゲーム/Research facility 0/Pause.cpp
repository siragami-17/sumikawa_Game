//--------------------------------------------------------------------------------
//
//	ポーズの処理 [Pause.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "pause.h"
#include "keyboard.h"
#include "fade.h"
#include "game.h"
#include"sound.h"

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define MAX_POLYGON		(7)		// ポーズ数
#define MERU_DISTANCE	(100)	// メニュー間距離

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
PAUSE g_aPause[MAX_POLYGON];							// ポーズの情報	

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;

LPDIRECT3DTEXTURE9 g_pTexturePause = NULL;				// 背景
LPDIRECT3DTEXTURE9 g_pGra = NULL;						// 背景(さらに後ろ)

LPDIRECT3DTEXTURE9 g_apMenu[PAUSE_MENU_MAX] = {};		// メニュー1～3

LPDIRECT3DTEXTURE9 g_pMenu_4 = NULL;					// ポーズ

LPDIRECT3DTEXTURE9 g_pMenu_5 = NULL;					// 玉
D3DXVECTOR3 g_posBall;									// 位置

int g_nCountPause;

//-------------------------------------------------------------------------------
//	ポーズ初期化処理
//-------------------------------------------------------------------------------
HRESULT InitPause(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// カーソルと選択内容の初期化
	g_posBall.y = 0;
	g_nCountPause = 0;

	// ストップの構造体の初期化処理
	g_aPause[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// 位置

	// 変数宣言
	VERTEX_2D *pVtx;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Slect.png", &g_pTexturePause);							// 背景
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause000.png", &g_apMenu[PAUSE_MENU_CONTINOE]);		// メニュー1
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause001.png", &g_apMenu[PAUSE_MENU_RETRY]);			// メニュー2
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause002.png", &g_apMenu[PAUSE_MENU_QUIT]);			// メニュー3
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause004.png", &g_pMenu_4);							// ポーズ
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Cursor.png", &g_pMenu_5);								// 玉

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,						   
		FVF_VERTEX_2D,							// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountPause = 0; nCountPause < MAX_POLYGON; nCountPause++)
	{
		switch (nCountPause)	// ポジションの設定
		{
		case 0:
			// 頂点座標(灰色)
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

			break;

		case 1:
			// 頂点座標(背景)
			pVtx[0].pos = D3DXVECTOR3(200 + 250, 610, 0.0f);		//左下
			pVtx[1].pos = D3DXVECTOR3(200 + 250, 110, 0.0f);		//左上
			pVtx[2].pos = D3DXVECTOR3(600 + 250, 610, 0.0f);		//右下
			pVtx[3].pos = D3DXVECTOR3(600 + 250, 110, 0.0f);		//右上

			break;



		case 5:
			// 頂点座標(メニュー4)
			pVtx[0].pos = D3DXVECTOR3(0 + 480, 60 + 150, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0 + 480, 0 + 150, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(320 + 480, 60 + 150, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(320 + 480, 0 + 150, 0.0f);

			break;

		case 6:
			// 頂点座標(メニュー玉)
			pVtx[0].pos = D3DXVECTOR3(0 + 480, 50 + 300, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0 + 480, 0 + 300, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(50 + 480, 50 + 300, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(50 + 480, 0 + 300, 0.0f);

			break;

		default:	// 上記以外

			// 頂点座標(メニュー1～3)
			pVtx[0].pos = D3DXVECTOR3(0 + 480, 60 + 100.0f * nCountPause + MERU_DISTANCE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0 + 480, 0 + 100.0f * nCountPause + MERU_DISTANCE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(320 + 480, 60 + 100.0f * nCountPause + MERU_DISTANCE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(320 + 480, 0 + 100.0f * nCountPause + MERU_DISTANCE, 0.0f);

			break;
		}

		switch (nCountPause)	// カラー用のswitch(頂点カラー.col)
		{	// カラー変更するやつ
		case 0:

			pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 100);
			pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 100);
			pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 100);
			pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 100);
			break;

		case 2:

			pVtx[0].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			break;

		case 3:

			pVtx[0].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			break;

		case 4:

			pVtx[0].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			break;

		default:	// カラー変更なし

			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			break;
		}

		switch (nCountPause)	// アニメーション用のswitch(頂点情報.tex)
		{	// アニメーションする

		case 6:// 玉

			pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);	// 左上
			pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);	// 左下
			pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);	// 右下
			pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);	// 右上
			break;

		default:	// アニメーションしない

			pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);	// 左上
			pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);	// 左下
			pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);	// 右下
			pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);	// 右上
			break;
		}

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	ポーズの終了処理
//-------------------------------------------------------------------------------
void UninitPause(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

	// テクスチャの開放(灰色)
	if (g_pGra != NULL)
	{
		g_pGra->Release();
		g_pGra = NULL;
	}

	// テクスチャの開放(背景)
	if (g_pTexturePause != NULL)
	{
		g_pTexturePause->Release();
		g_pTexturePause = NULL;
	}

	// テクスチャの開放(メニュー1～3)
	for (int nCntPause = 0; nCntPause < PAUSE_MENU_MAX; nCntPause++)
	{
		if (g_apMenu[nCntPause] != NULL)
		{
			g_apMenu[nCntPause]->Release();
			g_apMenu[nCntPause] = NULL;
		}
	}

	// テクスチャの開放(メニュー3)
	if (g_pMenu_4 != NULL)
	{
		g_pMenu_4->Release();
		g_pMenu_4 = NULL;
	}

	// テクスチャの開放(メニュー3)
	if (g_pMenu_5 != NULL)
	{
		g_pMenu_5->Release();
		g_pMenu_5 = NULL;
	}

}

//-------------------------------------------------------------------------------
//	ポーズの更新処理
//-------------------------------------------------------------------------------
void UpdatePause(void)
{
	// 変数宣言
	VERTEX_2D *pVtx;

	int nFade = GetFade();

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);


	if (nFade == FADE_NONE)
	{// フェード中は動けない
		if (GetkeyboardTrgger(DIK_W) == true)
		{// 上に移動
			g_nCountPause--;

			g_posBall.y -= 100;

			// SEの追加
			PlaySound(SOUND_LABEL_SE_CHOICE);	// オン

			if (g_nCountPause < PAUSE_MENU_CONTINOE)
			{// メニューの最大数に移動
				g_nCountPause = PAUSE_MENU_QUIT;
			}
		}

		if (GetkeyboardTrgger(DIK_S) == true)
		{// 下に移動
			g_nCountPause++;

			g_posBall.y += 100;

			// SEの追加
			PlaySound(SOUND_LABEL_SE_CHOICE);	// オン

			if (g_nCountPause > PAUSE_MENU_QUIT)
			{// メニューの最小数に移動
				g_nCountPause = PAUSE_MENU_CONTINOE;
			}
		}

		if (GetkeyboardTrgger(DIK_RETURN) == true)
		{// 決定
			if (g_nCountPause == PAUSE_MENU_CONTINOE)
			{//メニュー1の時	
				SetPause(false);

				// SEの追加
				PlaySound(SOUND_LABEL_SE_OFF);	// オフ
			}

			if (g_nCountPause == PAUSE_MENU_RETRY)
			{// メニュー2の時	

			 // ゲーム画面に移動
				SetFade(FADE_OUT, MODE_GAME);
			}

			if (g_nCountPause == PAUSE_MENU_QUIT)
			{// メニュー3の時	

			 // タイトルの移動
				SetFade(FADE_OUT, MODE_TITLE);

			}
		}
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();

	if (g_posBall.y < 0)
	{// カーソルが選択1にいったとき
		g_posBall.y = 200;				// 選択3に移動
	}

	if (g_posBall.y > 200)
	{// カーソルが選択3にいったとき
		g_posBall.y = 0;				// 選択1に移動
	}

	// 頂点座標(メニュー玉)
	pVtx[24].pos = D3DXVECTOR3(0 + 480, 50 + 300 + g_posBall.y, 0.0f);
	pVtx[25].pos = D3DXVECTOR3(0 + 480, 0 + 300 + g_posBall.y, 0.0f);
	pVtx[26].pos = D3DXVECTOR3(50 + 480, 50 + 300 + g_posBall.y, 0.0f);
	pVtx[27].pos = D3DXVECTOR3(50 + 480, 0 + 300 + g_posBall.y, 0.0f);

}

//-------------------------------------------------------------------------------
//	ポーズの描画処理
//-------------------------------------------------------------------------------
void DrawPause(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 頂点バッファをデータストーリに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePause);

	for (int nCntTitle = 0; nCntTitle < MAX_POLYGON; nCntTitle++)
	{
		switch (nCntTitle)
		{
		case 0:
			// タイトル(ポーズ)テクスチャの設定
			pDevice->SetTexture(0, g_pGra);
			break;

		case 1:
			// タイトル(ポーズ)テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePause);
			break;

		case 2:
			// タイトル(ポーズ)テクスチャの設定
			pDevice->SetTexture(0, g_apMenu[PAUSE_MENU_CONTINOE]);
			break;

		case 3:
			// タイトル(ポーズ)テクスチャの設定
			pDevice->SetTexture(0, g_apMenu[PAUSE_MENU_RETRY]);
			break;

		case 4:
			// タイトル(ポーズ)テクスチャの設定
			pDevice->SetTexture(0, g_apMenu[PAUSE_MENU_QUIT]);
			break;

		case 5:
			// タイトル(ポーズ)テクスチャの設定
			pDevice->SetTexture(0, g_pMenu_4);
			break;

		case 6:
			// タイトル(ポーズ)テクスチャの設定
			pDevice->SetTexture(0, g_pMenu_5);
			break;
		}
		// ポーズの描画
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
			nCntTitle * 4,			// 描画を開始する頂点インデックス
			2);						// 描画するプリミティブ数
	}
}