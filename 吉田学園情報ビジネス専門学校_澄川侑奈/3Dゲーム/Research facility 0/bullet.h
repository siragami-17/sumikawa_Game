//--------------------------------------------------------------------------------
//
//	�e�̏��� [bullet.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _BULLET_H_
#define	_BULLET_H_

#include "main.h"

//-------------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------------------
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SetBullet(D3DXVECTOR3 pos,		// �e�̈ʒu
	D3DXVECTOR3 move,				// �e�̈ړ���
	int nLife);						// �e�̐�

#endif
