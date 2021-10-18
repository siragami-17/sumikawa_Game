//--------------------------------------------------------------------------------
//
//	�i���o�[���� [number.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define NUMBER_HEIGHT		(70.0f)		// ����
#define NUMBER_WIDTH		(35.0f)		// ��

//-------------------------------------------------------------------------------
// �i���o�[�N���X
//-------------------------------------------------------------------------------
class CNumber
{
public:
	CNumber();
	~CNumber();

	// �e�N�X�`���֌W�̊֐�
	static HRESULT Load(void);
	static void Unload(void);

	// �I�u�W�F�N�g�̐���
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ݒ�
	void SetNumber(int nNumber);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
};

#endif