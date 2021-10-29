//--------------------------------------------------------------------------------
//
//	�^�C�g������ [Title.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Title.h"				// �^�C�g��
#include "manager.h"			// �}�l�[�W���[
#include "renderer.h"			// �����_��
#include "Input_Keyboard.h"		// �L�[
#include "fade.h"				// �t�F�[�h
#include "sound.h"				// �T�E���h

//-------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CTitle::m_apTexture[] = {};

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// �R���X�g���N
//-------------------------------------------------------------------------------
CTitle::CTitle()
{
	// �����o�ϐ��̏�����
	for (int nCnt = 0; nCnt < TITLE_MAX; nCnt++)
	{
		m_apScene2D[nCnt] = {};
	}

	m_Enter = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);;
	m_fAdd = 0.0f;
	m_bPressEnter = false;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CTitle::~CTitle()
{

}

//-------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-------------------------------------------------------------------------------
HRESULT CTitle::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Title_00.png", &m_apTexture[TITLE_BG]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Title_01.png", &m_apTexture[TITLE_PLAYER]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/press_enter.png", &m_apTexture[TITLE_ENTER]);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �e�N�X�`����j��
//-------------------------------------------------------------------------------
void CTitle::Unload(void)
{
	//�e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < TITLE_MAX; nCnt++)
	{
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
CTitle *CTitle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CTitle *pTitle = NULL;

	if (pTitle == NULL)
	{// NULL��������
	 // ���I�m��
		pTitle = new CTitle;

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
HRESULT CTitle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// �����o�ϐ��̏�����
	m_fAdd = 0.0f;
	m_bPressEnter = false;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;

	for (int nCnt = 0; nCnt < TITLE_MAX; nCnt++)
	{
		// ���I�m��(�������̊m��)
		m_apScene2D[nCnt] = new CScene2D;

		// �摜��ǂݍ���
		Load();

		// ����������
		m_apScene2D[nCnt]->Init(pos, scale);

		// �e�N�X�`���̊��蓖��
		m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	}
	// �e�N�X�`���̈ʒu��ݒ�
	SetTex();

	// �e�N�X�`�����W�X�V
	m_apScene2D[TITLE_PLAYER]->SetTex(m_nPatternAnim, 4);

	m_Enter = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �T�E���h�֌W
	CSound *pSound;
	pSound = CManager::GetSound();

	// BGM�̒ǉ�
	pSound->Play(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �|���S���̏I������
//-------------------------------------------------------------------------------
void CTitle::Uninit(void)
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
void CTitle::Update(void)
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

	// �_�ŏ���
	Blinking();

	// �G���^�[���������Ƃ�
	if (pFade->GetFade() == CFade::FADE_NONE && plnputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		// �G���^�[�L�[�������ꂽ
		m_bPressEnter = true;

		// ���[�h�̐ݒ�
		pFade->SetFade(CManager::MODE_TUTORIAL);
	}
	// �A�j���[�V��������
	Animation();
}

//-------------------------------------------------------------------------------
// �|���S���̕`�揈��
//-------------------------------------------------------------------------------
void CTitle::Draw(void)
{

}

//-------------------------------------------------------------------------------
// �e�N�X�`���̈ʒu��ݒ�
//-------------------------------------------------------------------------------
void CTitle::SetTex(void)
{
	// �v���C���[
	m_apScene2D[TITLE_PLAYER]->SetPosition(D3DXVECTOR3(500.0f, 450.0f, 0), D3DXVECTOR3(406.0f, 495.0f, 0.0f));

	// �v���X�G���^�[
	m_apScene2D[TITLE_ENTER]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 660.0f, 0), D3DXVECTOR3(490.0f, 90.0f, 0.0f));
}

//-------------------------------------------------------------------------------
// �_�ŏ���
//-------------------------------------------------------------------------------
void CTitle::Blinking(void)
{
	m_apScene2D[TITLE_ENTER]->SetCol(m_Enter);

	// ���Z
	m_Enter.a += m_fAdd;

	// �G���^�[�L�[��������Ă��Ȃ�������
	if (m_bPressEnter == false)
	{
		if (m_Enter.a >= 1.0f)
		{// �e�N�X�`����a�l��1.0f���傫��������
			// ���Z
			m_fAdd -= 0.04f;
		}
		else if (m_Enter.a <= 0.0f)
		{// �e�N�X�`����a�l��1.0f��菬����������
			// ���Z
			m_fAdd += 0.04f;
		}
	}

	// �G���^�[�L�[��������Ă�����
	if (m_bPressEnter == true)
	{
		if (m_Enter.a >= 1.0f)
		{// �e�N�X�`����a�l��1.0f���傫��������
			// ���Z
			m_fAdd -= 0.5f;
		}
		else if (m_Enter.a <= 0.0f)
		{// �e�N�X�`����a�l��1.0f��菬����������
			// ���Z
			m_fAdd += 0.5f;
		}
	}
}

//-------------------------------------------------------------------------------
// �A�j���[�V�����̏���
//-------------------------------------------------------------------------------
void CTitle::Animation(void)
{
	// �J�E���^�[�̍X�V
	m_nCounterAnim++;

	if (m_nCounterAnim % 10 == 0)
	{// �p�^�[��No�X�V
		m_nPatternAnim += 1;

		// �e�N�X�`�����W�X�V
		m_apScene2D[TITLE_PLAYER]->SetTex(m_nPatternAnim, 4);

		if (m_nPatternAnim > 4)
		{// �S�ăJ�E���g������
			// �����ʒu�ɖ߂�
			m_nPatternAnim = 0;
		}
	}
}