//--------------------------------------------------------------------------------
//
//	�^�C�g���L�����̏��� [Title_Player.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Title_Player.h"

//-------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------
#define MAN_X					(501)					// �摜�̕�
#define MAN_Y					(535)					// �摜�̍���
#define POS_X					(2)						// X�̈ʒu
#define POS_Y					(200)					// Y�̈ʒu
#define MAX_ANIMATION_COUNTER	(7)						// �X�s�[�h
#define MAX_ANIMATION_PATTERN	(16)					// �摜�R�}��
#define DIVISION				(0.0625f)				// ����Z

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle_Player = NULL;

LPDIRECT3DTEXTURE9 g_pTextureTitle_Player = NULL;		// �e�N�X�`��
D3DXVECTOR3 g_posTitle_Player;							// �ʒu
int g_nCountersTitle_Player;							// �R�}���̐؂�ւ�
int g_nCountersTitle_PlayerCnt;							// �J�E���^�X�V

//-------------------------------------------------------------------------------
//	�^�C�g����ʏ���������
//-------------------------------------------------------------------------------
HRESULT InitTitle_PLayer(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ϐ��錾
	VERTEX_2D *pVtx;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/1.png", &g_pTextureTitle_Player);		// �A�j���[�V�����摜

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4,		// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle_Player,
		NULL)))
	{
		return E_FAIL;
	}


	

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle_Player->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0      -POS_X	   , MAN_Y+POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0      -POS_X	   , 0    +POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(MAN_X  -POS_X, MAN_Y+POS_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(MAN_X  -POS_X, 0    +POS_Y, 0.0f);

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
	g_pVtxBuffTitle_Player->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�^�C�g����ʂ̏I������
//-------------------------------------------------------------------------------
void UninitTitle_PLayer(void)
{

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitle_Player != NULL)
	{
		g_pVtxBuffTitle_Player->Release();
		g_pVtxBuffTitle_Player = NULL;
	}

	// �^�C�g����ʂ̊J��
	if (g_pTextureTitle_Player != NULL)
	{
		g_pTextureTitle_Player->Release();
		g_pTextureTitle_Player = NULL;
	}
}

//-------------------------------------------------------------------------------
//	�^�C�g����ʂ̍X�V����
//-------------------------------------------------------------------------------
void UpdateTitle_PLayer(void)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;

	g_nCountersTitle_PlayerCnt++;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle_Player->Lock(0, 0, (void**)&pVtx, 0);


	// �A�j���[�V����
	if ((g_nCountersTitle_PlayerCnt %MAX_ANIMATION_COUNTER) == 0)	// �A�j���[�V�����̃J�E���g
	{
		g_nCountersTitle_Player = (g_nCountersTitle_Player + 1) % MAX_ANIMATION_PATTERN;	// �A�j���[�V�����̃R�}��

		// �A�j���[�V�����̒��_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + g_nCountersTitle_Player * DIVISION, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f + g_nCountersTitle_Player * DIVISION, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(DIVISION + g_nCountersTitle_Player * DIVISION, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(DIVISION + g_nCountersTitle_Player * DIVISION, 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle_Player->Unlock();
}

//-------------------------------------------------------------------------------
//	�A�j���[�V�����̕`�揈��
//-------------------------------------------------------------------------------
void DrawTitle_PLayer(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle_Player, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitle_Player);

	//�^�C�g���̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,						// �`����J�n���钸�_�C���f�b�N�X
		NUM_POLYGON);			// �`�悷��v���~�e�B�u��
}