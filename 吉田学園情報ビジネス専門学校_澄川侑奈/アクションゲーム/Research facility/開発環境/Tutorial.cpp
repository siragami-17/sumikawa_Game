//--------------------------------------------------------------------------------
//
//	�`���[�g���A����ʂ̏��� [Tutorial.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Tutorial.h"										// �`���[�g���A��
#include "keyboard.h"										// �L�[�{�[�h
#include "fade.h"											// �t�F�[�h
#include "sound.h"											// �T�E���h

//-------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------
#define MAX_POLYGON					(6)						// �|���S����

#define PLAYER_X					(428)					// �����̕�
#define PLAYER_Y					(430)					// �����̍���
#define MAX_ANIMATION_COUNTER_GIRL	(5)						// �X�s�[�h
#define MAX_ANIMATION_PATTERN_GIRL	(20)					// �摜�R�}��
#define DIVISION_GIRL				(0.05f)					// ����Z

#define HELP_X						(50 + HELP_POS_X)		// ����������̕�
#define HELP_Y						(120 + HELP_POS_Y)		// ����������̍���
#define HELP_POS_X					(750)					// �ʒu(X)
#define HELP_POS_Y					(450)					// �ʒu(Y)

#define UI_X						(690 + UI_POS_X)		// �`���[�g���A���̕�
#define UI_Y						(171 + UI_POS_Y)		// �`���[�g���A���̍���
#define UI_POS_X					(300)					// �ʒu(X)
#define UI_POS_Y					(20)					// �ʒu(Y)
#define MAX_ANIMATION_COUNTER		(6)						// �X�s�[�h
#define MAX_ANIMATION_PATTERN		(8)						// �摜�R�}��
#define DIVISION					(0.125f)				// ����Z

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;

LPDIRECT3DTEXTURE9 g_pTextureGirl = NULL;				// ����
int g_nCountersAnimation_Girl;							// �R�}���̐؂�ւ�
int g_nCountersAnimationCnt_Girl;						// �J�E���^�X�V

LPDIRECT3DTEXTURE9 g_pTextureHelp = NULL;				// ����������
D3DXVECTOR3 g_posHelp;									// �ʒu

LPDIRECT3DTEXTURE9 g_pTextureFframe = NULL;				// �g

LPDIRECT3DTEXTURE9 g_pTextureGround = NULL;				// �n��

LPDIRECT3DTEXTURE9 g_pTextureUI = NULL;					// UI
D3DXVECTOR3 g_posUI;									// �ʒu
int g_nCountersAnimation_UI;							// �R�}���̐؂�ւ�
int g_nCountersAnimationCnt_UI;							// �J�E���^�X�V

LPDIRECT3DTEXTURE9 g_pTextureBall = NULL;				// ��


