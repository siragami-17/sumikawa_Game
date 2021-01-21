//--------------------------------------------------------------------------------
//
//	�t�F�[�h�̏��� tTitle.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "fade.h"

//-------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------
#define SPEEDTIME	(0.05f)		//�t�F�[�h�̃X�s�[�h

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
FADE g_fade;			//�t�F�[�h�̏��
MODE g_modeNext;		//���̃��[�h(���)
D3DXCOLOR g_cdorFade;	//�t�F�[�h�F

LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxFade = NULL;

//-------------------------------------------------------------------------------
//	����������
//-------------------------------------------------------------------------------
HRESULT InitFade(MODE modeNext)
{
	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_cdorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4,		//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxFade,
		NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);				//����
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);							//����
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);	//�E��
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);				//�E��

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�ݒ�
	pVtx[0].col = g_cdorFade;
	pVtx[1].col = g_cdorFade;
	pVtx[2].col = g_cdorFade;
	pVtx[3].col = g_cdorFade;

	//���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);	//����
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);	//����
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);	//�E��
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);	//�E��

	//���_�o�b�t�@���A�����b�N����
	g_pVtxFade->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�I������
//-------------------------------------------------------------------------------
void UninitFade(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxFade != NULL)
	{
		g_pVtxFade->Release();
		g_pVtxFade = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}
}

//-------------------------------------------------------------------------------
//	�X�V����
//-------------------------------------------------------------------------------
void UpdateFade(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�ݒ�
	pVtx[0].col = g_cdorFade;
	pVtx[1].col = g_cdorFade;
	pVtx[2].col = g_cdorFade;
	pVtx[3].col = g_cdorFade;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxFade->Unlock();

	if (g_fade == FADE_IN)
	{//�t�F�[�h�C��
		g_cdorFade.a -= SPEEDTIME;		//�t�F�[�h�X�s�[�h
		
		if (g_cdorFade.a <= 0.0f)
		{
			g_fade = FADE_NONE;
			g_cdorFade.a = 0.0f;
		}
	}
	else if(g_fade == FADE_OUT)
	{//�t�F�[�h�A�E�g
		g_cdorFade.a += SPEEDTIME;		//�t�F�[�h�X�s�[�h

		if (g_cdorFade.a >= 1.0f)
		{
			g_fade = FADE_IN;
			SetMode(g_modeNext);
		}
	}
}

//-------------------------------------------------------------------------------
//	�`�揈��
//-------------------------------------------------------------------------------
void DrawFade(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureFade);

	//�|���S���̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,						//�`����J�n���钸�_�C���f�b�N�X
		2);						//�`�悷��v���~�e�B�u��
}

//-------------------------------------------------------------------------------
//	��ʏ�Ԃ̕ۑ�
//-------------------------------------------------------------------------------
void SetFade(FADE fade, MODE modeNext)
{
	g_fade = fade;
	g_modeNext = modeNext;
}

//-------------------------------------------------------------------------------
//	�t�F�[�h��Ԃ̎擾
//-------------------------------------------------------------------------------
FADE GetFade(void)
{
	return g_fade;
}