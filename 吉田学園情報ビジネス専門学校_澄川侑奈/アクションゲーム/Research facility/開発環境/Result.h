//--------------------------------------------------------------------------------
//
//	リザルト画面の処理 [Result.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _RESULT_H
#define	_RESULT_H

#include "main.h"

//-------------------------------------------------------------------------------
//プロトタイプ宣言
//-------------------------------------------------------------------------------
HRESULT InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetResult(bool bClear);

#endif