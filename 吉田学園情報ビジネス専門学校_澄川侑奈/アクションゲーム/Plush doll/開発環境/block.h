//--------------------------------------------------------------------------------
//
//	�u���b�N�̏��� [block.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"						// ���C��
#include "scene2D.h"					// 2D�|���S��

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define MAX_BLOCK		(256)			// �u���b�N�̍ő吔
#define MAX_BLOCKTEYP	(2)				// �u���b�N�̎��
#define BLOCK_X			(40.0f)			// �u���b�N�̕�
#define BLOCK_Y			(40.0f)			// �u���b�N�̍���

#define BLOCK_SIZE		(D3DXVECTOR3(40.0f, 40.0f, 0.0f))								// �傫��

//-------------------------------------------------------------------------------
// �G�̃N���X(�h���N���X)
//-------------------------------------------------------------------------------
class  CBlock : public CScene2D
{
public:

	CBlock(PRIORITY nPriority = PRIORITY_BLOCK);
	~CBlock();

	// �e�N�X�`���֌W�̊֐�
	static HRESULT Load(void);
	static void Unload(void);

	// ����
	static CBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	bool Collision(void);		// �u���b�N�ƃI�u�W�F�N�g�̓����蔻��

	// �u���b�N�����������
	int GetBlock(void) { return m_nBlock; }
	void SetBlock(int block) { m_nBlock = block; }

private:
	

	static LPDIRECT3DTEXTURE9 m_apTexture;								// �e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_pos;													// �ʒu
	D3DXVECTOR3 m_size;													// �傫��
	D3DXVECTOR3 m_move;													// �ړ���
	int m_nCounter;														// �J�E���^�[

	static int m_nBlock;		// �u���b�N�̌�
	bool m_bCollision;		// �I�u�W�F�N�g�Ɠ����������ǂ���

};

#endif