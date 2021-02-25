//--------------------------------------------------------------------------------
//
//	�J�����̏��� [camera.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _CAMERA_H_
#define	_CAMERA_H_

#include "main.h"

//--------------------------------------------------------------------------------
// �J�����̍\����
//--------------------------------------------------------------------------------
typedef struct 
{					
	D3DVIEWPORT9 viewport;			// �r���[�|�[�g
	D3DXVECTOR3 posV;				// ���݂̎��_(���Ă���ʒu)
	D3DXVECTOR3 posVDest;			// �ړI�̎��_
	D3DXVECTOR3 posR;				// ���݂̒����_(���S�Ƃ��Ă݂Ă���)
	D3DXVECTOR3 posRDest;			// �ړI�̒����_
	D3DXVECTOR3 vecU;				// ������x�N�g��
	D3DXVECTOR3 rot;				// �J�����̌���
	D3DXMATRIX mtxProjection;		// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;				// �r���[�}�g���b�N�X
}Camera;									

//--------------------------------------------------------------------------------
// �v���g�^�C�v�錾
//--------------------------------------------------------------------------------
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int nldx);
Camera * GetCamera(void);

#endif