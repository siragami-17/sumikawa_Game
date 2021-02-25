//--------------------------------------------------------------------------------
//
//	�ǂ̏��� [wall.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "wall.h"

//--------------------------------------------------------------------------------
// �}�N����`
//--------------------------------------------------------------------------------
#define MAX_VERTEX_WALL		(9*2)					// ���_��
#define MAX_IDX_WALL		(14*2)					// �C���f�b�N�X��

//--------------------------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;		// �ǂ̒��_�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffWall = NULL;		// �C���f�b�N�X�̃o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_apTextureWall;					// �e�N�X�`���̃|�C���^

Wall g_wall;										// �ǂ̏��

//--------------------------------------------------------------------------------
// ����������
//--------------------------------------------------------------------------------
HRESULT InitWall(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// �ϐ��錾
	VERTEX_3D *pVtx;
	
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/kabe.jpg", &g_apTextureWall);

	// �Ǐ��̏�����
		g_wall.pos = D3DXVECTOR3(0.0f, 0.0f, +250.0f);		// �ʒu
		g_wall.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����

	// ���_�o�b�t�@�̐���
		if (FAILED(pDevice->CreateVertexBuffer
		(sizeof(VERTEX_3D) * MAX_VERTEX_WALL,			// �m�ۂ���o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,								// ���_�t�H�[�}�b�g
			D3DPOOL_MANAGED,
			&g_pVtxBuffWall,
			NULL)))
		{
			return E_FAIL;
		}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W(X.Y.Z)
	pVtx[0].pos = D3DXVECTOR3(g_wall.pos.x - MAX_SIZE, g_wall.pos.y + 600.0f, g_wall.pos.z + 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_wall.pos.x - 0.0f  , g_wall.pos.y + 600.0f, g_wall.pos.z + 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_wall.pos.x + MAX_SIZE, g_wall.pos.y + 600.0f, g_wall.pos.z + 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_wall.pos.x - MAX_SIZE, g_wall.pos.y + MAX_SIZE, g_wall.pos.z + 0.0f);
	pVtx[4].pos = D3DXVECTOR3(g_wall.pos.x - 0.0f  , g_wall.pos.y + MAX_SIZE, g_wall.pos.z + 0.0f);
	pVtx[5].pos = D3DXVECTOR3(g_wall.pos.x + MAX_SIZE, g_wall.pos.y + MAX_SIZE, g_wall.pos.z + 0.0f);
	pVtx[6].pos = D3DXVECTOR3(g_wall.pos.x - MAX_SIZE, g_wall.pos.y + 0.0f  , g_wall.pos.z + 0.0f);
	pVtx[7].pos = D3DXVECTOR3(g_wall.pos.x - 0.0f  , g_wall.pos.y + 0.0f  , g_wall.pos.z + 0.0f);
	pVtx[8].pos = D3DXVECTOR3(g_wall.pos.x + MAX_SIZE, g_wall.pos.y + 0.0f  , g_wall.pos.z + 0.0f);

	pVtx[9].pos = D3DXVECTOR3(g_wall.pos.x  + MAX_SIZE, g_wall.pos.y + 600.0f, g_wall.pos.z + 0.0f);
	pVtx[10].pos = D3DXVECTOR3(g_wall.pos.x + 500.0f  , g_wall.pos.y + 600.0f, g_wall.pos.z - 100.0f);
	pVtx[11].pos = D3DXVECTOR3(g_wall.pos.x + MAX_SIZE, g_wall.pos.y + 600.0f, g_wall.pos.z - 200.0f);
	pVtx[12].pos = D3DXVECTOR3(g_wall.pos.x + MAX_SIZE, g_wall.pos.y + MAX_SIZE, g_wall.pos.z + 0.0f);
	pVtx[13].pos = D3DXVECTOR3(g_wall.pos.x + 500.0f  , g_wall.pos.y + MAX_SIZE, g_wall.pos.z - 100.0f);
	pVtx[14].pos = D3DXVECTOR3(g_wall.pos.x + MAX_SIZE, g_wall.pos.y + MAX_SIZE, g_wall.pos.z -200.0f);
	pVtx[15].pos = D3DXVECTOR3(g_wall.pos.x + MAX_SIZE, g_wall.pos.y + 0.0f  , g_wall.pos.z + 0.0f);
	pVtx[16].pos = D3DXVECTOR3(g_wall.pos.x + 500.0f  , g_wall.pos.y + 0.0f  , g_wall.pos.z - 100.0f);
	pVtx[17].pos = D3DXVECTOR3(g_wall.pos.x + MAX_SIZE, g_wall.pos.y + 0.0f  , g_wall.pos.z - 200.0f);

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	pVtx[9].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[10].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[11].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[12].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[13].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[14].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[15].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[16].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[17].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[16].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[17].col = D3DCOLOR_RGBA(255, 255, 255, 255);

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

	pVtx[9].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[10].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[11].tex = D3DXVECTOR2(2.0, 0.0);
	pVtx[12].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[13].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[14].tex = D3DXVECTOR2(2.0, 1.0);
	pVtx[15].tex = D3DXVECTOR2(0.0, 2.0);
	pVtx[16].tex = D3DXVECTOR2(1.0, 2.0);
	pVtx[17].tex = D3DXVECTOR2(2.0, 2.0);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD)*MAX_IDX_WALL,		// �K�v�ȃC���f�b�N�X��
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffWall,
		NULL)))
	{
		return E_FAIL;
	}

	// �ϐ��錾
	WORD *pIdx;		// �C���f�b�N�X���ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffWall->Lock(0, 0, (void**)&pIdx, 0);

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

	pIdx[14] = 12;
	pIdx[15] = 9;
	pIdx[16] = 13;
	pIdx[17] = 10;
	pIdx[18] = 14;
	pIdx[19] = 11;
	pIdx[20] = 11;
	pIdx[21] = 15;
	pIdx[22] = 15;
	pIdx[23] = 12;
	pIdx[24] = 16;
	pIdx[25] = 13;
	pIdx[26] = 17;
	pIdx[27] = 14;

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffWall->Unlock();

	return S_OK;
}

//--------------------------------------------------------------------------------
// �I������
//--------------------------------------------------------------------------------
void UninitWall(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

	// �e�N�X�`���̊J��(��)
	if (g_apTextureWall != NULL)
	{
		g_apTextureWall->Release();
		g_apTextureWall = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffWall != NULL)
	{
		g_pIdxBuffWall->Release();
		g_pIdxBuffWall = NULL;
	}
}

//--------------------------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------------------------
void UpdateWall(void)
{

}

//--------------------------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------------------------
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;			// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;		// �v�Z�p�̃}�g���b�N�X

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_wall.mtxWorld);

	// �����𔽉f(y,x,z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_wall.rot.y, g_wall.rot.x, g_wall.rot.z);
	D3DXMatrixMultiply(&g_wall.mtxWorld, &g_wall.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_wall.pos.x, g_wall.pos.y, g_wall.pos.z);
	D3DXMatrixMultiply(&g_wall.mtxWorld, &g_wall.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_wall.mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffWall);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �ǂ̃e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureWall);

	// �ǂ̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		MAX_VERTEX_WALL,								// ���_��
		0,
		26);											// �v���~�e�B�u��
}