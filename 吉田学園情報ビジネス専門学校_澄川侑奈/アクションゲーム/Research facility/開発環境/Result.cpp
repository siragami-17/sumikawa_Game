//--------------------------------------------------------------------------------
//
//	���U���g��ʂ̏��� tResult.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Result.h"
#include "keyboard.h"
#include "fade.h"
#include "sound.h"

//-------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------
#define MAX_RESULT	(2)	//�|���S����

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;				//�N���A���

LPDIRECT3DTEXTURE9 g_pGameOver = NULL;					//�Q�[���I�[�o���

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;

bool g_bClear = false;									//�N���A���Q�[���I�[�o�[��

bool g_bRetry = false;									//���g���C�����ǂ���

//-------------------------------------------------------------------------------
//	���U���g����������
//-------------------------------------------------------------------------------
HRESULT InitResult(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�ϐ��錾
	VERTEX_2D *pVtx;

	//�e�N�X�`���̐ݒ�
	if (g_bClear == true)
	{//�N���A���
		 //BGM�̒ǉ�
		PlaySound(SOUND_LABEL_BGM003);	//�N���ABGM
	}
	else if (g_bClear == false)
	{//�Q�[���I�[�o���
		 //BGM�̒ǉ�
		PlaySound(SOUND_LABEL_BGM004);	//�Q�[���I�[�o�[BGM
	}


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Result.png", &g_pTextureResult);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gameover.png", &g_pGameOver);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4,						//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W(�N���A���)
	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	���U���g�̏I������
//-------------------------------------------------------------------------------
void UninitResult(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	//�e�N�X�`���̊J��(�N���A���)
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//�e�N�X�`���̊J��(�Q�[���I�[�o���)
	if (g_pGameOver != NULL)
	{
		g_pGameOver->Release();
		g_pGameOver = NULL;
	}

	StopSound();//���~�߂�

}

//-------------------------------------------------------------------------------
//	���U���g�̍X�V����
//-------------------------------------------------------------------------------
void UpdateResult(void)
{
	//�t�F�[�h
	int nFade = GetFade();

	if (nFade == FADE_NONE)
	{//�t�F�[�h���͓����Ȃ�
		if (GetkeyboardTrgger(DIK_RETURN) == true)
		{	//ENTER�L�[����������^�C�g����ʂ�
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}
}

//-------------------------------------------------------------------------------
//	���U���g�̕`�揈��
//-------------------------------------------------------------------------------
void DrawResult(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	if (g_bClear == true)
	{//�N���A���
		pDevice->SetTexture(0, g_pTextureResult);
	}
	else if (g_bClear == false)
	{//�Q�[���I�[�o���
		pDevice->SetTexture(0, g_pGameOver);
	}

	//���U���g�̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
		0,							//�`����J�n���钸�_�C���f�b�N�X
		2);							//�`�悷��v���~�e�B�u��
}

//-------------------------------------------------------------------------------
//	���U���g���(�N���A���Q�[���I�[�o��)
//-------------------------------------------------------------------------------
void SetResult(bool bClear)
{
	g_bClear = bClear;	//��ʕύX
}