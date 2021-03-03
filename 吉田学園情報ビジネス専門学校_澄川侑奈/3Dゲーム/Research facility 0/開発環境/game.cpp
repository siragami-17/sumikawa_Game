//--------------------------------------------------------------------------------
//
//	ゲームの処理 [game.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "game.h"			// ゲーム
#include "sound.h"			// サウンド
#include "meshfild.h"		// 地面
#include "camera.h"			// カメラ
#include "light.h"			// ライト
#include "player.h"			// プレイヤー
#include "shadow.h"			// 影
#include "wall.h"			// 壁
#include "Key.h"			// 鍵
#include "bullet.h"			// 弾
#include "mouse.h"			// マウス
#include "Xcontroller.h"	// Xinput
#include "fade.h"			// フェード
#include "keyboard.h"		// キーボード
#include "time.h"			// タイマー
#include "heart.h"			// ハート
#include "Pause.h"			// ポーズ
#include "block.h"			// ブロック
#include "object.h"			// オブジェクト
#include "object_1.h"

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
bool g_bPause = false;	//ポーズ中かどうか

//-------------------------------------------------------------------------------
//	初期化処理
//-------------------------------------------------------------------------------
HRESULT InitGame(void)
{

	// BGMの読み込み
	PlaySound(SOUND_LABEL_GAME);		// ゲーム

	// 地面の初期化処理
	InitMeshfild();

	// カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	// 壁の初期化処理
	InitWall();

	// 影の初期化処理
	InitShadow();

	// 鍵の初期化処理
	InitKey();

	// Xファイルの初期化処理
	InitPlayer();

	// オブジェクト
	InitObject();

	// オブジェクト
//	InitObject_1();

	// ゴールの初期化処理
	InitBlock();

	// 弾の初期化処理
	InitBullet();

	// タイマーの初期化処理
	InitTime();

	// ハートの初期化処理
	InitHeart();

	//ポーズの初期化処理
	InitPause();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	終了処理 
//-------------------------------------------------------------------------------
void UninitGame(void)
{
	g_bPause = false;	//ポーズを終了

	//ポーズの終了処理
	UninitPause();

	// ハートの終了処理
	UninitHeart();

	// タイマーの終了処理
	UninitTime();

	// 弾の終了処理
	UninitBullet();

	// 地面の終了処理
	UninitMeshfild();

	// ゴールの終了処理
	UninitBlock();

	// オブジェクト
//	UninitObject_1();

	// オブジェクト
	UninitObject();

	// Xファイルの終了処理
	UninitPlayer();

	// 鍵の終了処理
	UninitKey();

	// 影の終了処理
	UninitShadow();

	// 壁の終了処理
	UninitWall();

	// ライトの終了処理
	UninitLight();

	// カメラの終了処理
	UninitCamera();

	//音止める
	StopSound();
}

//-------------------------------------------------------------------------------
//	更新処理
//-------------------------------------------------------------------------------
void UpdateGame(void)
{
	//フェード
	int nFade = GetFade();


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
	else
	{// 押さなかった

		// タイマーの更新処理
		UpdateTime();

		// ハートの更新処理
		UpdateHeart();



		// 地面の更新処理
		UpdateMeshfild();

		// ライトの更新処理
		UpdateLight();

		// Xファイルの更新処理
		UpdatePlayer();

		// オブジェクト
		UpdateObject();

		// オブジェクト
	//	UpdateObject_1();

		// ゴールの更新処理
		UpdateBlock();

		// 影の更新処理
		UpdateShadow();

		// 壁の更新処理
		UpdateWall();

		// 鍵の更新処理
		UpdateKey();

		// 弾の更新処理
		UpdateBullet();
	}
	// カメラの更新処理
	UpdateCamera();
}


//-------------------------------------------------------------------------------
//	描画処理
//-------------------------------------------------------------------------------
void DrawGame(void)
{
	// 壁の描画処理
	DrawWall();

	// 地面の描画処理
	DrawMeshfild();

	// Xファイルの描画処理
	DrawPlayer();

	// ゴールの描画処理
	DrawBlock();

	// オブジェクト
	DrawObject();

	// オブジェクト
//	DrawObject_1();

	// 鍵の描画処理
	DrawKey();

	// 弾の描画処理
	DrawBullet();

	// タイマーの描画処理
	DrawTime();

	// ハートの描画処理
	DrawHeart();


	// 影の描画処理
	DrawShadow();

	if (g_bPause == true)
	{//ポーズされた

	 //ポーズの描画処理
		DrawPause();
	}
}

//-------------------------------------------------------------------------------
//	ポーズ処理
//-------------------------------------------------------------------------------
void SetPause(bool bPause)
{
	g_bPause = bPause;	//ポーズ中かどうか
}