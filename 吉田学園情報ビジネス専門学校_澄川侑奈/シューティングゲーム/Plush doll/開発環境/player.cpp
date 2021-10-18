//--------------------------------------------------------------------------------
//
//	�v���C���[���� [player.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "renderer.h"			// �����_�����O
#include "scene2D.h"			// 2D�|���S��
#include "manager.h"			// �}�l�[�W���[
#include "Input_Keyboard.h"		// �L�[�{�[�h
#include "player.h"				// �v���C���[
#include "bullet.h"				// �e
#include "sound.h"				// �T�E���h
#include "explosion.h"			// ����
#include "life.h"				// ���C�t
#include "game.h"				// �Q�[��
#include "Bullet_UI.h"			// �e��UI
#include "fade.h"				// �t�F�[�h
#include "result.h"				// ���U���g
#include "block.h"				// �u���b�N
#include "enemy.h"				// �G
#include "scroll.h"				// �X�N���[��
#include "item.h"				// �A�C�e��
#include "result.h"				// ���U���g

#include "PlayerAI.h"			// �v���C���[AI

//-------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define PLAYER_MOVE		(5.0f)			// �ړ���
#define MAX_GRAVITY		(2.5f)			// �d��
#define MAX_JUMP		(-35.0f)		// �W�����v

//-------------------------------------------------------------------------------
// �R���X�g���N
//-------------------------------------------------------------------------------
CPlayer::CPlayer(PRIORITY nPriority):CScene2D(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosTexU = 0.0f;
	m_fPosTexV = 0.0f;
	m_fmove = 0.0f;
	m_bJump = true;
	m_bItem = false;
	m_bMove = false;
	m_bRigidity = false;
	m_bMoveAI = false;
	m_Place = POSPLAYER_NONE;
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CPlayer::~CPlayer()
{
}

//-------------------------------------------------------------------------------
// �v���C���[����
//-------------------------------------------------------------------------------
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CPlayer *pPlayer = NULL;

	if (pPlayer == NULL)
	{// NULL��������
		// ���I�m��
		pPlayer = new CPlayer;

		if (pPlayer != NULL)
		{// NULL����Ȃ�������
			// ����������
			pPlayer->Init(pos, scale);

			// �e�N�X�`���̊��蓖��
			pPlayer->BindTexture(m_pTexture);
		}
	}
	return pPlayer;
}

