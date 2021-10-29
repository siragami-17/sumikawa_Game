//--------------------------------------------------------------------------------
//
//	�eUI���� [Bullet_UI.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Bullet_UI.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"

//-------------------------------------------------------------------------------
// �ÓI�����o�ϐ���`
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CBullet_UI::m_pTexture = NULL;

//-------------------------------------------------------------------------------
// �R���X�g���N
//-------------------------------------------------------------------------------
CBullet_UI::CBullet_UI(PRIORITY nPriority) :CScene(nPriority)
{
	int m_nBullet_UI = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CBullet_UI::~CBullet_UI()
{
}

//-------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-------------------------------------------------------------------------------
HRESULT CBullet_UI::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet.png", &m_pTexture);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �e�N�X�`����j��
//-------------------------------------------------------------------------------
void CBullet_UI::Unload(void)
{
	//�e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//-------------------------------------------------------------------------------
// �X�R�A�̐���
//-------------------------------------------------------------------------------
CBullet_UI *CBullet_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CBullet_UI *pBullet_UI = NULL;

	if (pBullet_UI == NULL)
	{// NULL��������
	 // ���I�m��
		pBullet_UI = new CBullet_UI;

		if (pBullet_UI != NULL)
		{// NULL����Ȃ�������
		 // �������������Ăяo��
			pBullet_UI->Init(pos, scale);
		}
	}
	// �l��Ԃ�
	return pBullet_UI;
}

//-------------------------------------------------------------------------------
// ����������
//-------------------------------------------------------------------------------
HRESULT CBullet_UI::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// ���
	m_pos = pos;

	// 5�����ׂ鏈��
	for (int nCnt = 0; nCnt < MAX_BULLET_UI; nCnt++)
	{
		m_apPolygon[nCnt] = CPolygon::Create(D3DXVECTOR3((pos.x - (LIFE_WIDTH * BULLET_UI_HALF) + (LIFE_WIDTH * nCnt)) + (LIFE_WIDTH / 2.0f),
			(pos.y), 0.0f), D3DXVECTOR3(LIFE_WIDTH, LIFE_HEIGHT, 0));

		// �e�N�X�`���̊��蓖��
		m_apPolygon[nCnt]->BindTexture(m_pTexture);
	}

	// �������C�t
	m_nBullet_UI = MAX_BULLET_UI;

	return S_OK;
}

//-------------------------------------------------------------------------------
// �I������
//-------------------------------------------------------------------------------
void CBullet_UI::Uninit(void)
{
	for (int nCnt = 0; nCnt < m_nBullet_UI; nCnt++)
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
void CBullet_UI::Update(void)
{

}

//-------------------------------------------------------------------------------
// �`�揈��
//-------------------------------------------------------------------------------
void CBullet_UI::Draw(void)
{
	for (int nCnt = 0; nCnt < m_nBullet_UI; nCnt++)
	{
		m_apPolygon[nCnt]->Draw();
	}
}

//-------------------------------------------------------------------------------
// �e�̐ݒ�
//-------------------------------------------------------------------------------
void CBullet_UI::SetBullet(int nBullet)
{
	// ���
	m_nBullet_UI = nBullet;
}

//-------------------------------------------------------------------------------
//	�e���Z�̏���
// nValue : ���Z����e
//-------------------------------------------------------------------------------
void CBullet_UI::AddBullet(int nValue)
{
	// ���Z
	m_nBullet_UI += nValue;

	// 5�����ׂ鏈��
	for (int nCnt = 0; nCnt < MAX_BULLET_UI; nCnt++)
	{
		// NULL��������
		if (m_apPolygon[nCnt] == NULL)
		{
			// �\��������
			m_apPolygon[nCnt] = CPolygon::Create(D3DXVECTOR3((m_pos.x - (LIFE_WIDTH * BULLET_UI_HALF) + (LIFE_WIDTH * nCnt)) + (LIFE_WIDTH / 2.0f),
				(m_pos.y), 0.0f), D3DXVECTOR3(LIFE_WIDTH, LIFE_HEIGHT, 0));
		}
	}
}

//-------------------------------------------------------------------------------
//	�e���Z�̏���
// nValue : ���Z����e
//-------------------------------------------------------------------------------
void CBullet_UI::SubtractBullet(int nValue)
{
	// 5�����ׂ鏈��
	for (int nCnt = m_nBullet_UI - 1; nCnt > m_nBullet_UI - nValue - 1; nCnt--)
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
	m_nBullet_UI -= nValue;
}

//-------------------------------------------------------------------------------
// �e���擾
//-------------------------------------------------------------------------------
int CBullet_UI::GetBullet(void)
{
	// �e�̏��̐擪�A�h���X��Ԃ�
	return m_nBullet_UI;
}