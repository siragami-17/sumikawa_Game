//--------------------------------------------------------------------------------
//
//	�u���b�N�̏��� [block.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "block.h"			// �u���b�N
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
Block g_block;										// �u���b�N�̏��	
												
//--------------------------------------------------------------------------------
// ����������
//--------------------------------------------------------------------------------
HRESULT InitBlock(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �p�[�c���̏�����
	g_block.nNumModel = MAX_BLOCK;

	// X�t�@�C���̓ǂݍ���
	// �u���b�N
	D3DXLoadMeshFromX("data/MODEL/block.x",						// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_block.aModel[0].pBuffMat,							// �}�e���A��(���_���)
		NULL,
		&g_block.aModel[0].nNumMat,								// �}�e���A����
		&g_block.aModel[0].pMesh);								// ���b�V��(���_���)

	// �e�p�[�c�̊K�w�\���ݒ�
	// ��
	g_block.aModel[0].nldModelParent = -1;						// �e���f���̃C���f�b�N�X��ݒ�
	g_block.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 500.0f);	// �ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_block.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����̏����ݒ�



	// �u���b�N�̍\���̂̏�����
	g_block.pos = D3DXVECTOR3(0.0f, 0.0f, 650.0f);				// �ʒu�̏����ݒ�
	g_block.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �����̏����ݒ�
	g_block.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ړ��ʂ̏����ݒ�
	g_block.fHeight = 0.0f;										// �����̏����ݒ�
	g_block.fWidth = 0.0f;										// ���̏����ݒ�
	g_block.bUse = true;										// �g�p���Ă��邩

	return S_OK;
}

//--------------------------------------------------------------------------------
// �I������
//--------------------------------------------------------------------------------
void UninitBlock(void)
{
	for (int nCutModel = 0; nCutModel < g_block.nNumModel; nCutModel++)
	{
		// ���b�V���̊J��
		if (g_block.aModel[nCutModel].pMesh != NULL)
		{
			g_block.aModel[nCutModel].pMesh->Release();
			g_block.aModel[nCutModel].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_block.aModel[nCutModel].pBuffMat != NULL)
		{
			g_block.aModel[nCutModel].pBuffMat->Release();
			g_block.aModel[nCutModel].pBuffMat = NULL;
		}
	}
}

//--------------------------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------------------------
void UpdateBlock(void)
{
	// �v���C���[�̏��
	Player * pPlayer;
	pPlayer = GetPlayer();

	// �u���b�N�ƃv���C���[�̓����蔻��
	if (g_block.bUse == true)
	{// �u���b�N������Ƃ�
		if (pPlayer->pos.x - (50) < g_block.pos.x + (10) &&
			pPlayer->pos.x + (50) > g_block.pos.x - (10) &&
			pPlayer->pos.z - (150) < g_block.pos.z + (50) &&
			pPlayer->pos.z + (150) > g_block.pos.z - (50))
		{// �u���b�N�ƃv���C���[����������
			// ���U���g�ɂƂ�
			SetResult(true);					//�N���A���
			SetFade(FADE_OUT, MODE_RESULT);
		}
	}
}

//--------------------------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------------------------
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;					// �v�Z�p�̃}�g���b�N�X
	D3DMATERIAL9 matDef;							// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;								// �}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_block.mtxWorld);

	// �����𔽉f(y,x,z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_block.rot.y, g_block.rot.x, g_block.rot.z);
	D3DXMatrixMultiply(&g_block.mtxWorld, &g_block.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_block.pos.x, g_block.pos.y, g_block.pos.z);
	D3DXMatrixMultiply(&g_block.mtxWorld, &g_block.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_block.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCutModel = 0; nCutModel < g_block.nNumModel; nCutModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;		// �v�Z�p�}�g���b�N�X

		D3DXMATRIX mtxParent;						// �e�̃}�g���b�N�X

		// �e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_block.aModel[nCutModel].mtxWorld);

		// �����𔽉f(y,x,z)
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_block.aModel[nCutModel].rot.y, g_block.aModel[nCutModel].rot.x, g_block.aModel[nCutModel].rot.z);
		D3DXMatrixMultiply(&g_block.aModel[nCutModel].mtxWorld, &g_block.aModel[nCutModel].mtxWorld, &mtxRotModel);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_block.aModel[nCutModel].pos.x, g_block.aModel[nCutModel].pos.y, g_block.aModel[nCutModel].pos.z);
		D3DXMatrixMultiply(&g_block.aModel[nCutModel].mtxWorld, &g_block.aModel[nCutModel].mtxWorld, &mtxTransModel);
		
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_block.aModel[nCutModel].mtxWorld);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_block.aModel[nCutModel].pBuffMat->GetBufferPointer();

		for (int nCutMat = 0; nCutMat < (int)g_block.aModel[nCutModel].nNumMat; nCutMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			// ���f��(�p�[�c)�̕`��
			g_block.aModel[nCutModel].pMesh->DrawSubset(nCutMat);
		}
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//--------------------------------------------------------------------------------
//	�u���b�N���̎擾
//--------------------------------------------------------------------------------
Block *GetBlock(void)
{
	return &g_block;			// �u���b�N���̐擪�A�h���X��Ԃ�
}