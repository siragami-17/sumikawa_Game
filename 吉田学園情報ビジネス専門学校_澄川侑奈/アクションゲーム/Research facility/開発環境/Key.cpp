//--------------------------------------------------------------------------------
//
//	���̏��� [Key.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Key.h"
#include "Player.h"
#include "sound.h"

//-------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------
#define MAX_POLYGON		(1)			//�|���S����
#define MAX_KEY_X		(50)		//��X
#define MAX_KEY_Y		(60)		//��Y
#define MAX_KEY_COUNTER	(10)		//���̃X�s�[�h
#define MAX_KEY_PATTERN	(5)			//���̌�

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffKey = NULL;

LPDIRECT3DTEXTURE9 g_pTextureKey = NULL;			//��
D3DXVECTOR3 g_posAnimationKey;						//X,Y,Z�����߂�
int g_nCountersAnimationKey;						//���̃R�}���؂�ւ�
int g_nCountersAnimationCnt;						//���̃J�E���^�X�V

KEY g_Key;											//���̏��
//-------------------------------------------------------------------------------
//	������������
//-------------------------------------------------------------------------------
HRESULT InitKey(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	PLAYER *pPlayer;

	//�v���C���[�̏��
	pPlayer = GetPlayer();

	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���̍\���̂̏�����
	g_Key.pos = D3DXVECTOR3(100.0f, 150.0f, 0.0f);		//�ʒu
	g_Key.fWidth = 0.0f;								//��
	g_Key.fHeight = 0.0f;								//����
	g_Key.bUse = true;									//�g�p���Ă��邩�ǂ���

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Key.png", &g_pTextureKey);		//��

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffKey,
		NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffKey->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_Key.pos.x			 , g_Key.pos.y + MAX_KEY_Y , 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Key.pos.x			 , g_Key.pos.y			 , 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Key.pos.x + MAX_KEY_X, g_Key.pos.y + MAX_KEY_Y , 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Key.pos.x + MAX_KEY_X, g_Key.pos.y			 , 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.2f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.2f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffKey->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	���̏I������
//-------------------------------------------------------------------------------
void UninitKey(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffKey != NULL)
	{
		g_pVtxBuffKey->Release();
		g_pVtxBuffKey = NULL;
	}

	//�e�N�X�`���̊J��(�X�R�A�A�^�b�N�������)
	if (g_pTextureKey != NULL)
	{
		g_pTextureKey->Release();
		g_pTextureKey = NULL;
	}
}

//-------------------------------------------------------------------------------
//	���̍X�V����
//-------------------------------------------------------------------------------
void UpdateKey(void)
{
	VERTEX_2D *pVtx;
	PLAYER * pPlayer;

	//�v���C���[�̏��
	pPlayer = GetPlayer();

	g_nCountersAnimationCnt++;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffKey->Lock(0, 0, (void**)&pVtx, 0);


	//���ƃv���C���[�̓����蔻��
	if (g_Key.bUse == true)
	{	//�g�p���Ă��邩�ǂ���
		if (pPlayer->pos.x - (MAX_PLAYER_SIZE_X / 2) < g_Key.pos.x + (MAX_KEY_X / 2) &&		//��
			pPlayer->pos.x + (MAX_PLAYER_SIZE_X / 2) > g_Key.pos.x - (MAX_KEY_X / 2) &&		//�E
			pPlayer->pos.y - MAX_PLAYER_SIZE_Y < g_Key.pos.y + (MAX_KEY_Y / 2) &&			//��
			pPlayer->pos.y > g_Key.pos.y - (MAX_KEY_Y / 2))									//��
		{
			//������ɓ��ꂽ
			pPlayer->bGetKey = true;

			//SE�̒ǉ�
			PlaySound(SOUND_LABEL_SE_GET);	//�Q�b�g

			//���������Ȃ�����
			g_Key.bUse = false;

		}
	}

	//�A�j���[�V������
	if ((g_nCountersAnimationCnt %MAX_KEY_COUNTER) == 0)	//�A�j���[�V�����̃J�E���g
	{
		g_nCountersAnimationKey = (g_nCountersAnimationKey + 1) % MAX_KEY_PATTERN;	//�A�j���[�V�����̃R�}��

																					//�A�j���[�V�����̒��_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_Key.pos.x - 0.0f + g_nCountersAnimationKey * 0.2f, g_Key.pos.y + 1.0f);
		pVtx[1].tex = D3DXVECTOR2(g_Key.pos.x - 0.0f + g_nCountersAnimationKey * 0.2f, g_Key.pos.y - 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_Key.pos.x + 0.2f + g_nCountersAnimationKey * 0.2f, g_Key.pos.y + 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_Key.pos.x + 0.2f + g_nCountersAnimationKey * 0.2f, g_Key.pos.y - 0.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffKey->Unlock();
}

//-------------------------------------------------------------------------------
//	���̕`�揈��
//-------------------------------------------------------------------------------
void DrawKey(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffKey, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_Key.bUse == true)
	{
		//���e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureKey);

		//���̕`��
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
			0,						//�`����J�n���钸�_�C���f�b�N�X
			2);						//�`�悷��v���~�e�B�u��
	}


	
}