//-------------------------------------------------------------------------------
//	�`���[�g���A���̏���������
//-------------------------------------------------------------------------------
HRESULT InitTutorial(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// �ϐ��錾
	VERTEX_2D *pVtx;

	// BGM�̒ǉ�
	PlaySound(SOUND_LABEL_BGM001);		// �`���[�g���A��BGM

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Tutorial_Girl.png", &g_pTextureGirl);			// ����
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Tutorial_Help.png", &g_pTextureHelp);			// ����������
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Tutorial_Frame.png", &g_pTextureFframe);		// �g
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Tutorial_Ground.png", &g_pTextureGround);		// �n��
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Tutorial_UI.png", &g_pTextureUI);				// UI
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Tutorial_Ball.png", &g_pTextureBall);			// ��

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL)))
	{
		return E_FAIL;
	}


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCunTutorial = 0; nCunTutorial < MAX_POLYGON; nCunTutorial++)
	{
		// ���_���W�̐ݒ�
		switch (nCunTutorial)
		{
		case 0:						// �n��
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
			break;

		case 1:						// �g
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
			break;

		case 2:						// ����
			pVtx[0].pos = D3DXVECTOR3(0 + PLAYER_X, 275 + PLAYER_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0 + PLAYER_X, 0 + PLAYER_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(203 + PLAYER_X, 275 + PLAYER_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(203 + PLAYER_X, 0 + PLAYER_Y, 0.0f);
			break;

		case 3:						// ����������
			pVtx[0].pos = D3DXVECTOR3(g_posHelp.x + HELP_POS_X, g_posHelp.y + HELP_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posHelp.x + HELP_POS_X, g_posHelp.y + HELP_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posHelp.x + HELP_X, g_posHelp.y + HELP_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posHelp.x + HELP_X, g_posHelp.y + HELP_POS_Y, 0.0f);
			break;

		case 4:						// UI 
			pVtx[0].pos = D3DXVECTOR3(g_posUI.x + UI_POS_X, g_posUI.y + UI_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posUI.x + UI_POS_X, g_posUI.y + UI_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posUI.x + UI_X, g_posUI.y + UI_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posUI.x + UI_X, g_posUI.y + UI_POS_Y, 0.0f);
			break;

		case 5:						// �� 
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
			break;	    
		}

		// ���_���̐ݒ�
		switch (nCunTutorial)
		{// �A�j���[�V��������
		case 2:						// ����
			pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
			pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
			pVtx[2].tex = D3DXVECTOR2(DIVISION_GIRL, 1.0);
			pVtx[3].tex = D3DXVECTOR2(DIVISION_GIRL, 0.0);
			break;

		case 4:						// UI
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(DIVISION, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(DIVISION, 0.0f);
			break;

		// �A�j���[�V�������Ȃ�
		default:
			pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
			pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
			pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
			pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);
			break;

		}

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

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�`���[�g���A���̏I������
//-------------------------------------------------------------------------------
void UninitTutorial(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

	// �e�N�X�`���̊J��
	// �n��
	if (g_pTextureGround != NULL)
	{
		g_pTextureGround->Release();
		g_pTextureGround = NULL;
	}

	// �g
	if (g_pTextureFframe != NULL)
	{
		g_pTextureFframe->Release();
		g_pTextureFframe = NULL;
	}

	// ����
	if (g_pTextureGirl != NULL)
	{
		g_pTextureGirl->Release();
		g_pTextureGirl = NULL;
	}

	// ����������
	if (g_pTextureHelp != NULL)
	{
		g_pTextureHelp->Release();
		g_pTextureHelp = NULL;
	}

	// UI
	if (g_pTextureUI != NULL)
	{
		g_pTextureUI->Release();
		g_pTextureUI = NULL;
	}

	// ��
	if (g_pTextureBall != NULL)
	{
		g_pTextureBall->Release();
		g_pTextureBall = NULL;
	}

	// ���~�߂�
	StopSound();
}

//-------------------------------------------------------------------------------
//	�X�e�[�W1�̍X�V����
//-------------------------------------------------------------------------------
void UpdateTutorial(void)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;

	int nFade = GetFade();

	if (nFade == FADE_NONE)
	{// �t�F�[�h���͓����Ȃ�
		if (GetkeyboardTrgger(DIK_RETURN) == true)
		{// �G���^�[�L�[��������
		 // �X�e�[�W1�Ɉړ�
			SetFade(FADE_OUT, MODE_GAME_00);
		}
	}

	g_nCountersAnimationCnt_UI++;
	g_nCountersAnimationCnt_Girl++;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	// �A�j���[�V�����̏���
	// ����
	if ((g_nCountersAnimationCnt_Girl %MAX_ANIMATION_COUNTER_GIRL) == 0)	// �A�j���[�V�����̃J�E���g
	{
		g_nCountersAnimation_Girl = (g_nCountersAnimation_Girl + 1) % MAX_ANIMATION_PATTERN_GIRL;	// �A�j���[�V�����̃R�}��

		// �A�j���[�V�����̒��_���̐ݒ�
		pVtx[8].tex = D3DXVECTOR2(0.0f + g_nCountersAnimation_Girl * DIVISION_GIRL, 1.0f);
		pVtx[9].tex = D3DXVECTOR2(0.0f + g_nCountersAnimation_Girl * DIVISION_GIRL, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(DIVISION_GIRL + g_nCountersAnimation_Girl * DIVISION_GIRL, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(DIVISION_GIRL + g_nCountersAnimation_Girl * DIVISION_GIRL, 0.0f);
	}

	// UI
	if ((g_nCountersAnimationCnt_UI %MAX_ANIMATION_COUNTER) == 0)	// �A�j���[�V�����̃J�E���g
	{
		g_nCountersAnimation_UI = (g_nCountersAnimation_UI + 1) % MAX_ANIMATION_PATTERN;	// �A�j���[�V�����̃R�}��

		// �A�j���[�V�����̒��_���̐ݒ�
		pVtx[16].tex = D3DXVECTOR2(0.0f + g_nCountersAnimation_UI * DIVISION, 1.0f);
		pVtx[17].tex = D3DXVECTOR2(0.0f + g_nCountersAnimation_UI * DIVISION, 0.0f);
		pVtx[18].tex = D3DXVECTOR2(DIVISION + g_nCountersAnimation_UI * DIVISION, 1.0f);
		pVtx[19].tex = D3DXVECTOR2(DIVISION + g_nCountersAnimation_UI * DIVISION, 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();

}

//-------------------------------------------------------------------------------
//	�X�e�[�W1�̕`�揈��
//-------------------------------------------------------------------------------
void DrawTutorial(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCunTutorial = 0; nCunTutorial < MAX_POLYGON; nCunTutorial++)
	{
		switch (nCunTutorial)
		{// �e�N�X�`���̐ݒ�
		case 0:
			// �n��
			pDevice->SetTexture(0, g_pTextureGround);
			break;
		case 1:
			// �g
			pDevice->SetTexture(0, g_pTextureFframe);
			break;

		case 2:
			// ����
			pDevice->SetTexture(0, g_pTextureGirl);
			break;

		case 3:
			// ����������
			pDevice->SetTexture(0, g_pTextureHelp);
			break;

		case 4:
			// UI
			pDevice->SetTexture(0, g_pTextureUI);
			break;

		case 5:
			// ��
			pDevice->SetTexture(0, g_pTextureBall);
			break;
		}
			// �`���[�g���A���̕`��
			pDevice->DrawPrimitive
			(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
				nCunTutorial * 4,		// �`����J�n���钸�_�C���f�b�N�X
				NUM_POLYGON);			// �`�悷��v���~�e�B�u��
	}
}