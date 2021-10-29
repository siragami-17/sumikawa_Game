//--------------------------------------------------------------------------------
//
//	�A�C�e������ [item.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"			// ���C��
#include "scene2D.h"		// �V�[��

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// �A�C�e���N���X(�V�[���̔h���N���X)
//-------------------------------------------------------------------------------
class CItem :public CScene2D
{
public:
	// �A�C�e���̎��
	typedef enum
	{
		ITEM_NONE = 0,
		ITEM_GOAL,		// �S�[���A�C�e��
		ITEM_MAX
	}ITEM;

	CItem(PRIORITY nPriority = PRIORITY_ITEM);
	~CItem();

	// �e�N�X�`���֌W�̊֐�
	static HRESULT Load(void);
	static void Unload(void);

	// �I�u�W�F�N�g�̐���
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static bool GetBItem(void) { return m_bdemasita; }

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[ITEM_MAX];		// �e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_size;										// �T�C�Y
	D3DXVECTOR3 m_move;
	int m_nCounter;												// �J�E���^�[

	static bool m_bdemasita;
};

#endif