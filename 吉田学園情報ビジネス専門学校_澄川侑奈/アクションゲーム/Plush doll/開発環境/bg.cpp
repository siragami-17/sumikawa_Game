//--------------------------------------------------------------------------------
//
//	�w�i�̏��� [bg.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "bg.h"					// �w�i
#include "manager.h"			// �}�l�[�W���[
#include "renderer.h"			// �����_��
#include "scene2D.h"			// 2D�|���S��
#include "Input_Keyboard.h"		// �L�[�{�[�h
#include "playerAI.h"				// �v���C���[
#include "game.h"				// �Q�[��

#include "item.h"

//-------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CBg::m_apTexture[] = {};

//-------------------------------------------------------------------------------
// �R���X�g���N
//-------------------------------------------------------------------------------
CBg::CBg(PRIORITY nPriority) :CScene(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
		m_fSpeed[nCnt] = 0;
		m_fPosTexU[nCnt] = 0;
		m_fPosTexV[nCnt] = 0;
	}

}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CBg::~CBg()
{
}

//-------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-------------------------------------------------------------------------------
HRESULT CBg::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg003.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg002.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg001.png", &m_apTexture[2]);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �e�N�X�`����j��
//-------------------------------------------------------------------------------
 void CBg::Unload(void)
 {
	 for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
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
 CBg *CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
 {
	 CBg *pBg = NULL;

	 if (pBg == NULL)
	 {// NULL��������
		 // ���I�m��
		 pBg = new CBg;

		 if (pBg != NULL)
		 {// NULL����Ȃ�������
			 // ����������
			 pBg->Init(pos, scale);
		 }
	 }
	 return pBg;
 }

//-------------------------------------------------------------------------------
// ����������
//-------------------------------------------------------------------------------
HRESULT CBg::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// �`�揇�̐ݒ�
	m_apScene2D[0] = new CScene2D(PRIORITY_BGBEHING);
	m_apScene2D[1] = new CScene2D(PRIORITY_BGFRONT);
	m_apScene2D[2] = new CScene2D(PRIORITY_BGBEHING);

	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apScene2D[nCnt]->Init(pos, scale);
		m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
		m_fPosTexU[nCnt] = 0;
		m_fPosTexV[nCnt] = 0;
	}

	// �w�i�X�s�[�h����
	m_fSpeed[0] = SCROL_SPPED01;
	m_fSpeed[1] = SCROL_SPPED02;
	m_fSpeed[2] = SCROL_SPPED03;

	return S_OK;
}

//-------------------------------------------------------------------------------
// �|���S���̏I������
//-------------------------------------------------------------------------------
void CBg::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt] = NULL;
		}
	}
	// �j������
	Release();
}

//-------------------------------------------------------------------------------
// �|���S���̍X�V����
//-------------------------------------------------------------------------------
void CBg::Update(void)
{
	// �v���C���[�̈ړ��ʎ擾
	D3DXVECTOR3 PlayerAIMove;
	CPlayerAI *pPlayerAI;
	pPlayerAI = CGame::GetPlayerAI();
	PlayerAIMove = pPlayerAI->GetMove();

	// �L�[�{�[�h�֌W
	CInput_Keyboard *plnputKeyboard;
	plnputKeyboard = CManager::GetInputKeyboard();

		for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
		{

				// nCnt��0��1�̎��̂�
			if (nCnt == 0 || nCnt == 1)
			{

				if (!CItem::GetBItem())
				{
					// �v���C���[�̈ړ��ʂ�0���傫����
					if (PlayerAIMove.x > 0.0f)
					{// �w�i���E�ɃX�N���[��������
						m_fPosTexU[nCnt] += m_fSpeed[nCnt];
					}
					// �v���C���[�̈ړ��ʂ�0��菬������
					else if (PlayerAIMove.x < 0.0f)
					{// �w�i�����ɃX�N���[��������
						m_fPosTexU[nCnt] -= m_fSpeed[nCnt];
					}


					// �v���C���[�̈ړ��ʂ�0��菬������
					if (PlayerAIMove.x == 0.0f)
					{// �X�N���[�����~�߂�
					}

				}
			}
			// nCnt��2�̎�
			else
			{

					//// �v���C���[�������Ă��Ȃ��Ƃ�
					//if (PlayerAIMove.x == 0.0f)
					//{// ���ɓ�����
					m_fPosTexV[nCnt] -= m_fSpeed[nCnt];
					//}

					if (!CItem::GetBItem())
					{
					// �v���C���[�̈ړ��ʂ�0���傫����
					if (PlayerAIMove.x > 0.0f)
					{// �w�i���E�ɃX�N���[��������
						m_fPosTexU[nCnt] += m_fSpeed[nCnt];
						m_fPosTexV[nCnt] -= m_fSpeed[nCnt];
					}
					// �v���C���[�̈ړ��ʂ�0��菬������
					else if (PlayerAIMove.x < 0.0f)
					{// �w�i�����ɃX�N���[��������
						m_fPosTexU[nCnt] -= m_fSpeed[nCnt];
						m_fPosTexV[nCnt] -= m_fSpeed[nCnt];
					}

				}

				

			}



			// �����e�N�X�`����1���傫���Ȃ�����
			if (m_fPosTexU[nCnt] > 1.0f)
			{
				m_fPosTexU[nCnt] -= 1.0f;		// ���Ƃɖ߂�

			}
			if (m_fPosTexV[nCnt] > 1.0f)
			{
				m_fPosTexV[nCnt] -= 1.0f;
			}

			m_apScene2D[nCnt]->SetTex(m_fPosTexU[nCnt], m_fPosTexV[nCnt]);
		}
	
}

//-------------------------------------------------------------------------------
// �|���S���̕`�揈��
//-------------------------------------------------------------------------------
void CBg::Draw(void)
{

}