//--------------------------------------------------------------------------------
//
//	Xinoutの処理 [Xcontroller.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Xcontroller.h"
#include "fade.h"

//--------------------------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------------------------
XINPUT_STATE g_state;		// Xinputの情報

//-------------------------------------------------------------------------------
// コントローラーの更新処理
//-------------------------------------------------------------------------------
void UpdateXcontroller(void)
{
	ZeroMemory(&g_state, sizeof(XINPUT_STATE));

	//XInputからコントローラーの状態を取得する
	DWORD dwResult = XInputGetState(0, &g_state);

	if (dwResult == ERROR_SUCCESS)
	{// コントローラが接続された
		
	}
	else
	{// コントローラが接続されてない
		
	}

	if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{// A ボタンが押された
		SetFade(FADE_OUT, MODE_GAME_00);
	}
}

