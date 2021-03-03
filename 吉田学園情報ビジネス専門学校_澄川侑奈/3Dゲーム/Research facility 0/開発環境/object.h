//--------------------------------------------------------------------------------
//
//	�u���b�N�̏��� [object.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _OBJECT_H_
#define	_OBJECT_H_

#include "main.h"

//--------------------------------------------------------------------------------
//	�}�N����`
//--------------------------------------------------------------------------------
#define MAX_OBJECT		(7)		// �ǂݍ��ރp�[�c��

//--------------------------------------------------------------------------------
//	�񋓌^
//--------------------------------------------------------------------------------
typedef enum
{// �I�u�W�F�N�g�̎��
	OBJECT_WOLL = 0,	// ��
	OBJECT_FENCE,		// ��
	OBJECT_MAX
}OBJECT_TYPE;

//--------------------------------------------------------------------------------
// �}�e���A���̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	LPD3DXMESH g_pMeshObject;			// ���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER g_pBuffMatbject;		// �}�e���A���ւ̃|�C���^
	DWORD g_nNumMatObject;				// �}�e���A����

}MODEL_DATA;

//--------------------------------------------------------------------------------
// �I�u�W�F�N�g�̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;							// �ʒu
	D3DXVECTOR3 blockVec;						// �u���b�N�ƃv���C���[�̃x�N�g��
	D3DXVECTOR3 rot;							// ����
	D3DXVECTOR3 move;							// �ړ���
	D3DXVECTOR3 size;							// �T�C�Y
	D3DXMATRIX mtxWorld;						// ���[���h�}�g���b�N�X
	OBJECT_TYPE type;							// �I�u�W�F�N�g�̎��

	float fWidth;								// ��
	float fHeight;								// ����
	float fLength;								// ����
	float fRadius;								// ���a

	bool bUse;									// �g�p���Ă��邩�ǂ���

	MODEL_DATA GetModel[OBJECT_MAX];			// �}�e���A���̏��

}Object;

//--------------------------------------------------------------------------------
// �z�u�̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	MODEL_DATA GetModel[OBJECT_MAX];			// �}�e���A���̏��
	Object Getobject[MAX_OBJECT];				// �I�u�W�F�N�g�̏��

}Object_Set;

//--------------------------------------------------------------------------------
// �v���g�^�C�v�錾
//--------------------------------------------------------------------------------
HRESULT InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);

Object *Getobject(void);				// �I�u�W�F�N�g�̏��

void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, OBJECT_TYPE type);		// �I�u�W�F�N�g�̐ݒ�

#endif