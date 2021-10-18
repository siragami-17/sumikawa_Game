//--------------------------------------------------------------------------------
//
//	�e�̏��� [bullet.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "renderer.h"			// �����_�����O
#include "manager.h"			// �}�l�[�W���[
#include "Input_Keyboard.h"		// �L�[�{�[�h
#include "bullet.h"				// �e
#include "explosion.h"			// ����
#include "sound.h"				// �T�E���h
#include "enemy.h"				// �G
#include "scene.h"				// �|���S��
#include "score.h"				// �X�R�A

//-------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//-------------------------------------------------------------------------------
// �R���X�g���N
//-------------------------------------------------------------------------------
CBullet::CBullet(PRIORITY nPriority) :CScene2D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CBullet::~CBullet()
{
}

//-------------------------------------------------------------------------------
// �e�̐���
//-------------------------------------------------------------------------------
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale)
{
	CBullet *pBullet = NULL;

	if (pBullet == NULL)
	{
		// ���I�m��
		pBullet = new CBullet;

		if (pBullet != NULL)
		{// NULL����Ȃ�������
			pBullet->Init(pos, move, scale);

			pBullet->BindTexture(m_pTexture);
		}
	}
	return pBullet;
}

//-------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-------------------------------------------------------------------------------
HRESULT CBullet::Load(void)
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
 void CBullet::Unload(void)
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
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale)
{
	// �l�������
	m_move = move;
	m_scale = scale;

	// 2D�|���S���ɒl��n��
	CScene2D::Init(pos, scale);

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_BULLET);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �|���S���̏I������
//-------------------------------------------------------------------------------
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//-------------------------------------------------------------------------------
// �|���S���̍X�V����
//-------------------------------------------------------------------------------
void CBullet::Update(void)
{
	// �ϐ��錾
	D3DXVECTOR3 Pos;
	Pos = GetPosition();

	// �T�E���h�֌W
	CSound *pSound;
	pSound = CManager::GetSound();

	// pos��move�̒l�𖈕b+������
	Pos += m_move;
	SetPosition(Pos, m_scale);

	// ��ʂƒe�̓����蔻��
	//�e����ʊO�ɍs�������������
	if (Pos.x - m_scale.x / 2.0f < 0.0f||
		Pos.x + m_scale.x/2.0f >SCREEN_WIDTH||
		Pos.y - m_scale.y/2.0f<0.0f||
		Pos.y + m_scale.y/2.0f>SCREEN_HEIGHT)
	{
		// �����̐���
		CExplosion::Create(Pos, D3DXVECTOR3(50, 50, 0));

		// SE�̒ǉ�
		pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);


		Uninit();

		return;
	}

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			CScene *pScene;
			pScene = CScene::GetScene(nCntPriority,nCntScene);

			if (pScene != NULL)
			{// �I�u�W�F�N�g��NULL����Ȃ�������
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				if (objType == CScene::OBJTYPE_ENEMY)
				{// �I�u�W�F�N�g�^�C�v���G��������

					// �ϐ��錾
					D3DXVECTOR3 PosEnemy;
					D3DXVECTOR3 ScaleEnemy;

					// �G�̈ʒu�ƃT�C�Y���擾
					PosEnemy = pScene->GetPos();
					ScaleEnemy = pScene->GetScale();

					// �e�ƓG�̓����蔻��
					if (Pos.x - (m_scale.x / 2) < PosEnemy.x + (ScaleEnemy.x / 2) &&
						Pos.x + (m_scale.x / 2) > PosEnemy.x - (ScaleEnemy.x / 2) &&
						Pos.y - (m_scale.y / 2) < PosEnemy.y + (ScaleEnemy.y / 2) &&
						Pos.y + (m_scale.y / 2) > PosEnemy.y - (ScaleEnemy.y / 2))
					{
						// �����̐���
						CExplosion::Create(PosEnemy, D3DXVECTOR3(50, 50, 0));

						// SE�̒ǉ�
						pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);

						// �G�̔j��
						pScene->Uninit();

						// �X�R�A�̉��Z
						CScore::AddScore(350);

						// �e�̔j��
						Uninit();

						return;
					}
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------
// �|���S���̕`�揈��
//-------------------------------------------------------------------------------
void CBullet::Draw(void)
{
	CScene2D::Draw();
}