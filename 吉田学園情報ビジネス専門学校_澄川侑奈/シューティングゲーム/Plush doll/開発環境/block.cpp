//--------------------------------------------------------------------------------
//
//	�u���b�N�̏��� [block.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "block.h"			// �u���b�N
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_��
#include "scene2D.h"		// 2D�|���S��
#include "player.h"			// �v���C���[
#include "playerAI.h"		// �v���C���[AI
#include "game.h"			// �Q�[��

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define MAX_COUNTER		(50)		// �J�E���^�[

//-------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CBlock::m_apTexture = {};

//-------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-------------------------------------------------------------------------------
HRESULT CBlock::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block.png", &m_apTexture);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �e�N�X�`����j��
//-------------------------------------------------------------------------------
void CBlock::Unload(void)
{
	//�e�N�X�`���̊J��
	if (m_apTexture != NULL)
	{
		m_apTexture->Release();
		m_apTexture = NULL;
	}
}

//-------------------------------------------------------------------------------
// �u���b�N�̐���
//-------------------------------------------------------------------------------
CBlock *CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �ϐ��錾
	CBlock *pBlock = NULL;

	if (pBlock == NULL)
	{// ���Ƀf�[�^�������Ȃ�������
		// ���I�m��
		pBlock = new CBlock;

		if (pBlock != NULL)
		{// ���Ƀf�[�^����������
			// �������������Ăяo��
			pBlock->Init(pos, size);

			// �e�N�X�`�������蓖�Ă�
			pBlock->BindTexture(m_apTexture);
		}
	}
	// �l��Ԃ�
	return pBlock;
}

