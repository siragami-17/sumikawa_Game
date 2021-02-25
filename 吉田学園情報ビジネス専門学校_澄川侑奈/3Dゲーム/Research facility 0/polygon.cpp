//--------------------------------------------------------------------------------
//
//	�|���S���̏��� [polygon.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "polygon.h"
#include "keyboard.h"

//--------------------------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolgon = NULL;		// �|���S���̒��_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePolgon = NULL;				// �e�N�X�`���̃|�C���^

D3DXVECTOR3 g_posPolygon;								// �ʒu
D3DXVECTOR3 g_rotPolygon;								// �@���x�N�g��(����)
D3DXMATRIX g_mtxWorldPolygon;							// ���[���h�}�g���b�N�X

//--------------------------------------------------------------------------------
// ����������
//--------------------------------------------------------------------------------
HRESULT InitPolgon(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// �ϐ��錾
	VERTEX_3D *pVtx;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field000.jpg", &g_pTexturePolgon);

	// �|���S���̏�񏉊���
	g_posPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	g_rotPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����


	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * 4,					// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,							// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolgon,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPolgon->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W(X.Y.Z)
	pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - 100.0f, g_posPolygon.y + 0.0f, g_posPolygon.z + 100.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x + 100.0f, g_posPolygon.y + 0.0f, g_posPolygon.z + 100.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x - 100.0f, g_posPolygon.y + 0.0f, g_posPolygon.z - 100.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + 100.0f, g_posPolygon.y + 0.0f, g_posPolygon.z - 100.0f);

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// ���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(0.0, 1.0);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPolgon->Unlock();

	return S_OK;
}

//--------------------------------------------------------------------------------
// �I������
//--------------------------------------------------------------------------------
void UninitPolgon(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPolgon != NULL)
	{
		g_pVtxBuffPolgon->Release();
		g_pVtxBuffPolgon = NULL;
	}

	// �e�N�X�`���̊J��(�|���S��)
	if (g_pTexturePolgon != NULL)
	{
		g_pTexturePolgon->Release();
		g_pTexturePolgon = NULL;
	}
}

//--------------------------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------------------------
void UpdatePolgon(void)
{

}

//--------------------------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------------------------
void DrawPolgon(void)
{
	LPDIRECT3DDEVICE9 pDevice;			// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;		// �v�Z�p�̃}�g���b�N�X

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	// �����𔽉f(y,x,z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPolgon, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̃e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePolgon);
	
	// �|���S���̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,						// �`����J�n���钸�_�C���f�b�N�X
		2);						// �`�悷��v���~�e�B�u��
}