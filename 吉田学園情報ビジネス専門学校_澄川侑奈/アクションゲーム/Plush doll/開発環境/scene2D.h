//--------------------------------------------------------------------------------
//
//	2D�|���S������ [scene2D.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "scene.h"		// �|���S��
#include "main.h"		// ���C��

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define SCREEN_CENTER_X	(419.0f)									// ��
#define SCREEN_CENTER_Y	(419.0f)									// ����

//-------------------------------------------------------------------------------
// �\���̒�`
//-------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//1.0�ŌŒ�
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_2D;

//-------------------------------------------------------------------------------
// 2D�|���S���N���X(�h���N���X)
//-------------------------------------------------------------------------------
class CScene2D: public CScene
{
public:
	CScene2D(PRIORITY nPriority = PRIORITY_DEFAULT);
	~CScene2D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				// �I�u�W�F�N�g�̐���
	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void SetTex(int m_nPatternAnim,int PatterMax);								// �e�N�X�`�����W�X�V(�A�j���[�V����)
	void SetTex(float TexU,float TexV);											// �e�N�X�`�����W�X�V(�X�N���[��)
	void SetTex(D3DXVECTOR2 CntPlace,D3DXVECTOR2 Tex);							// �e�N�X�`�����W�X�V(�v���C���[)
	void SetCol(D3DXCOLOR col);													// �J���[�̍X�V
static	bool Collision(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 objectpos, D3DXVECTOR3 objectpossize);

	D3DXVECTOR3 GetPosition(void);												// �v���C���[�̈ʒu���擾
	D3DXVECTOR3 GetSize(void) { return m_scale; };								// �T�C�Y���擾

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);								// �e�N�X�`�����蓖�ď���

private:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;									// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;									// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_posPolygon;										// �|���S���̈ʒu(���S���W)
	D3DXVECTOR3				m_scale;											// �傫��
	int m_nPatternAnim;															// �A�j���[�V�����̃p�^�[��No
};

#endif