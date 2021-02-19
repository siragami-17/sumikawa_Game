//--------------------------------------------------------------------------------
//
//	���̏��� [billboard.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Key.h"
#include "player.h"

//--------------------------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------------------------
#define MAX_KEY			(1)		// �e�N�X�`���̍ő吔
#define MAX_KEY_COUNTER	(10)		//���̃X�s�[�h
#define MAX_KEY_PATTERN	(5)			//���̌�
#define MAX_KEY_X		(50)		//��X
#define MAX_KEY_Y		(60)		//��Y

//--------------------------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------------------------
KEY g_Key;											// ���̏��

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffKey = NULL;		// �r���{�[�h�̒��_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureKey = NULL;			// �e�N�X�`���̃|�C���^


D3DXMATRIX g_mtxWorldKey;							// ���[���h�}�g���b�N�X

int g_nCountersAnimationKey;						//���̃R�}���؂�ւ�
int g_nCountersAnimationCnt;						//���̃J�E���^�X�V

//--------------------------------------------------------------------------------
// ����������
//--------------------------------------------------------------------------------
HRESULT InitKey(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// �ϐ��錾
	VERTEX_3D *pVtx;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Key.png", &g_pTextureKey);

	// �\���̂̏�����
	 g_Key.pos= D3DXVECTOR3(50.0f, 0.0f, 0.0f);		// �ʒu
	 g_Key.fWidth = 0.0f;								//��
	 g_Key.fHeight = 0.0f;								//����
	 g_Key.bUse = true;									//�g�p���Ă��邩�ǂ���

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * 4,								// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,									// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffKey,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffKey->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W(X.Y.Z)
	pVtx[0].pos = D3DXVECTOR3(g_Key.pos.x - 25.0f, g_Key.pos.y + 50.0f,g_Key.pos.z + 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Key.pos.x + 25.0f, g_Key.pos.y + 50.0f,g_Key.pos.z + 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Key.pos.x - 25.0f, g_Key.pos.y - 0.0f, g_Key.pos.z + 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Key.pos.x + 25.0f, g_Key.pos.y - 0.0f, g_Key.pos.z + 0.0f);

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// ���_�J���[�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// ���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.2f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.2f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffKey->Unlock();

	return S_OK;
}

//--------------------------------------------------------------------------------
// �I������
//--------------------------------------------------------------------------------
void UninitKey(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffKey != NULL)
	{
		g_pVtxBuffKey->Release();
		g_pVtxBuffKey = NULL;
	}

	// �e�N�X�`���̊J��(�r���{�[�h)
	if (g_pTextureKey != NULL)
	{
		g_pTextureKey->Release();
		g_pTextureKey = NULL;
	}
}

//--------------------------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------------------------
void UpdateKey(void)
{
	VERTEX_2D *pVtx;

	// �v���C���[�̏��
	Player * pPlayer;
	pPlayer = GetPlayer();

	//���ƃv���C���[�̓����蔻��
	if (g_Key.bUse == true)
	{	//�g�p���Ă��邩�ǂ���
		if (pPlayer->pos.x - (150 / 2) < g_Key.pos.x + (MAX_KEY_X / 2) &&		//��
			pPlayer->pos.x + (150 / 2) > g_Key.pos.x - (MAX_KEY_X / 2) &&		//�E
			pPlayer->pos.y - 150 < g_Key.pos.y + (MAX_KEY_Y / 2) &&			//��
			pPlayer->pos.y > g_Key.pos.y - (MAX_KEY_Y / 2))									//��
		{



											//���������Ȃ�����
			g_Key.bUse = false;

		}
	}


	g_nCountersAnimationCnt++;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffKey->Lock(0, 0, (void**)&pVtx, 0);

	//�A�j���[�V������
	if ((g_nCountersAnimationCnt %MAX_KEY_COUNTER) == 0)	//�A�j���[�V�����̃J�E���g
	{
		g_nCountersAnimationKey = (g_nCountersAnimationKey + 1) % MAX_KEY_PATTERN;	//�A�j���[�V�����̃R�}��

		//�A�j���[�V�����̒��_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_Key.pos.x + 0.2f + g_nCountersAnimationKey * 0.2f, g_Key.pos.y + 1.0f);
		pVtx[1].tex = D3DXVECTOR2(g_Key.pos.x - 0.0f + g_nCountersAnimationKey * 0.2f, g_Key.pos.y + 1.0f);
		pVtx[2].tex = D3DXVECTOR2(g_Key.pos.x + 0.2f + g_nCountersAnimationKey * 0.2f, g_Key.pos.y - 0.0f);
		pVtx[3].tex = D3DXVECTOR2(g_Key.pos.x - 0.0f + g_nCountersAnimationKey * 0.2f, g_Key.pos.y - 0.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffKey->Unlock();
}

//--------------------------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------------------------
void DrawKey(void)
{
	LPDIRECT3DDEVICE9 pDevice;			// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxView;					// �r���[�}�g���b�N�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;		// �v�Z�p�̃}�g���b�N�X

										// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldKey);

	// �r���[�}�g���b�N�X�̎擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&g_mtxWorldKey, NULL, &mtxView);		// �t�s������߂�
	g_mtxWorldKey._41 = 0.0f;
	g_mtxWorldKey._42 = 0.0f;
	g_mtxWorldKey._43 = 0.0f;

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Key.pos.x, g_Key.pos.y, g_Key.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldKey, &g_mtxWorldKey, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldKey);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffKey, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �r���{�[�h�̃e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureKey);

	// �r���{�[�h�̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,						// �`����J�n���钸�_�C���f�b�N�X
		2);						// �`�悷��v���~�e�B�u��

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}