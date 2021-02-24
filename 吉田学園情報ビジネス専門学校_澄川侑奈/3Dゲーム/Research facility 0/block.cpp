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
LPD3DXMESH g_pMesh = NULL;				// ���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMat = NULL;			// �}�e���A���ւ̃|�C���^
D3DXMATRIX g_mtxWorld;					// ���[���h�}�g���b�N�X
DWORD g_nNumMat = 0;					// �}�e���A����

Block g_block;							// �u���b�N�̏��	
												
//--------------------------------------------------------------------------------
// ����������
//--------------------------------------------------------------------------------
HRESULT InitBlock(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// block�\���̂̏�����
	g_block.pos = D3DXVECTOR3(0.0f, 0.0f, 500.0f);			// �ʒu
	g_block.blockVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	g_block.fWidth = 0.0f;									// ��
	g_block.fHeight = 0.0f;									// ����
	g_block.fLength = 0.0f;									// ����
	g_block.fRadius = (float)10;							// ���a
	g_block.bUse = true;									// �g�p���Ă��邩�ǂ���

	// X�t�@�C���̓ǂݍ���
	// �u���b�N
	D3DXLoadMeshFromX("data/MODEL/Block_1.x",				// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMat,										// �}�e���A��(���_���)
		NULL,	
		&g_nNumMat,											// �}�e���A����
		&g_pMesh);											// ���b�V��(���_���)

	return S_OK;
}

//--------------------------------------------------------------------------------
// �I������
//--------------------------------------------------------------------------------
void UninitBlock(void)
{

	// ���b�V���̊J��
	if (g_pMesh != NULL)
	{		 
		g_pMesh->Release();
		g_pMesh = NULL;
	}				  

	// �}�e���A���̊J��
	if (g_pBuffMat != NULL)
	{	
		g_pBuffMat->Release();
		g_pBuffMat = NULL;
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

	 //�u���b�N�ƃv���C���[�̓����蔻��
	if (g_block.bUse == true)
	{// �u���b�N������Ƃ�
		g_block.blockVec = pPlayer->pos - g_block.pos;		// ���̃x�N�g�������߂�
		g_block.fLength = sqrtf((g_block.blockVec.x*g_block.blockVec.x) + (g_block.blockVec.z*g_block.blockVec.z));		// ���ƃv���C���[�̋���

		// �u���b�N�ƃv���C���[����������
		if (g_block.fLength < g_block.fRadius)
		{// ���������a��菬�����Ȃ���



			if (pPlayer->bGetKey == true)
			{// �v���C���[�����������Ă�����

			 //��������
				g_block.bUse = false;

				// ���U���g�ɔ��
				SetResult(true);					// �N���A���
				SetFade(FADE_OUT, MODE_RESULT);
			}
		
		
			

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

	if (g_block.bUse == true)
	{


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


		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMat->GetBufferPointer();

		for (int nCutMat = 0; nCutMat < g_nNumMat; nCutMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			// ���f��(�p�[�c)�̕`��
			g_pMesh->DrawSubset(nCutMat);
		}

		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//--------------------------------------------------------------------------------
//	�u���b�N���̎擾
//--------------------------------------------------------------------------------
Block *GetBlock(void)
{
	return &g_block;			// �u���b�N���̐擪�A�h���X��Ԃ�
}