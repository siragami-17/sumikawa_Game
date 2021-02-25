//--------------------------------------------------------------------------------
//
//	�|�[�Y�̏��� [Pause.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "pause.h"
#include "keyboard.h"
#include "fade.h"
#include "game.h"
#include"sound.h"

//-------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------
#define MAX_POLYGON		(7)		// �|�[�Y��
#define MERU_DISTANCE	(100)	// ���j���[�ԋ���

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
PAUSE g_aPause[MAX_POLYGON];							// �|�[�Y�̏��	

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;

LPDIRECT3DTEXTURE9 g_pTexturePause = NULL;				// �w�i
LPDIRECT3DTEXTURE9 g_pGra = NULL;						// �w�i(����Ɍ��)

LPDIRECT3DTEXTURE9 g_apMenu[PAUSE_MENU_MAX] = {};		// ���j���[1�`3

LPDIRECT3DTEXTURE9 g_pMenu_4 = NULL;					// �|�[�Y

LPDIRECT3DTEXTURE9 g_pMenu_5 = NULL;					// ��
D3DXVECTOR3 g_posBall;									// �ʒu

int g_nCountPause;

//-------------------------------------------------------------------------------
//	�|�[�Y����������
//-------------------------------------------------------------------------------
HRESULT InitPause(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// �J�[�\���ƑI����e�̏�����
	g_posBall.y = 0;
	g_nCountPause = 0;

	// �X�g�b�v�̍\���̂̏���������
	g_aPause[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// �ʒu

	// �ϐ��錾
	VERTEX_2D *pVtx;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Slect.png", &g_pTexturePause);							// �w�i
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause000.png", &g_apMenu[PAUSE_MENU_CONTINOE]);		// ���j���[1
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause001.png", &g_apMenu[PAUSE_MENU_RETRY]);			// ���j���[2
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause002.png", &g_apMenu[PAUSE_MENU_QUIT]);			// ���j���[3
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause004.png", &g_pMenu_4);							// �|�[�Y
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Cursor.png", &g_pMenu_5);								// ��

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,						   
		FVF_VERTEX_2D,							// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountPause = 0; nCountPause < MAX_POLYGON; nCountPause++)
	{
		switch (nCountPause)	// �|�W�V�����̐ݒ�
		{
		case 0:
			// ���_���W(�D�F)
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

			break;

		case 1:
			// ���_���W(�w�i)
			pVtx[0].pos = D3DXVECTOR3(200 + 250, 610, 0.0f);		//����
			pVtx[1].pos = D3DXVECTOR3(200 + 250, 110, 0.0f);		//����
			pVtx[2].pos = D3DXVECTOR3(600 + 250, 610, 0.0f);		//�E��
			pVtx[3].pos = D3DXVECTOR3(600 + 250, 110, 0.0f);		//�E��

			break;



		case 5:
			// ���_���W(���j���[4)
			pVtx[0].pos = D3DXVECTOR3(0 + 480, 60 + 150, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0 + 480, 0 + 150, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(320 + 480, 60 + 150, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(320 + 480, 0 + 150, 0.0f);

			break;

		case 6:
			// ���_���W(���j���[��)
			pVtx[0].pos = D3DXVECTOR3(0 + 480, 50 + 300, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0 + 480, 0 + 300, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(50 + 480, 50 + 300, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(50 + 480, 0 + 300, 0.0f);

			break;

		default:	// ��L�ȊO

			// ���_���W(���j���[1�`3)
			pVtx[0].pos = D3DXVECTOR3(0 + 480, 60 + 100.0f * nCountPause + MERU_DISTANCE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0 + 480, 0 + 100.0f * nCountPause + MERU_DISTANCE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(320 + 480, 60 + 100.0f * nCountPause + MERU_DISTANCE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(320 + 480, 0 + 100.0f * nCountPause + MERU_DISTANCE, 0.0f);

			break;
		}

		switch (nCountPause)	// �J���[�p��switch(���_�J���[.col)
		{	// �J���[�ύX������
		case 0:

			pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 100);
			pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 100);
			pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 100);
			pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 100);
			break;

		case 2:

			pVtx[0].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			break;

		case 3:

			pVtx[0].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			break;

		case 4:

			pVtx[0].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(0, 0, 255, 255);
			break;

		default:	// �J���[�ύX�Ȃ�

			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			break;
		}

		switch (nCountPause)	// �A�j���[�V�����p��switch(���_���.tex)
		{	// �A�j���[�V��������

		case 6:// ��

			pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);	// ����
			pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);	// ����
			pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);	// �E��
			pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);	// �E��
			break;

		default:	// �A�j���[�V�������Ȃ�

			pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);	// ����
			pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);	// ����
			pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);	// �E��
			pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);	// �E��
			break;
		}

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�|�[�Y�̏I������
//-------------------------------------------------------------------------------
void UninitPause(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

	// �e�N�X�`���̊J��(�D�F)
	if (g_pGra != NULL)
	{
		g_pGra->Release();
		g_pGra = NULL;
	}

	// �e�N�X�`���̊J��(�w�i)
	if (g_pTexturePause != NULL)
	{
		g_pTexturePause->Release();
		g_pTexturePause = NULL;
	}

	// �e�N�X�`���̊J��(���j���[1�`3)
	for (int nCntPause = 0; nCntPause < PAUSE_MENU_MAX; nCntPause++)
	{
		if (g_apMenu[nCntPause] != NULL)
		{
			g_apMenu[nCntPause]->Release();
			g_apMenu[nCntPause] = NULL;
		}
	}

	// �e�N�X�`���̊J��(���j���[3)
	if (g_pMenu_4 != NULL)
	{
		g_pMenu_4->Release();
		g_pMenu_4 = NULL;
	}

	// �e�N�X�`���̊J��(���j���[3)
	if (g_pMenu_5 != NULL)
	{
		g_pMenu_5->Release();
		g_pMenu_5 = NULL;
	}

}

//-------------------------------------------------------------------------------
//	�|�[�Y�̍X�V����
//-------------------------------------------------------------------------------
void UpdatePause(void)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;

	int nFade = GetFade();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);


	if (nFade == FADE_NONE)
	{// �t�F�[�h���͓����Ȃ�
		if (GetkeyboardTrgger(DIK_W) == true)
		{// ��Ɉړ�
			g_nCountPause--;

			g_posBall.y -= 100;

			// SE�̒ǉ�
			PlaySound(SOUND_LABEL_SE_CHOICE);	// �I��

			if (g_nCountPause < PAUSE_MENU_CONTINOE)
			{// ���j���[�̍ő吔�Ɉړ�
				g_nCountPause = PAUSE_MENU_QUIT;
			}
		}

		if (GetkeyboardTrgger(DIK_S) == true)
		{// ���Ɉړ�
			g_nCountPause++;

			g_posBall.y += 100;

			// SE�̒ǉ�
			PlaySound(SOUND_LABEL_SE_CHOICE);	// �I��

			if (g_nCountPause > PAUSE_MENU_QUIT)
			{// ���j���[�̍ŏ����Ɉړ�
				g_nCountPause = PAUSE_MENU_CONTINOE;
			}
		}

		if (GetkeyboardTrgger(DIK_RETURN) == true)
		{// ����
			if (g_nCountPause == PAUSE_MENU_CONTINOE)
			{//���j���[1�̎�	
				SetPause(false);

				// SE�̒ǉ�
				PlaySound(SOUND_LABEL_SE_OFF);	// �I�t
			}

			if (g_nCountPause == PAUSE_MENU_RETRY)
			{// ���j���[2�̎�	

			 // �Q�[����ʂɈړ�
				SetFade(FADE_OUT, MODE_GAME);
			}

			if (g_nCountPause == PAUSE_MENU_QUIT)
			{// ���j���[3�̎�	

			 // �^�C�g���̈ړ�
				SetFade(FADE_OUT, MODE_TITLE);

			}
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	if (g_posBall.y < 0)
	{// �J�[�\�����I��1�ɂ������Ƃ�
		g_posBall.y = 200;				// �I��3�Ɉړ�
	}

	if (g_posBall.y > 200)
	{// �J�[�\�����I��3�ɂ������Ƃ�
		g_posBall.y = 0;				// �I��1�Ɉړ�
	}

	// ���_���W(���j���[��)
	pVtx[24].pos = D3DXVECTOR3(0 + 480, 50 + 300 + g_posBall.y, 0.0f);
	pVtx[25].pos = D3DXVECTOR3(0 + 480, 0 + 300 + g_posBall.y, 0.0f);
	pVtx[26].pos = D3DXVECTOR3(50 + 480, 50 + 300 + g_posBall.y, 0.0f);
	pVtx[27].pos = D3DXVECTOR3(50 + 480, 0 + 300 + g_posBall.y, 0.0f);

}

//-------------------------------------------------------------------------------
//	�|�[�Y�̕`�揈��
//-------------------------------------------------------------------------------
void DrawPause(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePause);

	for (int nCntTitle = 0; nCntTitle < MAX_POLYGON; nCntTitle++)
	{
		switch (nCntTitle)
		{
		case 0:
			// �^�C�g��(�|�[�Y)�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pGra);
			break;

		case 1:
			// �^�C�g��(�|�[�Y)�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePause);
			break;

		case 2:
			// �^�C�g��(�|�[�Y)�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apMenu[PAUSE_MENU_CONTINOE]);
			break;

		case 3:
			// �^�C�g��(�|�[�Y)�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apMenu[PAUSE_MENU_RETRY]);
			break;

		case 4:
			// �^�C�g��(�|�[�Y)�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apMenu[PAUSE_MENU_QUIT]);
			break;

		case 5:
			// �^�C�g��(�|�[�Y)�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pMenu_4);
			break;

		case 6:
			// �^�C�g��(�|�[�Y)�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pMenu_5);
			break;
		}
		// �|�[�Y�̕`��
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
			nCntTitle * 4,			// �`����J�n���钸�_�C���f�b�N�X
			2);						// �`�悷��v���~�e�B�u��
	}
}