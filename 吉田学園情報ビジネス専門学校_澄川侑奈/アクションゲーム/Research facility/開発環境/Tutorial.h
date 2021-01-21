//--------------------------------------------------------------------------------
//
//	チュートリアル画面処理 [Tutorial.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _TUTORIAL_H
#define	_TUTORIAL_H

#include "main.h"

//-------------------------------------------------------------------------------
//プロトタイプ宣言
//-------------------------------------------------------------------------------
HRESULT InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void SetTutorial(bool bSelect);

#endif