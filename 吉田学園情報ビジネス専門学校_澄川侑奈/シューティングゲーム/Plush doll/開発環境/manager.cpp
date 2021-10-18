//--------------------------------------------------------------------------------
//
//	�}�l�[�W������ [manager.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "renderer.h"			// �����_�����O
#include "manager.h"			// �}�l�[�W��
#include "scene2D.h"			// 2D�|���S��
#include "scene.h"				// �|���S��
#include "Input_Keyboard.h"		// �L�[�{�[�h
#include "sound.h"				// �T�E���h
#include "game.h"				// �Q�[���V�[��
#include "Title.h"				// �^�C�g��
#include "tutorial.h"			// �`���[�g���A��
#include "result.h"				// ���U���g
#include "fade.h"				// �t�F�[�h

#include "player.h"				// �v���C���[
#include "bullet.h"				// �e
#include "explosion.h"			// ����
#include "bg.h"					// �w�i
#include "enemy.h"				// �G
#include "number.h"				// �i���o�[
#include "score.h"				// �X�R�A
#include "polygon.h"			// �|���S��
#include "life.h"				// ���C�t
#include "Pause.h"				// �|�[�Y

//-------------------------------------------------------------------------------
// �ÓI�����o�ϐ���`
//-------------------------------------------------------------------------------
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutoral = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;

CRenderer *CManager::m_pRenderer = NULL;
CInput_Keyboard *CManager::m_pInputKeyboard = NULL;
CSound *CManager::m_pSound = NULL;
CFade *CManager::m_pFade = NULL;

bool CManager::m_bPause = false;

CManager::MODE CManager::m_mode = MODE_TITLE;

//-------------------------------------------------------------------------------
// �R���X�g���N
//-------------------------------------------------------------------------------
CManager::CManager()
{
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CManager::~CManager()
{
}

//-------------------------------------------------------------------------------
// ����������
//-------------------------------------------------------------------------------
HRESULT CManager::Init(HWND hWnd, BOOL bWindow, HINSTANCE hInstance)
{
	// �����_�����O�N���X�̐���
	if (m_pRenderer == NULL)
	{	
		// ���I�m��
		m_pRenderer = new CRenderer;

		if (m_pRenderer != NULL)
		{
			// ����������
			m_pRenderer->Init(hWnd, bWindow);
		}
	}

	// �L�[�{�[�h�̐���
	if (m_pInputKeyboard == NULL)
	{
		// ���I�m��
		m_pInputKeyboard = new CInput_Keyboard;
		if (m_pInputKeyboard != NULL)
		{
			// ����������
			m_pInputKeyboard->Init(hInstance, hWnd);
		}
	}

	// �T�E���h�̐���
	if (m_pSound == NULL)
	{
		// ���I�m��
		m_pSound = new CSound;
		if (m_pSound != NULL)
		{
			// ����������
			m_pSound->Init(hWnd);
		}
	}

	// �t�F�[�h�̐���
	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 
							D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), m_mode);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �I������
