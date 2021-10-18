//--------------------------------------------------------------------------------
//
//	�|���S���̏��� [polygon.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define LIFE_HEIGHT			(67.0f)			// ����
#define LIFE_WIDTH			(52.0f)			// ��

#define BULLET_UI_HEIGHT	(200.0f)		// �eUI�̍���
#define BULLET_UI_WIDTH		(52.0f)			// �eUI�̕�

//-------------------------------------------------------------------------------
// �|���S���N���X
//-------------------------------------------------------------------------------
class CPolygon
{
public:
	CPolygon();
	~CPolygon();

	// �I�u�W�F�N�g�̐���
	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ݒ�
	void SetPolygon(int nNumber);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;				// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
};

#endif