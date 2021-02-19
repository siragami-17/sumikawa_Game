//--------------------------------------------------------------------------------
//
//	影の処理 [shadow.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _SHADOW_H_
#define	_SHADOW_H_

#include "main.h"

//--------------------------------------------------------------------------------
// プロトタイプ宣言
//--------------------------------------------------------------------------------
HRESULT InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int SetShadow(D3DXVECTOR3 pos, float fWindth, float fDepth);		// 何番目か
void SetPositionShadow(int nIdx, D3DXVECTOR3 pos);					// 何番目,位置

#endif