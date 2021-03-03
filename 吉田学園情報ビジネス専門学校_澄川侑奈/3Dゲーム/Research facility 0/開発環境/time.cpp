//--------------------------------------------------------------------------------
//
//	�^�C���̏��� [time.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "time.h"
#include "fade.h"
#include "result.h"

//--------------------------------------------------------------------------------
//	�}�N����`
//--------------------------------------------------------------------------------
#define MAX_TIME			(3)				//�^�C���̍ő�\����
#define MAX_TIME_SIZE_X		(35.0f)			//�^�C���̕�
#define MAX_TIME_SIZE_Y		(70.0f)			//�^�C���̍���
#define TIME_X				(1000.0f)		//�^�C����U�ʒu
#define TIME_Y				(10.0f)			//�^�C����V�ʒu
#define TIME				(900)			//�\������b��
#define COUNT_TIME			(60)			//�����Ă������o

//--------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//--------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;			//�e�N�X�`�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		//���_�o�b�t�@�̃|�C���^
D3DXVECTOR3 g_aTimepos[MAX_TIME];					//�^�C���̉摜
int g_nTime;										//���݂̃^�C��
int g_nCountTime;									//�J�E���g�^�C��

Time g_time;										// �^�C�}�[�̏��	

//-------------------------------------------------------------------------------
//	�^�C���̏���������
//-------------------------------------------------------------------------------
HRESULT InitTime(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	g_nTime = TIME;					//�^�C��
	g_nCountTime = COUNT_TIME;		//�J�E���g�^�C��

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_pTextureTime);	//�^�C���̃e�N�X�`��

	//���_���̐ݒ�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL)))
	{
		return E_FAIL;
	}

	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//�^�C���̈ʒu
		g_aTimepos[nCntTime] = D3DXVECTOR3(nCntTime *MAX_TIME_SIZE_X + 600, TIME_Y, 0.0f);

		////�^�C���̒��_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aTimepos[nCntTime].x - 0.0f, g_aTimepos[nCntTime].y + MAX_TIME_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTimepos[nCntTime].x - 0.0f, g_aTimepos[nCntTime].y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTimepos[nCntTime].x + MAX_TIME_SIZE_X, g_aTimepos[nCntTime].y + MAX_TIME_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTimepos[nCntTime].x + MAX_TIME_SIZE_X, g_aTimepos[nCntTime].y - 0.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);	//����
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);	//����
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);	//�E��
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);	//�E��

		pVtx += NUM_VERTEX;

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�I������
//-------------------------------------------------------------------------------
void UninitTime(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}

	//�e�N�X�`���̊J��(������)
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}
}

//-------------------------------------------------------------------------------
//	�X�V����
//-------------------------------------------------------------------------------
void UpdateTime(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	int aNumber[8];

	if (g_nTime != 0)
	{//�^�C����0�̎��J�E���g��STOP
		g_nCountTime -= 1;
	}

	if (g_nCountTime == 0)
	{
		g_nTime -= 1;
		g_nCountTime = COUNT_TIME;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//�^�C���̊i�[
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++, pVtx += 4)
	{
		aNumber[nCntTime] = (g_nTime / (int)powf(10.0f, (float)(MAX_TIME - (nCntTime + 1))));	//�^�C����1�����ɕ�����

		//�e�N�X�`�����W�X�V//���_���W
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aNumber[nCntTime] * 0.1f), 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f + (aNumber[nCntTime] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / 10.0f + (aNumber[nCntTime] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f / 10.0f + (aNumber[nCntTime] * 0.1f), 0.0f);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();

	if (g_nTime == 0)
	{//�b����0�ɂȂ����烊�U���g��ʂ�
		SetResult(false);					//�N���A���
		SetFade(FADE_OUT, MODE_RESULT);
	}
}

//-------------------------------------------------------------------------------
//	�^�C���̕`�揈��
//-------------------------------------------------------------------------------
void DrawTime(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTime);

		//�|���S���̕`��
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
			nCntTime * NUM_VERTEX,		//�`����J�n���钸�_�C���f�b�N�X
			NUM_POLYGON);				//�`�悷��v���~�e�B�u��
	}
	//�ϐ��錾
	D3DXVECTOR3*pTime;
	pTime = &g_aTimepos[0];
}


//-------------------------------------------------------------------------------
//	�^�C���e�N�X�`�����W�̍X�V
//-------------------------------------------------------------------------------
void SetVertexTime(int nIdx,int nNumber)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f*nNumber), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (0.1f*nNumber), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f + (0.1f*nNumber), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f*nNumber), 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//--------------------------------------------------------------------------------
//	�^�C�}�[�̎擾
//--------------------------------------------------------------------------------
Time *GetTime(void)
{
	return &g_time;			// �v���C���[�̏��̐擪�A�h���X��Ԃ�
}