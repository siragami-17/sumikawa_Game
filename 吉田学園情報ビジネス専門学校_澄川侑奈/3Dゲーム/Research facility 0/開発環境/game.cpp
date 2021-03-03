//--------------------------------------------------------------------------------
//
//	�Q�[���̏��� [game.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "game.h"			// �Q�[��
#include "sound.h"			// �T�E���h
#include "meshfild.h"		// �n��
#include "camera.h"			// �J����
#include "light.h"			// ���C�g
#include "player.h"			// �v���C���[
#include "shadow.h"			// �e
#include "wall.h"			// ��
#include "Key.h"			// ��
#include "bullet.h"			// �e
#include "mouse.h"			// �}�E�X
#include "Xcontroller.h"	// Xinput
#include "fade.h"			// �t�F�[�h
#include "keyboard.h"		// �L�[�{�[�h
#include "time.h"			// �^�C�}�[
#include "heart.h"			// �n�[�g
#include "Pause.h"			// �|�[�Y
#include "block.h"			// �u���b�N
#include "object.h"			// �I�u�W�F�N�g
#include "object_1.h"

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
bool g_bPause = false;	//�|�[�Y�����ǂ���

//-------------------------------------------------------------------------------
//	����������
//-------------------------------------------------------------------------------
HRESULT InitGame(void)
{

	// BGM�̓ǂݍ���
	PlaySound(SOUND_LABEL_GAME);		// �Q�[��

	// �n�ʂ̏���������
	InitMeshfild();

	// �J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	// �ǂ̏���������
	InitWall();

	// �e�̏���������
	InitShadow();

	// ���̏���������
	InitKey();

	// X�t�@�C���̏���������
	InitPlayer();

	// �I�u�W�F�N�g
	InitObject();

	// �I�u�W�F�N�g
//	InitObject_1();

	// �S�[���̏���������
	InitBlock();

	// �e�̏���������
	InitBullet();

	// �^�C�}�[�̏���������
	InitTime();

	// �n�[�g�̏���������
	InitHeart();

	//�|�[�Y�̏���������
	InitPause();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�I������ 
//-------------------------------------------------------------------------------
void UninitGame(void)
{
	g_bPause = false;	//�|�[�Y���I��

	//�|�[�Y�̏I������
	UninitPause();

	// �n�[�g�̏I������
	UninitHeart();

	// �^�C�}�[�̏I������
	UninitTime();

	// �e�̏I������
	UninitBullet();

	// �n�ʂ̏I������
	UninitMeshfild();

	// �S�[���̏I������
	UninitBlock();

	// �I�u�W�F�N�g
//	UninitObject_1();

	// �I�u�W�F�N�g
	UninitObject();

	// X�t�@�C���̏I������
	UninitPlayer();

	// ���̏I������
	UninitKey();

	// �e�̏I������
	UninitShadow();

	// �ǂ̏I������
	UninitWall();

	// ���C�g�̏I������
	UninitLight();

	// �J�����̏I������
	UninitCamera();

	//���~�߂�
	StopSound();
}

//-------------------------------------------------------------------------------
//	�X�V����
//-------------------------------------------------------------------------------
void UpdateGame(void)
{
	//�t�F�[�h
	int nFade = GetFade();


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
	else
	{// �����Ȃ�����

		// �^�C�}�[�̍X�V����
		UpdateTime();

		// �n�[�g�̍X�V����
		UpdateHeart();



		// �n�ʂ̍X�V����
		UpdateMeshfild();

		// ���C�g�̍X�V����
		UpdateLight();

		// X�t�@�C���̍X�V����
		UpdatePlayer();

		// �I�u�W�F�N�g
		UpdateObject();

		// �I�u�W�F�N�g
	//	UpdateObject_1();

		// �S�[���̍X�V����
		UpdateBlock();

		// �e�̍X�V����
		UpdateShadow();

		// �ǂ̍X�V����
		UpdateWall();

		// ���̍X�V����
		UpdateKey();

		// �e�̍X�V����
		UpdateBullet();
	}
	// �J�����̍X�V����
	UpdateCamera();
}


//-------------------------------------------------------------------------------
//	�`�揈��
//-------------------------------------------------------------------------------
void DrawGame(void)
{
	// �ǂ̕`�揈��
	DrawWall();

	// �n�ʂ̕`�揈��
	DrawMeshfild();

	// X�t�@�C���̕`�揈��
	DrawPlayer();

	// �S�[���̕`�揈��
	DrawBlock();

	// �I�u�W�F�N�g
	DrawObject();

	// �I�u�W�F�N�g
//	DrawObject_1();

	// ���̕`�揈��
	DrawKey();

	// �e�̕`�揈��
	DrawBullet();

	// �^�C�}�[�̕`�揈��
	DrawTime();

	// �n�[�g�̕`�揈��
	DrawHeart();


	// �e�̕`�揈��
	DrawShadow();

	if (g_bPause == true)
	{//�|�[�Y���ꂽ

	 //�|�[�Y�̕`�揈��
		DrawPause();
	}
}

//-------------------------------------------------------------------------------
//	�|�[�Y����
//-------------------------------------------------------------------------------
void SetPause(bool bPause)
{
	g_bPause = bPause;	//�|�[�Y�����ǂ���
}