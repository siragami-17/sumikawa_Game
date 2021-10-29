//--------------------------------------------------------------------------------
//
//	�v���C���[���� [player.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"		// ���C��
#include "scene2D.h"	// 2D�|���S��

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define MAX_PLAYER_X			(198.0f*0.5)		//�v���C���[�̕�(�����蔻��)
#define MAX_PLAYER_Y			(302.0f*0.5)		//�v���C���[�̍���(�����蔻��)
#define INTERVAL				(150.0f)			// �v���C���[�ƃv���C���[AI�̊Ԋu

//-------------------------------------------------------------------------------
// �v���C���[�N���X(2D�|���S���N���X�̔h��)
//-------------------------------------------------------------------------------
class CPlayer : public CScene2D
{
public:
	CPlayer(PRIORITY nPriority = PRIORITY_PLAYER);
	~CPlayer();

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);		// �I�u�W�F�N�g�̐���

	// �e�N�X�`���֌W�̊֐�
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetMove(void) { return m_move; }					// �v���C���[�̈ړ��ʎ擾
	D3DXVECTOR3 GetPosOld(void) { return m_PosOld; }				// �v���C���[�̉ߋ��̈ʒu�擾
	bool GetJump(void) { return m_bJump; }							// �v���C���[�̃W�����v���擾
	bool GetItem(void) { return m_bItem; }							// �A�C�e���̎擾

	void SetPos(D3DXVECTOR3 pos);									// �ʒu��ݒ�
	void SetPosOld(D3DXVECTOR3 posold) { m_PosOld = posold; }		// �ߋ��̈ʒu��ݒ�
	void SetMove(D3DXVECTOR3 move) { m_move = move; }				// �v���C���[�̈ړ��ʂ�ݒ�
	void SetJump(bool bJunp) { m_bJump = bJunp; }					// �v���C���[�̃W�����v��ݒ�
	void SetItem(bool bItem) { m_bItem = bItem; }					// �v���C���[���A�C�e������肵����

	

private:
	// �v���C���[�̈ʒu
	typedef enum
	{
		POSPLAYER_NONE = 0,
		POSPLAYER_LEFT,		// ��
		POSPLAYER_RIGHT,	// �E
	}POSPLAYER;

	// �����o�֐�
	void Animation(void);

	// �����o�ϐ�
	// �v���C���[�̈ʒu�֌W
	POSPLAYER m_Place;
	bool m_bMove;		// �ړ����Ă��邩�ǂ���

	D3DXVECTOR3 m_size;											// �傫��
	D3DXVECTOR3 m_move;											// �ړ���
	float m_fmove;												// �ړ���(x����)
	D3DXVECTOR3 m_PosOld;										// �ߋ��̏��

	static LPDIRECT3DTEXTURE9 m_pTexture;						// ���L�e�N�X�`���̃|�C���^
	float m_fPosTexU;											// �e�N�X�`����U���W
	float m_fPosTexV;											// �e�N�X�`����V���W
	bool m_bJump;												// �W�����v���Ă��邩
	bool m_bItem;												// �A�C�e�����Ƃ�����
	bool m_bMoveAI;												// �v���C���[AI�����������ǂ���


	// �F�֌W 
	D3DXCOLOR m_Colr;											// �J���[
	int m_nCounter;												// �J�E���^�[
	int m_nCntColr;												// �F�̐؂�ւ��J�E���^�[

	// �A�j���[�V�����֌W
	D3DXVECTOR2 m_TexNow;		// �e�N�X�`��������ꏊ
	D3DXVECTOR2 m_Tex;			// ������
	int m_nCntx;				// �J�E���gX
	int m_nCnty;				// �J�E���gY


	static bool m_bCollison;
	static int m_nCntEnemy;
	int m_nCnt;

};

#endif