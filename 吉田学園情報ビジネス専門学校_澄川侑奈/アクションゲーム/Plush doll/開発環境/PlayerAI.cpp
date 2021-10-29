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
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosTexU = 0;
	m_fPosTexV = 0;
	m_bMovement = false;
	m_bItem = false;
	m_bStart = false;

	m_Place = D3DXVECTOR2(0.0f, 0.0f);
	m_nCntx = 0;
	m_nCnty = 0;
	m_nCnt = 0;

	m_nCounter = 0;
	m_State = AI_NONE;

	m_bRigidity = false;
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
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPosTexU = 0;
	m_fPosTexV = 0;
	m_bMovement = false;
	m_bItem = false;
	m_Place = D3DXVECTOR2(0, 0);
	m_Tex = D3DXVECTOR2(4, 2);
	m_nCntx = 0;
	m_nCnty = 0;
	m_nCnt = 0;

	m_nCounter = 0;
	m_State = AI_NORMAL;

	m_bRigidity = false;

	// ���ѕt����
	m_size = scale;
	m_pos = pos;

	// �V�[��2D�̏���������
	CScene2D::Init(pos, scale);

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_PLAYERAI);

	//�v���C���[AI�̈ʒu��ݒ肷�鏈��
	SetPosition(m_pos, m_size);

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

	// �L�[�{�[�h�֌W
	CInput_Keyboard *plnputKeyboard;
	plnputKeyboard = CManager::GetInputKeyboard();

#ifdef _DEBUG

	if (plnputKeyboard->GetPress(DIK_F) == true)
	{// AI�����ɓ�����
		m_pos.x -= m_move.x;

		m_move.x = -1.0f;

		m_bMovement = true;

		// �A�j���[�V�����֌W
		m_nCntx++;
		m_nCnty = 1;

		if ((m_nCntx % 5) == 0)
		{// �A�j���[�V�������x�̐���
			m_Place = (D3DXVECTOR2((float)m_nCntx, (float)m_nCnty));
		}
	}
	else if (plnputKeyboard->GetPress(DIK_H) == true)
	{// AI���E�ɓ�����
		// ���Z
		m_pos.x += m_move.x;

		// �ړ���
		m_move.x = 1.0f;

		m_bMovement = true;

		// �A�j���[�V�����֌W
		m_nCntx++;
		m_nCnty = 0;

	if ((m_nCntx % 5) == 0)
	{// �A�j���[�V�������x�̐���
		m_Place = (D3DXVECTOR2((float)m_nCntx, (float)m_nCnty));
	}

	}
#endif

	// �S�[������������
	if (CItem::GetBItem())
	{
		m_pos.x += m_move.x;
		m_move.x = 1.0f;

		m_bMovement = false;

		// �A�j���[�V�����֌W
		m_nCntx++;
		m_nCnty = 0;

		if ((m_nCntx % 5) == 0)
		{// �A�j���[�V�������x�̐���
			m_Place = (D3DXVECTOR2((float)m_nCntx, (float)m_nCnty));
		}
	}
	else
	{// ����ȊO
		m_bMovement = false;

		if (m_bStart == false)
		{
			// �A�j���[�V�����֌W
			m_nCntx++;
			m_nCnty = 0;

			if ((m_nCntx % 5) == 0)
			{// �A�j���[�V�������x�̐���
				m_Place = (D3DXVECTOR2((float)m_nCntx, (float)m_nCnty));
			}
		}
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

					// AI�ƓG�̓����蔻��
					if (Collision(m_pos, m_size, PosEnemy, ScaleEnemy) == true)
					{
						// �G�����̐���
						//CExplosion::Create(PosEnemy, D3DXVECTOR3(50, 50, 0));

						// SE�̒ǉ�
						//pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
						//pSound->Play(CSound::SOUND_LABEL_SE_DAMAGE);

						// �G�̔j��
						pScene->Uninit();

						// ���C�t�����炷
						//pLife->SubtractLife(1);

						// �_���[�W��Ԃɂ���
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

					// AI�ƃA�C�e���̓����蔻��
					if (Collision(m_pos, m_size, PosItem, SizeItem) == true)
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

	Move();

	// �A�j���[�V�����̐ݒ�
	SetTex(m_Place, m_Tex);

	// AI�̏�Ԑݒ�
	Status(m_State);

	// AI�̈ʒu��ݒ肷�鏈��
	SetPosition(m_pos, m_size);
}

//-------------------------------------------------------------------------------
// �|���S���̕`�揈��
//-------------------------------------------------------------------------------
void CPlayerAI::Draw(void)
{
	CScene2D::Draw();
}

//-------------------------------------------------------------------------------
// �ړ�����
//-------------------------------------------------------------------------------
void CPlayerAI::Move(void)
{
	int nBlock;

	// �u���b�N�̏��
	CBlock *pBlock;
	pBlock = CGame::GetBlock();
	nBlock = pBlock->GetBlock();

	if (m_bStart == true)
	{
		if (m_nCnt % 5 == 0)
		{
			if (m_nCnt >= 240)
			{
				// ���Z
				//m_pos.x += m_move.x;
			}
			// �ړ���
			//		m_move.x = 1.0f;

			// �A�j���[�V�����֌W
			m_nCntx++;
			m_nCnty = 0;

			if (m_nCntx % 5 == 0)
			{// �A�j���[�V�������x�̐���
				m_Place = (D3DXVECTOR2((float)m_nCntx, (float)m_nCnty));
			}
		}
	}


	// 8�Ԗڂ̃u���b�N�ɕt������
	if (nBlock <= 8 && nBlock >= 8 && m_bStart == false)
	{

		// �ړ����~������
		m_move.x = 0.0f;

		// �J�E���g�����Z����
		m_nCnt++;

		// ��莞�Ԍo������
		if (m_nCnt % 300 == 0)
		{
			m_bStart = true;
		}

		// �A�j���[�V�����֌W
		m_nCntx = 0;
		m_nCnty = 0;

		if (m_nCntx % 5 == 0)
		{// �A�j���[�V�������x�̐���
			m_Place = (D3DXVECTOR2((float)m_nCntx, (float)m_nCnty));
		}

		//�v���C���[AI�̈ʒu��ݒ肷�鏈��
		SetPosition(m_pos, m_size);
	}
}

//-------------------------------------------------------------------------------
// AI�̏�ԏ���
//-------------------------------------------------------------------------------
void CPlayerAI::Status(AI status)
{
	if (status == AI_NORMAL)
	{// �ʏ�

		// �d����Ԃł͂Ȃ�
		m_bRigidity = false;
	}
	else if (status == AI_DAMAGE)
	{// �_���[�W��������

		// �d�����
		m_bRigidity = true;

		if (m_bRigidity == true)
		{// �d������������

			// �J�E���g�����Z��������
			m_nCounter++;

			// AI�̐F��Ԃ�����
			SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

			if (m_nCounter % 70 == 0)
			{// ��莞�Ԃ�������

				// �_���[�W��Ԃ�����
				m_State = AI_NORMAL;

				// �J�E���g�����Z�b�g
				m_nCounter = 0;

				// AI�̐F��߂�
				SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
	}
}