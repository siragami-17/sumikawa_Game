//--------------------------------------------------------------------------------
//
//	�G�t�F�N�g�̏��� [effect.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _EFFECT_H_
#define	_EFFECT_H_

#include "main.h"

//-------------------------------------------------------------------------------
//	�G�t�F�N�g�̍\����
//-------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 size;		// �T�C�Y
	D3DXCOLOR color;		// �J���[

	bool bUse;				// �g�p���Ă��邩

}Effect;

//-------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//-------------------------------------------------------------------------------
HRESULT InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

Effect *GetEffect(void);								// �G�t�F�N�g�̏��
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move);		// �G�t�F�N�g�̐ݒu(nNam=��)
void SetVertexEffect(int nIdx);							// �G�t�F�N�g�̒��_���W

void SetColor(D3DXCOLOR color, int nIdx);				// �Z�b�g�J���[

void SetBom(D3DXVECTOR3 pos, float speed , int nNum);	// �ԉ΂݂����ȃG�t�F�N�g�ɂ��邠��

#endif		// 1�񂾂��ǂݍ��ނ悤�ɂ���
