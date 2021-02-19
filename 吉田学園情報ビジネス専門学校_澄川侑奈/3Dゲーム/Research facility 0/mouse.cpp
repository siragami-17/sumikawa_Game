//--------------------------------------------------------------------------------
//
//	mausuの処理 [bullet.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include <windows.h>
#include "mouse.h"

int mainMouse(void)
{

	POINT pt;
	//マウスの現在の座標を取得する
	GetCursorPos(&pt);

	//マウスの位置を+10移動する
	SetCursorPos(pt.x + 10, pt.y + 10);

	//マウスの左ボタンを押す　右はMOUSEEVENTF_RIGHTDOWN　中央はMOUSEEVENTF_MIDDLEDOWN
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

	//マウスの左ボタンを離す
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

	//ホイールを下向きに回す
	mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -1, 0);

	//ホイールを上向きに回す
	mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 1, 0);

	//文字を入力
	//HWND hWnd = WindowFromPoint(pt);
	//SendMessage(hWnd,WM_SETTEXT,0,(LPARAM)"文字列");

	return 0;
}
