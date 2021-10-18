//--------------------------------------------------------------------------------
//
//	�Q�[���V�[������ [game.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"		// ���C��
#include "scene.h"		// �V�[��

//-------------------------------------------------------------------------------
// �O���錾
//-------------------------------------------------------------------------------
class CPlayer;						// �v���C���[
class CBg;							// �w�i
class CEnemy;						// �G
class CNumber;						// �i���o�[
class CScore;						// �X�R�A
class CPolygon;						// �|���S��
class CLife;						// ���C�t
class CBullet_UI;					// �eUI
class CBlock;						// �u���b�N
class CPlayerAI;					// �v���C���[AI
class CEffect;						// �G�t�F�N�g
class CPause;						// �|�[�Y
class CItem;						// �A�C�e��

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define MAX_LINE		(18)		// �c��
#define MAX_COLUMN		(100)		// ����

//-------------------------------------------------------------------------------
// �Q�[���V�[���N���X(�h���N���X)
//-------------------------------------------------------------------------------
class CGame : public CScene
{
public:
	// ���U���g�̎��
	typedef enum RESULTMODE
	{
		RESULTMODE_NONE = 0,
		RESULTMODE_GAMECLEAR,		// �N���A
		RESULTMODE_GAMEOVER,		// �Q�[���I�[�o�[
		RESULTMODE_MAX,
	}RESULTMODE;

	CGame();
	~CGame();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	static void LoadAll(void);										// �S�Ẵe�N�X�`����ǂݍ���
	static void UnloadAll(void);									// �S�Ẵe�N�X�`����j��

	//�f�o�C�X�̎擾
	static CPlayer *GetPlayer(void) { return m_pPlayer; }			// �v���C���[�̎擾
	static CPlayerAI *GetPlayerAI(void) { return m_pPlayerAI; }		// �v���C���[AI�̎擾
	static CBg *GetBg(void) { return m_pBg;}						// �w�i�̎擾
	static CEnemy *GetEnemy(void) { return m_pEnemy; }				// �G�̎擾
	static CNumber *GetNumber(void) { return m_pNumber; }			// �i���o�[�̎擾
	static CScore *GetScore(void) { return m_pScore; }				// �X�R�A�̎擾
	static CPolygon *GetPolygon(void) { return m_pPolygon; }		// �|���S���̎擾
	static CLife *GetLife(void) { return m_pLife; }					// ���C�t�̎擾
	static CBullet_UI *GetBullet_UI(void) { return m_pBullet_UI; }	// �eUI�̎擾
	static CBlock *GetBlock(void) { return m_pBlock; }				// �u���b�N�̎擾
	static RESULTMODE GetResult(void) { return m_resultmode; }		// ���U���g�̎擾
	static CEffect *GetEffect(void) { return m_effect; }			// �G�t�F�N�g�擾
	static CPause *GetPause(void) { return m_pPause; }				// �|�[�Y�̎擾
	static CItem *GetItem(void) { return m_pItem; }					// �A�C�e���̎擾

private:
	static CPlayer *m_pPlayer;										// �v���C���[�̃|�C���^
	static CPlayerAI *m_pPlayerAI;									// �v���C���[AI�̃|�C���^
	static CBg *m_pBg;												// �w�i�̃|�C���^
	static CEnemy *m_pEnemy;										// �G�̃|�C���^
	static CNumber *m_pNumber;										// �i���o�[�̃|�C���^
	static CScore *m_pScore;										// �X�R�A�̃|�C���^
	static CPolygon *m_pPolygon;									// �|���S���̃|�C���^
	static CLife *m_pLife;											// ���C�t�̃|�C���^
	static CBullet_UI * m_pBullet_UI;								// �eUI�̃|�C���^
	static CBlock *m_pBlock;										// �u���b�N�̃|�C���^
	static CEffect *m_effect;										// �G�t�F�N�g�̃|�C���^
	static CPause *m_pPause;										// �|�[�Y�̃|�C���^	
	static CItem *m_pItem;											// �A�C�e���̃|�C���^								

	static RESULTMODE m_resultmode;									// ���U���g���[�h				
	static int m_MapData[MAX_LINE][MAX_COLUMN];						// �}�b�v�̓񎟔z��
};

#endif