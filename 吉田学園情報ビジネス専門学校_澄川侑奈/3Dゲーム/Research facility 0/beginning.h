//--------------------------------------------------------------------------------
//
//	始まりの画面の処理 [beginninig.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _BEGINNING_H_
#define	_BEGINNING_H_

#include "main.h"

//-------------------------------------------------------------------------------
//プロトタイプ宣言
//-------------------------------------------------------------------------------
HRESULT InitBeginning(void);
void UninitBeginning(void);
void UpdateBeginning(void);
void DrawBeginning(void);

void SetPause(bool bPause);		// ポーズ

#endif