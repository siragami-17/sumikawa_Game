//--------------------------------------------------------------------------------
//
//	弾の処理 [bullet.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _BULLET_H_
#define	_BULLET_H_

#include "main.h"

//-------------------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------------------
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SetBullet(D3DXVECTOR3 pos,		// 弾の位置
	D3DXVECTOR3 move,				// 弾の移動量
	int nLife);						// 弾の数

#endif
