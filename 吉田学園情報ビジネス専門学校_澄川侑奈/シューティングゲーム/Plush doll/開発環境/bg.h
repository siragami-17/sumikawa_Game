//--------------------------------------------------------------------------------
//
//	�w�i�̏��� [bg.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _BG_H_
#define _BG_H_

#include "scene.h"		// �|���S��
#include "main.h"		// ���C��

//-------------------------------------------------------------------------------
// �O���錾
//-------------------------------------------------------------------------------
class CScene2D;

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define MAX_BG					(3)							// �|���S����

#define GIRL_X					(1280)						// �摜�̕�
#define GIRL_Y					(720)						// �摜�̍���

#define SCROL_SPPED01			(0.001f)					// �X�N���[���̃X�s�[�h1
#define SCROL_SPPED02			(0.005f)					// �X�N���[���̃X�s�[�h2
#define SCROL_SPPED03			(0.010f)					// �X�N���[���̃X�s�[�h3

//-------------------------------------------------------------------------------
// �w�i�N���X(�h���N���X)
//-------------------------------------------------------------------------------
class CBg : public CScene
{
public:
	CBg(PRIORITY nPriority = PRIORITY_BGBEHING);
	~CBg();

	static HRESULT Load(void);
	static void Unload(void);
	static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG];			// �e�N�X�`���̃|�C���^
	CScene2D *m_apScene2D[MAX_BG];							// 2D�|���S���̃|�C���^
	float m_fSpeed[MAX_BG];									// �X�N���[���̃X�s�[�h
	float m_fPosTexU[MAX_BG];								// �e�N�X�`����U���W
	float m_fPosTexV[MAX_BG];								// �e�N�X�`����V���W
};

#endif