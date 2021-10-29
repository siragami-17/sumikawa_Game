//--------------------------------------------------------------------------------
//
//	�v���C���[AI���� [PlayerAI.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _PLAYERAI_H_
#define _PLAYERAI_H_

#include "main.h"		// ���C��
#include "scene2D.h"	// 2D�|���S��

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define MAX_PLAYERAI_X			(223.0f/2)		// �v���C���[�̕�(�����蔻��)
#define MAX_PLAYERAI_Y			(277.0f/2)		// �v���C���[�̍���(�����蔻��)

//-------------------------------------------------------------------------------
// �v���C���[�N���X(2D�|���S���N���X�̔h��)
//-------------------------------------------------------------------------------
class CPlayerAI : public CScene2D
{
public:
	CPlayerAI(PRIORITY nPriority = PRIORITY_PLAYERAI);
	~CPlayerAI();

	static CPlayerAI *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);		// �I�u�W�F�N�g�̐���

	// �e�N�X�`���֌W�̊֐�
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �v���C���[AI�ʒu�֌W
	static D3DXVECTOR3 GetPos(void) { return m_pos; }				// �ʒu���擾
	D3DXVECTOR3 GetPosOld(void) { return m_PosOld; }				// �ߋ��̈ʒu���擾
	D3DXVECTOR3 GetMove(void) { return m_move; }					// �ړ������擾
	bool GetMovement(void) { return m_bMovement; }					// �ړ����Ă��邩�ǂ���
	bool GetItem(void) { return m_bItem; }							// �A�C�e���̎擾

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }					// �ʒu��ݒ�
	void SetMove(D3DXVECTOR3 move) { m_move = move; }				// �ړ��ʂ�ݒ�
	void SetMovement(bool movement) { m_bMovement = movement; }		// �ړ����Ă��邩�̏���ݒ�
	void SetItem(bool bItem) { m_bItem = bItem; }					// �v���C���[���A�C�e������肵����

	void Move(void);

private:
	// AI�̏��
	typedef enum
	{
		AI_NONE = 0,
		AI_NORMAL,		// �ʏ�
		AI_DAMAGE,		// �_���[�W
		AI_MAX,
	}AI;

	// �����o�֐�
	void Status(AI status);

	// �����o�ϐ�
	static D3DXVECTOR3 m_pos;										// �ʒu
	D3DXVECTOR3 m_size;												// �傫��
	D3DXVECTOR3 m_move;												// �ړ���
	D3DXVECTOR3 m_PosOld;											// �ʒu
	static LPDIRECT3DTEXTURE9 m_pTexture;							// ���L�e�N�X�`���̃|�C���^
	float m_fPosTexU;												// �e�N�X�`����U���W
	float m_fPosTexV;												// �e�N�X�`����V���W
	bool m_bMovement;												// �ړ��������ǂ���
	bool m_bItem;													// �A�C�e�����Ƃ�����
	bool m_bStart;													// �ړ����邩�ǂ���

	// �A�j���[�V�����֌W
	D3DXVECTOR2 m_Place;											// �e�N�X�`��������ꏊ
	D3DXVECTOR2 m_Tex;												// ������
	int m_nCntx;													// �J�E���gX
	int m_nCnty;													// �J�E���gY

	// �F�֌W 
	D3DXCOLOR m_Colr;												// �J���[
	AI m_State;														// ���
	int m_nCounter;													// �J�E���^�[
	int m_nCntColr;													// �F�̐؂�ւ��J�E���^�[

	int m_nCnt;

	bool m_bRigidity;											// �d�����Ă��邩
};

#endif