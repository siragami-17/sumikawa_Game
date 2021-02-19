//--------------------------------------------------------------------------------
//
//	�v���C���[�̏��� [player.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "player.h"			// �v���C���[
#include "keyboard.h"		// �L�[�{�[�h
#include "camera.h"			// �J����
#include "block.h"			// �u���b�N
#include "meshfild.h"		// �n��

//--------------------------------------------------------------------------------
//	�}�N����`
//--------------------------------------------------------------------------------
#define MAX_MOVE		(5)			// �ړ���
#define MAX_ROT			(0.1f)		// ����

#define MAX_FLAME		(40)		// �Đ��t���[����
#define MAX_COUNTER		(10)		// ���[�V�����J�E���^�[

#define MAX_JUMP		(-20)		//�W�����v


//--------------------------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------------------------
Player g_player;					// �v���C���[�̏��	

int nDifference;					// ����
											
//--------------------------------------------------------------------------------
// ����������
//--------------------------------------------------------------------------------
HRESULT InitPlayer(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �p�[�c���̏�����
	g_player.nNumModel = 14;										

	// X�t�@�C���̓ǂݍ���
	// ��
	D3DXLoadMeshFromX("data/MODEL/00_body.x",						// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[0].pBuffMat,								// �}�e���A��(���_���)
		NULL,
		&g_player.aModel[0].nNumMat,								// �}�e���A����
		&g_player.aModel[0].pMesh);									// ���b�V��(���_���)

	// ��
	D3DXLoadMeshFromX("data/MODEL/01_head.x",						// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[1].pBuffMat,								// �}�e���A��(���_���)
		NULL,
		&g_player.aModel[1].nNumMat,								// �}�e���A����
		&g_player.aModel[1].pMesh);									// ���b�V��(���_���)

	// �E�r_0
	D3DXLoadMeshFromX("data/MODEL/02_armR_0.x",						// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[2].pBuffMat,								// �}�e���A��(���_���)
		NULL,
		&g_player.aModel[2].nNumMat,								// �}�e���A����
		&g_player.aModel[2].pMesh);									// ���b�V��(���_���)

	// �E�r_1
	D3DXLoadMeshFromX("data/MODEL/02_armR_1.x",						// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[3].pBuffMat,								// �}�e���A��(���_���)
		NULL,
		&g_player.aModel[3].nNumMat,								// �}�e���A����
		&g_player.aModel[3].pMesh);									// ���b�V��(���_���)

	// �E��
	D3DXLoadMeshFromX("data/MODEL/03_handR.x",						// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[4].pBuffMat,								// �}�e���A��(���_���)
		NULL,
		&g_player.aModel[4].nNumMat,								// �}�e���A����
		&g_player.aModel[4].pMesh);									// ���b�V��(���_���)

	// ���r_0
	D3DXLoadMeshFromX("data/MODEL/04_armL_0.x",						// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[5].pBuffMat,								// �}�e���A��(���_���)
		NULL,
		&g_player.aModel[5].nNumMat,								// �}�e���A����
		&g_player.aModel[5].pMesh);									// ���b�V��(���_���)

	// ���r_1
	D3DXLoadMeshFromX("data/MODEL/04_armL_1.x",						// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[6].pBuffMat,								// �}�e���A��(���_���)
		NULL,
		&g_player.aModel[6].nNumMat,								// �}�e���A����
		&g_player.aModel[6].pMesh);									// ���b�V��(���_���)

	// ����
	D3DXLoadMeshFromX("data/MODEL/05_handL.x",						// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[7].pBuffMat,								// �}�e���A��(���_���)
		NULL,
		&g_player.aModel[7].nNumMat,								// �}�e���A����
		&g_player.aModel[7].pMesh);									// ���b�V��(���_���)

	// �E��_0
	D3DXLoadMeshFromX("data/MODEL/06_legR_0.x",						// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[8].pBuffMat,								// �}�e���A��(���_���)
		NULL,
		&g_player.aModel[8].nNumMat,								// �}�e���A����
		&g_player.aModel[8].pMesh);									// ���b�V��(���_���)

	// �E��_1
	D3DXLoadMeshFromX("data/MODEL/06_legR_1.x",						// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[9].pBuffMat,								// �}�e���A��(���_���)
		NULL,
		&g_player.aModel[9].nNumMat,								// �}�e���A����
		&g_player.aModel[9].pMesh);									// ���b�V��(���_���)

	// �E��
	D3DXLoadMeshFromX("data/MODEL/07_footR.x",						// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[10].pBuffMat,								// �}�e���A��(���_���)
		NULL,
		&g_player.aModel[10].nNumMat,								// �}�e���A����
		&g_player.aModel[10].pMesh);								// ���b�V��(���_���)

	// ����_0
	D3DXLoadMeshFromX("data/MODEL/08_legL_0.x",						// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[11].pBuffMat,								// �}�e���A��(���_���)
		NULL,
		&g_player.aModel[11].nNumMat,								// �}�e���A����
		&g_player.aModel[11].pMesh);								// ���b�V��(���_���)

	// ����_1
	D3DXLoadMeshFromX("data/MODEL/08_legL_1.x",						// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[12].pBuffMat,								// �}�e���A��(���_���)
		NULL,
		&g_player.aModel[12].nNumMat,								// �}�e���A����
		&g_player.aModel[12].pMesh);								// ���b�V��(���_���)

	// ����
	D3DXLoadMeshFromX("data/MODEL/09_footL.x",						// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[13].pBuffMat,								// �}�e���A��(���_���)
		NULL,
		&g_player.aModel[13].nNumMat,								// �}�e���A����
		&g_player.aModel[13].pMesh);								// ���b�V��(���_���)


	// �e�p�[�c�̊K�w�\���ݒ�
	// ��
	g_player.aModel[0].nIdModelParent = -1;							// �e���f���̃C���f�b�N�X��ݒ�
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 23.0f, 0.0f);		// �ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�

	// ��
	g_player.aModel[1].nIdModelParent = 0;							// �e���f���̃C���f�b�N�X��ݒ�
	g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 22.0f, 0.0f);		// �ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�

	// �E�r_0
	g_player.aModel[2].nIdModelParent = 0;							// �e���f���̃C���f�b�N�X��ݒ�
	g_player.aModel[2].pos = D3DXVECTOR3(-3.0f, 20.0f, 0.0f);		// �ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�

	// �E�r_1
	g_player.aModel[3].nIdModelParent = 2;							// �e���f���̃C���f�b�N�X��ݒ�
	g_player.aModel[3].pos = D3DXVECTOR3(-9.0f, 0.0f, 0.0f);		// �ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�

	// �E��
	g_player.aModel[4].nIdModelParent = 3;							// �e���f���̃C���f�b�N�X��ݒ�
	g_player.aModel[4].pos = D3DXVECTOR3(-9.0f, 0.0f, 0.0f);		// �ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�

	// ���r_0
	g_player.aModel[5].nIdModelParent = 0;							// �e���f���̃C���f�b�N�X��ݒ�
	g_player.aModel[5].pos = D3DXVECTOR3(3.0f, 20.0f, 0.0f);		// �ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�

	// ���r_1
	g_player.aModel[6].nIdModelParent = 5;							// �e���f���̃C���f�b�N�X��ݒ�
	g_player.aModel[6].pos = D3DXVECTOR3(9.0f, 0.0f, 0.0f);			// �ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�

	// ����
	g_player.aModel[7].nIdModelParent = 6;							// �e���f���̃C���f�b�N�X��ݒ�
	g_player.aModel[7].pos = D3DXVECTOR3(9.0f, 0.0f, 0.0f);			// �ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�

	// �E��_0
	g_player.aModel[8].nIdModelParent = 0;							// �e���f���̃C���f�b�N�X��ݒ�
	g_player.aModel[8].pos = D3DXVECTOR3(-3.5f, 0.0f, 0.0f);			// �ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�

	// �E��_1
	g_player.aModel[9].nIdModelParent = 8;							// �e���f���̃C���f�b�N�X��ݒ�
	g_player.aModel[9].pos = D3DXVECTOR3(0.0f, -9.5f, 0.0f);		// �ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�

	// �E��
	g_player.aModel[10].nIdModelParent = 9;							// �e���f���̃C���f�b�N�X��ݒ�
	g_player.aModel[10].pos = D3DXVECTOR3(0.0f, -10.0f, 0.0f);		// �ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����̏����ݒ�

	// ����_0
	g_player.aModel[11].nIdModelParent = 0;							// �e���f���̃C���f�b�N�X��ݒ�
	g_player.aModel[11].pos = D3DXVECTOR3(3.5f, 0.0f, 0.0f);		// �ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����̏����ݒ�

	// ����_1
	g_player.aModel[12].nIdModelParent = 11;						// �e���f���̃C���f�b�N�X��ݒ�
	g_player.aModel[12].pos = D3DXVECTOR3(0.0f, -9.5f, 0.0f);		// �ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����̏����ݒ�

	// ����
	g_player.aModel[13].nIdModelParent = 12;						// �e���f���̃C���f�b�N�X��ݒ�
	g_player.aModel[13].pos = D3DXVECTOR3(0.0f, -10.0f, 0.0f);		// �ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_player.aModel[13].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����̏����ݒ�

	//�����ݒ�
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ʒu
	g_player.rot = D3DXVECTOR3(0.0f, -3.14f, 0.0f);					// ����

	//�ϐ��錾
	int nNumVtx;													// ���_��
	DWORD sizeFVF;													// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;													// ���_�o�b�t�@�ւ̃|�C���^



	return S_OK;
}