//-------------------------------------------------------------------------------
void CManager::Uninit(void)
{
	// �S�ẴI�u�W�F�N�g�̔j��
	CScene::ReleaseAll();

	// �T�E���h�̔j��
	if (m_pSound != NULL)
	{// NULL����Ȃ�������
		m_pSound->Uninit();		// �I������
		delete m_pSound;
		m_pSound = NULL;
	}

	// �L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{// NULL����Ȃ�������
		m_pInputKeyboard->Uninit();		// �I������
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// �����_�����O�̔j��
	if (m_pRenderer != NULL)
	{// NULL����Ȃ�������
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// �i���o�[�̏I������
	CNumber::Unload();

	// �G�̏I������
	CEnemy::Unload();

	// �w�i�̏I������
	CBg::Unload();

	// �v���C���[�̏I������
	CPlayer::Unload();

	// �����̏I������
	CExplosion::Unload();

	// �e�̏I������
	CBullet::Unload();
}

//-------------------------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------------------------
void CManager::Update(void)
{
	// �L�[�{�[�h�̍X�V����
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// �����_�����O�̍X�V����
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	// �T�E���h�֌W
	CSound *pSound;
	pSound = CManager::GetSound();

	// �t�F�[�h�֌W
	CFade *pFade;
	pFade = CManager::GetFade();

	if (pFade->GetFade() == CFade::FADE_NONE)
	{// �t�F�[�h���͓����Ȃ�
		// �|�[�Y��`�悷��
		if (m_mode == MODE_GAME)
		{// ���[�h���Q�[���̎�
			if (m_pInputKeyboard->GetTrigger(DIK_P) == true)
			{// P�L�[�������ꂽ
				SetPause();

				if (m_bPause == true)
				{
					// SE�̍Đ�
					pSound->Play(CSound::SOUND_LABEL_SE_ON);

				}
			}
			if (m_pInputKeyboard->GetTrigger(DIK_P) == true && m_bPause == false)
			{
				// SE�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_SE_NO);
			}
		}
	}
}

//-------------------------------------------------------------------------------
// �`�揈��
//-------------------------------------------------------------------------------
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//-------------------------------------------------------------------------------
// ���[�h�̐ݒ�@
// mode:���[�h�̎��
//-------------------------------------------------------------------------------
void CManager::SetMode(MODE mode)
{
	// �ύX�O�̃��[�h�̏I������
	switch (m_mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{// NULL����Ȃ�������
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;

		// �`���[�g���A��
	case MODE_TUTORIAL:
		if (m_pTutoral != NULL)
		{// NULL����Ȃ�������
			m_pTutoral->Uninit();
			m_pTutoral = NULL;
		}
		break;

		// �Q�[���V�[��
	case MODE_GAME:
		if (m_pGame != NULL)
		{// NULL����Ȃ�������
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;

		// ���U���g�V�[��
	case MODE_RESULT:
		if (m_pResult != NULL)
		{// NULL����Ȃ�������
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;
	}

	// �S�Ă�����
	CScene::ReleaseAll();

	// ���[�h�̕ύX
	 m_mode = mode; 

	 // �ύX��̃��[�h�̏�����
	 switch (m_mode)
	 {
		 // �^�C�g��
	 case MODE_TITLE:
		 if (m_pTitle == NULL)
		 {// NULL��������
			 // ���I�m��
			 m_pTitle = new CTitle;
			 if (m_pTitle != NULL)
			 {
				 // ����������
				 m_pTitle->Init({ SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f }, { SCREEN_WIDTH,SCREEN_HEIGHT,0.0f });
			 }
		 }
		 break;

		 // �`���[�g���A��
	 case MODE_TUTORIAL:
		 if (m_pTutoral == NULL)
		 {// NULL��������
		  // ���I�m��
			 m_pTutoral = new CTutorial;

			 if (m_pTutoral != NULL)
			 {
				 // ����������
				 m_pTutoral->Init({ SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f }, { SCREEN_WIDTH,SCREEN_HEIGHT,0.0f });
			 }
		 }
		 break;

		 // �Q�[���V�[��
	 case MODE_GAME:
		 if (m_pGame == NULL)
		 {// NULL��������
			 // ���I�m��
			 m_pGame = new CGame;

			 if (m_pGame != NULL)
			 {
				 // ����������
				 m_pGame->Init({ 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });
			 }
		 }
		 break;

		 // ���U���g�V�[��
	 case MODE_RESULT:
		 if (m_pResult == NULL)
		 {// NULL��������
		  // ���I�m��
			 m_pResult = new CResult;

			 if (m_pResult != NULL)
			 {
				 // ����������
				 m_pResult->Init({ SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f }, { SCREEN_WIDTH,SCREEN_HEIGHT,0.0f });
			 }
		 }
		 break;
	 }
}

//-------------------------------------------------------------------------------
// �|�[�Y����Ă��邩�ǂ���
//-------------------------------------------------------------------------------
void CManager::SetPause(bool bPause)
{
	m_bPause = bPause;
}

//-------------------------------------------------------------------------------
// �|�[�Y���
//-------------------------------------------------------------------------------
void CManager::SetPause(void)
{
	m_bPause = m_bPause ? false : true;
}