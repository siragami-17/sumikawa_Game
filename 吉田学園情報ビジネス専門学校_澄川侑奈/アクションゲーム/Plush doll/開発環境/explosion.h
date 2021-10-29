//--------------------------------------------------------------------------------
//
//	�����̏��� [explosion.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "scene2D.h"	// 2D�|���S��
#include "main.h"		// ���C��

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define MAX_ANIMATION_COUNTER	(3)			// ���j�̃X�s�[�h
#define MAX_ANIMATION_PATTERN	(8)			// �����̃y�[�W��
#define MAX_EXPLOSION_SIZE_X	(100)		// �����̕�
#define MAX_EXPLOSION_SIZE_Y	(100)		// �����̍���

//-------------------------------------------------------------------------------
// �����N���X(2D�|���S���N���X�̔h��)
//-------------------------------------------------------------------------------
class CExplosion : public CScene2D
{
public:
	CExplosion(PRIORITY nPriority = PRIORITY_EXPLOSION);
	~CExplosion();

	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);							// �I�u�W�F�N�g�̐���

	// �e�N�X�`���֌W�̊֐�
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3 m_scale;																	// �傫��
	static LPDIRECT3DTEXTURE9 m_pTexture;													// ���L�e�N�X�`���̃|�C���^

	int m_nCounterAnim;																		// �J�E���^�[
	int m_nPatternAnim;																		// �p�^�[��No
};

#endif