//-------------------------------------------------------------------------------
// �R���X�g���N
//-------------------------------------------------------------------------------
CBlock::CBlock(PRIORITY nPriority) :CScene2D(nPriority)
{
	// ������
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounter = 0;
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CBlock::~CBlock()
{
}

//-------------------------------------------------------------------------------
// ����������
//-------------------------------------------------------------------------------
HRESULT CBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// ���
	m_size = scale;
	m_pos = pos;

	// 2D�|���S���̏������������Ăяo��
	CScene2D::Init(pos, scale);

	// �I�u�W�F�N�g�^�C�v��G�ɐݒ肷��
	SetObjType(CScene::OBJTYPE_BLOCK);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �|���S���̏I������
//-------------------------------------------------------------------------------
void CBlock::Uninit(void)
{
	// 2D�|���S���̏I���������Ăяo��
	CScene2D::Uninit();
}

//-------------------------------------------------------------------------------
// �|���S���̍X�V����
//-------------------------------------------------------------------------------
void CBlock::Update(void)
{
	// �ʒu�̎擾
	D3DXVECTOR3 Pos;
	Pos = GetPosition();

	// �v���C���[�̈ړ��ʎ擾
	D3DXVECTOR3 PlayerAIMove;
	CPlayerAI *pPlayerAI;
	pPlayerAI = CGame::GetPlayerAI();
	PlayerAIMove = pPlayerAI->GetMove();

	// ���
	m_pos = Pos;

	// �v���C���[�̉ߋ����
	pPlayerAI->GetPosOld();

	// �u���b�N�ƃv���C���[�̓����蔻��
	Collision();

	// �u���b�N�̈ʒu����2D�|���S���ɓn��
	CScene2D::SetPosition(Pos, m_size);
}

//-------------------------------------------------------------------------------
// �|���S���̕`�揈��
//-------------------------------------------------------------------------------
void CBlock::Draw(void)
{
	// 2D�|���S���̕`�揈�����Ăяo��
	CScene2D::Draw();
}

//-------------------------------------------------------------------------------
// �u���b�N�ƃI�u�W�F�N�g�̓����蔻��
//-------------------------------------------------------------------------------
bool CBlock::Collision()
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			// �V�[���֌W
			CScene *pScene;
			pScene = CScene::GetScene(nCntPriority, nCntScene);

			// �u���b�N�ƃv���C���[�̓����蔻��
			if (pScene != NULL)
			{// �I�u�W�F�N�g��NULL����Ȃ�������
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				if (objType == CScene::OBJTYPE_PLAYER)
				{// �u���b�N�ɓ��������I�u�W�F�N�g�^�C�v���v���C���[��������	
					// �ϐ��錾
					D3DXVECTOR3 PosPlayer;			// �ʒu
					D3DXVECTOR3 PosOldPlayer;		// �ߋ��̈ʒu
					D3DXVECTOR3 SizePlayer;			// �傫��
					D3DXVECTOR3 MovePlayer;			// �ړ���
					bool JumpPlayer;				// �W�����v���Ă��邩

					// �v���C���[�֌W
					CPlayer *pPlayer = NULL;
					pPlayer = (CPlayer*)pScene;		// �L���X�g

					// ���
					PosPlayer = pPlayer->GetPosition();
					SizePlayer = pPlayer->GetSize();
					MovePlayer = pPlayer->GetMove();
					PosOldPlayer = pPlayer->GetPosOld();
					JumpPlayer = pPlayer->GetJump();

					if (PosPlayer.x + SizePlayer.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
						PosPlayer.x - SizePlayer.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
						PosPlayer.y + SizePlayer.y / 2.0f >= m_pos.y - m_size.y / 2.0f &&
						PosOldPlayer.y + SizePlayer.y / 2.0f <= m_pos.y - m_size.y / 2.0f)	// �ߋ���pos���������ĂȂ���
					{// �v���C���[���ォ�瓖��������
						PosPlayer.y = m_pos.y - m_size.y / 2.0f - SizePlayer.y / 2.0f;

						MovePlayer.y = 0.0f;

						pPlayer->SetMove(MovePlayer);
						JumpPlayer = false;

						// �W�����v�̏���n��
						pPlayer->SetJump(JumpPlayer);

						// �v���C���[�̈ʒu��ݒ�
						pPlayer->SetPos(PosPlayer);
					}
				}

				if (objType == CScene::OBJTYPE_PLAYERAI)
				{// �u���b�N�ɓ��������I�u�W�F�N�g�^�C�v���v���C���[AI��������	
					// �ϐ��錾
					D3DXVECTOR3 PosPlayerAI;			// �ʒu
					D3DXVECTOR3 PosOldPlayerAI;			// �ߋ��̈ʒu
					D3DXVECTOR3 SizePlayerAI;			// �傫��
					D3DXVECTOR3 MovePlayerAI;			// �ړ���

					// �v���C���[�֌W
					CPlayerAI *pPlayerAI = NULL;
					pPlayerAI = (CPlayerAI*)pScene;		// �L���X�g

					// ���
					PosPlayerAI = pPlayerAI->GetPosition();
					SizePlayerAI = pPlayerAI->GetSize();
					MovePlayerAI = pPlayerAI->GetMove();
					PosOldPlayerAI = pPlayerAI->GetPosOld();

					if (PosPlayerAI.x + SizePlayerAI.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
						PosPlayerAI.x - SizePlayerAI.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
						PosPlayerAI.y + SizePlayerAI.y / 2.0f >= m_pos.y - m_size.y / 2.0f &&
						PosOldPlayerAI.y + SizePlayerAI.y / 2.0f <= m_pos.y - m_size.y / 2.0f)	// �ߋ���pos���������ĂȂ���
					{// �v���C���[AI���ォ�瓖��������
						PosPlayerAI.y = m_pos.y - m_size.y / 2.0f - SizePlayerAI.y / 2.0f;

						MovePlayerAI.y = 0.0f;

						pPlayerAI->SetMove(MovePlayerAI);

						

						// �v���C���[AI�̈ʒu��ݒ�
						pPlayerAI->SetPosition(PosPlayerAI, SizePlayerAI);

						return true;
					}
				}
			}
		}
	}
	return false;
}

