//--------------------------------------------------------------------------------
//
//	�^�C�}�[�̏��� [time.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _TIME_H_
#define	_TIME_H_

#include "main.h"


//-------------------------------------------------------------------------------
// �\����
//-------------------------------------------------------------------------------
typedef struct
{
	LPDIRECT3DTEXTURE9 pTextureTime = NULL;				//�e�N�X�`�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffTime = NULL;		//���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3 aTimepos[3];							//�^�C���̉摜

	int nTime;											//���݂̃^�C��
	int nCountTime;										//�J�E���g�^�C��

}Time;

//-------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//-------------------------------------------------------------------------------
HRESULT InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
void SetVertexTime(int nidx, int nNumber);

Time *GetTime(void);

#endif