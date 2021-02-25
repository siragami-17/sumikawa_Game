//--------------------------------------------------------------------------------
//
//	�e�̏��� [bullet.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "keyboard.h"								// �L�[�{�[�h
#include "bullet.h"									// �e
#include "player.h"									// �v���C���[

//--------------------------------------------------------------------------------
//	�}�N����`
//--------------------------------------------------------------------------------
#define MAX_BULLET			(256)					// �e�̍ő吔
#define MAX_BULLET_SIZE_X	(10)					// �e�̕�
#define MAX_BULLET_SIZE_Y	(10)					// �e�̍���
#define MAX_SPEED			(10)					// �e�̑���

//--------------------------------------------------------------------------------
//	�e�̍\����
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXMATRIX mtxWorldBullet;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;								// �ʒu
	D3DXVECTOR3 move;								// �ړ���
	D3DXVECTOR3 rot;								// ����
	int nLife;										// ������܂ł̒���
	bool bUse;										// �g�p���Ă��邩�ǂ���
} BULLET;

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			// �e�̃e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBullet = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;

BULLET g_aBullet[MAX_BULLET];						// �e�̏��	

//-------------------------------------------------------------------------------
//	����������
//-------------------------------------------------------------------------------
HRESULT InitBullet(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// �ϐ��錾
	VERTEX_3D *pVtx;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet000.png", &g_pTextureBullet);

	// �e���̏�����
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * 4 * MAX_BULLET,		// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,							// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// ���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_BULLET_SIZE_X, g_aBullet[nCntBullet].pos.y + MAX_BULLET_SIZE_Y, g_aBullet[nCntBullet].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_BULLET_SIZE_X, g_aBullet[nCntBullet].pos.y + MAX_BULLET_SIZE_Y, g_aBullet[nCntBullet].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_BULLET_SIZE_X, g_aBullet[nCntBullet].pos.y - MAX_BULLET_SIZE_Y, g_aBullet[nCntBullet].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_BULLET_SIZE_X, g_aBullet[nCntBullet].pos.y - MAX_BULLET_SIZE_Y, g_aBullet[nCntBullet].pos.z);

		// �@���x�N�g���̐ݒ�(���Ă������)
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
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�I������
//-------------------------------------------------------------------------------
void UninitBullet(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	// �e�N�X�`���̊J��(�e)
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}

//-------------------------------------------------------------------------------
//	�X�V����
//-------------------------------------------------------------------------------
void UpdateBullet(void)
{
	// �ϐ��錾
	BULLET *pBullet;
	pBullet = &g_aBullet[0];

	// �v���C���[�̏��
	Player * pPlayer;
	pPlayer = GetPlayer();

	// �X�y�[�X�L�[��������
	if (GetkeyboardPress(DIK_SPACE) == true)
	{
		SetBullet(pPlayer->pos, D3DXVECTOR3(sinf(pPlayer->rot.y)*MAX_SPEED, 0.0f, cosf(pPlayer->rot.y)*MAX_SPEED), 100);		// ),100)��100�̓��C�t
	}

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			// �ʒu�̍X�V
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			// �����`�F�b�N�@
			g_aBullet[nCntBullet].nLife--;

			// �e����ʊO�ɍs�������������
			if (SCREEN_HEIGHT > g_aBullet[nCntBullet].pos.z ||
				SCREEN_WIDTH > g_aBullet[nCntBullet].pos.x ||
				g_aBullet[nCntBullet].pos.z < 0 ||
				g_aBullet[nCntBullet].pos.x < 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}

		}
	}
}

//-------------------------------------------------------------------------------
//	�e�̕`�揈��
//-------------------------------------------------------------------------------
void DrawBullet(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxView;												// �r���[�}�g���b�N�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;									// �v�Z�p�̃}�g���b�N�X

	// �A���t�@�e�X�g�̗L��/����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			// �L���ɂ���

	// �A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);		// ���傫��

	// �A���t�@�l�̎Q�ƒl
	pDevice->SetRenderState(D3DRS_ALPHAREF,120);

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorldBullet);

			// �r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_aBullet[nCntBullet].mtxWorldBullet, NULL, &mtxView);		// �t�s������߂�
			g_aBullet[nCntBullet].mtxWorldBullet._41 = 0.0f;
			g_aBullet[nCntBullet].mtxWorldBullet._42 = 0.0f;
			g_aBullet[nCntBullet].mtxWorldBullet._43 = 0.0f;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorldBullet, &g_aBullet[nCntBullet].mtxWorldBullet, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorldBullet);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			// �|���S���̕`��
			pDevice->DrawPrimitive
			(D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
				nCntBullet * NUM_VERTEX,	// �`����J�n���钸�_�C���f�b�N�X
				NUM_POLYGON);				// �`�悷��v���~�e�B�u��
		}
	}
	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// �A���t�@�e�X�g�̗L��/����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// �A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_ALWAYS);

	// �A���t�@�l�̎Q�ƒl
	pDevice->SetRenderState(D3DRS_ALPHAREF,0x00);
}

//-------------------------------------------------------------------------------
//	�e�̐ݒ�
//-------------------------------------------------------------------------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	//�ϐ��錾
	BULLET * pBullet;
	pBullet = &g_aBullet[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{
			//�ʒu
			pBullet->pos = pos;

			//�ړ���
			pBullet->move = move;

			//����
			pBullet->nLife = nLife;

			//�g�p���Ă��邩
			pBullet->bUse = true;

			break;
		}
	}
}