//--------------------------------------------------------------------------------
//
//	�eUI���� [Bullet_UI.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _BULLET_UI_
#define _BULLET_UI_

#include "main.h"			// ���C��
#include "scene2D.h"
#include "Polygon.h"		// �|���S��

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define START_UI			(2)										// �����̃��C�t
#define MAX_BULLET_UI		(5)										// �ő包��

#define BULLET_UI_HALF		(MAX_BULLET_UI/2)						// �ő吔�����̌�
#define SCORE_MATH			((nScore % nMath / (nMath / 10)))		// �X�R�A�̌v�Z

//-------------------------------------------------------------------------------
// ���C�t�N���X(�V�[���̔h���N���X)
//-------------------------------------------------------------------------------
class CBullet_UI :public CScene
{
public:
	CBullet_UI(PRIORITY nPriority = PRIORITY_BULLET_UI);
	~CBullet_UI();

	// �e�N�X�`���֌W�̊֐�
	static HRESULT Load(void);
	static void Unload(void);

	// �I�u�W�F�N�g�̐���
	static CBullet_UI *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBullet(int nBullet);
	void AddBullet(int nValue);
	void SubtractBullet(int nValue);
	int GetBullet(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���̃|�C���^
	CPolygon *m_apPolygon[MAX_BULLET_UI];		// UI��
	int m_nBullet_UI;							// UI
	D3DXVECTOR3 m_pos;							// �ʒu
};

#endif