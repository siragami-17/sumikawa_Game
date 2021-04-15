//--------------------------------------------------------------------------------
//
//	キーボードの処理 [input.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "keyboard.h"

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECTINPUT8 g_pInput = NULL;				//DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevkeyboard = NULL;	//入力デバイス(キーボード)へのポインタ
BYTE g_akeyState[256];						//キーボードの入力情報()ぜんかいの
BYTE g_akeyStateTrigger[256];				//キートリガー情報
BYTE g_akeyStateRelease[256];				//キーリリース情報
BYTE g_akeyStateRepeat[256];				//キーリピート情報
BYTE g_aCountRepeat[256];					//キーリピートカウンター

//-------------------------------------------------------------------------------
//	初期化処理
//-------------------------------------------------------------------------------
HRESULT Initkeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevkeyboard, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットの設定
	if (FAILED(g_pDevkeyboard -> SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モード設定
	if (FAILED(g_pDevkeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//アクセス権の取得
	g_pDevkeyboard->Acquire();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	終了処理
//-------------------------------------------------------------------------------
void  Uninitkeyboard(void)
{
	if (g_pDevkeyboard != NULL)
	{
		//アクセス権の破棄
		g_pDevkeyboard->Unacquire();
		g_pDevkeyboard->Release();
		g_pDevkeyboard = NULL;
	}

	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//-------------------------------------------------------------------------------
//	更新処理
//-------------------------------------------------------------------------------
void Updatakeyboard(void)
{
	//変数宣言
	BYTE aKeyState[256];
	
	//デバイスからデータを取得

	if (SUCCEEDED(g_pDevkeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nKey = 0; nKey < 256; nKey++)
		{
			
			g_akeyStateTrigger[nKey] = (g_akeyState[nKey] ^ aKeyState[nKey])&aKeyState[nKey];	//トリガー

			//g_akeyStateRelease[nKey] = (g_akeyState[nKey] ^ aKeyState[nKey]) ^ aKeyState[nKey];	//リリース

			//g_akeyStateRepeat[nKey] = (g_akeyState[nKey]aKeyState[nKey])aKeyState[nKey];

			g_akeyState[nKey] = aKeyState[nKey];	//キーを押しているかの情報保存(プレス)
		}
	}
	else
	{
		//アクセス権の取得
		g_pDevkeyboard->Acquire();
	}

}

//-------------------------------------------------------------------------------
//	キーボード情報の取得
//-------------------------------------------------------------------------------
bool GetkeyboardPress(int nkey)
{
	return(g_akeyState[nkey] & 0x80) ? true : false;
}

//-------------------------------------------------------------------------------
//	キーボードのトリガー情報
//-------------------------------------------------------------------------------
bool GetkeyboardTrgger(int nkey)
{
	return(g_akeyStateTrigger[nkey] & 0x80) ? true : false;
}