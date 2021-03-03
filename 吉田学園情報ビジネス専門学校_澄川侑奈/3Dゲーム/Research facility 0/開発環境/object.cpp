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
Object g_object[MAX_OBJECT];						// �I�u�W�F�N�g�̏��	

// �񋓌^
char *g_apFilename[OBJECT_MAX] =
{// �t�@�C����
	{"data/MODEL/wall.x"},							// ��
	{"data/MODEL/Block_2.x" },						// ��
};
												
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
		g_object[nCntObject].type = OBJECT_WOLL;																// �I�u�W�F�N�g�̎��


		for (int nCntType = 0; nCntType < OBJECT_MAX; nCntType++)
		{// �����ǂݍ���
			// X�t�@�C���̓ǂݍ���

			// �I�u�W�F�N�g
			D3DXLoadMeshFromX((LPCSTR)g_apFilename[nCntType],													// �ǂݍ���X�t�@�C����
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_object[nCntObject].GetModel[nCntType].g_pBuffMatbject,										// �}�e���A��(���_���)
				NULL,
				&g_object[nCntObject].GetModel[nCntType].g_nNumMatObject,										// �}�e���A����
				&g_object[nCntObject].GetModel[nCntType].g_pMeshObject);
		}
	}
	// �I�u�W�F�N�g�̐ݒu
	// ��
	SetObject(D3DXVECTOR3(0.0f, 0.0f, 490.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(MAX_SIZE_OBJECT_X, MAX_SIZE_OBJECT_Y, MAX_SIZE_OBJECT_Z),OBJECT_WOLL);
	SetObject(D3DXVECTOR3(490.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f), D3DXVECTOR3(10.0f, 400.0f, 1000.0f), OBJECT_WOLL);
	SetObject(D3DXVECTOR3(-490.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DXToRadian(-90.0f), 0.0f), D3DXVECTOR3(10.0f, 400.0f, 1000.0f), OBJECT_WOLL);
	SetObject(D3DXVECTOR3(0.0f, 0.0f, -490.0f), D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f), D3DXVECTOR3(MAX_SIZE_OBJECT_X, MAX_SIZE_OBJECT_Y, MAX_SIZE_OBJECT_Z), OBJECT_WOLL);

	// ��
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -420.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f), D3DXVECTOR3(15.0f, 400.0f, 150.0f), OBJECT_FENCE);
	SetObject(D3DXVECTOR3(-100.0f, 0.0f, -420.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f), D3DXVECTOR3(15.0f, 400.0f, 150.0f), OBJECT_FENCE);
	
	SetObject(D3DXVECTOR3(-170.0f, 0.0f, -350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(150.0f, 400.0f, 15.0f), OBJECT_FENCE);

	return S_OK;
}

//--------------------------------------------------------------------------------
// �I������
//--------------------------------------------------------------------------------
void UninitObject(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{// �z�u���郂�f����
		for (int nCntType = 0; nCntType < OBJECT_MAX; nCntType++)
		{// �ǂݍ��ރ��f����
			// ���b�V���̊J��
			if (g_object[nCntObject].GetModel[nCntType].g_pMeshObject != NULL)
			{
				g_object[nCntObject].GetModel[nCntType].g_pMeshObject->Release();
				g_object[nCntObject].GetModel[nCntType].g_pMeshObject = NULL;
			}

			// �}�e���A���̊J��
			if (g_object[nCntObject].GetModel[nCntType].g_pBuffMatbject != NULL)
			{
				g_object[nCntObject].GetModel[nCntType].g_pBuffMatbject->Release();
				g_object[nCntObject].GetModel[nCntType].g_pBuffMatbject = NULL;

			}
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
  			pMat = (D3DXMATERIAL*)g_object[nCntObject].GetModel[g_object[nCntObject].type].g_pBuffMatbject->GetBufferPointer();

			for (unsigned int nCutMat = 0; nCutMat <g_object[nCntObject].GetModel[g_object[nCntObject].type].g_nNumMatObject; nCutMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				// ���f��(�p�[�c)�̕`��
				g_object[nCntObject].GetModel[g_object[nCntObject].type].g_pMeshObject->DrawSubset(nCutMat);
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
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, OBJECT_TYPE type)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{// �z�u���郂�f����
		if (g_object[nCntObject].bUse == false)
		{// �I�u�W�F�N�g���g���Ă��Ȃ��Ƃ�
			g_object[nCntObject].pos = pos;

			g_object[nCntObject].rot = rot;

			g_object[nCntObject].size = size;

			g_object[nCntObject].type = type;

			g_object[nCntObject].bUse = true;

			return;
		}
	}
}