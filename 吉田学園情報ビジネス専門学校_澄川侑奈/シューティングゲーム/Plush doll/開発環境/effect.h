//--------------------------------------------------------------------------------
//
//	�G�t�F�N�g�̏��� [effect.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"			// ���C��
#include "scene2D.h"		// 2D�|���S��

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// �G�t�F�N�g�̃N���X(�h���N���X)
//-------------------------------------------------------------------------------
class  CEffect : public CScene2D
{
public:

	CEffect(PRIORITY nPriority = PRIORITY_EFFECT);
	~CEffect();

	// �e�N�X�`���֌W�̊֐�
	static HRESULT Load(void);
	static void Unload(void);

	// ����
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture;								// �e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_scale;												// �T�C�Y
	D3DXVECTOR3 m_move;													// �ړ���
};

#endif