//--------------------------------------------------------------------------------
// �I������
//--------------------------------------------------------------------------------
void UninitPlayer(void)
{
	for (int nCutModel = 0; nCutModel < g_player.nNumModel; nCutModel++)
	{
		// ���b�V���̊J��
		if (g_player.aModel[nCutModel].pMesh != NULL)
		{
			g_player.aModel[nCutModel].pMesh->Release();
			g_player.aModel[nCutModel].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_player.aModel[nCutModel].pBuffMat != NULL)
		{
			g_player.aModel[nCutModel].pBuffMat->Release();
			g_player.aModel[nCutModel].pBuffMat = NULL;
		}
	}
}

//--------------------------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------------------------
void UpdatePlayer(void)
{
	// �J�����̏������炤
	Camera * pCamera;
	pCamera = GetCamera();

	// �u���b�N���
	Block *pBlock = GetBlock();

	// ���f���̈ړ�����
	// ��L�[��������
	if (GetkeyboardPress(DIK_W) == true)
	{// �o�b�N
		g_player.pos.x += sinf(pCamera->rot.y) * MAX_MOVE;		// +=�͂����Ɖ����Ă锽��
		g_player.pos.z += cosf(pCamera->rot.y) * MAX_MOVE;

		g_player.rot.y = pCamera->rot.y - D3DX_PI;				// �v���C���[�̌�����O�ɂ���

	}

	// ���L�[��������
	if (GetkeyboardPress(DIK_S) == true)
	{// �O�i
		g_player.pos.x -= sinf(pCamera->rot.y) * MAX_MOVE;
		g_player.pos.z -= cosf(pCamera->rot.y) * MAX_MOVE;

		g_player.rot.y = pCamera->rot.y;						// �v���C���[�̌��������ɂ���
	}

	// ���L�[��������
	if (GetkeyboardPress(DIK_A) == true)
	{// ���ړ�
		g_player.pos.x -= cosf(pCamera->rot.y) * MAX_MOVE;
		g_player.pos.z += sinf(pCamera->rot.y) * MAX_MOVE;

		g_player.rot.y = +D3DX_PI / 2 + pCamera->rot.y;			// �v���C���[�̌������������ɂ���
	}

	// �E�L�[��������
	if (GetkeyboardPress(DIK_D) == true)
	{// �E�ړ�
		g_player.pos.x += cosf(pCamera->rot.y) * MAX_MOVE;
		g_player.pos.z -= sinf(pCamera->rot.y) * MAX_MOVE;

		g_player.rot.y = -D3DX_PI / 2 + pCamera->rot.y;			// �v���C���[�̌������E������
	}

	// ���V�t�g��������
	if (GetkeyboardPress(DIK_LSHIFT) == true)
	{// ����]
		g_player.rot.y -= MAX_ROT;
	}

	// �E�V�t�g��������
	if (GetkeyboardPress(DIK_RSHIFT) == true)
	{// �E��]
		g_player.rot.y += MAX_ROT;
	}

	// move��pos�����Z
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	// �ړ��ʂ̐���
	g_player.move.x += (0.0f - g_player.move.x)*0.25f;
	g_player.move.y += (0.0f - g_player.move.y)*0.25f;

	// �G���^�[�L�[��������
	if (GetkeyboardPress(DIK_RETURN) == true)
	{// �ʒu��߂�
		g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rot = D3DXVECTOR3(0.0f, -3.14f, 0.0f);
	}

	// ���[�V����
	// �j���[�g�������[�V����

	for (int nCuntPlayer = 0; nCuntPlayer < 2; nCuntPlayer++)
	{
		// �E�r



	}




	//�d��
//	g_player.move.y += +2;
//
//	if (GetkeyboardTrgger(DIK_SPACE) == true && g_player.bJump == false)
//	{//�W�����v�̏���(2�i�W�����v�̐���)
//		g_player.move.y = MAX_JUMP;
//		g_player.bJump = true;
//	}






}

