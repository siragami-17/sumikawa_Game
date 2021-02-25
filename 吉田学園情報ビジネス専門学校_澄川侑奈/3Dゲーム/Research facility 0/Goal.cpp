//--------------------------------------------------------------------------------
//
//	�S�[���̏��� [Goal.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Goal.h"			// �S�[��
#include "keyboard.h"		// �L�[����
#include "player.h"			// �v���C���[
#include "result.h"			// ���U���g
#include "fade.h"			// �t�F�[�h

//--------------------------------------------------------------------------------
//	�}�N����`
//--------------------------------------------------------------------------------
#define MAX_MOVE	(3)			// �ړ���
#define MAX_ROT		(0.1f)		// ����

//--------------------------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------------------------
Goal g_goal;										// �u���b�N�̏��	
												
//--------------------------------------------------------------------------------
// ����������
//--------------------------------------------------------------------------------
HRESULT InitGoal(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �p�[�c���̏�����
	g_goal.nNumModel = MAX_GOAL;

	// X�t�@�C���̓ǂݍ���
	// �u���b�N
	D3DXLoadMeshFromX("data/MODEL/goal.x",						// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_goal.aModel[0].pBuffMat,							// �}�e���A��(���_���)
		NULL,
		&g_goal.aModel[0].nNumMat,								// �}�e���A����
		&g_goal.aModel[0].pMesh);								// ���b�V��(���_���)

	// �e�p�[�c�̊K�w�\���ݒ�
	// ��
	g_goal.aModel[0].nldModelParent = -1;						// �e���f���̃C���f�b�N�X��ݒ�
	g_goal.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 500.0f);	// �ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_goal.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����̏����ݒ�


	// �u���b�N�̍\���̂̏�����
	g_goal.pos = D3DXVECTOR3(0.0f, 0.0f, 650.0f);				// �ʒu�̏����ݒ�
	g_goal.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �����̏����ݒ�
	g_goal.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ړ��ʂ̏����ݒ�
	g_goal.fHeight = 0.0f;										// �����̏����ݒ�
	g_goal.fWidth = 0.0f;										// ���̏����ݒ�
	g_goal.bUse = true;										// �g�p���Ă��邩

	return S_OK;
}

//--------------------------------------------------------------------------------
// �I������
//--------------------------------------------------------------------------------
void UninitGoal(void)
{
	for (int nCutModel = 0; nCutModel < g_goal.nNumModel; nCutModel++)
	{
		// ���b�V���̊J��
		if (g_goal.aModel[nCutModel].pMesh != NULL)
		{
			g_goal.aModel[nCutModel].pMesh->Release();
			g_goal.aModel[nCutModel].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_goal.aModel[nCutModel].pBuffMat != NULL)
		{
			g_goal.aModel[nCutModel].pBuffMat->Release();
			g_goal.aModel[nCutModel].pBuffMat = NULL;
		}
	}
}

//--------------------------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------------------------
void UpdateGoal(void)
{
	// �v���C���[�̏��
	Player * pPlayer;
	pPlayer = GetPlayer();

	// �u���b�N�ƃv���C���[�̓����蔻��
	if (g_goal.bUse == true)
	{// �u���b�N������Ƃ�
		if (pPlayer->pos.x - (50) < g_goal.pos.x + (10) &&
			pPlayer->pos.x + (50) > g_goal.pos.x - (10) &&
			pPlayer->pos.z - (150) < g_goal.pos.z + (50) &&
			pPlayer->pos.z + (150) > g_goal.pos.z - (50))
		{// �u���b�N�ƃv���C���[����������
			if (pPlayer->bGetKey == true)
			{
				if (GetkeyboardTrgger(DIK_RETURN) == true)
				{
					// ���U���g�ɂƂ�
					SetResult(true);					//�N���A���
					SetFade(FADE_OUT, MODE_RESULT);
				}
			}

		}
	}
}

//--------------------------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------------------------
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;					// �v�Z�p�̃}�g���b�N�X
	D3DMATERIAL9 matDef;							// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;								// �}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_goal.mtxWorld);

	// �����𔽉f(y,x,z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_goal.rot.y, g_goal.rot.x, g_goal.rot.z);
	D3DXMatrixMultiply(&g_goal.mtxWorld, &g_goal.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_goal.pos.x, g_goal.pos.y, g_goal.pos.z);
	D3DXMatrixMultiply(&g_goal.mtxWorld, &g_goal.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_goal.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCutModel = 0; nCutModel < g_goal.nNumModel; nCutModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;		// �v�Z�p�}�g���b�N�X

		D3DXMATRIX mtxParent;						// �e�̃}�g���b�N�X

		// �e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_goal.aModel[nCutModel].mtxWorld);

		// �����𔽉f(y,x,z)
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_goal.aModel[nCutModel].rot.y, g_goal.aModel[nCutModel].rot.x, g_goal.aModel[nCutModel].rot.z);
		D3DXMatrixMultiply(&g_goal.aModel[nCutModel].mtxWorld, &g_goal.aModel[nCutModel].mtxWorld, &mtxRotModel);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_goal.aModel[nCutModel].pos.x, g_goal.aModel[nCutModel].pos.y, g_goal.aModel[nCutModel].pos.z);
		D3DXMatrixMultiply(&g_goal.aModel[nCutModel].mtxWorld, &g_goal.aModel[nCutModel].mtxWorld, &mtxTransModel);
		
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_goal.aModel[nCutModel].mtxWorld);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_goal.aModel[nCutModel].pBuffMat->GetBufferPointer();

		for (int nCutMat = 0; nCutMat < (int)g_goal.aModel[nCutModel].nNumMat; nCutMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			// ���f��(�p�[�c)�̕`��
			g_goal.aModel[nCutModel].pMesh->DrawSubset(nCutMat);
		}
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//--------------------------------------------------------------------------------
//	�u���b�N���̎擾
//--------------------------------------------------------------------------------
Goal *GetGoal(void)
{
	return &g_goal;			// �u���b�N���̐擪�A�h���X��Ԃ�
}