//--------------------------------------------------------------------------------
//
//	�Z���N�g�̏��� [Select.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Select.h"
#include "keyboard.h"
#include "fade.h"
#include "sound.h"

//-------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------
#define MAX_POLYGON			(5)				//�|�[�Y��
#define MERU_DISTANCE		(150)			//�Z���N�g���S�̊ԋ���
#define MAX_BACKGROUND_X	(440)			//�Z���N�g�w�i�̕�
#define MAX_BACKGROUND_Y	(460)			//�Z���N�g�w�i�̍���

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelect = NULL;

LPDIRECT3DTEXTURE9 g_pTextureSelect = NULL;						//�w�i

LPDIRECT3DTEXTURE9 g_apSelectLogo[SELECT_MENU_MAX] = {};		//�Z���N�g���S1�`3

LPDIRECT3DTEXTURE9 g_pCursor = NULL;							//�J�[�\��
D3DXVECTOR3 g_posCursor;	//X,Y,Z�����߂�

int g_nCountSelect;

//-------------------------------------------------------------------------------
//	�|�[�Y����������
//-------------------------------------------------------------------------------
HRESULT InitSelect(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�J�[�\���ƑI����e�̏�����
	g_posCursor.y = 0;
	g_nCountSelect = SELECT_MENU_TUTORIAL;

	//�ϐ��錾
	VERTEX_2D *pVtx;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Slect.png", &g_pTextureSelect);									//�w�i
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Tutorial.png", &g_apSelectLogo[SELECT_MENU_TUTORIAL]);				//�`���[�g���A��
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/GameStart.png", &g_apSelectLogo[SELECT_MENU_GAMESTART]);			//�Q�[���X�^�[�g
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/CharacterChange.png", &g_apSelectLogo[SELECT_MODE_END]);			//�L�����N�^�[�ύX
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Cursor.png", &g_pCursor);											//�J�[�\��

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelect,
		NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountSelect = 0; nCountSelect < MAX_POLYGON; nCountSelect++)
	{
		switch (nCountSelect)	//�|�W�V�����̐ݒ�
		{
		case 0:
			//�w�i
			pVtx[0].pos = D3DXVECTOR3(0				   + 210, MAX_BACKGROUND_Y + 150, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0				   + 210, 0			       + 150, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(MAX_BACKGROUND_X + 210, MAX_BACKGROUND_Y + 150, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(MAX_BACKGROUND_X + 210, 0			       + 150, 0.0f);

			break;

		case 4:
			//�J�[�\��
			pVtx[0].pos = D3DXVECTOR3(0  + 350, 50  + 375, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0  + 350, 0   + 375, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(50 + 350, 50 + 375, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(50 + 350, 0  + 375, 0.0f);

			break;

		default:	//��L�ȊO

			//�Z���N�g���S1�`3
			pVtx[0].pos = D3DXVECTOR3(0	  + 280, 180  + 100.0f * nCountSelect + 50, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0   + 280, 120  + 100.0f * nCountSelect + 50, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(320 + 280, 180  + 100.0f * nCountSelect + 50, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(320 + 280, 120  + 100.0f * nCountSelect + 50, 0.0f);

			break;
		}

		//���_�J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		switch (nCountSelect)	//�A�j���[�V�����p��switch(���_���.tex)
		{//�A�j���[�V��������

		case 4:		//�J�[�\��

			pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);	//����
			pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);	//����
			pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);	//�E��
			pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);	//�E��
			break;

		default:	//�A�j���[�V�������Ȃ�

			pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);	//����
			pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);	//����
			pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);	//�E��
			pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);	//�E��
			break;
		}

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelect->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�|�[�Y�̏I������
//-------------------------------------------------------------------------------
void UninitSelect(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffSelect != NULL)
	{
		g_pVtxBuffSelect->Release();
		g_pVtxBuffSelect = NULL;
	}

	//�e�N�X�`���̊J��(�w�i)
	if (g_pTextureSelect != NULL)
	{
		g_pTextureSelect->Release();
		g_pTextureSelect = NULL;
	}

	//�e�N�X�`���̊J��(�Z���N�g���S1�`3)
	for (int nCntSelect = 0; nCntSelect < SELECT_MENU_MAX; nCntSelect++)
	{
		if (g_apSelectLogo[nCntSelect] != NULL)
		{
			g_apSelectLogo[nCntSelect]->Release();
			g_apSelectLogo[nCntSelect] = NULL;
		}
	}

	//�e�N�X�`���̊J��(�J�[�\��)
	if (g_pCursor != NULL)
	{
		g_pCursor->Release();
		g_pCursor = NULL;
	}

}

