//--------------------------------------------------------------------------------
//
//	�u���b�N�̏��� [object.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _OBJECT_1_H_
#define	_OBJECT_1_H_

#include "main.h"

//--------------------------------------------------------------------------------
//	�}�N����`
//--------------------------------------------------------------------------------
#define MAX_OBJECT_1		(10)		// �ǂݍ��ރp�[�c��

//--------------------------------------------------------------------------------
// �u���b�N�̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 blockVec;			// �u���b�N�ƃv���C���[�̃x�N�g��
	D3DXVECTOR3 rot;				// ����
	D3DXVECTOR3 move;				// �ړ���
	D3DXVECTOR3 size;				// �T�C�Y
	D3DXMATRIX mtxWorld;			// ���[���h�}�g���b�N�X

	float fWidth;					// ��
	float fHeight;					// ����
	float fLength;					// ����
	float fRadius;					// ���a

	bool bUse;						// �g�p���Ă��邩�ǂ���

}Object_1;

//--------------------------------------------------------------------------------
// �v���g�^�C�v�錾
//--------------------------------------------------------------------------------
HRESULT InitObject_1(void);
void UninitObject_1(void);
void UpdateObject_1(void);
void DrawObject_1(void);

Object_1 *Getobject_1(void);				// �I�u�W�F�N�g�̏��

void SetObject_1(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);		// �I�u�W�F�N�g�̐ݒ�

#endif