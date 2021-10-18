//--------------------------------------------------------------------------------
//
//	ステージ1の背景処理 [background_00.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _BACKGROUND_00_H
#define	_BACKGROUND_00_H

#include "main.h"

//-------------------------------------------------------------------------------
//プロトタイプ宣言
//-------------------------------------------------------------------------------
HRESULT Initbackground_00(void);
void Uninitbackground_00(void);
void Updatebackground_00(void);
void Drawbackground_00(void);
void Setbackground_00(bool bSelect);

#endif