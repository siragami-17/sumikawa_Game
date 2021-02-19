//--------------------------------------------------------------------------------
//
//	�v���C���[�̏��� [player.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _PLAYER_H_
#define	_PLAYER_H_

#include "main.h"

//--------------------------------------------------------------------------------
// ���f���̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	LPD3DXMESH pMesh;			// ���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;		// �}�e���A���ւ̃|�C���^
	DWORD nNumMat;				// �}�e���A���̐�
	D3DXVECTOR3 pos;			// �ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 rot;			// ����
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	int nIdModelParent;			// �e�̃��f���̃C���f�b�N�X
}Model;

//--------------------------------------------------------------------------------
// �v���C���[�̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;			// ���̈ʒu
	D3DXVECTOR3 posOld;			// �̂̈ʒu
	D3DXVECTOR3 rot;			// ����
	D3DXVECTOR3 move;			// �ړ���
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X

	bool bJump;				//�W�����v�����ǂ���

	Model aModel[14];			// ���f��(�p�[�c)
	int nNumModel;				// ���f��(�p�[�c)��
}Player;

//--------------------------------------------------------------------------------
// �v���g�^�C�v�錾
//--------------------------------------------------------------------------------
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

Player *GetPlayer(void);

#endif