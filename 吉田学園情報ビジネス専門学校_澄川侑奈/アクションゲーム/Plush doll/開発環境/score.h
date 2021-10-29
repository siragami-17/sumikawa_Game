//--------------------------------------------------------------------------------
//
//	�X�R�A���� [score.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"			// ���C��
#include "scene.h"			// �|���S��
#include "number.h"			// �i���o�[

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define MAX_NUMBER		(8)										// �ő包��
#define NUMBER_HALF		(MAX_NUMBER/2)							// �ő吔�����̌�
#define SCORE_MATH		((nScore % nMath / (nMath / 10)))		// �X�R�A�̌v�Z

//-------------------------------------------------------------------------------
// �X�R�A�N���X(�|���S���̔h���N���X)
//-------------------------------------------------------------------------------
class CScore:public CScene
{
public:
	CScore(PRIORITY nPriority = PRIORITY_SCORE);
	~CScore();

	// �I�u�W�F�N�g�̐���
	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetScore(int nScore);
	static void AddScore(int nValue);
	int GetScore(void);

private:
	static CNumber *m_apNumber[MAX_NUMBER];		// ����
	static int m_nScore;						// �X�R�A
};

#endif