//--------------------------------------------------------------------------------
//
//	�G�̏��� [enemy.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "enemy.h"			// �G
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_��
#include "scene2D.h"		// 2D�|���S��
#include "game.h"			// �Q�[��
#include "PlayerAI.h"		// �v���C���[AI

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define MAX_COUNTER		(50)		// �J�E���^�[

//-------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture = {};

//-------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-------------------------------------------------------------------------------
HRESULT CEnemy::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy01.png", &m_apTexture);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �e�N�X�`����j��
//-------------------------------------------------------------------------------
void CEnemy::Unload(void)
{
	//�e�N�X�`���̊J��
	if (m_apTexture != NULL)
	{
		m_apTexture->Release();
		m_apTexture = NULL;
	}
}

//-------------------------------------------------------------------------------
// �G�̐���
//-------------------------------------------------------------------------------
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, ENEMYTYPE type)
{
	// �ϐ��錾
	CEnemy *pEnemy = NULL;

	if (pEnemy == NULL)
	{// ���Ƀf�[�^�������Ȃ�������
		// ���I�m��
		pEnemy = new CEnemy;

		if (pEnemy != NULL)
		{// ���Ƀf�[�^����������
			// �������������Ăяo��
			pEnemy->Init(pos, scale, move);

			// �G�̃e�N�X�`�������蓖�Ă�
			pEnemy->BindTexture(m_apTexture);
		}
	}
	// �l��Ԃ�
	return pEnemy;
}

//-------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------
CEnemy::CEnemy(PRIORITY nPriority) :CScene2D(nPriority)
{
	// ������
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Colr = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nCounter = 0;
	m_nCntColr = 0;
	m_State = ENEMY_NONE;
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CEnemy::~CEnemy()
{
}

//-------------------------------------------------------------------------------
// ����������
//-------------------------------------------------------------------------------
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move)
{
	// ������
	m_Colr = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nCounter = 0;
	m_nCntColr = 0;
	m_State = ENEMY_NONE;

	// ���
	m_scale = scale;
	m_move = move;

	// 2D�|���S���̏������������Ăяo��
	CScene2D::Init(pos, scale);

	// �I�u�W�F�N�g�^�C�v��G�ɐݒ肷��
	SetObjType(CScene::OBJTYPE_ENEMY);

	// �G�̏�Ԃ�ʏ�ɂ���
	SetState(ENEMY::ENEMY_NORMAL);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �|���S���̏I������
//-------------------------------------------------------------------------------
void CEnemy::Uninit(void)
{
	// 2D�|���S���̏I���������Ăяo��
	CScene2D::Uninit();
}

//-------------------------------------------------------------------------------
// �|���S���̍X�V����
//-------------------------------------------------------------------------------
void CEnemy::Update(void)
{
	// �ʒu�̎擾
	D3DXVECTOR3 Pos;
	Pos = GetPosition();

	D3DXVECTOR3 move = MoveSearch(m_move.x);

	// �ړ��ʉ��Z
	Pos += move;

	// �G�̓��������Z
	Pos.y += MoveSnake();




// �G�̈ʒu����2D�|���S���ɓn��
	CScene2D::SetPosition(Pos, m_scale);

	//// �G�̏��
	//switch (m_State)
	//{
	//	// �ʏ�
	//case CEnemy::ENEMY_NORMAL:
	//	m_Colr = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//	// �����i�[
	//	SetCol(m_Colr);
	//	break;

	//	// �_���[�W
	//case CEnemy::ENEMY_DAMAGE:
	//	m_Colr = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	//	if (m_nCntColr %2 == 0)
	//	{// �_��
	//		CEnemy::ENEMY_NORMAL;
	//	}

	//	// �����i�[
	//	SetCol(m_Colr);
	//	break;
	//}
}

//-------------------------------------------------------------------------------
// �|���S���̕`�揈��
//-------------------------------------------------------------------------------
void CEnemy::Draw(void)
{
	// 2D�|���S���̕`�揈�����Ăяo��
	CScene2D::Draw();

	//for (int nCnt = 0; nCnt < ENEMYTYPE_MAX-1; nCnt++)
	//{
	//	switch (nCnt)
	//	{
	//	case 0:
	//		SetInversion();
	//		break;

	//	case 1:
	//		SetTex();
	//		break;
	//	}
	//}

}

//-------------------------------------------------------------------------------
// �G�̈ړ�����
//-------------------------------------------------------------------------------
float CEnemy::MoveSnake(void)
{
	// �ړ��ʐؑ�
	if (m_nCounter >= MAX_COUNTER*2)
	{// �J�E���^�[��20�ȏゾ������
		m_nCounter = 0;			// �J�E���^�[��0�ɂ���
	}

	if (m_nCounter >= MAX_COUNTER)
	{// �J�E���^�[��10�ȏ�ɂȂ�����
		m_move.y = 0.5f;		// y��������5.0f
	}
	else
	{// �J�E���^�[��10�ȉ��ɂȂ�����
		m_move.y = -0.5f;		// y��������-5.0f
	}

	if (m_move.y == 0)
	{// �G�̈ړ��ʂ�0�̎�
	 // ���
		m_move.y = 10.0f;		// �ړ��ʂ�10.0f�ɂ���
	}

	m_nCounter++;

	// �l��Ԃ�
	return m_move.y;
}

//-------------------------------------------------------------------------------
// �G�̒T������
//-------------------------------------------------------------------------------
D3DXVECTOR3 CEnemy::MoveSearch(float move)
{
	// �ʒu�̎擾
	D3DXVECTOR3 Pos;
	Pos = GetPosition();

	// AI�֌W
	D3DXVECTOR3 PosPlayerAI;
	CPlayerAI * pPlayerAI;
	PosPlayerAI = pPlayerAI->GetPos();

	// �ۑ��p
	D3DXVECTOR3 moveAI;

	// ���Βl�����߂�
	D3DXVECTOR3 vec = PosPlayerAI - Pos;

	// �p�x�v�Z
	float fAtan = atan2f(vec.x, vec.y);

	if (move < 0.0f)
	{
		move *= -1.0f;
	}
	moveAI.x = move * (float)sin(fAtan);
	moveAI.y = move * (float)cos(fAtan);

	return moveAI;
}