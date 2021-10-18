//--------------------------------------------------------------------------------
//
//	�^�C�g����ʂ̏��� [title.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "title.h"
#include "keyboard.h"
#include "fade.h"
#include "Select.h"
#include "sound.h"

//-------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------
#define MAX_POLYGON				(3)		//�|���S����

#define PRESSENTER_X			(490)	//�v���X�G���^�[�̕�
#define PRESSENTER_Y			(90)	//�v���X�G���^�[�̍���

#define GIRL_X					(320)	//�����̕�
#define GIRL_Y					(700)	//�����̍���
#define MAX_ANIMATION_COUNTER	(6)		//����(�X�s�[�h)
#define MAX_ANIMATION_PATTERN	(10)	//����(��)

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;

LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;			// �^�C�g�����
													   
LPDIRECT3DTEXTURE9 g_pPressEnter = NULL;			// �v���X�G���^�[
D3DCOLOR g_col;										// �J���[
int g_nCount;										// �J�E���g
bool g_bPressEnter;									// �L�[��������

int nPressEnter;									// �v���X�G���^�[��������
													   
LPDIRECT3DTEXTURE9 g_pGirl = NULL;					// ����
D3DXVECTOR3 g_posAnimationGirl;						// X,Y,Z�����߂�
int g_nCountersAnimationGirl;						// ����(�R�}���̐؂�ւ�)
int g_nCountersAnimationCntGirl;					// ����(�J�E���^�X�V)
													   
bool g_bSelect = false;								// �Z���N�g�����ǂ���
//-------------------------------------------------------------------------------
//	�^�C�g����ʏ���������
//-------------------------------------------------------------------------------
HRESULT InitTitle(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�ϐ��錾
	VERTEX_2D *pVtx;

	//BGM�̒ǉ�
	PlaySound(SOUND_LABEL_BGM000);	//�^�C�g��BGM

	// ������
	nPressEnter = 0;
	


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Title.png", &g_pTextureTitle);				//�^�C�g�����
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/press_enter.png", &g_pPressEnter);			//�v���X�G���^�[
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Girl.png", &g_pGirl);						//����

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCunTitle = 0; nCunTitle < MAX_POLYGON; nCunTitle++)
	{

		switch (nCunTitle)		//�|�W�V�����̐ݒ�(���_���W.pos)
		{
		case 0:					//�w�i

			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
			break;


		case 1:					//�v���X�G���^�[

			pVtx[0].pos = D3DXVECTOR3(0			   + 200, PRESSENTER_Y + 500, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0			   + 200,			 0 + 500, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(PRESSENTER_X + 200, PRESSENTER_Y + 500, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(PRESSENTER_X + 200,			 0 + 500, 0.0f);
			break;

		case 2:					//����

			pVtx[0].pos = D3DXVECTOR3(0      + 850, GIRL_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0      + 850, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(GIRL_X + 850, GIRL_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(GIRL_X + 850, 0, 0.0f);
			break;
		}

		switch (nCunTitle)		//�A�j���[�V�����p��switch(���_���.tex)
		{//�A�j���[�V��������
		case 2:					//����

			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);
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
	g_pVtxBuffTitle->Unlock();

	//�Z���N�g�̏���������
	InitSelect();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�^�C�g����ʂ̏I������
//-------------------------------------------------------------------------------
void UninitTitle(void)
{
	g_bSelect = false;		//�Z���N�g�I��

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	//�^�C�g����ʂ̊J��
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	//�v���X�G���^�[�̊J��
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	//�����̊J��
	if (g_pGirl != NULL)
	{
		g_pGirl->Release();
		g_pGirl = NULL;
	}

	//���~�߂�
	StopSound();

	//�Z���N�g�̏I������
	UninitSelect();
}

//-------------------------------------------------------------------------------
//	�^�C�g����ʂ̍X�V����
//-------------------------------------------------------------------------------
void UpdateTitle(void)
{
	VERTEX_2D *pVtx;

	int nFade = GetFade();

	g_nCountersAnimationCntGirl++;

	g_nCount++;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	if (nFade == FADE_NONE)
	{//�t�F�[�h���͓����Ȃ�

		// �J�E���^���X�V
		if (0 == g_nCount % 70)
		{
			pVtx[4].col = D3DCOLOR_RGBA(255,255,255, 0);
			pVtx[5].col = D3DCOLOR_RGBA(255,255,255, 0);
			pVtx[6].col = D3DCOLOR_RGBA(255,255,255, 0);
			pVtx[7].col = D3DCOLOR_RGBA(255,255,255, 0);
		}
		else if (g_nCount  %100  )
		{
			pVtx[4].col = D3DCOLOR_RGBA(255,255,255, 255);
			pVtx[5].col = D3DCOLOR_RGBA(255,255,255, 255);
			pVtx[6].col = D3DCOLOR_RGBA(255,255,255, 255);
			pVtx[7].col = D3DCOLOR_RGBA(255,255,255, 255);
		}


		if (g_bSelect == true)
		{//�Z���N�g��\��

		 //�Z���N�g
			UpdateSelect();

			//�v�b�V���G���^�[�������Ȃ�����
			pVtx[4].col = D3DCOLOR_RGBA(0, 0, 0, 0);
			pVtx[5].col = D3DCOLOR_RGBA(0, 0, 0, 0);
			pVtx[6].col = D3DCOLOR_RGBA(0, 0, 0, 0);
			pVtx[7].col = D3DCOLOR_RGBA(0, 0, 0, 0);
		}
		else if (g_bSelect == false)
		{//�Z���N�g���\������ĂȂ��Ƃ�
			if (GetkeyboardTrgger(DIK_RETURN) == true)
			{//ENTER�L�[��������
				g_bSelect = true;

				//SE�̒ǉ�
				PlaySound(SOUND_LABEL_SE_ON);	//�I��
			}
		}
	}

	//�A�j���[�V����(����)
	if ((g_nCountersAnimationCntGirl %MAX_ANIMATION_COUNTER) == 0)	//�A�j���[�V�����̃J�E���g
	{
		g_nCountersAnimationGirl = (g_nCountersAnimationGirl + 1) % MAX_ANIMATION_PATTERN;	//�A�j���[�V�����̃R�}��

		//�A�j���[�V�����̒��_���̐ݒ�
		pVtx[8].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationGirl * 0.1f, 1.0f);
		pVtx[9].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationGirl * 0.1f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.1f + g_nCountersAnimationGirl * 0.1f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(0.1f + g_nCountersAnimationGirl * 0.1f, 0.0f);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}

//-------------------------------------------------------------------------------
//	�^�C�g����ʂ̕`�揈��
//-------------------------------------------------------------------------------
void DrawTitle(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < MAX_POLYGON; nCntTitle++)
	{
		switch (nCntTitle)
		{
		case 0:
			//�^�C�g����ʂ̐ݒ�
			pDevice->SetTexture(0, g_pTextureTitle);
			break;

		case 1:
			//�v���X�G���^�[�̐ݒ�
			pDevice->SetTexture(0, g_pPressEnter);
			break;

		case 2:
			//�����̐ݒ�
			pDevice->SetTexture(0, g_pGirl);
			break;
		}
		//�^�C�g���̕`��
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
			nCntTitle * 4,			//�`����J�n���钸�_�C���f�b�N�X
			NUM_POLYGON);			//�`�悷��v���~�e�B�u��
	}

	if (g_bSelect == true)
	{//g_bSelect���I���̎��`�悷��
	 //�Z���N�g
		DrawSelect();
	}
}