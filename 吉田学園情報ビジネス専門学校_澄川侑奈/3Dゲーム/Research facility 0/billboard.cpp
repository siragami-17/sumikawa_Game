//--------------------------------------------------------------------------------
//
//	�r���{�[�h�̏��� [billboard.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Billboard.h"

//--------------------------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------------------------
#define MAX_Billboard		(1)		// �e�N�X�`���̍ő吔

//--------------------------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;		// �r���{�[�h�̒��_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;			// �e�N�X�`���̃|�C���^

D3DXVECTOR3 g_posBillboard;								// �ʒu
D3DXMATRIX g_mtxWorldBillboard;							// ���[���h�}�g���b�N�X

//--------------------------------------------------------------------------------
// ����������
//--------------------------------------------------------------------------------
HRESULT InitBillboard(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// �ϐ��錾
	VERTEX_3D *pVtx;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Key.png", &g_pTextureBillboard);

	// �r���{�[�h�̏�񏉊���
	g_posBillboard = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * 4,								// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,									// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	//// ���_���W(X.Y.Z)
	//pVtx[0].pos = D3DXVECTOR3(g_posBillboard.x - 100.0f, g_posBillboard.y + 100.0f, g_posBillboard.z + 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_posBillboard.x + 100.0f, g_posBillboard.y + 100.0f, g_posBillboard.z + 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_posBillboard.x - 100.0f, g_posBillboard.y - 0.0f, g_posBillboard.z + 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_posBillboard.x + 100.0f, g_posBillboard.y - 0.0f, g_posBillboard.z + 0.0f);

	// ���_���W(X.Y.Z)
	pVtx[0].pos = D3DXVECTOR3(g_posBillboard.x - 25.0f, g_posBillboard.y + 50.0f, g_posBillboard.z + 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posBillboard.x + 25.0f, g_posBillboard.y + 50.0f, g_posBillboard.z + 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posBillboard.x - 25.0f, g_posBillboard.y - 0.0f, g_posBillboard.z + 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posBillboard.x + 25.0f, g_posBillboard.y - 0.0f, g_posBillboard.z + 0.0f);

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	g_pVtxBuffBillboard->Unlock();

	return S_OK;
}

//--------------------------------------------------------------------------------
// �I������
//--------------------------------------------------------------------------------
void UninitBillboard(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}

	// �e�N�X�`���̊J��(�r���{�[�h)
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
}

//--------------------------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------------------------
void UpdateBillboard(void)
{

}

//--------------------------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------------------------
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;			// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxView;					// �r���[�}�g���b�N�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;		// �v�Z�p�̃}�g���b�N�X

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldBillboard);

	// �r���[�}�g���b�N�X�̎擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);		// �t�s������߂�
	g_mtxWorldBillboard._41 = 0.0f;
	g_mtxWorldBillboard._42 = 0.0f;
	g_mtxWorldBillboard._43 = 0.0f;

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posBillboard.x, g_posBillboard.y, g_posBillboard.z);
	D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �r���{�[�h�̃e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBillboard);

	// �r���{�[�h�̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,						// �`����J�n���钸�_�C���f�b�N�X
		2);						// �`�悷��v���~�e�B�u��

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//--------------------------------------------------------------------------------
// �r���{�[�h�̐ݒ�
//--------------------------------------------------------------------------------
void SetBillboard(D3DXVECTOR3 pos)
{

}
