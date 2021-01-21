//--------------------------------------------------------------------------------
//
//	���C�t�̏��� [Life.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Life.h"		// ���C�t
#include "Player.h"		// �v���C���[

//-------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------
#define MAX_POLYGON			(3)			// �|���S����
										   
#define MAX_LIFE_X			(55)		// ���C�t�̕�
#define MAX_LIFE_Y			(85)		// ���C�t�̍���
#define MAX_LIFE_COUNTER	(8)			// ���C�t�̃X�s�[�h
#define MAX_LIFE_PATTERN	(5)			// ���C�t�̌�

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;

LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;						// ���C�t�e�N�X�`��

int g_nCountersAnimationLife[MAX_POLYGON];						// ���C�t�̃R�}���؂�ւ�
int g_nCountersAnimationCntLife[MAX_POLYGON];					// ���C�t�̃J�E���^�X�V

//-------------------------------------------------------------------------------
//	���C�t����������
//-------------------------------------------------------------------------------
HRESULT InitLife(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ϐ��錾
	VERTEX_2D *pVtx;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Life.png", &g_pTextureLife);		// ���C�t

	//�z��̏�����
	for (int nCutLife = 0; nCutLife < MAX_POLYGON; nCutLife++)
	{
		g_nCountersAnimationLife[nCutLife] = 0;											// ���C�t�̃R�}���؂�ւ�
		g_nCountersAnimationCntLife[nCutLife] = 0;										// ���C�t�̃J�E���^�X�V
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCutLife = 0; nCutLife < MAX_POLYGON; nCutLife++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3((float)nCutLife * 60, MAX_LIFE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((float)nCutLife * 60, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(MAX_LIFE_X + (float)nCutLife * 60, MAX_LIFE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(MAX_LIFE_X + (float)nCutLife * 60, 0, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// ���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.2f, 1.0);
		pVtx[3].tex = D3DXVECTOR2(0.2f, 0.0);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	���C�t�̏I������
//-------------------------------------------------------------------------------
void UninitLife(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}

	// �e�N�X�`���̊J��
	// ���C�t
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}
}

//-------------------------------------------------------------------------------
//	���C�t�̍X�V����
//-------------------------------------------------------------------------------
void UpdateLife(void)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCutLife = 0; nCutLife < MAX_POLYGON; nCutLife++)
	{
		g_nCountersAnimationCntLife[nCutLife]++;

		// �A�j���[�V����
		if ((g_nCountersAnimationCntLife[nCutLife] %MAX_LIFE_COUNTER) == 0)										// �A�j���[�V�����̃J�E���g
		{
			g_nCountersAnimationLife[nCutLife] = (g_nCountersAnimationLife[nCutLife] + 1) % MAX_LIFE_PATTERN;	// �A�j���[�V�����̃R�}��

			// �A�j���[�V�����̒��_���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + nCutLife * 60 + g_nCountersAnimationLife[nCutLife] * 0.2f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f + nCutLife * 60 + g_nCountersAnimationLife[nCutLife] * 0.2f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.2f + nCutLife * 60 + g_nCountersAnimationLife[nCutLife] * 0.2f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.2f + nCutLife * 60 + g_nCountersAnimationLife[nCutLife] * 0.2f, 0.0f);
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();
}

//-------------------------------------------------------------------------------
//	���C�t�̕`�揈��
//-------------------------------------------------------------------------------
void DrawLife(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v���C���[�̏��
	PLAYER * pPlayer = GetPlayer();

	// ���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCutLife = 0; nCutLife < MAX_POLYGON; nCutLife++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureLife);		// ���C�t

		// ���C�t�̕`��
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,						// �v���~�e�B�u�̎��
			nCutLife * 4,							// �`����J�n���钸�_�C���f�b�N�X
			NUM_POLYGON);							// �`�悷��v���~�e�B�u��
	}
}