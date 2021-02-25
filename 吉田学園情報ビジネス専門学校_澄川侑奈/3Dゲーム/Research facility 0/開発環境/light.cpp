//--------------------------------------------------------------------------------
//
//	���C�g�̏��� [light.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "light.h"

//--------------------------------------------------------------------------------
//	�}�N����`
//--------------------------------------------------------------------------------
#define MAX_LIGHT	(3)			// ���C�g�̍ő吔
#define LIGHT_X		(0.2f)		// ���C�g�̕���X
#define LIGHT_Y		(-0.8f)		// ���C�g�̕���Y
#define LIGHT_Z		(-0.4f)		// ���C�g�̕���Z

//--------------------------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------------------------
D3DLIGHT9 g_alight[MAX_LIGHT];		// ���C�g�̏��

//--------------------------------------------------------------------------------
// ����������
//--------------------------------------------------------------------------------
HRESULT InitLight(void)
{
	
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�̃|�C���^

	D3DXVECTOR3 vecDir;				// �ݒ�p�����x�N�g��

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���C�g0
	// ���C�g���N���A�ɂ���(���݂���菜��)
	ZeroMemory(&g_alight[0], sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	g_alight[0].Type = D3DLIGHT_DIRECTIONAL;		// �����̃��C�g

	// ���C�g�̊g�U����ݒ�
	g_alight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);

	// ���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(LIGHT_X, LIGHT_Y, LIGHT_Z);
	D3DXVec3Normalize(&vecDir, &vecDir);		// ���K���ɂ���(��������邱�ƂŃ��C�g�����������ɂȂ�)

	g_alight[0].Direction = vecDir;

	// ���C�g��ݒ肷��
	pDevice->SetLight(0, &g_alight[0]);				// �����͉��Ԗڂ̃��C�g���Ƃ����Ӗ�

	// ���C�g��L������(���C�g�̃X�C�b�`ON!)
	pDevice->LightEnable(0, TRUE);


	// ���C�g1
	// ���C�g���N���A�ɂ���(���݂���菜��)
	ZeroMemory(&g_alight[1], sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	g_alight[1].Type = D3DLIGHT_DIRECTIONAL;		// �����̃��C�g

	// ���C�g�̊g�U����ݒ�
	g_alight[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);

	// ���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(-0.1f, 0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// ���K���ɂ���(��������邱�ƂŃ��C�g�����������ɂȂ�)

	g_alight[1].Direction = vecDir;

	// ���C�g��ݒ肷��
	pDevice->SetLight(1, &g_alight[1]);				// �����͉��Ԗڂ̃��C�g���Ƃ����Ӗ�

	// ���C�g��L������(���C�g�̃X�C�b�`ON!)
	pDevice->LightEnable(1, TRUE);


	// ���C�g2
	// ���C�g���N���A�ɂ���(���݂���菜��)
	ZeroMemory(&g_alight[2], sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	g_alight[2].Type = D3DLIGHT_DIRECTIONAL;		// �����̃��C�g

	// ���C�g�̊g�U����ݒ�
	g_alight[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(0.8f, -0.1f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// ���K���ɂ���(��������邱�ƂŃ��C�g�����������ɂȂ�)

	g_alight[2].Direction = vecDir;

	// ���C�g��ݒ肷��
	pDevice->SetLight(2, &g_alight[2]);				// �����͉��Ԗڂ̃��C�g���Ƃ����Ӗ�

	// ���C�g��L������(���C�g�̃X�C�b�`ON!)
	pDevice->LightEnable(2, TRUE);
	// �l��Ԃ�
	return S_OK;							


	//	for (int nLight = 0; nLight < MAX_LIGHT; nLight++)
	//{
	//	// ���C�g���N���A�ɂ���(���݂���菜��)
	//	ZeroMemory(&g_alight[nLight], sizeof(D3DLIGHT9));

	//	// ���C�g�̎�ނ�ݒ�
	//	g_alight[nLight].Type = D3DLIGHT_DIRECTIONAL;		// �����̃��C�g

	//	// ���C�g�̊g�U����ݒ�
	//	g_alight[nLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//	// ���C�g�̕�����ݒ�
	//	vecDir = D3DXVECTOR3(LIGHT_X, LIGHT_Y, LIGHT_Z);
	//	vecDir = D3DXVECTOR3(-0.1f, 0.8f, -0.4f);
	//	vecDir = D3DXVECTOR3(0.8f, -0.1f, 0.4f);
	//	D3DXVec3Normalize(&vecDir, &vecDir);		// ���K���ɂ���(��������邱�ƂŃ��C�g�����������ɂȂ�)

	//	g_alight[nLight].Direction = vecDir;

	//	// ���C�g��ݒ肷��
	//	pDevice->SetLight(nLight, &g_alight[nLight]);				// �����͉��Ԗڂ̃��C�g���Ƃ����Ӗ�

	//													// ���C�g��L������(���C�g�̃X�C�b�`ON!)
	//	pDevice->LightEnable(nLight, TRUE);

	//}
}

//--------------------------------------------------------------------------------
// �I������
//--------------------------------------------------------------------------------
void UninitLight(void)
{

}

//--------------------------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------------------------
void UpdateLight(void)
{

}