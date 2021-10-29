//--------------------------------------------------------------------------------
//
//	�����̏��� [explosion.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "renderer.h"			// �����_�����O
#include "scene2D.h"			// 2D�|���S��
#include "manager.h"			// �}�l�[�W���[
#include "Input_Keyboard.h"		// �L�[�{�[�h
#include "explosion.h"			// ����

//-------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//-------------------------------------------------------------------------------
// �R���X�g���N
//-------------------------------------------------------------------------------
CExplosion::CExplosion(PRIORITY nPriority) :CScene2D(nPriority)
{
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CExplosion::~CExplosion()
{
}

//-------------------------------------------------------------------------------
// �����̐���
//-------------------------------------------------------------------------------
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CExplosion *pExplosion = NULL;

	if (pExplosion == NULL)
	{
		// ���I�m��
		pExplosion = new CExplosion;

		if (pExplosion != NULL)
		{// NULL����Ȃ�������
			pExplosion->Init(pos, scale);

			pExplosion->BindTexture(m_pTexture);
		}
	}
	return pExplosion;
}

//-------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-------------------------------------------------------------------------------
HRESULT CExplosion::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/explosion000.png", &m_pTexture);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �e�N�X�`����j��
//-------------------------------------------------------------------------------
 void CExplosion::Unload(void)
 {
	 //�e�N�X�`���̊J��
	 if (m_pTexture != NULL)
	 {
		 m_pTexture->Release();
		 m_pTexture = NULL;
	 }
 }

//-------------------------------------------------------------------------------
// ����������
//-------------------------------------------------------------------------------
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// �l�������
	m_scale = scale;

	// 2D�|���S���ɒl��n��
	CScene2D::Init(pos, scale);

	// �e�N�X�`�����W�X�V
	SetTex(m_nPatternAnim, MAX_ANIMATION_PATTERN);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �|���S���̏I������
//-------------------------------------------------------------------------------
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//-------------------------------------------------------------------------------
// �|���S���̍X�V����
//-------------------------------------------------------------------------------
void CExplosion::Update(void)
{
	// �J�E���^�[�̍X�V
	m_nCounterAnim++;

	if (m_nCounterAnim % MAX_ANIMATION_COUNTER == 0)
	{// �p�^�[��No�X�V
		m_nPatternAnim += 1;

		// �e�N�X�`�����W�X�V
		SetTex(m_nPatternAnim, MAX_ANIMATION_PATTERN);

		if (m_nPatternAnim > MAX_ANIMATION_PATTERN)
		{// �S�ăJ�E���g������
			Uninit();		// �I������
		}
	}
}

//-------------------------------------------------------------------------------
// �|���S���̕`�揈��
//-------------------------------------------------------------------------------
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}