//-------------------------------------------------------------------------------
//	�|�[�Y�̍X�V����
//-------------------------------------------------------------------------------
void UpdateSelect(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	int nFade = GetFade();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);


	if (nFade == FADE_NONE)
	{//�t�F�[�h���͓����Ȃ�
		if (GetkeyboardTrgger(DIK_W) == true)
		{//���Ɉړ�
			g_nCountSelect -= 1;

			g_posCursor.y -= 100;

			if (g_nCountSelect < SELECT_MENU_TUTORIAL)
			{//���j���[�̍ő吔�Ɉړ�
				g_nCountSelect = SELECT_MODE_END;
			}
		}

		if (GetkeyboardTrgger(DIK_S) == true)
		{//���Ɉړ�
			g_nCountSelect += 1;

			g_posCursor.y += 100;

			if (g_nCountSelect > SELECT_MODE_END)
			{//���j���[�̍ŏ����Ɉړ�
				g_nCountSelect = SELECT_MENU_TUTORIAL;
			}
		}

		if (GetkeyboardTrgger(DIK_RETURN) == true)
		{//�G���^�[�L�[��������
			if (g_nCountSelect == SELECT_MENU_TUTORIAL)
			{//�`���[�g���A���̎�	

				//�`���[�g���A����ʂɈړ�
				SetFade(FADE_OUT, MODE_TUTORIAL);

			}
			else if (g_nCountSelect == SELECT_MENU_GAMESTART)
			{//�Q�[���X�^�[�g�̎�	

				//�Q�[����ʂɈړ�
				SetFade(FADE_OUT, MODE_GAME_00);
			}
			else if (g_nCountSelect == SELECT_MODE_END)
			{//�Q�[���I���̎�	

				//�x�����o��
				//SetMode(MODE_END);
				//ESC�Ɠ���
			}
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelect->Unlock();

	if (g_posCursor.y < 0)
	{//�J�[�\�����I��1�ɂ������Ƃ�
		g_posCursor.y = 200;				//�I��3�Ɉړ�
	}

	if (g_posCursor.y > 200)
	{//�J�[�\�����I��3�ɂ������Ƃ�
		g_posCursor.y = 0;					//�I��1�Ɉړ�
	}

	//���_���W(�J�[�\��)
	pVtx[16].pos = D3DXVECTOR3(0  + 250, 50 + 270 + g_posCursor.y, 0.0f);
	pVtx[17].pos = D3DXVECTOR3(0  + 250, 0  + 270  + g_posCursor.y, 0.0f);
	pVtx[18].pos = D3DXVECTOR3(50 + 250, 50 + 270 + g_posCursor.y, 0.0f);
	pVtx[19].pos = D3DXVECTOR3(50 + 250, 0  + 270  + g_posCursor.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelect->Unlock();
}

//-------------------------------------------------------------------------------
//	�|�[�Y�̕`�揈��
//-------------------------------------------------------------------------------
void DrawSelect(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSelect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < MAX_POLYGON; nCntTitle++)
	{
		switch (nCntTitle)
		{
		case 0:
			//�Z���N�g�w�i�̃e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSelect);
			break;

		case 1:
			//�`���[�g���A���̃e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apSelectLogo[SELECT_MENU_TUTORIAL]);
			break;

		case 2:
			//�Q�[���X�^�[�g�̃e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apSelectLogo[SELECT_MENU_GAMESTART]);
			break;

		case 3:
			//�L�����N�^�[�ύX�̃e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apSelectLogo[SELECT_MODE_END]);
			break;

		case 4:
			//�J�[�\���̃e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pCursor);
			break;
		}
		//�Z���N�g�̕`��
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
			nCntTitle * 4,			//�`����J�n���钸�_�C���f�b�N�X
			2);						//�`�悷��v���~�e�B�u��
	}
}