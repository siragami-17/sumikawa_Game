//--------------------------------------------------------------------------------
//
//	�v���C���[AI���� [PlayerAI.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "renderer.h"			// �����_�����O
#include "scene2D.h"			// 2D�|���S��
#include "manager.h"			// �}�l�[�W���[
#include "PlayerAI.h"			// �v���C���[AI
#include "game.h"				// �Q�[��
#include "block.h"				// �u���b�N
#include "Input_Keyboard.h"		// �L�[�{�[�h
#include "scroll.h"

#include "sound.h"
#include "explosion.h"
#include "life.h"
#include "Item.h"

//-------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CPlayerAI::m_pTexture = NULL;
D3DXVECTOR3 CPlayerAI::m_pos(0.0f,0.0f,0.0f);

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define MAX_GRAVITY		(2.5f)			// �d��

//-------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------
CPlayerAI::CPlayerAI(PRIORITY nPriority):CScene2D(nPriority)
{
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosTexU = 0;
	m_fPosTexV = 0;
	m_bMovement = false;
	m_bItem = false;
	m_Place = D3DXVECTOR2(0.0f, 0.0f);
	m_nCnt = 0;
	m_nFlame = 0;

	m_nCounter = 0;
	m_State = AI_NONE;
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CPlayerAI::~CPlayerAI()
{
}

//-------------------------------------------------------------------------------
// �v���C���[����
//-------------------------------------------------------------------------------
CPlayerAI *CPlayerAI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CPlayerAI *pPlayerAI = NULL;

	if (pPlayerAI == NULL)
	{// NULL��������
		// ���I�m��
		pPlayerAI = new CPlayerAI;

		if (pPlayerAI != NULL)
		{// NULL����Ȃ�������
			// ����������
			pPlayerAI->Init(pos, scale);

			// �e�N�X�`���̊��蓖��
			pPlayerAI->BindTexture(m_pTexture);
		}
	}
	return pPlayerAI;
}

//-------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-------------------------------------------------------------------------------
HRESULT CPlayerAI::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/AI.png", &m_pTexture);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �e�N�X�`����j��
//-------------------------------------------------------------------------------
void CPlayerAI::Unload(void)
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
HRESULT CPlayerAI::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// ������
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosTexU = 0;
	m_fPosTexV = 0;
	m_bMovement = false;
	m_bItem = false;
	m_Place = D3DXVECTOR2(0, MAX_PLAYERAI_Y);
	m_Tex = D3DXVECTOR2(4, 0.0f);
	m_nCnt = 0;
	m_nFlame = 0;

	m_nCounter = 0;
	m_State = AI_NONE;

	// ���ѕt����
	m_scale = scale;
	m_pos = pos;

	// �V�[��2D�̏���������
	CScene2D::Init(pos, scale);

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_PLAYERAI);

	//�v���C���[AI�̈ʒu��ݒ肷�鏈��
	SetPosition(m_pos, m_scale);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �|���S���̏I������
//-------------------------------------------------------------------------------
void CPlayerAI::Uninit(void)
{
	CScene2D::Uninit();
}

