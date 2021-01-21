//--------------------------------------------------------------------------------
//
//	�X�g�b�v�w�i�̏��� [StopBG.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "StopBG.h"

//-------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------
#define MAX_POLYGON	(2)	//�|���S����

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStopBG = NULL;

LPDIRECT3DTEXTURE9 g_pTextureStopBG = NULL;							//�_��

//-------------------------------------------------------------------------------
//	�X�g�b�v�w�i����������
//-------------------------------------------------------------------------------
HRESULT InitStopBG(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�ϐ��錾
	VERTEX_2D *pVtx;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/aaaa.png", &g_pTextureStopBG);		//�_��

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffStopBG,
		NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffStopBG->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);


	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffStopBG->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�X�g�b�v�w�i�̏I������
//-------------------------------------------------------------------------------
void UninitStopBG(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffStopBG != NULL)
	{
		g_pVtxBuffStopBG->Release();
		g_pVtxBuffStopBG = NULL;
	}



	//�_���̊J��
	if (g_pTextureStopBG != NULL)
	{
		g_pTextureStopBG->Release();
		g_pTextureStopBG = NULL;
	}
}

//-------------------------------------------------------------------------------
//	�X�g�b�v�w�i�̍X�V����
//-------------------------------------------------------------------------------
void UpdateStopBG(void)
{

}

//-------------------------------------------------------------------------------
//	�X�g�b�v�w�i�̕`�揈��
//-------------------------------------------------------------------------------
void DrawStopBG(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStopBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�w�i�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureStopBG);

	//�_���̐ݒ�
	pDevice->SetTexture(0, g_pTextureStopBG);


	//�X�g�b�v�w�i�̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,			//�`����J�n���钸�_�C���f�b�N�X
		NUM_POLYGON);			//�`�悷��v���~�e�B�u��
}
