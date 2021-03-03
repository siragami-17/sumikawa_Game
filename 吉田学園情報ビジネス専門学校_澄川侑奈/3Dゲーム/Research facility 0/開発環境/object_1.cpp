//--------------------------------------------------------------------------------
//
//	�I�u�W�F�N�g�̏��� [block.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "object_1.h"		// �I�u�W�F�N�g
#include "keyboard.h"		// �L�[����
#include "player.h"			// �v���C���[
#include "result.h"			// ���U���g
#include "fade.h"			// �t�F�[�h
#include "collision.h"		// �����蔻��

//--------------------------------------------------------------------------------
//	�}�N����`
//--------------------------------------------------------------------------------
#define MAX_SIZE_OBJECT_1_X	(1000.0f)		// �T�C�Y_x
#define MAX_SIZE_OBJECT_1_Y	(400.0f)		// �T�C�Y_y
#define MAX_SIZE_OBJECT_1_Z	(10.0f)			// �T�C�Y_z

//--------------------------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------------------------
LPD3DXMESH g_pMeshObject_1 = NULL;				// ���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatbject_1 = NULL;			// �}�e���A���ւ̃|�C���^
D3DXMATRIX g_mtxWorldObject_1;					// ���[���h�}�g���b�N�X
DWORD g_nNumMatObject_1 = 0;						// �}�e���A����

Object_1 g_object[MAX_OBJECT_1];					// �I�u�W�F�N�g�̏��	
												
//--------------------------------------------------------------------------------
// ����������
//--------------------------------------------------------------------------------
HRESULT InitObject_1(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntObject_1 = 0; nCntObject_1 < MAX_OBJECT_1; nCntObject_1++)
	{
		// �I�u�W�F�N�g�\���̂̏�����
		g_object[nCntObject_1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);												// �ʒu
		g_object[nCntObject_1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);												// ����
		g_object[nCntObject_1].blockVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);											// �ʒu
		g_object[nCntObject_1].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �T�C�Y
		g_object[nCntObject_1].fWidth = 0.0f;																		// ��
		g_object[nCntObject_1].fHeight = 0.0f;																	// ����
		g_object[nCntObject_1].fLength = 0.0f;																	// ����
		g_object[nCntObject_1].fRadius = 50.0f;																	// ���a
		g_object[nCntObject_1].bUse = false;																		// �g�p���Ă��邩�ǂ���
	}

	// X�t�@�C���̓ǂݍ���
	// �I�u�W�F�N�g
	D3DXLoadMeshFromX("data/MODEL/Block_2.x",														// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatbject_1,																		// �}�e���A��(���_���)
		NULL,	
		&g_nNumMatObject_1,																		// �}�e���A����
		&g_pMeshObject_1);																		// ���b�V��(���_���)

		// �I�u�W�F�N�g�̐ݒu
		SetObject_1(D3DXVECTOR3(100.0f, 0.0f, -420.0f),D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f), D3DXVECTOR3(15.0f, 400.0f, 150.0f));
		SetObject_1(D3DXVECTOR3(-100.0f, 0.0f, -420.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f), D3DXVECTOR3(15.0f, 400.0f, 150.0f));

		SetObject_1(D3DXVECTOR3(-170.0f, 0.0f, -350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(150.0f, 400.0f, 15.0f));

		

	return S_OK;
}

//--------------------------------------------------------------------------------
// �I������
//--------------------------------------------------------------------------------
void UninitObject_1(void)
{
	// ���b�V���̊J��
	if (g_pMeshObject_1 != NULL)
	{
		g_pMeshObject_1->Release();
		g_pMeshObject_1 = NULL;
	}


	// �}�e���A���̊J��
	if (g_pBuffMatbject_1 != NULL)
	{
		g_pBuffMatbject_1->Release();
		g_pBuffMatbject_1 = NULL;
	}

}

//--------------------------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------------------------
void UpdateObject_1(void)
{

}

//--------------------------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------------------------
void DrawObject_1(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;					// �v�Z�p�̃}�g���b�N�X
	D3DMATERIAL9 matDef;							// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;								// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntObject_1 = 0; nCntObject_1 < MAX_OBJECT_1; nCntObject_1++)
	{
		if (g_object[nCntObject_1].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_object[nCntObject_1].mtxWorld);

			// �����𔽉f(y,x,z)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_object[nCntObject_1].rot.y, g_object[nCntObject_1].rot.x, g_object[nCntObject_1].rot.z);
			D3DXMatrixMultiply(&g_object[nCntObject_1].mtxWorld, &g_object[nCntObject_1].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_object[nCntObject_1].pos.x, g_object[nCntObject_1].pos.y, g_object[nCntObject_1].pos.z);
			D3DXMatrixMultiply(&g_object[nCntObject_1].mtxWorld, &g_object[nCntObject_1].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_object[nCntObject_1].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatbject_1->GetBufferPointer();


			for (unsigned int nCutMat = 0; nCutMat < g_nNumMatObject_1; nCutMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				// ���f��(�p�[�c)�̕`��
				g_pMeshObject_1->DrawSubset(nCutMat);
			}

			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//--------------------------------------------------------------------------------
//	�I�u�W�F�N�g���̎擾
//--------------------------------------------------------------------------------
Object_1 *Getobject_1(void)
{
	return &g_object[0];		// �I�u�W�F�N�g���̐擪�A�h���X��Ԃ�
}

//--------------------------------------------------------------------------------
//	�I�u�W�F�N�g���̎擾
//--------------------------------------------------------------------------------
void SetObject_1(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	for (int nCntObject_1 = 0; nCntObject_1 < MAX_OBJECT_1; nCntObject_1++)
	{
		if (g_object[nCntObject_1].bUse == false)
		{// �I�u�W�F�N�g���g���Ă��Ȃ��Ƃ�
			g_object[nCntObject_1].pos = pos;

			g_object[nCntObject_1].rot = rot;

			g_object[nCntObject_1].size = size;

			g_object[nCntObject_1].bUse = true;

			return;
		}
	}
}