//--------------------------------------------------------------------------------
//
//	�`���[�g���A������ [Tutorial.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"		// ���C��
#include "scene2D.h"	// 2D�|���S��

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// �`���[�g���A���N���X(�V�[���N���X�̔h��)
//-------------------------------------------------------------------------------
class CTutorial : public CScene
{
public:
	CTutorial();
	~CTutorial();

	static CTutorial *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);		// �I�u�W�F�N�g�̐���

	// �e�N�X�`���֌W�̊֐�
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;							// ���L�e�N�X�`���̃|�C���^
	CScene2D *m_pScene2D;											// �V�[��2D�|�C���^
};

#endif