//--------------------------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------------------------
void DrawPlayer(void)
{
	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾:
	D3DXMATRIX mtxRot, mtxTrans;					// �v�Z�p�̃}�g���b�N�X
	D3DMATERIAL9 matDef;							// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;								// �}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorld);

	// �����𔽉f(y,x,z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCutModel = 0; nCutModel < g_player.nNumModel; nCutModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;		// �v�Z�p�}�g���b�N�X

		D3DXMATRIX mtxParent;						// �e�̃}�g���b�N�X

		// �e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player.aModel[nCutModel].mtxWorld);

		// �����𔽉f(y,x,z)
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCutModel].rot.y, g_player.aModel[nCutModel].rot.x, g_player.aModel[nCutModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCutModel].mtxWorld, &g_player.aModel[nCutModel].mtxWorld, &mtxRotModel);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCutModel].pos.x, g_player.aModel[nCutModel].pos.y, g_player.aModel[nCutModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCutModel].mtxWorld, &g_player.aModel[nCutModel].mtxWorld, &mtxTransModel);
		
		// �e�p�[�c�̐e�̃}�g���b�N�X��ݒ�
		if (g_player.aModel[nCutModel].nIdModelParent != -1)		// p:�v���C���[ m:���f�� nld:�ԍ�
		{
			mtxParent = g_player.aModel[g_player.aModel[nCutModel].nIdModelParent].mtxWorld;
		}
		else
		{// �e�ȊO
			// �v���C���[�̃}�g���b�N�X��ݒ�
			mtxParent = g_player.mtxWorld;
		}

		//�e�ǂݍ���
		D3DXMatrixMultiply(&g_player.aModel[nCutModel].mtxWorld,
						   &g_player.aModel[nCutModel].mtxWorld,
						   &mtxParent);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCutModel].mtxWorld);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[nCutModel].pBuffMat->GetBufferPointer();

		for (int nCutMat = 0; nCutMat < (int)g_player.aModel[nCutModel].nNumMat; nCutMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			// ���f��(�p�[�c)�̕`��
			g_player.aModel[nCutModel].pMesh->DrawSubset(nCutMat);
		}
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//--------------------------------------------------------------------------------
//	�v���C���[�̎擾
//--------------------------------------------------------------------------------
Player *GetPlayer(void)
{
	return &g_player;			// �v���C���[�̏��̐擪�A�h���X��Ԃ�
}