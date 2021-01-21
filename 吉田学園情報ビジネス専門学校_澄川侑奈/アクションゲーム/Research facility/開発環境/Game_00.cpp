//--------------------------------------------------------------------------------
//
//	ステージ1の処理 [Game_00.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "main.h"
#include "Player.h"				// プレイヤー
#include "block.h"				// ブロック
#include "background_00.h"		// ゲーム背景
#include "mark.h"				// カーソル
#include "StopBG.h"				// 停止背景
#include "keyboard.h"			// キーボード
#include "pause.h"				// ポーズ
#include "Key.h"				// 鍵
#include "Life.h"				// ライフ
#include "enemy.h"				// 敵
#include "goal.h"				// ゴール
#include "fade.h"				// フェード
#include "sound.h"				// 音
#include "Xcontroller.h"				// Xinout

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
bool g_bStop = false;	//カーソル中かどうか
bool g_bPause = false;	//ポーズ中かどうか

//-------------------------------------------------------------------------------
//	初期化処理
//-------------------------------------------------------------------------------
HRESULT InitGame_00(void)
{

	//BGMの追加
	PlaySound(SOUND_LABEL_BGM002);	//ゲームBGM

	//背景の初期化処理
	Initbackground_00();

	g_bStop = false;

	//ブロックの初期化処理
	InitBlock();


	//ブロックの位置(pos,幅,高さ)
	SetBlock(D3DXVECTOR3(610.0f, 600.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(670.0f, 540.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(730.0f, 480.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(790.0f, 420.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(850.0f, 360.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(910.0f, 300.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(970.0f, 300.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(1030.0f, 300.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(1090.0f, 300.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(1150.0f, 300.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(1210.0f, 300.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);


	//SetBlock(D3DXVECTOR3(0.0f, 100.0f, 0.0f), 10.0f, 690.0f, BLOCKTYPE_NOT_CATCH);//壁左

	//SetBlock(D3DXVECTOR3(0.0f, 100.0f, 0.0f), 10.0f, 720.0f, BLOCKTYPE_NOT_CATCH);//壁右
	
	//地面
	SetBlock(D3DXVECTOR3(-50.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(10.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(70.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(130.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(190.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(250.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(310.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(370.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(430.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(490.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(550.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(610.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(670.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(730.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(790.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(850.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(910.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(970.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(1030.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(1090.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(1150.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(1210.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(1270.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(1330.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);


	//SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 60, 0.0f), SCREEN_WIDTH, 60.0f, BLOCKTYPE_NOT_CATCH);		//地面

	//SetBlock(D3DXVECTOR3(940.0f, 300.0f - 40, 0.0f), 450.0f, 60.0f);				//下から数えて1段目の右地面


	//プレイヤーの初期化処理																		
	InitPlayer();

	//敵の初期化処理
	InitEnemy();

	//鍵の初期化処理
	InitKey();

	//扉の初期化処理
	Initdoor();

	//カーソルの初期化処理
	InitMarker();

	//停止背景の初期化処理
	InitStopBG();

	//ライフの初期化処理
	InitLife();

	//ポーズの初期化処理
	InitPause();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	終了処理
//-------------------------------------------------------------------------------
void UninitGame_00(void)
{
	g_bPause = false;	//ポーズを終了

	//ポーズの終了処理
	UninitPause();

	//停止背景の終了処理
	UninitStopBG();

	//カーソルの終了処理
	UninitMarker();

	// 扉の終了処理
	Uninitdoor();

	// 鍵の終了処理
	UninitKey();

	// 敵の終了処理
	UninitEnemy();

	// プレイヤーの終了処理
	UninitPlayer();

	// ブロックの終了処理
	UninitBlock();

	// ライフの終了処理
	UninitLife();

	// 背景の終了処理
	Uninitbackground_00();

	// 音止める
	StopSound();
}

//-------------------------------------------------------------------------------
//	更新処理
//-------------------------------------------------------------------------------
void UpdateGame_00(void)
{
	// 敵の更新処理
	UpdateEnemy();

	if (GetkeyboardTrgger(DIK_P) == true)
	{// Pを押した
		g_bPause = g_bPause ? false : true;

		// SEの追加
		PlaySound(SOUND_LABEL_SE_ON);	// オン
	}
	if (g_bPause == true)
	{// ポーズへ移動

	 // ポーズの更新処理
		UpdatePause();
	}
	else if (GetkeyboardTrgger(DIK_J) == true)
	{// Jを押した
		g_bStop = g_bStop ? false : true;

		// SEの追加
		PlaySound(SOUND_LABEL_SE_ON);	// オン
	}
	else if (g_bStop == true)
	{// 停止画面を表示

		// 停止背景の更新処理
		UpdateStopBG();

		// カーソルの更新処理
		UpdateMarker();

		// ブロックの更新処理
		UpdateBlock();
	}
	else
	{// 押さなかった

		// プレイヤーの更新処理
		UpdatePlayer();

		// 鍵の更新処理
		UpdateKey();

		// 扉の更新処理
		Updatedoor();

		// ライフの更新処理
		UpdateLife();

		// 背景の更新処理
		Updatebackground_00();
	}
}

//-------------------------------------------------------------------------------
//	描画処理
//-------------------------------------------------------------------------------
void DrawGame_00(void)
{
	// 背景の描画処理
	Drawbackground_00();

	// 扉の描画処理
	Drawdoor();

	// ブロックの描画処理
	DrawBlock();

	// 鍵の描画処理
	DrawKey();

	// プレイヤーの描画処理
	DrawPlayer();

	// 敵の描画処理
	DrawEnemy();

	// ライフの描画処理
	DrawLife();

	if (g_bStop == true)
	{// 停止された

		// 停止背景の描画処理
		DrawStopBG();

		// カーソルの描画処理
		DrawMarker();
	}

	if (g_bPause == true)
	{//ポーズされた

		//ポーズの描画処理
		DrawPause();
	}
}

//-------------------------------------------------------------------------------
//	停止処理
//-------------------------------------------------------------------------------
void SetStop(bool bStop)
{
	g_bStop = bStop;	//停止中かどうか
}

//-------------------------------------------------------------------------------
//	ポーズ処理
//-------------------------------------------------------------------------------
void SetPause(bool bPause)
{
	g_bPause = bPause;	//ポーズ中かどうか
}

bool GetStop(void)
{
	return g_bStop;
}