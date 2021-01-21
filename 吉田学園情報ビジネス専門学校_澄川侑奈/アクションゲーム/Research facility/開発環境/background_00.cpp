//--------------------------------------------------------------------------------
//
//	�X�e�[�W1�̔w�i���� [background_00.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "title.h"
#include "keyboard.h"
#include "fade.h"

//-------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------
#define MAX_POLYGON	(3)					//�|���S����

//#define MAX_PLAY_X			(55)		//�Đ��}�[�NX
//#define MAX_PLAY_Y			(100)		//�Đ��}�[�NY

#define MAX_PLAY_X			(0)			//�Đ��}�[�NX
#define MAX_PLAY_Y			(00)		//�Đ��}�[�NY
#define MAX_PLAY_COUNTER	(8)			//�Đ��}�[�N�̃X�s�[�h
#define MAX_PLAY_PATTERN	(4)			//�Đ��}�[�N�̌�

//#define MAX_STOP_X			(60)		//��~�}�[�NX
//#define MAX_STOP_Y			(100)		//��~�}�[�NY

#define MAX_STOP_X			(0)			//��~�}�[�NX
#define MAX_STOP_Y			(00)		//��~�}�[�NY
#define MAX_STOP_COUNTER	(8)			//��~�}�[�N�̃X�s�[�h
#define MAX_STOP_PATTERN	(4)			//��~�}�[�N�̌�

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBackground_00 = NULL;

LPDIRECT3DTEXTURE9 g_pTexturebackground_00 = NULL;				//�X�e�[�W1

LPDIRECT3DTEXTURE9 g_pTexturePlay = NULL;						//�Đ��}�[�N
int g_nCountersAnimationPlay;									//�Đ��}�[�N�̃R�}���؂�ւ�
int g_nCountersAnimationCntPlay;								//�Đ��}�[�N�̃J�E���^�X�V

LPDIRECT3DTEXTURE9 g_pTextureStop = NULL;						//��~�}�[�N
int g_nCountersAnimationStop;									//��~�}�[�N�̃R�}���؂�ւ�
int g_nCountersAnimationCntStop;								//��~�}�[�N�̃J�E���^�X�V

