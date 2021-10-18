//--------------------------------------------------------------------------------
//
//	���C�t���� [life.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "life.h"			// ���C�t
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "game.h"
#include "Input_Keyboard.h"
#include "fade.h"

//-------------------------------------------------------------------------------
// �ÓI�����o�ϐ���`
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;

//-------------------------------------------------------------------------------
// �R���X�g���N
//-------------------------------------------------------------------------------
CLife::CLife(PRIORITY nPriority) :CScene(nPriority)
{
	int m_nLife = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CLife::~CLife()
{
}

//-------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-------------------------------------------------------------------------------
HRESULT CLife::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Life.png", &m_pTexture);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �e�N�X�`����j��
//-------------------------------------------------------------------------------
void CLife::Unload(void)
{
	//�e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//-------------------------------------------------------------------------------
// ���C�t�̐���
//-------------------------------------------------------------------------------
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CLife *pLife = NULL;

	if (pLife == NULL)
	{// NULL��������
	 // ���I�m��
		pLife = new CLife;

		if (pLife != NULL)
		{// NULL����Ȃ�������
		 // �������������Ăяo��
			pLife->Init(pos, scale);
		}
	}
	// �l��Ԃ�
	return pLife;
}

//-------------------------------------------------------------------------------
// ����������
//-------------------------------------------------------------------------------
HRESULT CLife::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// ���
	m_pos = pos;

	CLife *pLife = NULL;

	// 5�����ׂ鏈��
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		m_apPolygon[nCnt] = CPolygon::Create(D3DXVECTOR3((pos.x - (LIFE_WIDTH * LIFE_HALF) + (LIFE_WIDTH * nCnt)) + (LIFE_WIDTH / 2.0f),
			(pos.y), 0.0f), D3DXVECTOR3(LIFE_WIDTH, LIFE_HEIGHT, 0));

		// �e�N�X�`���̊��蓖��
		m_apPolygon[nCnt]->BindTexture(m_pTexture);
	}

	// �������C�t
	m_nLife = MAX_LIFE;

	return S_OK;
}

//-------------------------------------------------------------------------------
// �I������
//-------------------------------------------------------------------------------
void CLife::Uninit(void)
{
	for (int nCnt = 0; nCnt < m_nLife; nCnt++)
	{
		if (m_apPolygon[nCnt] != NULL)
		{// NULL����Ȃ�������
			m_apPolygon[nCnt]->Uninit();
			delete m_apPolygon[nCnt];
			m_apPolygon[nCnt] = NULL;
		}
	}
	Release();
}

//-------------------------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------------------------
void CLife::Update(void)
{

}

//-------------------------------------------------------------------------------
// �`�揈��
//-------------------------------------------------------------------------------
void CLife::Draw(void)
{
	for (int nCnt = 0; nCnt < m_nLife; nCnt++)
	{
		m_apPolygon[nCnt]->Draw();
	}
}

//-------------------------------------------------------------------------------
// ���C�t�̐ݒ�
//-------------------------------------------------------------------------------
void CLife::SetLife(int nLife)
{
	// ���
	m_nLife = nLife;
}

//-------------------------------------------------------------------------------
//	���C�t���Z�̏���
// nValue : ���Z���郉�C�t
//-------------------------------------------------------------------------------
void CLife::AddLife(int nValue)
{
	// ���Z
	m_nLife += nValue;

	// 5�����ׂ鏈��
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		// NULL��������
		if (m_apPolygon[nCnt] == NULL)
		{
			// �\��������
			m_apPolygon[nCnt] = CPolygon::Create(D3DXVECTOR3((m_pos.x - (LIFE_WIDTH * LIFE_HALF) + (LIFE_WIDTH * nCnt)) + (LIFE_WIDTH / 2.0f),
				(m_pos.y), 0.0f), D3DXVECTOR3(LIFE_WIDTH, LIFE_HEIGHT, 0));
		}
	}
}

//-------------------------------------------------------------------------------
//	���C�t���Z�̏���
// nValue : ���Z���郉�C�t
//-------------------------------------------------------------------------------
void CLife::SubtractLife(int nValue)
{
	if (m_nLife > 0)
	{// ���C�t��0�ȏ�̎��̂�
		// 5�����ׂ鏈��
		for (int nCnt = m_nLife - 1; nCnt > m_nLife - nValue - 1; nCnt--)
		{
			// NULL����Ȃ�������
			if (m_apPolygon[nCnt] != NULL)
			{
				m_apPolygon[nCnt]->Uninit();
				delete m_apPolygon[nCnt];
				m_apPolygon[nCnt] = NULL;
			}
		}
		// ���Z
		m_nLife -= nValue;
	}
}

//-------------------------------------------------------------------------------
// ���C�t���擾
//-------------------------------------------------------------------------------
int CLife::GetLife(void)
{
	// �X�R�A�̏��̐擪�A�h���X��Ԃ�
	return m_nLife;
}