//-------------------------------------------------------------------------------
// �u���b�N�ƃI�u�W�F�N�g�̓����蔻��
// posobject:�I�u�W�F�N�g�̈ʒu	sizeobject:�I�u�W�F�N�g�̑傫��	posoldobject:�I�u�W�F�N�g�̉ߋ��̈ʒu
//-------------------------------------------------------------------------------
bool CBlock::Collision(D3DXVECTOR3 posobject, D3DXVECTOR3 posoldobject, D3DXVECTOR3 sizeobject)
{
	//// �v���C���[�̈ړ��ʎ擾
	//D3DXVECTOR3 PlayerMove;
	//CPlayer *pPlayer;
	//pPlayer = CGame::GetPlayer();
	//PlayerMove = pPlayer->GetMove();

	//// �v���C���[AI�̈ړ��ʎ擾
	//D3DXVECTOR3 PlayerAIMove;
	//CPlayerAI *pPlayerAI;
	//pPlayerAI = CGame::GetPlayerAI();
	//PlayerAIMove = pPlayerAI->GetMove();

	//// �u���b�N�̏��
	//D3DXVECTOR3 posBlock = GetPosition();
	//D3DXVECTOR3 sizeBlock = m_size;

	//// �u���b�N�ɏ���Ă��邩
	//bool bLand = false;

	//for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	//{
	//	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	//	{
	//		// �V�[���֌W
	//		CScene *pScene;
	//		pScene = CScene::GetScene(nCntPriority, nCntScene);

	//		// �u���b�N�ƃv���C���[�̓����蔻��
	//		if (pScene != NULL)
	//		{// �I�u�W�F�N�g��NULL����Ȃ�������
	//			CScene::OBJTYPE objType;
	//			objType = pScene->GetObjType();

	//			if (objType == CScene::OBJTYPE_PLAYER)
	//			{// �u���b�N�ɓ��������I�u�W�F�N�g�^�C�v���v���C���[��������					
	//				// �v���C���[�ƃu���b�N(��)�̓����蔻��
	//				if (posobject.x + sizeobject.x / 2.0f > posBlock.x - sizeBlock.x / 2.0f &&
	//					posobject.x - sizeobject.x / 2.0f < posBlock.x + sizeBlock.x / 2.0f)
	//				{// �u���b�N�̊Ԃɂ��邩�ǂ���
	//					if (posobject.y + sizeobject.y / 2.0f > posBlock.y - sizeBlock.y / 2.0f &&
	//						posoldobject.y + sizeobject.y / 2.0f <= posBlock.y - sizeBlock.y / 2.0f)
	//					{// �ߋ���posBlock���������ĂȂ���
	//						posobject.y = posBlock.y - BLOCK_Y / 2.0f - sizeobject.y / 2.0f;

	//						// �v���C���[�̈ʒu��ݒ�
	//						pPlayer->SetPos(posobject);
	//						pPlayer->SetJump(false);
	//						pPlayer->SetMove(D3DXVECTOR3(PlayerAIMove.x, 0.0f, 0.0f));

	//						// �v���C���[AI�̈ʒu��ݒ�
	//						pPlayerAI->SetPos(posobject);
	//						pPlayerAI->SetMove(D3DXVECTOR3(PlayerAIMove.x, 0.0f, 0.0f));

	//						// �u���b�N�ɏ���Ă���
	//						bLand =  true;
	//					}
	//					else if (posobject.y - sizeobject.y / 2.0f < posBlock.y + sizeBlock.y / 2.0f &&
	//						posoldobject.y - sizeobject.y / 2.0f >= posBlock.y + sizeBlock.y / 2.0f)
	//					{// �v���C���[�ƃu���b�N(��)�̓����蔻��
	//						posobject.y = posBlock.y + BLOCK_Y / 2.0f + sizeobject.y / 2.0f;

	//						// �v���C���[�̈ʒu��ݒ�
	//						pPlayer->SetPos(posobject);

	//						pPlayer->SetMove(D3DXVECTOR3(PlayerMove.x, 0.0f, 0.0f));
	//					}
	//				}

	//				// �v���C���[�ƃu���b�N(��)�̓����蔻��
	//				if (posobject.y + sizeobject.y / 2.0f > posBlock.y - sizeBlock.y / 2.0f &&
	//					posobject.y - sizeobject.y / 2.0f < posBlock.y + sizeBlock.y / 2.0f)
	//				{// �u���b�N�̊Ԃɂ��邩�ǂ���

	//					//posBlock.x += PlayerMove.x;

	//					if ((posobject.x + sizeobject.x / 2.0f) > (posBlock.x - sizeBlock.x / 2.0f) &&
	//						(posoldobject.x + sizeobject.x / 2.0f) <= (posBlock.x - sizeBlock.x / 2.0f) + PlayerMove.x)
	//					{// �ߋ���posBlock���������ĂȂ���
	//						
	//						posobject.x = posBlock.x - BLOCK_X / 2.0f - sizeobject.x / 2.0f;
	//						posoldobject.x = posobject.x - PlayerMove.x;

	//						// �v���C���[�̈ʒu��ݒ�
	//						pPlayer->SetPos(posobject);
	//						pPlayer->SetPosOld(posoldobject);
	//							
	//						pPlayer->SetMove(D3DXVECTOR3(0.0f, PlayerAIMove.y, 0.0f));
	//					}
	//					/*else if((posobject.x - sizeobject.x / 2.0f) > (posBlock.x + sizeBlock.x / 2.0f) &&
	//							(posoldobject.x - sizeobject.x / 2.0f) <= (posBlock.x + sizeBlock.x / 2.0f))
	//					{
	//						posobject.x = posBlock.x + BLOCK_X / 2.0f + sizeobject.x / 2.0f;

	//						// �v���C���[�̈ʒu��ݒ�
	//						pPlayer->SetPos(posobject);
	//						pPlayer->SetMove(D3DXVECTOR3(0.0f, PlayerMove.y, 0.0f));		// ������
	//					}*/
	//				}
	//			}
	//		}
	//	}
	//}
	return false;
}