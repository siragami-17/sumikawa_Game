//--------------------------------------------------------------------------------
//
//	�n�[�g�̏��� [heart.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "heart.h"
#include "keyboard.h"		// �L�[�{�[�h

//-------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------
#define MAX_X					(75*2)			// �摜�̕�
#define MAX_Y					(60*2)			// �摜�̍���
#define MAX_COUNTER				(5)				// �X�s�[�h
#define MAX_PATTERN				(10)			// �摜�R�}��
#define DIVISION				(0.1f)			// ����Z
#define RED						(255)			// �J���[(��)
//#define 

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHeart = NULL;

LPDIRECT3DTEXTURE9 g_pTextureHeart = NULL;		// �e�N�X�`��
D3DXVECTOR3 g_posHeart;							// �ʒu
int g_nCountersHeart;							// �R�}���̐؂�ւ�
int g_nCountersHeartCnt;						// �J�E���^�X�V

//-------------------------------------------------------------------------------
//	�^�C�g����ʏ���������
//-------------------------------------------------------------------------------
HRESULT InitHeart(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ϐ��錾
	VERTEX_2D *pVtx;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/heart.png", &g_pTextureHeart);				// �n�[�g

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4,		// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffHeart,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHeart->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(g_posHeart.x + 0    ,g_posHeart.y +  MAX_Y, g_posHeart.z + 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posHeart.x + 0    ,g_posHeart.y +  0    , g_posHeart.z + 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posHeart.x + MAX_X,g_posHeart.y +  MAX_Y, g_posHeart.z + 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posHeart.x + MAX_X,g_posHeart.y +  0    , g_posHeart.z + 0.0f);

	// ���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(DIVISION, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(DIVISION, 0.0f);

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

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHeart->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�^�C�g����ʂ̏I������
//-------------------------------------------------------------------------------
void UninitHeart(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffHeart != NULL)
	{
		g_pVtxBuffHeart->Release();
		g_pVtxBuffHeart = NULL;
	}

	// �^�C�g����ʂ̊J��
	if (g_pTextureHeart != NULL)
	{
		g_pTextureHeart->Release();
		g_pTextureHeart = NULL;
	}
}

//-------------------------------------------------------------------------------
//	�^�C�g����ʂ̍X�V����
//-------------------------------------------------------------------------------
void UpdateHeart(void)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;

	g_nCountersHeartCnt++;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHeart->Lock(0, 0, (void**)&pVtx, 0);



	// �A�j���[�V����
	if ((g_nCountersHeartCnt %MAX_COUNTER) == 0)	// �A�j���[�V�����̃J�E���g
	{
		g_nCountersHeart = (g_nCountersHeart + 1) % MAX_PATTERN;	// �A�j���[�V�����̃R�}��

		// �A�j���[�V�����̒��_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + g_nCountersHeart * DIVISION, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f + g_nCountersHeart * DIVISION, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(DIVISION + g_nCountersHeart * DIVISION, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(DIVISION + g_nCountersHeart * DIVISION, 0.0f);
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHeart->Unlock();
}

//-------------------------------------------------------------------------------
//	�A�j���[�V�����̕`�揈��
//-------------------------------------------------------------------------------
void DrawHeart(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffHeart, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureHeart);

	//�^�C�g���̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,						// �`����J�n���钸�_�C���f�b�N�X
		NUM_POLYGON);			// �`�悷��v���~�e�B�u��
}