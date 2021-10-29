//--------------------------------------------------------------------------------
//
//	�G�̏��� [enemy.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
// �t�@�C���ǂݍ��݂ɕK�v
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>	

#include "SpawnEnemy.h"
#include "enemy.h"

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------------------------------------------
CSpawnEnemy::ENEMYSTATUS CSpawnEnemy::m_EnemyStatus[MAX_ENEMY] = {};
int CSpawnEnemy::m_nCntEnemy = 0;
int CSpawnEnemy::m_nCnt = 0;

//-------------------------------------------------------------------------------
// �G�̏��̓ǂݍ���
//-------------------------------------------------------------------------------
bool CSpawnEnemy::LoadSpawnEnemyData(void)
{
	// ������
	m_nCntEnemy = 0;
	m_nCnt = 0;

	// txt�t�@�C���̓ǂݍ���
	FILE *pFileEnemy = fopen("data/TEXT/enemy.txt", "r");
	char string[255];

	// �ϐ��錾
	bool bEnemy = false;		// �G�̏��
	int nCntEnemy = 0;

	if (pFileEnemy != NULL)
	{
		// �t�@�C���̓ǂݍ���
		while (fgets(&string[0], 255, pFileEnemy) != NULL)
		{// NULL����Ȃ�������
		 // �t�@�C��1�s���Ƃɕۑ�
			fscanf(pFileEnemy, "%s", &string[0]);

			if (strcmp(&string[0], "ENEMYSET") == 0)
			{//�@strcmp������͈�v������
				bEnemy = true;
			}
			if (bEnemy == true)
			{
				//�@strcmp������͈�v������
				//if (strcmp(&string[0], "TYPE") == 0)
				//{// �^�C�v�̓ǂݍ���

				//	fscanf(pFileEnemy, "%s %d", &string[0], &m_EnemyStatus[nCntEnemy].nEnemyType);
				//}
				if (strcmp(&string[0], "POS") == 0)
				{//�@�ʒu�̓ǂݍ���

					fscanf(pFileEnemy, "%s %f %f %f", &string[0], &m_EnemyStatus[nCntEnemy].PosEnemy.x, &m_EnemyStatus[nCntEnemy].PosEnemy.y, &m_EnemyStatus[nCntEnemy].PosEnemy.z);
				}
				if (strcmp(&string[0], "SIZE") == 0)
				{//�@�ʒu�̓ǂݍ���

					fscanf(pFileEnemy, "%s %f %f %f", &string[0], &m_EnemyStatus[nCntEnemy].SizeEnemy.x, &m_EnemyStatus[nCntEnemy].SizeEnemy.y, &m_EnemyStatus[nCntEnemy].SizeEnemy.z);
				}

				if (strcmp(&string[0], "MOVE") == 0)
				{//�@�ړ��ʂ̓ǂݍ���

					fscanf(pFileEnemy, "%s %f %f %f", &string[0], &m_EnemyStatus[nCntEnemy].MoveEnemy.x, &m_EnemyStatus[nCntEnemy].MoveEnemy.y, &m_EnemyStatus[nCntEnemy].MoveEnemy.z);
				}
				if (strcmp(&string[0], "INTERVAL") == 0)
				{//�@�G�̏o���Ԋu�̓ǂݍ���

					fscanf(pFileEnemy, "%s %d", &string[0], &m_EnemyStatus[nCntEnemy].interval);
				}
				if (strcmp(&string[0], "END_ENEMYSET") == 0)
				{
					m_EnemyStatus[nCntEnemy].bUes = true;

					bEnemy = false;

					nCntEnemy++;
				}
			}
			if (strcmp(&string[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}

	}

	return false;
}
//-------------------------------------------------------------------------------
// �G�̐���
//-------------------------------------------------------------------------------
void CSpawnEnemy::SpawnEnemy(void)
{
	m_nCnt++;
	if (m_EnemyStatus[m_nCntEnemy].bUes != false)
	{
		if (m_nCnt  %m_EnemyStatus[m_nCntEnemy].interval == 0)
		{
			// �G�𐶐�
			CEnemy::Create(m_EnemyStatus[m_nCntEnemy].PosEnemy, m_EnemyStatus[m_nCntEnemy].SizeEnemy, m_EnemyStatus[m_nCntEnemy].MoveEnemy);

			// �G�𐶐�
//			CEnemy::Create(m_EnemyStatus[m_nCntEnemy].PosEnemy, m_EnemyStatus[m_nCntEnemy].SizeEnemy, m_EnemyStatus[m_nCntEnemy].MoveEnemy, m_EnemyStatus[m_nCntEnemy].nEnemyType);

			m_nCntEnemy++;

			// ������
			m_nCnt = 0;
		}
		
	}
}