//--------------------------------------------------------------------------------
//
//	�n�ʂ̏��� [meshfild.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _MESHFILD_H_
#define	_MESHFILD_H_

#include "main.h"

//--------------------------------------------------------------------------------
// �n�ʂ̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffMeshfild = NULL;		// �|���S���̒��_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pIdxBuffMeshField = NULL;		// �C���f�b�N�X�̃o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9 pTextureMeshfild = NULL;				// �e�N�X�`���̃|�C���^

	D3DXVECTOR3 pos;								// �ʒu
	D3DXVECTOR3 rot;								// �@���x�N�g��(����)
	D3DXMATRIX mtxWorld;							// ���[���h�}�g���b�N�X

	bool bUse;												// �g�p���Ă��邩

}Meshfild;

//--------------------------------------------------------------------------------
// �v���g�^�C�v�錾
//--------------------------------------------------------------------------------
HRESULT InitMeshfild(void);
void UninitMeshfild(void);
void UpdateMeshfild(void);
void DrawMeshfild(void);

Meshfild *GetMeshfild(void);

#endif