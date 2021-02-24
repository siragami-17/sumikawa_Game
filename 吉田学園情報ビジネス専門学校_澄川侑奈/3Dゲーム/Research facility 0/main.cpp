//--------------------------------------------------------------------------------
//
//	ウインドウの処理 [main.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "main.h"
#include "camera.h"			// カメラ
#include "keyboard.h"		// キーボード
#include "mouse.h"			// マウス
#include "Xcontroller.h"	// Xinput
#include "fade.h"			// フェード
#include "sound.h"			// BGM
#include "title.h"			// タイトル
#include "tutorial.h"		// チュートリアル
#include "game.h"			// ゲーム
#include "result.h"			// リザルト
#include "ranking.h"		// ランキング
#include "beginning.h"		// 初めの画面

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define CLASS_NAME "windowclass"									// ウインドウクラス名
#define WINDOW_NAME "Research facility 0"							// ウインドウ名
#define ID_BUTTON000	(101)										// ボタン000のID
#define ID_EDIT000		(111)										// エディットのID
#define WINDOW_POS_X	(500)										// ウインドウの左上X座標
#define WINDOW_POS_Y	(500)										// ウインドウの左上Y座標
#define ID_TIMER		(121)										// タイマーのID
#define TIMER_INTERVAL	(1000/60)									// タイマー発生間隔
#define MAX_FPS			(256)										// FPS

#define RED				(0)											// カラー(赤)
#define GREEN			(0)											// カラー(緑)
#define BLUE			(0)											// カラー(青)
#define OPACITY			(255)										// カラー(不透明)

//-------------------------------------------------------------------------------
//	プロトタイプ宣言
//-------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hEnd, BOOL bWindow);
void DrawFPS(void);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawTxT(void);		// 数値を出す

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3D9 g_pD3D = NULL;				// Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	// Direct3Dデバイスへもポインタ
LPD3DXFONT g_pFont = NULL;				// フォントへのポインタ
int g_nCountFPS;						// FPSカウンタ
MODE g_mode = MODE_TITLE;				// モードの種類

//-------------------------------------------------------------------------------
//	メイン関数
//-------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpcmdLine, int nCmdShow)
{
	DWORD dwExecLastTime;			// 処理実行最終時刻
	DWORD dwFPSLastTime;			// FPS計測最終時刻
	DWORD dwCurrentTime;			// 現在時刻
	DWORD dwFrameCount;				// フレームカウント

	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();
	dwCurrentTime = timeGetTime();	// 現在時刻を設定
	dwFrameCount = 0;				// 初期化

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		"CLASS_NAME",
		LoadIcon(NULL,IDI_APPLICATION),
	};
	HWND hWnd;
	MSG msg;

	// ウインドウクラスの登録
	RegisterClassEx(&wcex);

	// ウインドウ作成
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);	// ウインドウの大きさを調整する

	hWnd = CreateWindowEx
	(0,
		"CLASS_NAME",
		WINDOW_NAME,				// ウインドウの名前
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,		// 幅
		rect.bottom - rect.top,		// 高さ
		NULL,
		NULL,
		hInstance,
		NULL);

	// 初期化処理
	if (FAILED(Init(hInstance, hWnd, FALSE)))// FALSEだとフルスクリーン。TRUEだと指定の大きさ
	{
		return -1;
	}

	// ウインドウの表示
	ShowWindow(hWnd, nCmdShow);

	UpdateWindow(hWnd);

	// ループメッセージ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{	// Windowsの処理
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{	// DirectXの処理

			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	// 最終時刻の保存
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime)>(1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}
	// 終了処理
	Uninit();

	// ウインドウの登録解除
	UnregisterClass("CLASS_NAME", wcex.hInstance);
	return(int)msg.wParam;
}

//-------------------------------------------------------------------------------
//	ウインドウプロシージャ
//-------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 変数宣言
	int nID;
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		// ×ボタンを押したとき
	case WM_CLOSE:
		nID = MessageBox(NULL, "終了しますか？", "注意", (MB_YESNO | MB_ICONQUESTION));						//ウインドウに表示
		if (nID == IDYES)
		{	//はいを選択
			DestroyWindow(hWnd);
		}
		else
		{	// いいえを選択
			return 0;
		}
		break;
	case WM_KEYDOWN:

		//ESCキーを押したとき
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(NULL, "終了しますか？", "注意", (MB_YESNO | MB_ICONQUESTION | MB_TOPMOST));	//ウインドウに表示
			if (nID == IDYES)
			{	// はいを選択
				DestroyWindow(hWnd);
			}
			break;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//-------------------------------------------------------------------------------
