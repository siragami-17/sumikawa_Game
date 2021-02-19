//--------------------------------------------------------------------------------
//
//	�J�����̏��� [camera.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "camera.h"				// �J����
#include "keyboard.h"			// �L�[�{�[�h
#include "player.h"				// �v���C���[
#include "Xcontroller.h"		// Xinput

//--------------------------------------------------------------------------------
//	�}�N����`
//--------------------------------------------------------------------------------
#define NEAR_CAMERA_Z	(10.0f)			// Z���̎�O
#define BACK_CAMERA_Z	(1000.0f)		// Z���̉�

#define MAX_V			(3)				// �J����(���_)����
#define MAX_LONG		(-200)			// ���_���璍���_�̒���

//--------------------------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------------------------
Camera g_camera;		//�J�����̏��

//--------------------------------------------------------------------------------
// ����������
//--------------------------------------------------------------------------------
void InitCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// �J�����̏�񏉊���
	g_camera.posV = D3DXVECTOR3(0.0f, 250.0f, -400.0f);
	//g_camera.posV = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �r���[�|�[�g
	// g_camera.viewport.X = 0;			// �`�悷���ʂ̍���X���W
	// g_camera.viewport.Y = 100;			// Y
	// g_camera.viewport.Width = 500;		// ��
	// g_camera.viewport.Height = 250;		// ����
	// g_camera.viewport.MinZ = 0.0f;
	// g_camera.viewport.MinZ = 1.0f;
}

//--------------------------------------------------------------------------------
// �I������
//--------------------------------------------------------------------------------
void UninitCamera(void)
{

}

//--------------------------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------------------------
void UpdateCamera(void)
{
	// �v���C���[���
	Player *pPlayer = GetPlayer();

	if (GetkeyboardPress(DIK_X) == true)
	{
		// �����_
		g_camera.posR.x = pPlayer->pos.x;
		g_camera.posR.z = pPlayer->pos.z;
		g_camera.posR.y = pPlayer->pos.y;

		// ���_
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * 100.0f;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * 200.0f;
		g_camera.posV.y = g_camera.posR.y + 100.0f;
	}





	


	// �J�����̈ړ�����(P���_)
	// W�L�[��������
	if (GetkeyboardPress(DIK_UP) == true)
	{// ��
		g_camera.posV.x += sinf(g_camera.rot.y) * MAX_V;
		g_camera.posR.x += sinf(g_camera.rot.y) * MAX_V;
		g_camera.posR.z += cosf(g_camera.rot.y) * MAX_V;
		g_camera.posV.z += cosf(g_camera.rot.y) * MAX_V;
	}

	// S�L�[��������
	if (GetkeyboardPress(DIK_DOWN) == true)
	{// ��
		g_camera.posV.x -= sinf(g_camera.rot.y) * MAX_V;
		g_camera.posR.x -= sinf(g_camera.rot.y) * MAX_V;
		g_camera.posR.z -= cosf(g_camera.rot.y) * MAX_V;
		g_camera.posV.z -= cosf(g_camera.rot.y) * MAX_V;
	}

	// A�L�[��������
	if (GetkeyboardPress(DIK_LEFT) == true)
	{// ��
		g_camera.posV.x -= cosf(g_camera.rot.y) * MAX_V;
		g_camera.posR.x -= cosf(g_camera.rot.y) * MAX_V;
		g_camera.posR.z += sinf(g_camera.rot.y) * MAX_V;
		g_camera.posV.z += sinf(g_camera.rot.y) * MAX_V;
	}

	// D�L�[��������
	if (GetkeyboardPress(DIK_RIGHT) == true)
	{// �E
		g_camera.posV.x += cosf(g_camera.rot.y) * MAX_V;
		g_camera.posR.x += cosf(g_camera.rot.y) * MAX_V;
		g_camera.posR.z -= sinf(g_camera.rot.y) * MAX_V;
		g_camera.posV.z -= sinf(g_camera.rot.y) * MAX_V;
	}

	// �J����(���_)�̈ړ�����
	// Y�L�[��������
	if (GetkeyboardPress(DIK_Y) == true)
	{// ��
		g_camera.posV.y += MAX_V;
	}

	// N�L�[��������
	if (GetkeyboardPress(DIK_N) == true)
	{// ��
		g_camera.posV.y -= MAX_V;
	}

	// Z�L�[��������
	if (GetkeyboardPress(DIK_Z) == true)
	{// ��
		g_camera.rot.y += 0.05f;		// �p�x

		// �J�����̌����̏���
		if (g_camera.rot.y < -D3DX_PI)
		{	// -3.14
			g_camera.rot.y += D3DX_PI * 2.0f;
		}
	}

	// C�L�[��������
	if (GetkeyboardPress(DIK_C) == true)
	{// �E
		g_camera.rot.y -= 0.05f;		// �p�x

		// �J�����̌����̏���
		if (g_camera.rot.y > D3DX_PI)
		{	// +3.14
			g_camera.rot.y -= D3DX_PI * 2.0f;

		}
	}

	// �J����(�����_)�̈ړ�����

	// T�L�[��������
	if (GetkeyboardPress(DIK_T) == true)
	{// ��
		g_camera.posR.y += MAX_V;
	}

	// B�L�[��������
	if (GetkeyboardPress(DIK_B) == true)
	{// ��
		g_camera.posR.y -= MAX_V;
	}

	// Q�L�[��������
//	if (GetkeyboardPress(DIK_Q) == true) 
//	{// ��
//		g_camera.rot.y -= 0.05f;		// �p�x
//		g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y) * MAX_LONG;
//		g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y) * MAX_LONG;
//
//		// �J�����̌����̏���
//		if (g_camera.rot.y < -D3DX_PI)
//		{	// -3.14
//			g_camera.rot.y += D3DX_PI * 2.0f;
//
//		}
//	}
//
//	// E�L�[��������
//	if (GetkeyboardPress(DIK_E) == true)
//	{// �E
//		g_camera.rot.y += 0.05f;		// �p�x
//		g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y) * MAX_LONG;
//		g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y) * MAX_LONG;
//
//		// �J�����̌����̏���
//		if (g_camera.rot.y > D3DX_PI)
//		{	// +3.14
//			g_camera.rot.y -= D3DX_PI * 2.0f;
//
//		}
//	}

	//�J�����̈ʒu���Z�b�g
	// �X�y�[�X�L�[��������
	if (GetkeyboardPress(DIK_M) == true)
	{
		g_camera.posV = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//--------------------------------------------------------------------------------
// �J�����̐ݒ�
//--------------------------------------------------------------------------------
void SetCamera(int nldx)
{
	// �f�o�C�X�̎擾a
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// �r���[�|�[�g�̐ݒ�
//	pDevice->SetViewport(&g_camera.viewport);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),								// ��p(�����ς���Ɖ�ʂ��M�������ĂȂ�(�}���J�̃_�b�V���݂����Ȃ��))
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			// ��ʔ䗦(�t���[�g�ɂ��Ă��邩�珬���_���o�Ă��������ɂȂ�)
	//	(float)500 / (float)250,			// ��ʔ䗦(�r���[�|�[�g)
		NEAR_CAMERA_Z,										// Z���̎�O
		BACK_CAMERA_Z);										// Z���̉�

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//--------------------------------------------------------------------------------
//	�J�����̎擾
//--------------------------------------------------------------------------------
Camera * GetCamera(void)
{
	return &g_camera;		// �J�����̏��̐擪�A�h���X��Ԃ�
}