//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_TITLE = 0,			// �^�C�g��BGM
	SOUND_LABEL_TUTORIAL,			// �`���[�g���A��BGM
	SOUND_LABEL_GAME,				// �Q�[��BGM
	SOUND_LABEL_BGM003,				// �N���ABGM
	SOUND_LABEL_BGM004,				// BGM4(�Q�[���I�[�o�[)

	SOUND_LABEL_SE_CHOICE,			// �I��
	SOUND_LABEL_SE_DAMAGE,			// �_���[�W
	SOUND_LABEL_SE_GET,				// �Q�b�g
	SOUND_LABEL_SE_JUMP,			// �W�����v
	SOUND_LABEL_SE_OFF,				// �I�t
	SOUND_LABEL_SE_ON,				// �I��
	SOUND_LABEL_SE_WALK,			// ����


	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