//	初期化処理
//-------------------------------------------------------------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bwindow)
{
	//変数宣言
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//ディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth = SCREEN_WIDTH;	//ゲーム画面の幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;	//ゲーム画面の高さ
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;	//有効にする
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bwindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direact3Dデバイスの生成
	if (FAILED(g_pD3D->CreateDevice
	(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice
		(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice
			(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステート
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//カリングの設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//αブレンド(α値の合成)の設定
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//ソースの合成方法の設定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//デスティネーションの合成方法の設定

	//サンプラーステートの設定(テクスチャの設定)
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//縮小の時	補間
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//拡大の時	補間
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//U値		繰り返し
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//V値		繰り返し

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	D3DXCreateFont(g_pD3DDevice,
		18,	//サイズ
		0,
		0,
		0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&g_pFont);

	// キー入力の初期化処理
	Initkeyboard(hInstance, hWnd);

	//サウンド
	InitSound(hWnd);

	//フェード
	InitFade(g_mode);

	//モードの設定
	SetMode(g_mode);

	// マウスの初期化処理
	mainMouse();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	終了処理
//-------------------------------------------------------------------------------
void Uninit(void)
{
	//サウンドの終了処理
	UninitSound();

	//フェードの終了処理
	UninitFade();

	// キーボードの終了処理
	Uninitkeyboard();

	//モードの終了処理
	switch (g_mode)
	{
	case MODE_TITLE:					// タイトル画面の終了処理
		UninitTitle();
		break;
	case MODE_TUTORIAL:					// チュートリアル画面の終了処理
		UniniTtutorial();
		break;
	case MODE_BEGINNING:				// 初めの画面の終了処理
		UninitBeginning();
		break;
	case MODE_GAME:						// ゲームの終了処理
		UninitGame();
		break;
	case MODE_RESULT:					// リザルトの終了処理
		UninitResult();
		break;
	case MODE_RANKING:
		UninitRanking();				// ランキングの終了処理
		break;
	}

	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	// Direct3Dデバイスの開放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// birect3Dオブジェクトの開放
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//-------------------------------------------------------------------------------
//	更新処理
//-------------------------------------------------------------------------------
void Update(void)
{
	UpdateXcontroller();	// Xinput
	UpdateFade();			// フェードの更新処理
	Updatakeyboard();		// キーボードの更新処理

	//モードの更新処理
	switch (g_mode)
	{
	case MODE_TITLE:					// タイトル画面の更新処理
		UpdateTitle();
		break;
	case MODE_TUTORIAL:					// チュートリアル画面の更新処理
		UpdateTutorial();
		break;
	case MODE_BEGINNING:				// 初めの画面の更新処理
		UpdateBeginning();
		break;
	case MODE_GAME:						// ゲームの更新処理
		UpdateGame();
		break;
	case MODE_RESULT:					//リザルトの更新処理
		UpdateResult();
		break;
	case MODE_RANKING:
		UpdateRanking();				// ランキングの更新処理
		break;
	}
}

//-------------------------------------------------------------------------------
//	描画処理
//-------------------------------------------------------------------------------
void Draw(void)
{
	// バックバッファ&バッファのクリア(画面のクリア)
	g_pD3DDevice->Clear
	(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(RED, GREEN, BLUE, OPACITY),		// ウインドウのカラー設定
		1.0f,
		0);


	// カメラの設定
	SetCamera(1);

	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{// 描画開始(描画に必要)

		D3DVIEWPORT9 viewportDef;

		// 現在のビューポートを取得
		g_pD3DDevice->GetViewport(&viewportDef);

		// カメラの設定
		SetCamera(1);

		 //モードの描画処理
		switch (g_mode)
		{
		case MODE_TITLE:					//タイトル画面の描画処理
			DrawTitle();
			break;
		case MODE_TUTORIAL:					//チュートリアル画面の描画処理
			DrawtuTorial();
			break;
		case MODE_BEGINNING:				// 初めの画面の描画処理
			DrawBeginning();
			break;
		case MODE_GAME:						//ゲームの描画処理
			DrawGame();
			break;
		case MODE_RESULT:					//リザルトの描画処理
			DrawResult();
			break;
		case MODE_RANKING:
			DrawRanking();					// ランキングの描画処理
			break;
		}

		// ビューポートを元に戻す
		g_pD3DDevice->SetViewport(&viewportDef);

		DrawFade();					//フェードの描画処理

		// Releaseの時FPSの表示を消す
#ifdef _DEBUG
		DrawFPS();						// FPSの描画処理
		DrawTxT();						// 数値の描画処理

#endif

		g_pD3DDevice->EndScene();		// 描画終了

	}
	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//-------------------------------------------------------------------------------
//	デバイスの取得
//-------------------------------------------------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//-------------------------------------------------------------------------------
//	FPSの描画処理
//-------------------------------------------------------------------------------
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[MAX_FPS];

	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	// テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));		// FPSの色を変える
}

//-------------------------------------------------------------------------------
//	カメラ数値の描画処理
//-------------------------------------------------------------------------------
void DrawTxT(void)
{
	// カメラの情報
	Camera pCamera;
	pCamera = *GetCamera();

	// どこまでの範囲か
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	// 変数宣言
	char aStr[256];

	int nNum = sprintf(&aStr[0],"%.2f",pCamera.rot.y);

	// テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 255, 255, 255));		// FPSの色を変える
}

//-------------------------------------------------------------------------------
//	モードの設定
//-------------------------------------------------------------------------------
void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:					//タイトル画面の終了処理
		UninitTitle();
		break;
	case MODE_TUTORIAL:					//チュートリアル画面の終了処理
		UniniTtutorial();
		break;
	case MODE_BEGINNING:				// 初めの画面の終了処理
		UninitBeginning();
		break;
	case MODE_GAME:						//ゲームの終了処理
		UninitGame();
		break;
	case MODE_RESULT:					//リザルトの終了処理
		UninitResult();
		break;
	case MODE_RANKING:
		UninitRanking();				// ランキングの終了処理
		break;
	}

	switch (mode)
	{
	case MODE_TITLE:					//タイトル画面の初期化処理
		InitTitle();
		break;
	case MODE_TUTORIAL:					//チュートリアル画面の初期化処理
		InitTutorial();
		break;
	case MODE_BEGINNING:				// 初めの画面の初期化処理
		InitBeginning();
		break;
	case MODE_GAME:						//ゲームの初期化処理
		InitGame();
		break;
	case MODE_RESULT:					//リザルトの初期化処理
		InitResult();
		break;
	case MODE_RANKING:
		InitRanking();					// ランキングの初期化処理
		break;
	}
	g_mode = mode;
}

//-------------------------------------------------------------------------------
//	モードの取得
//-------------------------------------------------------------------------------
MODE * GetMode(void)
{
	return &g_mode;		// モードの情報の先頭アドレスを返す
}