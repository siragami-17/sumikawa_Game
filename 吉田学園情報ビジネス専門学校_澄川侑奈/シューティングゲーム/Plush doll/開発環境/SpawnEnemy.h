//--------------------------------------------------------------------------------
//
//	�G�̔������� [LoadSpawnEnemyData.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _SPAWNENEMY_H_
#define _SPAWNENEMY_H_

#include "main.h"		// ���C��
#include "enemy.h"

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define MAX_ENEMY		(256)		// �G�̍ő吔

//-------------------------------------------------------------------------------
// �G�̔����N���X
//-------------------------------------------------------------------------------
class  CSpawnEnemy
{
public:

	static bool LoadSpawnEnemyData(void);
	static void SpawnEnemy(void);

private:
	// �G�̏��
	typedef struct
	{
		
		bool bUes;					// �g�p���Ă��邩
		CEnemy::ENEMYTYPE nEnemyType;				// �G�̃^�C�v

		D3DXVECTOR3 PosEnemy;		// �G�̈ʒu
		D3DXVECTOR3 SizeEnemy;		// �G�̈ړ���
		D3DXVECTOR3 MoveEnemy;		// �G�̈ړ���
		int interval;				// �G�̏o��Ԋu
	}ENEMYSTATUS;

	static int m_nCntEnemy;						// ���̖ڂ̓G��

	static ENEMYSTATUS m_EnemyStatus[MAX_ENEMY];


	static int m_nCnt;		// �J�E���g
};

#endif