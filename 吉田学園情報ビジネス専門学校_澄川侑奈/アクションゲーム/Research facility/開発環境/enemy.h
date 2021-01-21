//--------------------------------------------------------------------------------
//
//	�G�̏��� [enemy.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _ENEMY_H_
#define	_ENEMY_H_

#include "main.h"

//--------------------------------------------------------------------------------
//	�}�N����`
//--------------------------------------------------------------------------------
#define MAX_ENEMY			(256)			//�G�̍ő吔
#define MAX_ENEMY_SIZE_X	(152/4)			//�G�̕�
#define MAX_ENEMY_SIZE_Y	(284/2.5f)		//�G�̍���
#define ENEMMY_QUANTITY		(10)			//�G�̌�
#define ENEMY_X				(120)			//�G��X
#define ENEMY_Y				(280)			//�G��Y
#define DAMAGE_PAPER		(1)				//�G���^����_���[�W��

//--------------------------------------------------------------------------------
//	�G�̗񋓌^
//--------------------------------------------------------------------------------
typedef enum
{
	ENEMYTYPE_000 = 0, 		//�G
	ENEMYTYPE_MAX,			//�ő吔
} ENEMYTYPE;

//--------------------------------------------------------------------------------
//	�G�̏�ԗ񋓌^
//--------------------------------------------------------------------------------
typedef enum
{
	ENEMYSTATE_NORMA = 0,	//�ʏ���
	ENEMYSTATE_DAMAGE,		//�_���[�W���
	ENEMYSTATE_MAX
}ENEMYSTATE;
//--------------------------------------------------------------------------------
//	�G�̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̏��(�ʒu)
	D3DXVECTOR3 posOld;		//�Â����(�ʒu)
	D3DXVECTOR3 move;		//�ړ���
	ENEMYTYPE type;			//���
	int nLife;				//������܂ł̒���
	int nCunt;				//�d������
	float fWidth;			//��
	float fHeight;			//����
	float fEnemyU;			//U
	float fEnemyV;			//V
	bool bMove;				//�ړ���
	bool bJump;				//�W�����v�����ǂ���
	bool bUse;				//�g�p���Ă��邩�ǂ���
} ENEMY;

//-------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//-------------------------------------------------------------------------------
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMYTYPE type, int nLife);
ENEMY * GetEnemy(void);
void SetVertexEnemy(int nCntEnemy);
bool HitEnemy(int nIdx, int nDamage);
#endif