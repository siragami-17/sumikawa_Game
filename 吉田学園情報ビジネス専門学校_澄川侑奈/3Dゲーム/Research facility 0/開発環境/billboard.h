//--------------------------------------------------------------------------------
//
//	ビルボードの処理 [billboard.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _BILLBOARD_H_
#define	_BILLBOARD_H_

#include "main.h"

//--------------------------------------------------------------------------------
// プロトタイプ宣言
//--------------------------------------------------------------------------------
HRESULT InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);

void SetBillboard(D3DXVECTOR3 pos);

#endif