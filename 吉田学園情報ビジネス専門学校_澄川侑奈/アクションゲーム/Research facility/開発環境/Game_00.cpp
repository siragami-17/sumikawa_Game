//--------------------------------------------------------------------------------
//
//	�X�e�[�W1�̏��� [Game_00.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "main.h"
#include "Player.h"				// �v���C���[
#include "block.h"				// �u���b�N
#include "background_00.h"		// �Q�[���w�i
#include "mark.h"				// �J�[�\��
#include "StopBG.h"				// ��~�w�i
#include "keyboard.h"			// �L�[�{�[�h
#include "pause.h"				// �|�[�Y
#include "Key.h"				// ��
#include "Life.h"				// ���C�t
#include "enemy.h"				// �G
#include "goal.h"				// �S�[��
#include "fade.h"				// �t�F�[�h
#include "sound.h"				// ��
#include "Xcontroller.h"				// Xinout

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
bool g_bStop = false;	//�J�[�\�������ǂ���
bool g_bPause = false;	//�|�[�Y�����ǂ���

//-------------------------------------------------------------------------------
//	����������
//-------------------------------------------------------------------------------
HRESULT InitGame_00(void)
{

	//BGM�̒ǉ�
	PlaySound(SOUND_LABEL_BGM002);	//�Q�[��BGM

	//�w�i�̏���������
	Initbackground_00();

	g_bStop = false;

	//�u���b�N�̏���������
	InitBlock();


	//�u���b�N�̈ʒu(pos,��,����)
	SetBlock(D3DXVECTOR3(610.0f, 600.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(670.0f, 540.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(730.0f, 480.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(790.0f, 420.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(850.0f, 360.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(910.0f, 300.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(970.0f, 300.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(1030.0f, 300.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(1090.0f, 300.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(1150.0f, 300.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);
	SetBlock(D3DXVECTOR3(1210.0f, 300.0f, 0.0f), 60.0f, 60.0f,BLOCKTYPE_CATCH);


	//SetBlock(D3DXVECTOR3(0.0f, 100.0f, 0.0f), 10.0f, 690.0f, BLOCKTYPE_NOT_CATCH);//�Ǎ�

	//SetBlock(D3DXVECTOR3(0.0f, 100.0f, 0.0f), 10.0f, 720.0f, BLOCKTYPE_NOT_CATCH);//�ǉE
	
	//�n��
	SetBlock(D3DXVECTOR3(-50.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(10.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(70.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(130.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(190.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(250.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(310.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(370.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(430.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(490.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(550.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(610.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(670.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(730.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(790.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(850.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(910.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(970.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(1030.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(1090.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(1150.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(1210.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(1270.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);
	SetBlock(D3DXVECTOR3(1330.0f, 660.0f, 0.0f), 60.0f, 60.0f, BLOCKTYPE_NOT_CATCH);


	//SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 60, 0.0f), SCREEN_WIDTH, 60.0f, BLOCKTYPE_NOT_CATCH);		//�n��

	//SetBlock(D3DXVECTOR3(940.0f, 300.0f - 40, 0.0f), 450.0f, 60.0f);				//�����琔����1�i�ڂ̉E�n��


	//�v���C���[�̏���������																		
	InitPlayer();

	//�G�̏���������
	InitEnemy();

	//���̏���������
	InitKey();

	//���̏���������
	Initdoor();

	//�J�[�\���̏���������
	InitMarker();

	//��~�w�i�̏���������
	InitStopBG();

	//���C�t�̏���������
	InitLife();

	//�|�[�Y�̏���������
	InitPause();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�I������
//-------------------------------------------------------------------------------
void UninitGame_00(void)
{
	g_bPause = false;	//�|�[�Y���I��

	//�|�[�Y�̏I������
	UninitPause();

	//��~�w�i�̏I������
	UninitStopBG();

	//�J�[�\���̏I������
	UninitMarker();

	// ���̏I������
	Uninitdoor();

	// ���̏I������
	UninitKey();

	// �G�̏I������
	UninitEnemy();

	// �v���C���[�̏I������
	UninitPlayer();

	// �u���b�N�̏I������
	UninitBlock();

	// ���C�t�̏I������
	UninitLife();

	// �w�i�̏I������
	Uninitbackground_00();

	// ���~�߂�
	StopSound();
}

//-------------------------------------------------------------------------------
//	�X�V����
//-------------------------------------------------------------------------------
void UpdateGame_00(void)
{
	// �G�̍X�V����
	UpdateEnemy();

	if (GetkeyboardTrgger(DIK_P) == true)
	{// P��������
		g_bPause = g_bPause ? false : true;

		// SE�̒ǉ�
		PlaySound(SOUND_LABEL_SE_ON);	// �I��
	}
	if (g_bPause == true)
	{// �|�[�Y�ֈړ�

	 // �|�[�Y�̍X�V����
		UpdatePause();
	}
	else if (GetkeyboardTrgger(DIK_J) == true)
	{// J��������
		g_bStop = g_bStop ? false : true;

		// SE�̒ǉ�
		PlaySound(SOUND_LABEL_SE_ON);	// �I��
	}
	else if (g_bStop == true)
	{// ��~��ʂ�\��

		// ��~�w�i�̍X�V����
		UpdateStopBG();

		// �J�[�\���̍X�V����
		UpdateMarker();

		// �u���b�N�̍X�V����
		UpdateBlock();
	}
	else
	{// �����Ȃ�����

		// �v���C���[�̍X�V����
		UpdatePlayer();

		// ���̍X�V����
		UpdateKey();

		// ���̍X�V����
		Updatedoor();

		// ���C�t�̍X�V����
		UpdateLife();

		// �w�i�̍X�V����
		Updatebackground_00();
	}
}

//-------------------------------------------------------------------------------
//	�`�揈��
//-------------------------------------------------------------------------------
void DrawGame_00(void)
{
	// �w�i�̕`�揈��
	Drawbackground_00();

	// ���̕`�揈��
	Drawdoor();

	// �u���b�N�̕`�揈��
	DrawBlock();

	// ���̕`�揈��
	DrawKey();

	// �v���C���[�̕`�揈��
	DrawPlayer();

	// �G�̕`�揈��
	DrawEnemy();

	// ���C�t�̕`�揈��
	DrawLife();

	if (g_bStop == true)
	{// ��~���ꂽ

		// ��~�w�i�̕`�揈��
		DrawStopBG();

		// �J�[�\���̕`�揈��
		DrawMarker();
	}

	if (g_bPause == true)
	{//�|�[�Y���ꂽ

		//�|�[�Y�̕`�揈��
		DrawPause();
	}
}

//-------------------------------------------------------------------------------
//	��~����
//-------------------------------------------------------------------------------
void SetStop(bool bStop)
{
	g_bStop = bStop;	//��~�����ǂ���
}

//-------------------------------------------------------------------------------
//	�|�[�Y����
//-------------------------------------------------------------------------------
void SetPause(bool bPause)
{
	g_bPause = bPause;	//�|�[�Y�����ǂ���
}

bool GetStop(void)
{
	return g_bStop;
}