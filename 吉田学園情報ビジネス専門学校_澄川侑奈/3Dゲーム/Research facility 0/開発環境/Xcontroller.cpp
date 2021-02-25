//--------------------------------------------------------------------------------
//
//	XInputの処理 [Xcontroller.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Xcontroller.h"		// Xinput
#include "camera.h"				// カメラ
#include "player.h"				// プレイヤー
#include "keyboard.h"			// キーボード
#include "fade.h"				// フェード

//--------------------------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------------------------
XINPUT_STATE g_state;		// Xinputの情報

XinputGamepad g_Xinput;		// ゲームパットの情報

//-------------------------------------------------------------------------------
// Xinputの更新処理
//-------------------------------------------------------------------------------
void UpdateXcontroller(void)
{
	ZeroMemory(&g_state, sizeof(XINPUT_STATE));

	//XInputからコントローラーの状態を取得する
	DWORD dwResult = XInputGetState(0, &g_state);

	if (dwResult == ERROR_SUCCESS)
	{// コントローラが接続された
		XinputButton();		// ボタンの処理
		XinputStick();		// スティックの処理
	}
	else
	{// コントローラが接続されてない

	}
}

//-------------------------------------------------------------------------------
// ボタンの処理
//-------------------------------------------------------------------------------
void XinputButton(void)
{
	// プレイヤーの情報をもらう
	Player * pPlayer = GetPlayer();

	if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{// A ボタンが押された
		SetFade(FADE_OUT, MODE_GAME);
	}
}

//-------------------------------------------------------------------------------
// ステックの処理
//-------------------------------------------------------------------------------
void XinputStick(void)
{
	// カメラの情報をもらう
	Camera * pCamer = GetCamera();
	// プレイヤーの情報をもらう
	Player * pPlayer = GetPlayer();

	// デットゾーンの設定
	if ((g_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		g_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(g_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		g_state.Gamepad.sThumbLX = 0;
		g_state.Gamepad.sThumbLY = 0;
	}

	// JOYPADのスティック入力
	if (g_state.Gamepad.sThumbLX != 0 || g_state.Gamepad.sThumbLY != 0)
	{//  スティックの入力角度
		g_Xinput.fAngle = atan2f((float)g_state.Gamepad.sThumbLX, (float)g_state.Gamepad.sThumbLY * -1);

		// スティックの入力伝える
		g_Xinput.bPlessLStick = true;

		// 移動量
		pPlayer->move.x -= 1 * sinf(pCamer->rot.y - g_Xinput.fAngle);		// X軸
		pPlayer->move.z -= 1 * cosf(pCamer->rot.y - g_Xinput.fAngle);		// Z軸
	}
}

//-------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------
#if 0

XINPUT_STATE * GetXcontroller(void)
{

}

#endif
