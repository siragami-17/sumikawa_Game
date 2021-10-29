//--------------------------------------------------------------------------------
//
//	�^�C�g������ [Title.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"		// ���C��
#include "scene2D.h"	// 2D�|���S��

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// �^�C�g���N���X(�V�[���N���X�̔h��)
//-------------------------------------------------------------------------------
class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();

	static CTitle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);		// �I�u�W�F�N�g�̐���

	// �e�N�X�`���֌W�̊֐�
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// �^�C�g���̔w�i�e�N�X�`��
	typedef enum
	{
		TITLE_BG,			// �w�i
		TITLE_PLAYER,		// �v���C���[
		TITLE_ENTER,		// �G���^�[
		TITLE_MAX
	}TITLE;

	void SetTex(void);
	void Blinking(void);
	void Animation(void);

	static LPDIRECT3DTEXTURE9 m_apTexture[TITLE_MAX];				// ���L�e�N�X�`���̃|�C���^
	CScene2D *m_apScene2D[TITLE_MAX];								// �V�[��2D�|�C���^

	// �_�Ŋ֌W
	D3DXCOLOR m_Enter;												// �J���[�̕ύX
	float m_fAdd;													// �v�Z�p
	bool m_bPressEnter;												// �G���^�[�L�[�������ꂽ��

	TITLE m_Texture;												// �^�C�g����ʃe�N�X�`���̎��

	// �A�j���[�V�����֌W
	int m_nCounterAnim;												// �J�E���^�[
	int m_nPatternAnim;												// �p�^�[��No
};

#endif