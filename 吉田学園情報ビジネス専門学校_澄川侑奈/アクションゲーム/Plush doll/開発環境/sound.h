//--------------------------------------------------------------------------------
//
//	�T�E���h���� [sound.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
// �T�E���h�N���X(��{�N���X)
//-------------------------------------------------------------------------------
class  CSound
{
public:
	CSound();													// �R���X�g���N
	virtual ~CSound();											// �f�X�g���N�^

	// �T�E���h�t�@�C��
	typedef enum
	{
		// BGM
		SOUND_LABEL_TITLE = 0,			// �^�C�g��
		SOUND_LABEL_TUTORIAL,			// �`���[�g���A��
		SOUND_LABEL_GAME,				// �Q�[��
		SOUND_LABEL_GAMECLEAR,			// �Q�[���N���A
		SOUND_LABEL_GAMEOVER,			// �Q�[���I�[�o�[

		// SE
		SOUND_LABEL_SE_SHOT,			// �e���ˉ�
		SOUND_LABEL_SE_EXPLOSION,		// ����
		SOUND_LABEL_SE_NO,				// �e���o�Ȃ�,OFF
		SOUND_LABEL_SE_ON,				// ON
		SOUND_LABEL_SE_DAMAGE,			// �_���[�W
		SOUND_LABEL_SE_JUMP,			// �W�����v

		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	 HRESULT Init(HWND hWnd);
	 void Uninit(void);
	 HRESULT Play(SOUND_LABEL label);
	 void Stop(SOUND_LABEL label);
	 void Stop(void);

protected:

	// �p�����[�^�\���̒�`
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);


	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^
	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];
};

#endif