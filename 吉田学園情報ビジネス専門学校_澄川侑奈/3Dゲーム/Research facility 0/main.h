//--------------------------------------------------------------------------------
//
//	�E�C���h�E�̏��� [main.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_

// �C���N���[�h�t�@�C��	
#include <windows.h>
#include <XInput.h>		// Xinput�ɕK�v
#include "d3dx9.h"
#include "xaudio2.h"	// �T�E���h�Đ��ɕK�v5

// �L�[�{�[�h���͏���
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"

// ���C�u�����t�@�C��
#pragma	comment(lib,"dinput8.lib")
#pragma comment(lib,"winmm.lib")

// ���C�u�����̃����N
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "xinput.lib")

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define SCREEN_WIDTH (1280)														// �Q�[����ʂ̕�
#define SCREEN_HEIGHT (720)														// �Q�[����ʂ̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)				// �e�N�X�`���̍��W(2D)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)		// �e�N�X�`���̍��W(3D)
#define NUM_VERTEX (4)															// ���_��
#define NUM_POLYGON (2)															// �|���S����(�v���~�e�B�u)

//-------------------------------------------------------------------------------
// ���_�t�H�[�}�b�g�ɍ��킹���\����(2D)
//-------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// 1.0�ŌŒ�
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_2D;

//-------------------------------------------------------------------------------
// ���_�t�H�[�}�b�g�ɍ��킹���\����(3D)
//-------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_3D;

//-------------------------------------------------------------------------------
// ���[�h�̎��
//-------------------------------------------------------------------------------
typedef enum
{
	MODE_TITLE = 0,					// �^�C�g�����
	MODE_TUTORIAL,					// �`���[�g���A�����
	MODE_BEGINNING,					// ���߂̉��
	MODE_GAME,						// �Q�[��
	MODE_RESULT,					// ���U���g���
	MODE_RANKING,					// �����L���O���
	MODE_MAX
}MODE;

//-------------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE * GetMode(void);

#endif 