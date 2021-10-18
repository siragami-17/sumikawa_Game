//--------------------------------------------------------------------------------
//
//	�^�C�g������ [Title.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "tutorial.h"			// �`���[�g���A��
#include "manager.h"			// �}�l�[�W���[
#include "renderer.h"			// �����_��
#include "Input_Keyboard.h"		// �L�[
#include "fade.h"
#include "sound.h"

//-------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture = NULL;

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// �R���X�g���N
//-------------------------------------------------------------------------------
CTutorial::CTutorial()
{
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CTutorial::~CTutorial()
{

}

//-------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-------------------------------------------------------------------------------
HRESULT CTutorial::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/tutorial.png", &m_pTexture);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �e�N�X�`����j��
//-------------------------------------------------------------------------------
void CTutorial::Unload(void)
{
	//�e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//-------------------------------------------------------------------------------
// �w�i�̐���
//-------------------------------------------------------------------------------
CTutorial *CTutorial::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CTutorial *pTitle = NULL;

	if (pTitle == NULL)
	{// NULL��������
	 // ���I�m��
		pTitle = new CTutorial;

		if (pTitle != NULL)
		{// NULL����Ȃ�������
		 // ����������
			pTitle->Init(pos, scale);
		}
	}
	return pTitle;
}


//-------------------------------------------------------------------------------
// ����������
//-------------------------------------------------------------------------------
HRESULT CTutorial::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// ���I�m��(�������̊m��)
	m_pScene2D = new CScene2D;

	// �摜��ǂݍ���
	Load();

	// ����������
	m_pScene2D->Init(pos, scale);

	// �e�N�X�`���̊��蓖��
	m_pScene2D->BindTexture(m_pTexture);

	// �T�E���h�֌W
	CSound *pSound;
	pSound = CManager::GetSound();

	// BGM�̒ǉ�
	pSound->Play(CSound::SOUND_LABEL_TUTORIAL);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �|���S���̏I������
//-------------------------------------------------------------------------------
void CTutorial::Uninit(void)
{
	// �摜�̔j��
	Unload();

	// �j������
	Release();

	// �T�E���h�֌W
	CSound *pSound;
	pSound = CManager::GetSound();

	// BGM������
	pSound->Stop();
}

//-------------------------------------------------------------------------------
// �|���S���̍X�V����
//-------------------------------------------------------------------------------
void CTutorial::Update(void)
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
	if (pFade->GetFade() == CFade::FADE_NONE && plnputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		// ���[�h�̐ݒ�
		pFade->SetFade(CManager::MODE_GAME);
	}
}

//-------------------------------------------------------------------------------
// �|���S���̕`�揈��
//-------------------------------------------------------------------------------
void CTutorial::Draw(void)
{

}