//--------------------------------------------------------------------------------
//
//	�V�[������ [scene.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define MAX_POLYGON		(256)											// �e�N�X�`������(�I�u�W�F�N�g��)

//-------------------------------------------------------------------------------
// �|���S���N���X(��{�N���X)
//-------------------------------------------------------------------------------
class  CScene
{
public:

	//	�`�揇�̗񋓌^
	typedef enum
	{
		PRIORITY_DEFAULT = 0,		// �f�t�H���g
		PRIORITY_BGBEHING, 			// ��둤�̔w�i
		PRIORITY_EFFECT,			// �G�t�F�N�g
		PRIORITY_BULLET,			// �e
		PRIORITY_EXPLOSION,			// ���j
		PRIORITY_ENEMY,				// �G
		

		PRIORITY_PLAYER,			// �v���C���[
		PRIORITY_PLAYERAI,			// �v���C���[AI
	
		PRIORITY_BLOCK,				// �u���b�N
		PRIORITY_ITEM,				// �A�C�e��
		PRIORITY_BGFRONT,			// ��O���̔w�i	
		PRIORITY_BULLET_UI,			// UI(�e)
		PRIORITY_SCORE,				// �X�R�A
		PRIORITY_LIFE,				// ���C�t
		PRIORITY_PAUSE,				// �|�[�Y
		PRIORITY_FADE,				// �t�F�[�h
		PRIORITY_MAX
	} PRIORITY;

	// �I�u�W�F�N�g�̎��
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,													// �v���C���[
		OBJTYPE_PLAYERAI,												// �v���C���[AI
		OBJTYPE_ENEMY,													// �G
		OBJTYPE_BULLET,													// �e
		OBJTYPE_BLOCK,													// �u���b�N
		OBJTYPE_ITEM,													// �A�C�e��
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(PRIORITY nPriority = PRIORITY_DEFAULT);						// �R���X�g���N
	virtual ~CScene();													// �f�X�g���N�^

	void SetObjType(OBJTYPE objType);									// �I�u�W�F�N�g�̐ݒ�
	OBJTYPE GetObjType(void);											// �I�u�W�F�N�g�̎��
	static CScene *GetScene(int nPriority, int nCntScene);				// �I�u�W�F�N�g�̎擾

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale) = 0;		// ����������(�������z�֐�)
	virtual void Uninit(void) = 0;										// �I������(�������z�֐�)
	virtual void Update(void) = 0;										// �X�V����(�������z�֐�)
	virtual void Draw(void) = 0;										// �`�揈��(�������z�֐�)

	static void ReleaseAll(void);										// �S�Ă�j������
	static void UpdateAll(void);										// �S�Ă��X�V����
	static void DrawAll(void);											// �S�Ă�`�悷��

	void SetPos(D3DXVECTOR3 pos);										// �ʒu��ݒ�
	void SetScale(D3DXVECTOR3 scale);									// �T�C�Y��ݒ�
	void SetPriority(PRIORITY priority);								// �`�揇��ݒ�

	D3DXVECTOR3 GetPos(void);											// pos���擾
	D3DXVECTOR3 GetScale(void);											// scale���擾

protected:
	void Release(void);

private:
	static CScene *m_apScene[PRIORITY_MAX][MAX_POLYGON];				// ��ʂɕ\������I�u�W�F�N�g��
	static int m_nNumAll;												// �ő吔
	int m_nID;															// �i�[��̔ԍ�
	PRIORITY m_Priority;												// �`�揇�̎��
	D3DXVECTOR3 m_Pos;													// �ʒu
	D3DXVECTOR3 m_Scale;												// �T�C�Y

	OBJTYPE m_objType;													// �I�u�W�F�N�g�̎��

	// ���X�g�\���֌W
	static CScene *m_pTop[PRIORITY_MAX];								// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CScene *m_pCur[PRIORITY_MAX];								// ����(�Ō��)�̃I�u�W�F�N�g�̃|�C���^
	CScene *m_pPrev;													// �O�̃I�u�W�F�N�g�̃|�C���^
	CScene *m_pNext;													// ���̃I�u�W�F�N�g�̃|�C���^
};

#endif