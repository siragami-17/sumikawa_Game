//--------------------------------------------------------------------------------
//
//	�p�[�e�B�N���̏��� [particl.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _CParticl_H_
#define _CParticl_H_

#include "main.h"					// ���C��
#include "effect.h"					// �G�t�F�N�g

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define MAX_EFFECT		(256)		// �G�t�F�N�g�̍ő吔

//-------------------------------------------------------------------------------
// �p�[�e�B�N���̃N���X
//-------------------------------------------------------------------------------
class  CParticl
{
public:

	CParticl();
	~CParticl();

	// �e�N�X�`���֌W�̊֐�
	static HRESULT Load(void);
	static void Unload(void);

	// ����
	static CParticl *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,int number);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture;		// �e�N�X�`���̃|�C���^
	CEffect *m_pEffect[256];					// �G�t�F�N�g�̃|�C���^
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Size;
	int m_Number;
};

#endif