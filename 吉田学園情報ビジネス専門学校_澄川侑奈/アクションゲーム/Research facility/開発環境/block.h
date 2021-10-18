//-------------------------------------------------------------------
//
// �u���b�N�w�b�_�[ (block.h)
// Author:Yuna Sumikawa
//
//-------------------------------------------------------------------
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//-------------------------------------------------------------------
// �u���b�N�̏��
//-------------------------------------------------------------------
typedef enum
{
	BLOCKSTATE_NORMAL = 0,	// �n��
	BLOCKSTATE_FLOAT,		// �����Ă鏰
	BLOCKSTATE_RIFT,		// �㉺�ɓ�����
	BLOCKSTATE_MAX,
}BLOCKSTATE;

//-------------------------------------------------------------------
// �u���b�N�̎��
//-------------------------------------------------------------------
typedef enum
{
	BLOCKTYPE_CATCH = 0,		// �͂߂�
	BLOCKTYPE_NOT_CATCH,		// �͂߂Ȃ�
	BLOCKTYPE_MAX,
}BLOCKTYPE;

//-------------------------------------------------------------------
// �Փ˂����͉̂���
//-------------------------------------------------------------------
typedef enum
{
	COLLISIONINFO_PLAYER = 0,	// �v���C���[
	COLLISIONINFO_FRUITS,		// �t���[�c
	COLLISIONINFO_ENEMY,		// �G
	COLLISIONINFO_MAX,
}COLLISIONINFO;

//-------------------------------------------------------------------
// �\���̂̒�`
//-------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// ���W
	D3DXVECTOR3 posOld;	// �O�̍��W
	D3DXVECTOR3 move;	// �ړ���
	int nTimer;			// ���ԂŐ܂�Ԃ�
	float fWidth;		// ��
	float fHeight;		// ����
	float fTexU;		// �e�N�X�`�����WU�̒l
	float fTexV;		// �e�N�X�`�����WV�̒l
	BLOCKSTATE state;	// �u���b�N�̏��
	BLOCKTYPE type;		// �u���b�N�̎��
	bool bChach;		// ���܂�Ă���ǂ���
	bool bUse;			// �g�p���Ă��邩�ǂ���
}BLOCK;

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
HRESULT InitBlock(void);															// �u���b�N�̏���������
void UninitBlock(void);																// �u���b�N�̏I������
void UpdateBlock(void);																// �u���b�N�̍X�V����
void DrawBlock(void);																// �u���b�N�̕`�揈��
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight,
	float fTexU, float fTexV, BLOCKSTATE state, BLOCKTYPE type);					// �u���b�N�̔z�u
void SetVertexBlock(int nIdx);														// ���_���W�̐ݒ�
BLOCK *GetBlock(void);																// �u���b�N���̎擾
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove,
	float fWidth, float fHeight, COLLISIONINFO info);								// �u���b�N�̓����蔻��
void LandBlock(int nCntBlock, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, float fHeight);	// ���̃u���b�N�̏�ɏ���Ă��邩
void CollisionBlockSide(D3DXVECTOR3 *pMove, COLLISIONINFO info);					// �u���b�N�̉��ɓ��������Ƃ�

void SetBlock(D3DXVECTOR3 pos,
	float fWidth,
	float fHeight,
	BLOCKTYPE type);

bool ColBlock(int nCntBlock);

#endif
