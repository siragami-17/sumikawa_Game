//--------------------------------------------------------------------------------
//
//	�v���C���[�̏��� [Player.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _PLAYER_H_
#define	_PLAYER_H_

#include "main.h"

//--------------------------------------------------------------------------------
//	�}�N����`
//--------------------------------------------------------------------------------
#define MAX_PLAYER_SIZE_X		(168/4.5)		//�v���C���[�̕�
#define MAX_PLAYER_SIZE_Y		(304/2.5)	//�v���C���[�̍���
#define MAX_PLAYER				(1)			//�v���C���[�̐l��

//--------------------------------------------------------------------------------
//	�v���C���[�̏�ԗ񋓌^
//--------------------------------------------------------------------------------
typedef enum
{
	PLAYERSTATE_NORMA = 0,	//�ʏ���
	PLAYERSTATE_DAMAGE,		//�_���[�W���
	PLAYERSTATE_MAX
}PLAYERSTATE;

//--------------------------------------------------------------------------------
//	�v���C���[�̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̏��(�ʒu)
	D3DXVECTOR3 posOld;		//�Â����(�ʒu)
	D3DXVECTOR3 move;		//�ړ���
	PLAYERSTATE state;		//���
	int nLife;				//������܂ł̒���
	int nCunt;				//�d������
	int nCounterState;		//��ԃJ�E���^
	float fWidth;			//��
	float fHeight;			//����
	float fPlayerU;			//U
	float fPlayerV;			//V
	bool bMove;				//�ړ���
	bool bUse;				//�g�p���Ă��邩�ǂ���
	bool bJump;				//�W�����v�����ǂ���
	bool bGetKey;			//���������Ă��邩
	bool bFall;				//���S�t���O
} PLAYER;

//-------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//-------------------------------------------------------------------------------
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
bool HitPlayer(int nDamage);	//�v���C���[(�_���[�W)
void MovePlayer(void);
PLAYER * GetPlayer(void);

#endif
