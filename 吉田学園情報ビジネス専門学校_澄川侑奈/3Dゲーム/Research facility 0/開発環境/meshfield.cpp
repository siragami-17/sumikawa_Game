//--------------------------------------------------------------------------------
//
//	�n�ʂ̏��� [meshfild.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "meshfild.h"		// �n��
#include "player.h"			// �v���C���[

//--------------------------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------------------------
#define MAX_VERTEX	(12)								// ���_��
#define MAX_IDX		(22)								// �C���f�b�N�X��
#define MAX_SIZE	(500.0f)							// �n�ʂ̃T�C�Y
#define MAX_SPEED	(2)									// �v���C���[�̗����鑬�x

//--------------------------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------------------------
Meshfild g_meshfild;									// �n�ʂ̏��

//--------------------------------------------------------------------------------
// ����������
//--------------------------------------------------------------------------------
HRESULT InitMeshfild(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// �ϐ��錾
	VERTEX_3D *pVtx;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/metal_00025.jpg", &g_meshfild.pTextureMeshfild);

	// �n�ʂ̍\���̂̏�����
	g_meshfild.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	g_meshfild.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	bool bUse = false;									// �g�p���Ă��邩

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * MAX_VERTEX,					// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,									// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_meshfild.pVtxBuffMeshfild,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_meshfild.pVtxBuffMeshfild->Lock(0, 0, (void**)&pVtx, 0);


		// ������E�ݒ�
		// ���_���W(X.Y.Z)
		pVtx[0].pos = D3DXVECTOR3(g_meshfild.pos.x - MAX_SIZE, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z + MAX_SIZE);
		pVtx[1].pos = D3DXVECTOR3(g_meshfild.pos.x + 0.0f, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z + MAX_SIZE);
		pVtx[2].pos = D3DXVECTOR3(g_meshfild.pos.x + MAX_SIZE, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z + MAX_SIZE);
		pVtx[3].pos = D3DXVECTOR3(g_meshfild.pos.x - MAX_SIZE, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z + 0.0f);
		pVtx[4].pos = D3DXVECTOR3(g_meshfild.pos.x + 0.0f, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z + 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_meshfild.pos.x + MAX_SIZE, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z + 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_meshfild.pos.x - MAX_SIZE, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z - MAX_SIZE);
		pVtx[7].pos = D3DXVECTOR3(g_meshfild.pos.x - 0.0f, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z - MAX_SIZE);
		pVtx[8].pos = D3DXVECTOR3(g_meshfild.pos.x + MAX_SIZE, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z - MAX_SIZE);
		pVtx[9].pos = D3DXVECTOR3(g_meshfild.pos.x - MAX_SIZE, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z - MAX_SIZE);
		pVtx[10].pos = D3DXVECTOR3(g_meshfild.pos.x - 0.0f, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z - MAX_SIZE);
		pVtx[11].pos = D3DXVECTOR3(g_meshfild.pos.x + MAX_SIZE, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z - MAX_SIZE);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[9].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[10].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[11].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// ���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(2.0, 0.0);
		pVtx[3].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[4].tex = D3DXVECTOR2(1.0, 1.0);
		pVtx[5].tex = D3DXVECTOR2(2.0, 1.0);
		pVtx[6].tex = D3DXVECTOR2(0.0, 2.0);
		pVtx[7].tex = D3DXVECTOR2(1.0, 2.0);
		pVtx[8].tex = D3DXVECTOR2(2.0, 2.0);
		pVtx[9].tex = D3DXVECTOR2(0.0, 3.0);
		pVtx[10].tex = D3DXVECTOR2(1.0, 3.0);
		pVtx[11].tex = D3DXVECTOR2(2.0, 3.0);
	


	// ���_�o�b�t�@���A�����b�N����
	g_meshfild.pVtxBuffMeshfild->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	if(FAILED(pDevice->CreateIndexBuffer(sizeof(WORD)*MAX_IDX,		//�@�K�v�ȃC���f�b�N�X��
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_meshfild.pIdxBuffMeshField,
		NULL)))
	{
		return E_FAIL;
	}

	// �ϐ��錾
	WORD *pIdx;		// �C���f�b�N�X���ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_meshfild.pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	// �ԍ��f�[�^�̐ݒ�
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;
	pIdx[14] = 5;
	pIdx[15] = 9;
	pIdx[16] = 9;
	pIdx[17] = 6;
	pIdx[18] = 10;
	pIdx[19] = 7;
	pIdx[20] = 11;
	pIdx[21] = 8;

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	g_meshfild.pIdxBuffMeshField->Unlock();

	return S_OK;
}

//--------------------------------------------------------------------------------
// �I������
//--------------------------------------------------------------------------------
void UninitMeshfild(void)
{
	// �e�N�X�`���̊J��(�|���S��)
	if (g_meshfild.pTextureMeshfild != NULL)
	{
		g_meshfild.pTextureMeshfild->Release();
		g_meshfild.pTextureMeshfild = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_meshfild.pVtxBuffMeshfild != NULL)
	{
		g_meshfild.pVtxBuffMeshfild->Release();
		g_meshfild.pVtxBuffMeshfild = NULL;
	}
	
	// �C���f�b�N�X�o�b�t�@�̊J��
	if (g_meshfild.pIdxBuffMeshField != NULL)
	{
		g_meshfild.pIdxBuffMeshField->Release();
		g_meshfild.pIdxBuffMeshField = NULL;
	}
}

//--------------------------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------------------------
void UpdateMeshfild(void)
{
	// �v���C���[�̏��
	Player * pPlayer;
	pPlayer = GetPlayer();

	// �n�ʂƃv���C���[�̓����蔻��
	if (g_meshfild.bUse == true)
	{// �n�ʂ�����Ƃ�
		if (pPlayer->pos.x - (150) < g_meshfild.pos.x + (500 * 6) &&		// ��
			pPlayer->pos.x + (150) > g_meshfild.pos.x - (500 * 6) &&		// �E
			pPlayer->pos.z - (150) < g_meshfild.pos.z + (500 * 6) &&		// ��
			pPlayer->pos.z + (150) > g_meshfild.pos.z - (500 * 6))			// ��
		{
			pPlayer->pos.y = 0;
		}
	}
//	else
//	{// �n�ʂ��Ȃ�
//		pPlayer->pos.y -= MAX_SPEED;		// �v���C���[��������
//	}





}

//--------------------------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------------------------
void DrawMeshfild(void)
{
	LPDIRECT3DDEVICE9 pDevice;			// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;		// �v�Z�p�̃}�g���b�N�X

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_meshfild.mtxWorld);

	// �����𔽉f(y,x,z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshfild.rot.y, g_meshfild.rot.x, g_meshfild.rot.z);
	D3DXMatrixMultiply(&g_meshfild.mtxWorld, &g_meshfild.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_meshfild.pos.x, g_meshfild.pos.y, g_meshfild.pos.z);
	D3DXMatrixMultiply(&g_meshfild.mtxWorld, &g_meshfild.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_meshfild.mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_meshfild.pVtxBuffMeshfild, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_meshfild.pIdxBuffMeshField);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̃e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_meshfild.pTextureMeshfild);
	//pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		MAX_VERTEX,										// ���_��
		0,
		20);											// �v���~�e�B�u��
}

//--------------------------------------------------------------------------------
// �n�ʏ��̎擾
//--------------------------------------------------------------------------------
Meshfild *GetMeshfild(void)
{
	return &g_meshfild;		// �n�ʏ��̐擪�A�h���X�ɕԂ�
}