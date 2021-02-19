//--------------------------------------------------------------------------------
//
//	�`���[�g���A���̏��� [tutorial.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "tutorial.h"			// �`���[�g���A��
#include "fade.h"				// �t�F�[�h
#include "sound.h"				// BGM
#include "keyboard.h"			// �L�[�{�[�h
#include "Xcontroller.h"		// Xinput

//-------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------
#define MAX_POLYGON	(1)		// �e�N�X�`������

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;
LPDIRECT3DTEXTURE9 g_pTexTutorial = NULL;				// �`���[�g���A��

//-------------------------------------------------------------------------------
//	�^�C�g����ʏ���������
//-------------------------------------------------------------------------------
HRESULT InitTutorial(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ϐ��錾
	VERTEX_2D *pVtx;

	// BGM�̓ǂݍ���
	PlaySound(SOUND_LABEL_TUTORIAL);		// �`���[�g���A��BGM

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TutorialBG.png", &g_pTexTutorial);		// �`���[�g���A��

	// ���_�o�b�t�@�̐���
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

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

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
	g_pVtxBuffTutorial->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�`���[�g���A����ʂ̏I������
//-------------------------------------------------------------------------------
void UniniTtutorial(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

	// �e�N�X�`���̊J��(�`���[�g���A�����)
	if (g_pTexTutorial != NULL)
	{
		g_pTexTutorial->Release();
		g_pTexTutorial = NULL;
	}
}

//-------------------------------------------------------------------------------
//	�`���[�g���A����ʂ̍X�V����
//-------------------------------------------------------------------------------
void UpdateTutorial(void)
{
	int nFade = GetFade();

	if (nFade == FADE_NONE)
	{//�@�t�F�[�h���͓����Ȃ�
		if (GetkeyboardTrgger(DIK_RETURN) == true)
		{//�@�G���^�[�L�[��������
		 //�@�Q�[����ʂɈړ�
			SetFade(FADE_OUT, MODE_BEGINNING);

			//���~�߂�
			StopSound();
		}
	}
}

//-------------------------------------------------------------------------------
//	�`���[�g���A����ʂ̕`�揈��
//-------------------------------------------------------------------------------
void DrawtuTorial(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�(�`���[�g���A��)
	pDevice->SetTexture(0, g_pTexTutorial);

	// �`���[�g���A����ʂ̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,						// �`����J�n���钸�_�C���f�b�N�X
		2);						// �`�悷��v���~�e�B�u��
}