//-------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-------------------------------------------------------------------------------
HRESULT CPlayer::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Player00.png", &m_pTexture);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �e�N�X�`����j��
//-------------------------------------------------------------------------------
void CPlayer::Unload(void)
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
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// ������
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosTexU = 0.0f;
	m_fPosTexV = 0.0f;
	m_fmove = 0.0f;
	m_bJump = true;
	m_bItem = false;
	m_bMove = false;
	m_bRigidity = false;
	m_bMoveAI = false;
	m_Place = POSPLAYER_LEFT;

	// ���ѕt����
	m_size = scale;

	// �V�[��2D�̏���������
	CScene2D::Init(pos, scale);

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_PLAYER);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �|���S���̏I������
//-------------------------------------------------------------------------------
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//-------------------------------------------------------------------------------
// �|���S���̍X�V����
//-------------------------------------------------------------------------------
void CPlayer::Update(void)
{
	// �ϐ��錾
	D3DXVECTOR3 Pos;
	Pos = GetPosition();

	// �L�[�{�[�h�֌W
	CInput_Keyboard *plnputKeyboard;
	plnputKeyboard = CManager::GetInputKeyboard();

	// �T�E���h�֌W
	CSound *pSound;
	pSound = CManager::GetSound();

	// �eUI�֌W
	CBullet_UI *pBullet_UI;					// �ϐ�
	pBullet_UI = CGame::GetBullet_UI();		// �擾

	// �t�F�[�h�֌W
	CFade *pFade;
	pFade = CManager::GetFade();

	// ���C�t�֌W
	CLife *pLife;
	pLife = CGame::GetLife();

	// AI�̈ړ��ʎ擾
	D3DXVECTOR3 PosPlayerAI;
	CPlayerAI *pPlayerAI;
	pPlayerAI = CGame::GetPlayerAI();
	PosPlayerAI = pPlayerAI->GetPos();


	// �v���C���[�𔽓]
	if (Pos.x < PosPlayerAI.x)
	{
		SetInversion();		// ���]
	}
	if (Pos.x > PosPlayerAI.x)
	{
		SetTex();			// ���ɖ߂�	
	}

	if (pFade->GetFade() == CFade::FADE_NONE)
	{// �t�F�[�h���͓����Ȃ�
		// �e��������
		if (plnputKeyboard->GetTrigger(DIK_SPACE) == true)
		{
			if (m_bRigidity == false)
			{
				if (Pos.x < PosPlayerAI.x)
				{
					CBullet::Create(Pos, D3DXVECTOR3(-9.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

					// SE�̍Đ�
					pSound->Play(CSound::SOUND_LABEL_SE_SHOT);
				}

				if (Pos.x > PosPlayerAI.x)
				{
					CBullet::Create(Pos, D3DXVECTOR3(9.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

					// SE�̍Đ�
					pSound->Play(CSound::SOUND_LABEL_SE_SHOT);
				}
			}
		}

		// �v���C���[�̑���֌W
		if (plnputKeyboard->GetTrigger(DIK_W) == true && m_bJump == false)
		{//�W�����v�̏���(2�i�W�����v�̐���)
			if (m_bRigidity == false)
			{
				m_move.y = MAX_JUMP;
				m_bJump = true;
				printf("%s", "jump����\n");		// �f�o�b�N���O
			}

			// SE�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_SE_JUMP);
		}

		// �v���C���[�̈ړ�����
		if (plnputKeyboard->GetPress(DIK_A) == true)
		{// A�L�[��������
			if (m_bRigidity == false)
			{// �d�����Ă��Ȃ�������
				m_move.x += -5.0f;
			}
		}

		if (plnputKeyboard->GetPress(DIK_D) == true)
		{// D�L�[��������
			if (m_bRigidity == false)
			{// �d�����Ă��Ȃ�������
				m_move.x += 5.0f;
			}
		}

		// �������烉�C�t�����炷
		if (Pos.y - MAX_PLAYER_Y > 720)
		{
			// ���C�t�����炷
			pLife->SubtractLife(1);
		}
	}
	// �d��
	m_move.y += MAX_GRAVITY;

	// AI���ړ��������ǂ����̏����擾
	m_bMoveAI = pPlayerAI->GetMovement();

	if (m_bMoveAI == false)
	{// AI���ړ����Ă��Ȃ�������
		if (m_bMove == true)
		{// �ړ����Ă�����
			if (m_Place == POSPLAYER_LEFT)
			{// �v���C���[��AI�̉E���ɂ�����
				Pos.x += 15.0f;
				if (Pos.x > PosPlayerAI.x + INTERVAL)
				{
					m_bMove = false;
					m_Place = POSPLAYER_RIGHT;
				}
			}
			else if (m_Place == POSPLAYER_RIGHT)
			{// �v���C���[��AI�̍����ɂ�����
				Pos.x += -15.0f;
				if (Pos.x < PosPlayerAI.x - INTERVAL)
				{
					m_bMove = false;
					m_Place = POSPLAYER_LEFT;
				}
			}
			m_move.x = 0.0f;
		}
		// ����n��
		pPlayerAI->SetMovement(m_bMoveAI);
	}


	// ����
	m_move.x += (0.0f - m_move.x) * 0.4f;

	// �ʒu��ۑ�
	m_PosOld.x = Pos.x;
	m_PosOld.y = Pos.y;



	// �ړ�����
	if (Pos.y > 550.0f)
	{// �v���C���[�ƃv���C���[AI�̓����蔻��(�_)
		if (Pos.x < PosPlayerAI.x + INTERVAL &&m_Place == POSPLAYER_RIGHT)
		{// ��
			Pos.x = PosPlayerAI.x + INTERVAL;

			if (m_bMoveAI == false)
			{
				if (m_bJump == false)
				{// �W�����v���Ă��Ȃ�������
					m_move.y = MAX_JUMP;
					m_bMove = true;
					m_bJump = true;

					// SE�̍Đ�
					pSound->Play(CSound::SOUND_LABEL_SE_JUMP);
				}

			}
		}
		if (Pos.x > PosPlayerAI.x - INTERVAL &&m_Place == POSPLAYER_LEFT)
		{// �E
			Pos.x = PosPlayerAI.x - INTERVAL;

			if (m_bMoveAI == false)
			{
				if (m_bJump == false)
				{// �W�����v���Ă��Ȃ�������
					m_move.y = MAX_JUMP;
					m_bMove = true;
					m_bJump = true;

					// SE�̍Đ�
					pSound->Play(CSound::SOUND_LABEL_SE_JUMP);
				}
			}
		}
	}
	// �ړ��ʉ��Z
	Pos += m_move;
	//	�v���C���[�ƕǂ̓����蔻��
	if (Pos.x < PosPlayerAI.x - 300.0f)
	{
		Pos.x = PosPlayerAI.x - 300.0f;

	}
	if (Pos.x > PosPlayerAI.x + 300.0f)
	{
		Pos.x = PosPlayerAI.x + 300.0f;

	}
	
	// �v���C���[�Ɖ�ʂ̓����蔻��
	if (Pos.x < 0.0)
	{
		Pos.x = 0.0;
	}
	if (Pos.x > 1280.0f)
	{
		Pos.x = 1280.0f;
	}

	// �ʒu�̐ݒ�
	SetPosition(Pos, m_size);

	// �v���C���[�ƓG�̓����蔻��
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
					if (Pos.x - (m_size.x / 2) < PosEnemy.x + (ScaleEnemy.x / 2) &&
						Pos.x + (m_size.x / 2) > PosEnemy.x - (ScaleEnemy.x / 2) &&
						Pos.y - (m_size.y / 2) < PosEnemy.y + (ScaleEnemy.y / 2) &&
						Pos.y + (m_size.y / 2) > PosEnemy.y - (ScaleEnemy.y / 2))
					{
						// �G�����̐���
						CExplosion::Create(PosEnemy, D3DXVECTOR3(50, 50, 0));

						// SE�̒ǉ�
						pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
						pSound->Play(CSound::SOUND_LABEL_SE_DAMAGE);

						// �G�̔j��
						pScene->Uninit();

						// �_���[�W���
						m_State = PLAYER_DAMAGE;

						m_bRigidity = true;
					}
					// �d������
					if (m_bRigidity == true)
					{
						m_nCounter++;

						SetCol(D3DXCOLOR(255, 0, 0, 255));

						if (m_nCounter  %180 == 0)
						{// 2�b��������
							m_bRigidity = false;		// �d����Ԃ�����
							m_nCounter = 0;				// �J�E���^�[�����Z�b�g
							m_State = PLAYER_NORMAL;	// �_���[�W��Ԃ�����
							SetCol(D3DXCOLOR(255, 255, 255, 255));
						}
					}
				}

				if (objType == CScene::OBJTYPE_ITEM)
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
					if (Pos.x - (m_size.x / 2) < PosItem.x + (SizeItem.x / 2) &&
						Pos.x + (m_size.x / 2) > PosItem.x - (SizeItem.x / 2) &&
						Pos.y - (m_size.y / 2) < PosItem.y + (SizeItem.y / 2) &&
						Pos.y + (m_size.y / 2) > PosItem.y - (SizeItem.y / 2))
					{
						// �A�C�e�����Ƃ���
						m_bItem = true;
					}
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------
// �|���S���̕`�揈��
//-------------------------------------------------------------------------------
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//-------------------------------------------------------------------------------
// �ʒu��ݒ�
//-------------------------------------------------------------------------------
void CPlayer::SetPos(D3DXVECTOR3 pos)
{
	// Scene2D�ɏ���n��
	SetPosition(pos, m_size);
}

//-------------------------------------------------------------------------------
// �v���C���[�̈ړ��A�j���[�V����
//-------------------------------------------------------------------------------
void CPlayer::Move(void)
{
	// �L�[�{�[�h�֌W
	CInput_Keyboard *plnputKeyboard;
	plnputKeyboard = CManager::GetInputKeyboard();

	if (plnputKeyboard->GetPress(DIK_A) == true)
	{

	}
}