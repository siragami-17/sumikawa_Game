//--------------------------------------------------------------------------------
//
//	�I�u�W�F�N�g�̏��� [block.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "object.h"			// �I�u�W�F�N�g
#include "keyboard.h"		// �L�[����
#include "player.h"			// �v���C���[
#include "result.h"			// ���U���g
#include "fade.h"			// �t�F�[�h
#include "collision.h"		// �����蔻��

//--------------------------------------------------------------------------------
//	�}�N����`
//--------------------------------------------------------------------------------
#define MAX_SIZE_OBJECT_X	(1000.0f)		// �T�C�Y_x
#define MAX_SIZE_OBJECT_Y	(400.0f)		// �T�C�Y_y
#define MAX_SIZE_OBJECT_Z	(10.0f)			// �T�C�Y_z

//--------------------------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------------------------
LPD3DXMESH g_pMeshObject = NULL;				// ���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatbject = NULL;			// �}�e���A���ւ̃|�C���^
D3DXMATRIX g_mtxWorldObject;					// ���[���h�}�g���b�N�X
DWORD g_nNumMatObject = 0;						// �}�e���A����

Object g_object[MAX_OBJECT];					// �I�u�W�F�N�g�̏��	
												
//--------------------------------------------------------------------------------
// ����������
//--------------------------------------------------------------------------------
HRESULT InitObject(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// �I�u�W�F�N�g�\���̂̏�����
		g_object[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);												// �ʒu
		g_object[nCntObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);												// ����
		g_object[nCntObject].blockVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);											// �ʒu
		g_object[nCntObject].size = D3DXVECTOR3(MAX_SIZE_OBJECT_X, MAX_SIZE_OBJECT_Y, MAX_SIZE_OBJECT_Z);		// �T�C�Y
		g_object[nCntObject].fWidth = 0.0f;																		// ��
		g_object[nCntObject].fHeight = 0.0f;																	// ����
		g_object[nCntObject].fLength = 0.0f;																	// ����
		g_object[nCntObject].fRadius = 50.0f;																	// ���a
		g_object[nCntObject].bUse = false;																		// �g�p���Ă��邩�ǂ���
	}

	// X�t�@�C���̓ǂݍ���
	// �I�u�W�F�N�g
	D3DXLoadMeshFromX("data/MODEL/wall.x",														// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatbject,																		// �}�e���A��(���_���)
		NULL,	
		&g_nNumMatObject,																		// �}�e���A����
		&g_pMeshObject);																		// ���b�V��(���_���)

		// �I�u�W�F�N�g�̐ݒu
		SetObject(D3DXVECTOR3(0.0f, 0.0f, 490.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(MAX_SIZE_OBJECT_X, MAX_SIZE_OBJECT_Y, MAX_SIZE_OBJECT_Z));
		SetObject(D3DXVECTOR3(490.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f), D3DXVECTOR3(10.0f, 400.0f, 1000.0f));
		SetObject(D3DXVECTOR3(-490.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DXToRadian (-90.0f), 0.0f), D3DXVECTOR3(10.0f, 400.0f, 1000.0f));
		SetObject(D3DXVECTOR3(0.0f, 0.0f, -490.0f), D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f), D3DXVECTOR3(MAX_SIZE_OBJECT_X, MAX_SIZE_OBJECT_Y, MAX_SIZE_OBJECT_Z));

		

	return S_OK;
}

//--------------------------------------------------------------------------------
// �I������
//--------------------------------------------------------------------------------
void UninitObject(void)
{
	// ���b�V���̊J��
	if (g_pMeshObject != NULL)
	{		 
		g_pMeshObject->Release();
		g_pMeshObject = NULL;
	}				  

	for (int nCntObject = 0; nCntObject < g_nNumMatObject; g_nNumMatObject++)
	{
		// �}�e���A���̊J��
		if (g_pBuffMatbject != NULL)
		{
			g_pBuffMatbject->Release();
			g_pBuffMatbject = NULL;
		}
	}
}

//--------------------------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------------------------
void UpdateObject(void)
{

}

//--------------------------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------------------------
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;					// �v�Z�p�̃}�g���b�N�X
	D3DMATERIAL9 matDef;							// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;								// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_object[nCntObject].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_object[nCntObject].mtxWorld);

			// �����𔽉f(y,x,z)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_object[nCntObject].rot.y, g_object[nCntObject].rot.x, g_object[nCntObject].rot.z);
			D3DXMatrixMultiply(&g_object[nCntObject].mtxWorld, &g_object[nCntObject].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_object[nCntObject].pos.x, g_object[nCntObject].pos.y, g_object[nCntObject].pos.z);
			D3DXMatrixMultiply(&g_object[nCntObject].mtxWorld, &g_object[nCntObject].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_object[nCntObject].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatbject->GetBufferPointer();


			for (unsigned int nCutMat = 0; nCutMat < g_nNumMatObject; nCutMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				// ���f��(�p�[�c)�̕`��
				g_pMeshObject->DrawSubset(nCutMat);
			}

			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//--------------------------------------------------------------------------------
//	�I�u�W�F�N�g���̎擾
//--------------------------------------------------------------------------------
Object *Getobject(void)
{
	return &g_object[0];		// �I�u�W�F�N�g���̐擪�A�h���X��Ԃ�
}

//--------------------------------------------------------------------------------
//	�I�u�W�F�N�g���̎擾
//--------------------------------------------------------------------------------
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_object[nCntObject].bUse == false)
		{// �I�u�W�F�N�g���g���Ă��Ȃ��Ƃ�
			g_object[nCntObject].pos = pos;

			g_object[nCntObject].rot = rot;

			g_object[nCntObject].size = size;

			g_object[nCntObject].bUse = true;

			return;
		}
	}
}