//-------------------------------------------------------------------------------
//	�X�e�[�W1����������
//-------------------------------------------------------------------------------
HRESULT Initbackground_00(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�ϐ��錾
	VERTEX_2D *pVtx;


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/background.png", &g_pTexturebackground_00);		//�X�e�[�W1
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Plye.png", &g_pTexturePlay);						//�Đ��}�[�N
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Stop.png", &g_pTextureStop);						//��~�}�[�N

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffBackground_00,
		NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBackground_00->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCunBG = 0; nCunBG < MAX_POLYGON; nCunBG++)
	{
		switch (nCunBG)		//�|�W�V�����̐ݒ�(���_���W.pos)
		{
		case 0:					//�w�i

			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
			break;

		case 1:					//�Đ��}�[�N

			pVtx[0].pos = D3DXVECTOR3(0			 + 1210, MAX_PLAY_Y + 10, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0			 + 1210, 0          + 10, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(MAX_PLAY_X + 1210, MAX_PLAY_Y + 10, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(MAX_PLAY_X + 1210, 0          + 10, 0.0f);
			break;

		case 2:					//��~�}�[�N

			pVtx[0].pos = D3DXVECTOR3(0 + 500, MAX_STOP_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0 + 500, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(MAX_STOP_X + 500, MAX_STOP_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(MAX_STOP_X + 500, 0, 0.0f);
			break;
		}

		switch (nCunBG)		//�A�j���[�V�����p��switch(���_���.tex)
		{//�A�j���[�V��������
		case 1:					//�Đ��}�[�N

			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0);
			pVtx[2].tex = D3DXVECTOR2(0.25f, 1.0);
			pVtx[3].tex = D3DXVECTOR2(0.25f, 0.0);
			break;

		case 2:					//��~�}�[�N

			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0);
			pVtx[2].tex = D3DXVECTOR2(0.25f, 1.0);
			pVtx[3].tex = D3DXVECTOR2(0.25f, 0.0);
			break;

		default:				//�A�j���[�V�������Ȃ�

			pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
			pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
			pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
			pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);
			break;
		}

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBackground_00->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�X�e�[�W1�̏I������
//-------------------------------------------------------------------------------
void Uninitbackground_00(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBackground_00 != NULL)
	{
		g_pVtxBuffBackground_00->Release();
		g_pVtxBuffBackground_00 = NULL;
	}

	//�w�i�̊J��
	if (g_pTexturebackground_00 != NULL)
	{
		g_pTexturebackground_00->Release();
		g_pTexturebackground_00 = NULL;
	}

	//�Đ��}�[�N�̊J��
	if (g_pTexturePlay != NULL)
	{
		g_pTexturePlay->Release();
		g_pTexturePlay = NULL;
	}

	//��~�}�[�N�̊J��
	if (g_pTextureStop != NULL)
	{
		g_pTextureStop->Release();
		g_pTextureStop = NULL;
	}
}

//-------------------------------------------------------------------------------
//	�X�e�[�W1�̍X�V����
//-------------------------------------------------------------------------------
void Updatebackground_00(void)
{
	VERTEX_2D *pVtx;

	g_nCountersAnimationCntPlay++;
	g_nCountersAnimationCntStop++;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBackground_00->Lock(0, 0, (void**)&pVtx, 0);

	//�A�j���[�V�����Đ��}�[�N
	if ((g_nCountersAnimationCntPlay %MAX_PLAY_COUNTER) == 0)							//�A�j���[�V�����̃J�E���g
	{
		g_nCountersAnimationPlay = (g_nCountersAnimationPlay + 1) % MAX_PLAY_PATTERN;	//�A�j���[�V�����̃R�}��

		//�A�j���[�V�����̒��_���̐ݒ�
		pVtx[4].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationPlay * 0.25f, 1.0f);
		pVtx[5].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationPlay * 0.25f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.25f + g_nCountersAnimationPlay * 0.25f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(0.25f + g_nCountersAnimationPlay * 0.25f, 0.0f);
	}

	//�A�j���[�V������~�}�[�N
	if ((g_nCountersAnimationCntStop %MAX_STOP_COUNTER) == 0)							//�A�j���[�V�����̃J�E���g
	{
		g_nCountersAnimationStop = (g_nCountersAnimationStop + 1) % MAX_STOP_PATTERN;	//�A�j���[�V�����̃R�}��

		//�A�j���[�V�����̒��_���̐ݒ�
		pVtx[8].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationStop * 0.25f, 1.0f);
		pVtx[9].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationStop * 0.25f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.25f + g_nCountersAnimationStop * 0.25f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(0.25f + g_nCountersAnimationStop * 0.25f, 0.0f);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBackground_00->Unlock();
}

//-------------------------------------------------------------------------------
//	�X�e�[�W1�̕`�揈��
//-------------------------------------------------------------------------------
void Drawbackground_00(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBackground_00, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCunBG = 0; nCunBG < MAX_POLYGON; nCunBG++)
	{
		switch (nCunBG)
		{
		case 0:
			//�w�i�̐ݒ�
			pDevice->SetTexture(0, g_pTexturebackground_00);
			break;

		case 1:
			//�Đ��}�[�N�̐ݒ�
			pDevice->SetTexture(0, g_pTexturePlay);
			break;

		case 2:
			//�Đ��}�[�N�̐ݒ�
			pDevice->SetTexture(0, g_pTextureStop);
			break;
		}
		//�X�e�[�W�w�i�̕`��
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
			nCunBG * 4,			//�`����J�n���钸�_�C���f�b�N�X
			NUM_POLYGON);			//�`�悷��v���~�e�B�u��
	}
}