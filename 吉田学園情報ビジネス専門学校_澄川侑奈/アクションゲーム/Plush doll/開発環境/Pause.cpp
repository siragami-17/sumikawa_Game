//--------------------------------------------------------------------------------
//
//	�|�[�Y�̏��� [Pause.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Pause.h"			
#include "manager.h"
#include "renderer.h"
#include "fade.h"			
#include "Input_Keyboard.h"
#include "sound.h"

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CPause::m_apTexture[] = {};

//-------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-------------------------------------------------------------------------------
HRESULT CPause::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Slect.png", &m_apTexture[PAUSE_MENU_MENUBJ]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause000.png", &m_apTexture[PAUSE_MENU_CONTINOE]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause001.png", &m_apTexture[PAUSE_MENU_RETRY]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause002.png", &m_apTexture[PAUSE_MENU_QUIT]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg000.png", &m_apTexture[PAUSE_MENU_MENUYOP]);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �e�N�X�`����j��
//-------------------------------------------------------------------------------
void CPause::Unload(void)
{
	for (int nCnt = 0; nCnt < PAUSE_MENU_MAX; nCnt++)
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
// �|�[�Y�̐���
//-------------------------------------------------------------------------------
CPause *CPause::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// �ϐ��錾
	CPause *pPause = NULL;

	if (pPause == NULL)
	{// ���Ƀf�[�^�������Ȃ�������
		// ���I�m��
		pPause = new CPause;

		if (pPause != NULL)
		{// ���Ƀf�[�^����������
			// �������������Ăяo��
			pPause->Init(pos, scale);
		}
	}
	// �l��Ԃ�
	return pPause;
}

//-------------------------------------------------------------------------------
// �R���X�g���N
//-------------------------------------------------------------------------------
CPause::CPause(PRIORITY nPriority) :CScene(nPriority)
{
	// ������
	m_Cursor = PAUSE_MENU_CONTINOE;
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CPause::~CPause()
{
}

//-------------------------------------------------------------------------------
// ����������
//-------------------------------------------------------------------------------
HRESULT CPause::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// ������
	m_Cursor = PAUSE_MENU_CONTINOE;

	// ���[�J��
	D3DXVECTOR3 nPos[PAUSE_MENU_MAX] = { pos,
		D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f),		// �|�[�Y���j���[�w�i
		D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT / 2-100, 0.0f),		// �R���e�B�j���[
		D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT / 2, 0.0f),		// �N�C�b�g
		D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT / 2+100, 0.0f),
		pos};
	D3DXVECTOR3 nSize[PAUSE_MENU_MAX] = { scale,
		D3DXVECTOR3(500.0f*0.7, 610.0f*0.7, 0.0f),
		D3DXVECTOR3(640.0f*0.5, 120.0f*0.5, 0.0f),
		D3DXVECTOR3(640.0f*0.5, 120.0f*0.5, 0.0f),
		D3DXVECTOR3(640.0f*0.5, 120.0f*0.5, 0.0f),
		scale };

	// UI�̈ʒu�֌W
	for (int nCnt = 0; nCnt < PAUSE_MENU_MAX; nCnt++)
	{
		// ���I�m��(�������̊m��)
		m_pScene2D[nCnt] = new CScene2D(CScene::PRIORITY_PAUSE);

		if (m_pScene2D[nCnt] != NULL)
		{
			// ����������
			m_pScene2D[nCnt]->Init(nPos[nCnt], nSize[nCnt]);

			if (m_apTexture[nCnt] != NULL)
			{
				// �e�N�X�`�������蓖�Ă�
				m_pScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
			}
		}
	}
	// �J���[�֌W
	for (int nCnt = PAUSE_MENU_CONTINOE; nCnt <= PAUSE_MENU_QUIT; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			// �J���[�̐ݒ�
			if (m_Cursor == nCnt)
			{// �J�[�\�����I�����Ă���
				m_pScene2D[nCnt]->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
			}
			else
			{// ����ȊO�͔�����
				m_pScene2D[nCnt]->SetCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f));
			}
		}
	}
	// �w�i�̐F�𔖂�����
	m_pScene2D[PAUSE_MENU_BLACK]->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

	return S_OK;
}

//-------------------------------------------------------------------------------
// �|���S���̏I������
//-------------------------------------------------------------------------------
void CPause::Uninit(void)
{
	for (int nCnt = 0; nCnt < PAUSE_MENU_MAX; nCnt++)
	{
		// �|���S���̏I���������Ăяo��
		m_pScene2D[nCnt]->Uninit();
	}
}

//-------------------------------------------------------------------------------
// �|���S���̍X�V����
//-------------------------------------------------------------------------------
void CPause::Update(void)
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

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		if (plnputKeyboard->GetTrigger(DIK_W) == true)
		{// ��Ɉړ�
			m_Cursor--;

			if (m_Cursor < PAUSE_MENU_CONTINOE)
			{
				m_Cursor = PAUSE_MENU_QUIT;
			}
		}
		if (plnputKeyboard->GetTrigger(DIK_S) == true)
		{// ���Ɉړ�
			m_Cursor++;

			if (m_Cursor > PAUSE_MENU_QUIT)
			{
				m_Cursor = PAUSE_MENU_CONTINOE;
			}
		}

		// �T�E���h�֌W
		CSound *pSound;
		pSound = CManager::GetSound();

		if (plnputKeyboard->GetTrigger(DIK_RETURN) == true)
		{// �G���^�[�L�[��������
			if (m_Cursor == PAUSE_MENU_CONTINOE)
			{// �|�[�Y�����
				CManager::SetPause(false);

				// SE�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_SE_NO);
			}

			if (m_Cursor == PAUSE_MENU_RETRY)
			{// �Q�[���Ɉړ�
			 // SE�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_SE_ON);
				CManager::SetPause(false);
				pFade->SetFade(CManager::MODE_GAME);
			}

			if (m_Cursor == PAUSE_MENU_QUIT)
			{// �^�C�g���Ɉړ�
			 // SE�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_SE_ON);
				CManager::SetPause(false);
				pFade->SetFade(CManager::MODE_TITLE);
			}
		}
	}

	for (int nCnt = PAUSE_MENU_CONTINOE; nCnt <= PAUSE_MENU_QUIT; nCnt++)
	{
		// �J���[�̐ݒ�
		if (m_Cursor == nCnt)
		{
			m_pScene2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{// ����ȊO�͔�����
			m_pScene2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}
	}
	
}

//-------------------------------------------------------------------------------
// �|�[�Y�̕`�揈��
//-------------------------------------------------------------------------------
void CPause::Draw(void)
{
	for (int nCnt = 0; nCnt < PAUSE_MENU_MAX; nCnt++)
	{
			// �|���S���̕`�揈�����Ăяo��
		m_pScene2D[nCnt]->Draw();
	}
}

