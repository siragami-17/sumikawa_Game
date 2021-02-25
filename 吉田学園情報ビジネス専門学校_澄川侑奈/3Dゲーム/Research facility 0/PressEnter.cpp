//--------------------------------------------------------------------------------
//
//	�v���X�G���^�[�̏��� [pressenter.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "PressEnter.h"			// ���S

//-------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------
#define MAX_LOGO		(1)			// �e�N�X�`����
#define MAX_LOGO_X		(425)		// ���S�̑傫��(x)
#define MAX_LOGO_Y		(131)		// ���S�̑傫��(y)
#define MAX_POS_X		(650)		// ���S�̈ʒu(x)
#define MAX_POS_Y		(500)		// ���S�̈ʒu(y)

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTexturePressEnter = NULL;			// �e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPressEnter = NULL;


//-------------------------------------------------------------------------------
//	���S�̏���������
//-------------------------------------------------------------------------------
HRESULT InitPressEnter(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;	
	pDevice = GetDevice();

	// �ϐ��錾
	VERTEX_2D *pVtx;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title_PressEnter.png", &g_pTexturePressEnter);		// ���S

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4* MAX_LOGO,		// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,						// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPressEnter,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(		   0+MAX_POS_X, MAX_LOGO_Y+MAX_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(		   0+MAX_POS_X,          0+MAX_POS_Y, 0.0f);							
	pVtx[2].pos = D3DXVECTOR3(MAX_LOGO_X+MAX_POS_X, MAX_LOGO_Y+MAX_POS_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(MAX_LOGO_X+MAX_POS_X,          0+MAX_POS_Y, 0.0f);				

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// ���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);	
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);	
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);	
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);	

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPressEnter->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	���S�̏I������
//-------------------------------------------------------------------------------
void UninitPressEnter(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPressEnter != NULL)
	{
		g_pVtxBuffPressEnter->Release();
		g_pVtxBuffPressEnter = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTexturePressEnter != NULL)
	{
		g_pTexturePressEnter->Release();
		g_pTexturePressEnter = NULL;
	}
}

//-------------------------------------------------------------------------------
//	���S�̍X�V����
//-------------------------------------------------------------------------------
void UpdatePressEnter(void)
{

}

//-------------------------------------------------------------------------------
//	���S�̕`�揈��
//-------------------------------------------------------------------------------
void DrawPressEnter(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPressEnter, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePressEnter);

	// ���S�̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,						// �`����J�n���钸�_�C���f�b�N�X
		2);						// �`�悷��v���~�e�B�u��
}