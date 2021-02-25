//--------------------------------------------------------------------------------
//
//	�v���C���[�̏��� [player.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _PLAYER_H_
#define	_PLAYER_H_

#include "main.h"

//--------------------------------------------------------------------------------
// �\����
//--------------------------------------------------------------------------------
#define MOTION_MAX	(20)		//	�ő吔

//--------------------------------------------------------------------------------
// ���[�V�����^�C�v�̗񋓌^
//--------------------------------------------------------------------------------
typedef enum
{
	MOTION_NONE = 0,
	MOTION_WORK,			// ����
	MOTION_ATTACK,			// �A�N�V����
	MOTION_JUMP,			// �W�����v
}MOTION_STATE;

//--------------------------------------------------------------------------------
// �L�[�̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	float fPosKeyX;		// �L�[�Őݒ肷��ʒu���
	float fPosKeyY;		// �L�[�Őݒ肷��ʒu���
	float fPosKeyZ;		// �L�[�Őݒ肷��ʒu���
	float fRotKeyX;		// �L�[�Őݒ肷��ʒu���
	float fRotKeyY;		// �L�[�Őݒ肷��ʒu���
	float fRotKeyZ;		// �L�[�Őݒ肷��ʒu���

}Key;

//--------------------------------------------------------------------------------
// �L�[���̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	int nFrame;							// �Đ��t���[��
	Key aKey[MOTION_MAX];				// �e���f���L�[�v�f
}Key_Info;

//--------------------------------------------------------------------------------
// ���[�V�����̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	int nLoop;							// ���[�v���邩
	int nMaxKey;						// �L�[�̑���
	Key_Info  aKeyInfo[MOTION_MAX];		// �L�[���

}Motion_Info;

//--------------------------------------------------------------------------------
// ���f���̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	LPD3DXMESH pMesh;				// ���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;			// �}�e���A���ւ̃|�C���^
	DWORD nNumMat;					// �}�e���A���̐�
	D3DXVECTOR3 pos;				// �ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 rot;				// ����
	D3DXVECTOR3 g_VtxMinModel;		// ���f���̍ŏ��l
	D3DXVECTOR3	g_VtxMaxModel;		// ���f���̍ő�l
	D3DXMATRIX mtxWorld;			// ���[���h�}�g���b�N�X
	int nIdModelParent;				// �e�̃��f���̃C���f�b�N�X
	int nIdxModelNum;				// ���f���̃C���f�b�N�X

	char sModelFailName[256];		// ���f���t�@�C���̖��O

	int nNumVtx;					// ���_��
	DWORD sizeFVF;					// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATERIAL *pMat;				// �}�e���A���f�[�^�̃|�C���^
	D3DXVECTOR3 vtx;				// �o�[�e�b�N�X
	D3DXVECTOR3 vtxMax, vtxMin;		// �v���C���[�̑傫���ő吔,�ŏ���

}Model;

//--------------------------------------------------------------------------------
// �v���C���[�̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;							// ���̈ʒu
	D3DXVECTOR3 posOld;							// �̂̈ʒu
	D3DXVECTOR3 rot;							// ����
	D3DXVECTOR3 size;							// �T�C�Y
	D3DXVECTOR3 rotDest;						// �ړI�̌���
	D3DXVECTOR3 move;							// �ړ���
	D3DXMATRIX mtxWorld;						// ���[���h�}�g���b�N�X

	Model aModel[14];							// ���f��(�p�[�c)
	int nNumModel;								// ���f��(�p�[�c)��

	MOTION_STATE motionType;					// ���[�V�����^�C�v
	MOTION_STATE oldmotionType;					// �O��̃��[�V�����^�C�v

	Motion_Info aMotionInfo[MOTION_MAX];		// ���[�V�������
	int nNumMotion;								// ���[�V�����J�E���^�[

	int nNumKey;								// ���݂̃L�[��

	bool bJump;									// �W�����v�����ǂ���
	bool bGetKey;								// ���������Ă��邩

	int nIdx;									// �e

}Player;

//--------------------------------------------------------------------------------
// �v���g�^�C�v�錾
//--------------------------------------------------------------------------------
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

Player *GetPlayer(void);

void MotionPlayer(MOTION_STATE motionType);		// ���[�V����

void Setcollision(void);						// ���Ƃ̓����蔻��

#endif