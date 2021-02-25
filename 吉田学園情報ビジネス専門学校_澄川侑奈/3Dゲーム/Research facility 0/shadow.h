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
// 影の構造体
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	bool bUse;				// 使用しているか
}Shadow;

//--------------------------------------------------------------------------------
// プロトタイプ宣言
//--------------------------------------------------------------------------------
HRESULT InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int SetShadow(D3DXVECTOR3 pos);		// 影の情報
//int SetShadow(D3DXVECTOR3 pos, float fWindth, float fDepth);		// 何番目か
void SetPositionShadow(int nIdx, D3DXVECTOR3 pos);					// 何番目,位置

Shadow *GetShadow(void);

#endif