//--------------------------------------------------------------------------------
//
//	XInputの処理 [Xcontroller.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _XCONTROLLE_H
#define	_XCONTROLLE_H

#include "main.h"

//-------------------------------------------------------------------------------
// 構造体
//-------------------------------------------------------------------------------
typedef struct
{
	bool bPless = false;			// ボタン
	bool bPlessLStick = false;		// Lスティック
	float fAngle;
}XinputGamepad;

//-------------------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------------------
void UpdateXcontroller(void);
void XinputButton(void);		// ボタンの処理
void XinputStick(void);			// スティックの処理

//XINPUT_STATE*GetXcontroller(void);

#endif