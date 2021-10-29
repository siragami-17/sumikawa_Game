//--------------------------------------------------------------------------------
//
//	�e�̏��� [bullt.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

#include "scene2D.h"	// 2D�|���S��
#include "main.h"		// ���C��

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// �e�N���X(2D�|���S���N���X�̔h��)
//-------------------------------------------------------------------------------
class CBullet : public CScene2D
{
public:
	CBullet(PRIORITY nPriority = PRIORITY_BULLET);
	~CBullet();

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale);		// �I�u�W�F�N�g�̐���

	// �e�N�X�`���֌W�̊֐�
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3 m_move;																	// �ړ���
	D3DXVECTOR3 m_scale;																// �傫��
	static LPDIRECT3DTEXTURE9 m_pTexture;												// ���L�e�N�X�`���̃|�C���^																		// ����
};

#endif