//-------------------------------------------------------------------------------
// �|���S���̍X�V����
//-------------------------------------------------------------------------------
void CPlayerAI::Update(void)
{
	m_pos = GetPosition();

	// �d��
	m_move.y += MAX_GRAVITY;

	// �ʒu��ۑ�
	m_PosOld.x = m_pos.x;
	m_PosOld.y = m_pos.y;

	// �X�N���[���ۑ�
	CScroll::UpdateMoveObject(m_move);

	// �ړ��ʉ��Z
	m_pos.y += m_move.y;
	m_move.x = 1.0f;


	// �f�o�b�N���[�h�̂�
#ifdef _DEBUG

	CInput_Keyboard *plnputKeyboard;
	plnputKeyboard = CManager::GetInputKeyboard();

	if (plnputKeyboard->GetPress(DIK_F) == true)
	{// AI�����ɓ�����
		m_pos.x -= m_move.x;

		m_move.x = -1.0f;

		m_bMovement = true;
	}
	else if (plnputKeyboard->GetPress(DIK_H) == true)
	{// AI���E�ɓ�����
		// ���Z
		m_pos.x += m_move.x;

		// �ړ���
		m_move.x = 1.0f;

		// ���ɖ߂�	
		SetTex();

		m_bMovement = true;
	}
#endif

	if (CItem::GetBItem())
	{
		m_pos.x += m_move.x;
		m_move.x = 1.0f;

		m_bMovement = true;
	}
	else
	{
		m_bMovement = false;
	}

	// �A�j���[�V�����֌W
	m_nCnt++;

	if ((m_nCnt % 5) == 0)
	{// �A�j���[�V�������x�̐���
		m_Place = (D3DXVECTOR2((float)m_nCnt, MAX_PLAYERAI_Y));
	}

	// �T�E���h�֌W
	CSound *pSound;
	pSound = CManager::GetSound();

	// ���C�t�֌W
	CLife *pLife;
	pLife = CGame::GetLife();

	// �������烉�C�t�����炷
	if (m_pos.y - MAX_PLAYERAI_Y > 720)
	{
		// ���C�t�����炷
		pLife->SubtractLife(1);
	}

	// �v���C���[�ƃI�u�W�F�N�g�̓����蔻��
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			// �V�[���֌W
			CScene *pScene;
			pScene = CScene::GetScene(nCntPriority, nCntScene);

			if (pScene != NULL)
			{// �I�u�W�F�N�g��NULL����Ȃ�������
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				if (objType == CScene::OBJTYPE_ENEMY)
				{// �v���C���[�ɓ��������I�u�W�F�N�g�^�C�v���G��������
				 // �ϐ��錾
					D3DXVECTOR3 PosEnemy;
					D3DXVECTOR3 ScaleEnemy;

					// �G�̈ʒu�ƃT�C�Y���擾
					PosEnemy = pScene->GetPos();
					ScaleEnemy = pScene->GetScale();

					// �G�̏��
					CEnemy *pEnemy;
					pEnemy = (CEnemy*)pScene;

					// �v���C���[�ƓG�̓����蔻��
					if (m_pos.x - (m_scale.x / 2) < PosEnemy.x + (ScaleEnemy.x / 2) &&
						m_pos.x + (m_scale.x / 2) > PosEnemy.x - (ScaleEnemy.x / 2) &&
						m_pos.y - (m_scale.y / 2) < PosEnemy.y + (ScaleEnemy.y / 2) &&
						m_pos.y + (m_scale.y / 2) > PosEnemy.y - (ScaleEnemy.y / 2))
					{
						// �G�����̐���
						CExplosion::Create(PosEnemy, D3DXVECTOR3(50, 50, 0));

						// SE�̒ǉ�
						pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
						pSound->Play(CSound::SOUND_LABEL_SE_DAMAGE);

						// �G�̔j��
						pScene->Uninit();

						// ���C�t�����炷
						pLife->SubtractLife(1);

						m_State = AI_DAMAGE;
					}
				}
				else if (objType == CScene::OBJTYPE_ITEM)
				{// �v���C���[�ɓ��������I�u�W�F�N�g�^�C�v���A�C�e����������
				 // �ϐ��錾
					D3DXVECTOR3 PosItem;
					D3DXVECTOR3 SizeItem;

					// �G�̈ʒu�ƃT�C�Y���擾
					PosItem = pScene->GetPos();
					SizeItem = pScene->GetScale();

					// �A�C�e�����
					CItem *pIteme;
					pIteme = (CItem*)pScene;

					// �v���C���[�ƃA�C�e���̓����蔻��
					if (m_pos.x - (m_scale.x / 2) < PosItem.x + (SizeItem.x / 2) &&
						m_pos.x + (m_scale.x / 2) > PosItem.x - (SizeItem.x / 2) &&
						m_pos.y - (m_scale.y / 2) < PosItem.y + (SizeItem.y / 2) &&
						m_pos.y + (m_scale.y / 2) > PosItem.y - (SizeItem.y / 2))
					{
						// �A�C�e�����Ƃ���
						m_bItem = true;

						m_pos.x += m_move.x;

						m_move.x = 0.0f;
					}
				}
			}
		}
	}
	// �A�j���[�V�����̐ݒ�
	SetTex(m_Place, m_Tex);

	//�v���C���[AI�̈ʒu��ݒ肷�鏈��
	SetPosition(m_pos, m_scale);
}

//-------------------------------------------------------------------------------
// �|���S���̕`�揈��
//-------------------------------------------------------------------------------
void CPlayerAI::Draw(void)
{
	CScene2D::Draw();
}