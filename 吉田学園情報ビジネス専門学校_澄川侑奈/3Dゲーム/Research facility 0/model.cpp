#if 0

//--------------------------------------------------------------------------------
//
//	���f���̏��� [model.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "model.h"
#include "keyboard.h"
#include "camera.h"

//--------------------------------------------------------------------------------
//	�}�N����`
//--------------------------------------------------------------------------------
#define MAX_MOVE	(3)			// �ړ���
#define MAX_ROT		(0.1f)		// ����

//--------------------------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------------------------
LPD3DXMESH g_pMeshModel = NULL;							// ���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL;					// �}�e���A��(���_���)�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_apTexture[10] = {};				// �e�N�X�`���ւ̃|�C���^
DWORD g_nNumMatModel = 0;								// �}�e���A����

MODEL g_Model;											// �v���C���[�̏��	
														
D3DXMATRIX g_mtxWorldModel;								// ���[���h�}�g���b�N�X

int g_nCountersAnimationCun;							// �J�E���g����(�J�E���^�X�V��x������)

//--------------------------------------------------------------------------------
// ����������
//--------------------------------------------------------------------------------
void InitModel(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATERIAL *pMat;									// �}�e���A���ւ̃|�C���^

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/01_head.x",			// �ǂݍ���X�t�@�C����
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,								// �}�e���A��(���_���)
		NULL,
		&g_nNumMatModel,								// �}�e���A����
		&g_pMeshModel);									// ���b�V��(���_���)

	int nNumVtx;										// ���_��
	DWORD sizeFVF;										// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;										// ���_�o�b�t�@�ւ̃|�C���^

	// ���_�����擾
	nNumVtx = g_pMeshModel->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());

	// ���_�o�b�t�@�����b�N
	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntMat = 0; nCntMat < nNumVtx; nCntMat++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		// ���_���W�̑��

		// �S�Ă̒��_���r���ă��f���̍ŏ��l�E�ő�l�𔲂��o��



		pVtxBuff += sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}






	// �}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{// �t�@�C���ǂݍ��݂�����
			
		}
	}


	// �|���S���̏�񏉊���
	g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	g_Model.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
}

//--------------------------------------------------------------------------------
// �I������
//--------------------------------------------------------------------------------
void UninitModel(void)
{
	// ���b�V���̊J��
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	// �}�e���A���̊J��
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//--------------------------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------------------------
void UpdateModel(void)
{
	// �J�����̏������炤
	Camera * pCamer;
	pCamer = GetCamera();

	// ���f���̈ړ�����
	// ��L�[��������
	if (GetkeyboardPress(DIK_UP) == true)
	{// �o�b�N
		g_Model.pos.x += sinf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.x += sinf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.z += cosf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.z += cosf(pCamer->rot.y) * MAX_MOVE;
	}

	// ���L�[��������
	if (GetkeyboardPress(DIK_DOWN) == true)
	{// �O�i
		g_Model.pos.x -= sinf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.x -= sinf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.z -= cosf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.z -= cosf(pCamer->rot.y) * MAX_MOVE;
	}

	// ���L�[��������
	if (GetkeyboardPress(DIK_LEFT) == true)
	{// ���ړ�
		g_Model.pos.x -= cosf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.x -= cosf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.z += sinf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.z += sinf(pCamer->rot.y) * MAX_MOVE;
	}

	// �E�L�[��������
	if (GetkeyboardPress(DIK_RIGHT) == true)
	{// �E�ړ�
		g_Model.pos.x += cosf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.x += cosf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.z -= sinf(pCamer->rot.y) * MAX_MOVE;
		g_Model.pos.z -= sinf(pCamer->rot.y) * MAX_MOVE;
	}

	// ���V�t�g��������
	if (GetkeyboardPress(DIK_LSHIFT) == true)
	{// ����]
		g_Model.rot.y -= MAX_ROT;
	}

	// �E�V�t�g��������
	if (GetkeyboardPress(DIK_RSHIFT) == true)
	{// �E��]
		g_Model.rot.y += MAX_ROT;
	}

	// �G���^�[�L�[��������
	if (GetkeyboardPress(DIK_RETURN) == true)
	{// �ʒu��߂�
		g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//--------------------------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------------------------
void DrawModel(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;		// �v�Z�p�̃}�g���b�N�X
	D3DMATERIAL9 matDef;				// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;					// �}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldModel);

	// �����𔽉f(y,x,z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.rot.y, g_Model.rot.x, g_Model.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Model.pos.x, g_Model.pos.y, g_Model.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCnyMat = 0; nCnyMat < (int)g_nNumMatModel; nCnyMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCnyMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		// ���f��(�p�[�c)�̕`��
		g_pMeshModel->DrawSubset(nCnyMat);
	}
	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//--------------------------------------------------------------------------------
//	�v���C���[�̎擾
//--------------------------------------------------------------------------------
MODEL *GetModel(void)
{
	return &g_Model;			// �v���C���[�̏��̐擪�A�h���X��Ԃ�
}

#endif