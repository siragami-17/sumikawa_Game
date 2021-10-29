//--------------------------------------------------------------------------------
//
//	���U���g���� [result.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"		// ���C��
#include "scene2D.h"	// 2D�|���S��

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// ���U���g�N���X(�V�[���N���X�̔h��)
//-------------------------------------------------------------------------------
class CResult : public CScene
{
public:
	//�e�N�X�`���̎��
	typedef enum
	{
		TEXTURETYPE_GAMECLEAR = 0,		// �Q�[���N���A
		TEXTURETYPE_GAMEOVER,			// �Q�[���I�[�o�[
		TEXTURETYPE_MAX,
	}TEXTURETYPE;

	CResult();
	~CResult();

	static CResult *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);		// �I�u�W�F�N�g�̐���

	// �e�N�X�`���֌W�̊֐�
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEXTURETYPE_MAX];			// �e�N�X�`���̃|�C���^
	CScene2D *m_pScene2D;											// �V�[��2D�̃|�C���^
};

#endif