//--------------------------------------------------------------------------------
//
//	プレスエンターの処理 [plessenter.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _PLESSENTER_H_
#define	_PLESSENTER_H_

#include "main.h"

//-------------------------------------------------------------------------------
//プロトタイプ宣言
//-------------------------------------------------------------------------------

HRESULT InitPressEnter(void);
void UninitPressEnter(void);
void UpdatePressEnter(void);
void DrawPressEnter(void);

#endif