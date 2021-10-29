//--------------------------------------------------------------------------------
//
//	���U���g���� [result.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "result.h"				// ���U���g
#include "manager.h"			// �}�l�[�W���[
#include "renderer.h"			// �����_��
#include "Input_Keyboard.h"		// �L�[
#include "fade.h"				// �t�F�[�h
#include "game.h"				// �Q�[��
#include "sound.h"

//-------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CResult::m_apTexture[] = {};

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// �R���X�g���N
//-------------------------------------------------------------------------------
CResult::CResult()
{
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CResult::~CResult()
{

}

//-------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-------------------------------------------------------------------------------
HRESULT CResult::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Result.png", &m_apTexture[TEXTURETYPE_GAMECLEAR]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/GameOver.png", &m_apTexture[TEXTURETYPE_GAMEOVER]);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �e�N�X�`����j��
//-------------------------------------------------------------------------------
void CResult::Unload(void)
{
	for (int nCnt = 0; nCnt < TEXTURETYPE_MAX; nCnt++)
	{
		//�e�N�X�`���̊J��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//-------------------------------------------------------------------------------
// �w�i�̐���
//-------------------------------------------------------------------------------
CResult *CResult::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CResult *pResult = NULL;

	if (pResult == NULL)
	{// NULL��������
	 // ���I�m��
		pResult = new CResult;

		if (pResult != NULL)
		{// NULL����Ȃ�������
		 // ����������
			pResult->m_pScene2D = NULL;
			pResult->Init(pos, scale);
		}
	}
	return pResult;
}

//-------------------------------------------------------------------------------
// ����������
//-------------------------------------------------------------------------------
HRESULT CResult::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// ������
	m_pScene2D = NULL;

	// �摜��ǂݍ���
	Load();

	if (m_pScene2D == NULL)
	{
		m_pScene2D = CScene2D::Create(CENTER_POS, D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	}

	// �T�E���h�֌W
	CSound *pSound;
	pSound = CManager::GetSound();

	if (m_pScene2D != NULL)
	{
		//�e�N�X�`���̐ݒ�
		if (CGame::GetResult() == CGame::RESULTMODE_GAMECLEAR)
		{//�N���A���
			 // �e�N�X�`���̊��蓖��
			m_pScene2D->BindTexture(m_apTexture[TEXTURETYPE_GAMECLEAR]);


			// BGM�̒ǉ�
			pSound->Play(CSound::SOUND_LABEL_GAMECLEAR);
		}
		else if (CGame::GetResult() == CGame::RESULTMODE_GAMEOVER)
		{//�Q�[���I�[�o���
			// �e�N�X�`���̊��蓖��
			m_pScene2D->BindTexture(m_apTexture[TEXTURETYPE_GAMEOVER]);

			// BGM�̒ǉ�
			pSound->Play(CSound::SOUND_LABEL_GAMEOVER);

		}
	}
	return S_OK;
}

//-------------------------------------------------------------------------------
// �|���S���̏I������
//-------------------------------------------------------------------------------
void CResult::Uninit(void)
{

	// �T�E���h�֌W
	CSound *pSound;
	pSound = CManager::GetSound();

	// �摜�̔j��
	Unload();

	// �j������
	Release();

	// BGM������
	pSound->Stop();
}

//-------------------------------------------------------------------------------
// �|���S���̍X�V����
//-------------------------------------------------------------------------------
void CResult::Update(void)
{
	// �L�[�{�[�h�֌W
	CInput_Keyboard *plnputKeyboard;
	plnputKeyboard = CManager::GetInputKeyboard();

	// ���[�h�֌W
	CManager::MODE pManager;
	pManager = CManager::GetMode();

	// �t�F�[�h�֌W
	CFade *pFade;
	pFade = CManager::GetFade();

	// �G���^�[���������Ƃ�
	if (pFade->GetFade() == CFade::FADE_NONE&& plnputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		// �^�C�g���Ɉړ�
		pFade->SetFade(CManager::MODE_TITLE);
	}
}

//-------------------------------------------------------------------------------
// �|���S���̕`�揈��
//-------------------------------------------------------------------------------
void CResult::Draw(void)
{

}