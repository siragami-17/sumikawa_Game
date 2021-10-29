//--------------------------------------------------------------------------------
//
//	�|�[�Y�̏��� [effect.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"			// ���C��
#include "scene.h"
#include "scene2D.h"

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
// �|�[�Y�̃N���X(�h���N���X)
//-------------------------------------------------------------------------------
class  CPause : public CScene
{
public:
	// �|�[�Y�̎��
	typedef enum
	{
		PAUSE_MENU_BLACK = 0,		// ������
		PAUSE_MENU_MENUBJ,			// ���j���[�w�i
		PAUSE_MENU_CONTINOE,		// �R���e�B�j���[
		PAUSE_MENU_RETRY,			// ���g���C
		PAUSE_MENU_QUIT,			// �I��
		PAUSE_MENU_MENUYOP,			// ���j���[�w�i(��O)
		PAUSE_MENU_MAX
	}PAUSE_MENU;

	CPause(PRIORITY nPriority = PRIORITY_PAUSE);
	~CPause();

	// �e�N�X�`���֌W�̊֐�
	static HRESULT Load(void);
	static void Unload(void);

	// ����
	static CPause *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[PAUSE_MENU_MAX];		// �e�N�X�`���̃|�C���^
	CScene2D *m_pScene2D[PAUSE_MENU_MAX];						// �V�[��2D�̃|�C���^
	int m_Cursor;												// �J�[�\��

};

#endif