//--------------------------------------------------------------------------------
//
//	�G�t�F�N�g�̏��� [effect.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "effect.h"		// �G�t�F�N�g

//-------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------
#define MAX_EFFECT			(256)						// �G�t�F�N�g�̍ő吔

#define MAX_EFFECT_X		(20.0f)						// X��
#define MAX_EFFECT_Y		(20.0f)						// Y��

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;		// �o�b�t�@�ւ̃|�C���^

LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;				// �e�N�X�`���ւ̃|�C���^

Effect g_aEffect[MAX_EFFECT];							// �G�t�F�N�g���

//-------------------------------------------------------------------------------
//	�G�t�F�N�g�̏���������
//-------------------------------------------------------------------------------
HRESULT InitEffect(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ϐ��錾
	VERTEX_2D *pVtx;

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		// �G�t�F�N�g�̍\���̂̏�����
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �ʒu
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �ړ�
		g_aEffect[nCntEffect].size = D3DXVECTOR3(MAX_EFFECT_X, MAX_EFFECT_Y, 0.0f);		// �T�C�Y
		g_aEffect[nCntEffect].color = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);				// �J���[
		g_aEffect[nCntEffect].bUse = false;												// �g���Ă��邩
	}
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/star.png", &g_pTextureEffect);		// �G�t�F�N�g�摜

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,		// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		// ���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 0, g_aEffect[nCntEffect].pos.y + MAX_EFFECT_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 0, g_aEffect[nCntEffect].pos.y + 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + MAX_EFFECT_X, g_aEffect[nCntEffect].pos.y + MAX_EFFECT_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + MAX_EFFECT_X, g_aEffect[nCntEffect].pos.y + 0, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		// ���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�G�t�F�N�g�̏I������
//-------------------------------------------------------------------------------
void UninitEffect(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
}

//-------------------------------------------------------------------------------
//	�G�t�F�N�g�̍X�V����
//-------------------------------------------------------------------------------
void UpdateEffect(void)
{
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{// �G�t�F�N�g���g��ꂽ��
			g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;	// �X�V����邽�тɓ�����

			g_aEffect[nCntEffect].color.a -= 0.1f;						// �����ɂ���

			SetColor(g_aEffect[nCntEffect].color, nCntEffect);			// ���f

			SetVertexEffect(nCntEffect);

			// �����̏���
			if (g_aEffect[nCntEffect].color.a <= 0.0f)
			{// �J���[�̃A���t�@�l��0.0f�ȉ��ɂȂ�����
				g_aEffect[nCntEffect].bUse = false;						// �G�t�F�N�g�����S�ɏ���
			}
		}
	}
}

//-------------------------------------------------------------------------------
//	�G�t�F�N�g�̕`�揈��
//-------------------------------------------------------------------------------
void DrawEffect(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// ������
		if (g_aEffect[nCntEffect].bUse == true)
		{// bUse��true�̎��`�悷��
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);
			// �G�t�F�N�g�̕`��
			pDevice->DrawPrimitive
			(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
				nCntEffect * 4,			// �`����J�n���钸�_�C���f�b�N�X
				2);						// �`�悷��v���~�e�B�u��
		}
	}
}

//-------------------------------------------------------------------------------
//	�G�t�F�N�g���̎擾
//-------------------------------------------------------------------------------
Effect *GetEffect(void)
{
	return &g_aEffect[0];			// �G�t�F�N�g�̏��̐擪�A�h���X��Ԃ�
}

//-------------------------------------------------------------------------------
//	�G�t�F�N�g�̐ݒ�
//-------------------------------------------------------------------------------
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// ������
		if (g_aEffect[nCntEffect].bUse == false)
		{// �g���Ă��Ȃ���
			g_aEffect[nCntEffect].pos = pos;										// �ʒu

			g_aEffect[nCntEffect].move = move;										// �ړ���

			g_aEffect[nCntEffect].color = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);		// �J���[

			g_aEffect[nCntEffect].bUse = true;										// �g���Ă���

			break;
		}
	}
}

//-------------------------------------------------------------------------------
//	�G�t�F�N�g�̒��_���W
//-------------------------------------------------------------------------------
void SetVertexEffect(int nIdx)
{
	// �ϐ��錾
	float ShaikingMove = 0.0f;

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	// �e�̏������ɂ���
	pVtx += nIdx * 4;

	// ���_���W�̐ݒ�	
	pVtx[0].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x, g_aEffect[nIdx].pos.y + g_aEffect[nIdx].size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x, g_aEffect[nIdx].pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x + g_aEffect[nIdx].size.x, g_aEffect[nIdx].pos.y + g_aEffect[nIdx].size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x + g_aEffect[nIdx].size.x, g_aEffect[nIdx].pos.y, 0.0f);

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//-------------------------------------------------------------------------------
//	�G�t�F�N�g�̃J���[
//-------------------------------------------------------------------------------
void SetColor(D3DXCOLOR color, int nIdx)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_���W�̐ݒ�	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	// �J���[�̏������ɂ���
	pVtx += nIdx * 4;

	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//-------------------------------------------------------------------------------
//	�ԉ΂݂����ȃG�t�F�N�g
//	[����]
//	pos			�ʒu
//	speed		�ړ���
//	nNum		�\����������
//-------------------------------------------------------------------------------
void SetBom(D3DXVECTOR3 pos, float speed, int nNum)
{
	for (int nCntEffect = 0; nCntEffect < nNum; nCntEffect++)
	{// ������
		float fAngle = float(rand() % 314 / 100.0f)  - float(rand() % 314 / 100.0f) ;		// �p�x�������_������

		D3DXVECTOR3 move = D3DXVECTOR3(sinf(fAngle)*speed, cosf(fAngle)*speed, 0.0f);

	//D3DXVECTOR3 move;
	//if (nCntEffect == 0)
	//{
	//	move = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//}
	//else
	//{
	//	move = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	//
	//}
		//g_aEffect[0].move = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		//g_aEffect[1].move = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		//g_aEffect[2].move = D3DXVECTOR3(0.0f, 4.0f, 0.0f);
		//g_aEffect[3].move = D3DXVECTOR3(0.0f, 6.0f, 0.0f);
		//g_aEffect[4].move = D3DXVECTOR3(0.0f, 8.0f, 0.0f);
		//g_aEffect[5].move = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		//g_aEffect[6].move = D3DXVECTOR3(0.0f, 12.0f, 0.0f);
		//g_aEffect[7].move = D3DXVECTOR3(0.0f, -14.0f, 0.0f);

		SetEffect(pos, move);
	}
}