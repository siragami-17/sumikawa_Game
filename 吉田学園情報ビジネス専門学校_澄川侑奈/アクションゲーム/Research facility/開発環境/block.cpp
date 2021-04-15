//--------------------------------------------------------------------------------
//
//	�u���b�N�̏��� [block.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "block.h"
#include "Mark.h"			//�J�[�\��
#include "keyboard.h"		//�L�[�{�[�h
#include "Game_00.h"
#include "sound.h"
#include "Effect.h"		// �G�t�F�N�g

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define MAX_BLOCK		(256)		//�u���b�N�̍ő吔	
#define MAX_BLOCKTYPE		(2)


#define BLOCK_SIZE			(60.0f)		// �u���b�N�̑傫��
#define SMALL_BLOOCK		(2.0f)		//�u���b�N������ł���Ƃ�����������

#define NORMAL_BLOCK		(43.0f)
#define FLOAT_BLOCK			(10.0f)
#define RIFT_BLOCK			(5.0f)

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;			// �u���b�N�̃e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBlock[MAX_BLOCKTYPE] = {};	// �u���b�N�̒��_�o�b�t�@�̃|�C���^
BLOCK g_aBlock[MAX_BLOCK];								// �u���b�N�̏��

//-----------------------------------------------------------------
// �u���b�N�̏���������
//-----------------------------------------------------------------
HRESULT InitBlock(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block000.png", &g_pTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block001.png", &g_pTextureBlock[1]);

	// �e���̏�����
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].posOld = g_aBlock[nCntBlock].pos;
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].nTimer = 0;
		g_aBlock[nCntBlock].fWidth = BLOCK_SIZE;
		g_aBlock[nCntBlock].fHeight = BLOCK_SIZE;
		g_aBlock[nCntBlock].fTexU = 1.0f;
		g_aBlock[nCntBlock].fTexV = 1.0f;
		g_aBlock[nCntBlock].state = BLOCKSTATE_NORMAL;
		g_aBlock[nCntBlock].type = BLOCKTYPE_CATCH;
		g_aBlock[nCntBlock].bChach = false;
		g_aBlock[nCntBlock].bUse = false;
	}

	//���_�o�b�t�@�̐���5
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,		//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	for (int nCntBullet = 0; nCntBullet < MAX_BLOCK; nCntBullet++)
	{
		// ���_���W�̐ݒ�
		SetVertexBlock(nCntBullet);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�̏������ɂ���
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �u���b�N�̏I������
//-----------------------------------------------------------------
void UninitBlock(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntTexture = 0; nCntTexture < MAX_BLOCKTYPE; nCntTexture++)
	{
		if (g_pTextureBlock[nCntTexture] != NULL)
		{
			g_pTextureBlock[nCntTexture]->Release();
			g_pTextureBlock[nCntTexture] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// �u���b�N�̍X�V����
//-----------------------------------------------------------------
void UpdateBlock(void)
{
	// �\���̂̃|�C���^�ϐ�
	BLOCK *pBlock = &g_aBlock[0];
	MARKER *pMarker = GetMarker();

	// �G�t�F�N�g�̏��
	Effect * pEffect = GetEffect();

	// �ϐ��錾
	bool bStop = GetStop();		// �����Ă���ǂ���

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		if (pBlock->bUse == true)

		{// L�L�[�������Ă���Ȃ珈��
			if (bStop == true)
			{
				pMarker->nCntPatternAnim = 0;

				// �u���b�N��͂�ł��邩�͂܂�Ă����Ԃ̂Ƃ�����
				if (pBlock->bChach == true && pMarker->state == MARKERSTATE_CHACHING)
				{
					pMarker->nCntPatternAnim = 2;

					// �u���b�N�̈ʒu���}�[�J�[�̒��S���W�ɕύX
					pBlock->pos.x = pMarker->pos.x - (pBlock->fWidth / 2.0f);
					pBlock->pos.y = pMarker->pos.y - (pBlock->fHeight / 2.0f);

					// �͂�ł���u���b�N�����̃u���b�N�ɓ������Ă��邩
					bool bHit = ColBlock(nCntBlock);

					// �͂�or�����L�[���������Ƃ�
					if (GetkeyboardTrgger(DIK_RETURN) == true)
					{

						if (bHit == false)
						{// �������Ă��Ȃ��Ƃ�
							pBlock->fWidth = BLOCK_SIZE;											// �T�C�Y�����ɖ߂�
							pBlock->fHeight = BLOCK_SIZE;											// �T�C�Y�����ɖ߂�
							pBlock->pos.x = pMarker->pos.x - (pBlock->fWidth / SMALL_BLOOCK);		// ���̈ʒu���班������Ă���̂Œ��S���W�̐ݒ�
							pBlock->pos.y = pMarker->pos.y - (pBlock->fHeight / SMALL_BLOOCK);		// ���̈ʒu���班������Ă���̂Œ��S���W�̐ݒ�
							pMarker->state = MARKERSTATE_NORMAL;									// �}�[�J�[�̏�Ԃ�����ł��Ȃ��Ƃ��ɂ���
							pBlock->bChach = false;													// �͂�ł��Ȃ��Ƃ��ɂ���

							// SE�̒ǉ�
							PlaySound(SOUND_LABEL_SE_SET_1);										// OFF

							// �G�t�F�N�g
							SetBom(pBlock->pos+D3DXVECTOR3(0.f,15.f,0.f), 10.0f, 10);
							
						}
					}
					else if (bHit == true)
					{// �������Ă���Ƃ�
						pMarker->pos = pMarker->posOld;		// �}�[�J�[��O��̈ʒu�ɂ���
					}
				}
				else if (pBlock->bChach == false && pMarker->state == MARKERSTATE_NORMAL)
				{// �u���b�N���͂܂�Ă��Ȃ����}�[�J�[���ʏ�̂Ƃ�
					// �͂�or�����L�[���������Ƃ�
					if (pBlock->pos.x <= pMarker->pos.x &&
						pBlock->pos.x + pBlock->fWidth >= pMarker->pos.x &&
						pBlock->pos.y <= pMarker->pos.y &&
						pBlock->pos.y + pBlock->fHeight >= pMarker->pos.y)
					{// �}�[�J�[�̒��S���W���u���b�N�͈͓̔��ɂ���Ȃ珈��

						pMarker->nCntPatternAnim = 1;
						if (GetkeyboardTrgger(DIK_RETURN) == true)
						{

							if (pBlock->type == BLOCKTYPE_CATCH)
							{
								pBlock->fWidth = BLOCK_SIZE / SMALL_BLOOCK;		// �u���b�N�̃T�C�Y������������
								pBlock->fHeight = BLOCK_SIZE / SMALL_BLOOCK;	// �u���b�N�̃T�C�Y������������
								pMarker->state = MARKERSTATE_CHACHING;			// �}�[�J�[�̏�Ԃ�͂�ł����Ԃɂ���
								pBlock->bChach = true;							// �u���b�N��͂܂��Ă����Ԃɂ���

								PlaySound(SOUND_LABEL_SE_ON);					//SE�̒ǉ�(�I��)

							
							}
						}
					}
				}
				if (bStop == false)
				{
					pBlock->bChach = false;

		
				}
			}

			// ��ʊO�ɏo�Ȃ��悤�ɂ���
			if (pBlock->pos.y  < 0)
			{// ��ԏ�ɓ��B�����Ƃ�����
				pBlock->pos.y = 0;
			}
			if (pBlock->pos.y + pBlock->fHeight > SCREEN_HEIGHT)
			{// ��ԉ��ɓ��B�����Ƃ�����
				pBlock->pos.y = SCREEN_HEIGHT - pBlock->fHeight;
			}
			if (pBlock->pos.x <= 0)
			{// ��ԍ��ɓ��B�����Ƃ�����
				pBlock->pos.x = 0;
			}
			if (pBlock->pos.x + pBlock->fWidth >= SCREEN_WIDTH)
			{// ��ԉE�ɓ��B�����Ƃ�����
				pBlock->pos.x = SCREEN_WIDTH - pBlock->fWidth;
			}

			// ���_���W�̍X�V
			SetVertexBlock(nCntBlock);
		}
	}

}

//-----------------------------------------------------------------
// �u���b�N�̕`�揈��
//-----------------------------------------------------------------
void DrawBlock(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�̕`��
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{// �e���g���Ă���Ƃ�����
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].type]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
		}
	}
}

//-----------------------------------------------------------------
// �u���b�N�̐ݒ�
//-----------------------------------------------------------------
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, float fTexU, float fTexV,BLOCKSTATE state, BLOCKTYPE type)
{
	// �\���̂̃|�C���^�ϐ�
	BLOCK *pBlock;

	// �ϐ��̎󂯓n��
	pBlock = &g_aBlock[0];

	// �e�̐ݒ�
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		if (pBlock->bUse == false)
		{// �ʒu�ݒ�
			pBlock->pos = pos;

			// �ړ��ʂ̐ݒ�
			pBlock->move = move;

			// ���̐ݒ�
			pBlock->fWidth = fWidth;

			// �����̐ݒ�
			pBlock->fHeight = fHeight;

			// �e�N�X�`�����WU�̐ݒ�
			pBlock->fTexU = fTexU;

			// �e�N�X�`�����WV�̐ݒ�
			pBlock->fTexV = fTexV;

			// �u���b�N�̏�Ԃ̐ݒ�
			pBlock->state = state;

			// �u���b�N�̏�Ԃ̐ݒ�
			pBlock->type = type;

			// true�ŕԂ�
			pBlock->bUse = true;

			break;
		}
	}
}

//-----------------------------------------------------------------
// �u���b�N���̎擾
//-----------------------------------------------------------------
BLOCK *GetBlock(void)
{
	return &g_aBlock[0];
}

//-----------------------------------------------------------------
// �u���b�N�̒��_���W
//-----------------------------------------------------------------
void SetVertexBlock(int nIdx)
{
	// �ϐ��錾
	float ShaikingMove = 0.0f;

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	// �e�̏������ɂ���
	pVtx += nIdx * 4;

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x , g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x , g_aBlock[nIdx].pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y, 0.0f);

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, g_aBlock[nIdx].fTexV);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aBlock[nIdx].fTexU, g_aBlock[nIdx].fTexV);
	pVtx[3].tex = D3DXVECTOR2(g_aBlock[nIdx].fTexU, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//-----------------------------------------------------------------
// �u���b�N�̓����蔻��
//-----------------------------------------------------------------
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, COLLISIONINFO info)
{
	// �\���̂̃|�C���^�ϐ�
	BLOCK *pBlock = &g_aBlock[0];
	bool bLand = false;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++,pBlock++)
	{
		if (pBlock->bUse == true)
		{// �u���b�N���g���Ă���Ƃ�
			if (pBlock->type == BLOCKTYPE_CATCH)
			{// �����蔻�肪����u���b�N�̎�����
				if ((pPos->x - fWidth * 0.7f) < (pBlock->pos.x + pBlock->fWidth) &&
					(pPos->x + fWidth * 0.7f) > pBlock->pos.x)
				{// �v���C���[���u���b�N�̒��ɂ���Ƃ�
					if (pPosOld->y + fHeight <= pBlock->pos.y)
					{// �v���C���[���u���b�N�̏�ɂ���Ƃ�
						if (pPos->y + fHeight > (pBlock->pos.y - 2.0f))
						{// �߂荞�񂾂珈��
							LandBlock(nCntBlock, pPos, pMove, fHeight);
							bLand = true;
						}
					}
					else if ((pPosOld->y - fHeight) >= (pBlock->pos.y + pBlock->fHeight))
					{// �v���C���[���u���b�N�̉��ɂ���Ƃ�
						if ((pPos->y - fHeight) < (pBlock->pos.y + pBlock->fHeight))
						{// �߂荞�񂾂�u���b�N�̉��̍��W�ɂ���
							pPos->y = (pBlock->pos.y + pBlock->fHeight + fHeight);
							pMove->y = 1.0f;
						}
					}
				}
				if ((pPos->y + fHeight) > pBlock->pos.y && (pPos->y - fHeight) < (pBlock->pos.y + pBlock->fHeight))
				{// �v���C���[���u���b�N��Y���ɂ���Ƃ�
					if ((pPosOld->x + fWidth * 0.7f) <= pBlock->pos.x)
					{// �v���C���[���u���b�N�̍����ɂ���Ƃ�
						if ((pPos->x + fWidth * 0.7f) > pBlock->pos.x)
						{// �߂荞�񂾂�u���b�N�̍��̍��W�ɂ���
							pPos->x = pBlock->pos.x - (fWidth * 0.7f) + pBlock->move.x;
							CollisionBlockSide(pMove, info);
						}
					}
					else if ((pPosOld->x - fWidth * 0.7f) >= (pBlock->pos.x + pBlock->fWidth))
					{// �v���C���[���u���b�N�̉E���ɂ���Ƃ�
						if ((pPos->x - fWidth * 0.7f) < (pBlock->pos.x + pBlock->fWidth))
						{// �߂荞�񂾂�u���b�N�̉E�̍��W�ɂ���
							pPos->x = pBlock->pos.x + pBlock->fWidth + (fWidth * 0.7f) + pBlock->move.x;
							CollisionBlockSide(pMove, info);
						}
					}
				}
			}
		}
	}
	// ����Ă��邩�Ԃ�
	return bLand;
}

//-----------------------------------------------------------------
// ���̃u���b�N�ɏ���Ă��邩
//-----------------------------------------------------------------
void LandBlock(int nCntBlock, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, float fHeight)
{
	// �\���̂̃|�C���^�ϐ�
	BLOCK *pBlock = &g_aBlock[0];
	
	// ���Ԗڂ�
	pBlock += nCntBlock;

	if (pBlock->state == BLOCKSTATE_NORMAL || pBlock->state == BLOCKSTATE_FLOAT)
	{// �u���b�N�̏�Ԃ����������Ă��鏰�̂Ƃ�
		pPos->y = pBlock->pos.y - fHeight;
	}
	else if (pBlock->state == BLOCKSTATE_RIFT)
	{// �u���b�N�̏�Ԃ��㉺�ɓ������̂Ƃ�
		if (pBlock->move.y >= 0)
		{// �ォ�牺�̎�
			pPos->y = pBlock->pos.y - fHeight;
		}
		else if (pBlock->move.y < 0)
		{// �������̎�
			pPos->y = pBlock->pos.y + pBlock->move.y - fHeight;
		}
	}
}

//-----------------------------------------------------------------
// �u���b�N�̉��ɓ��������Ƃ�
//-----------------------------------------------------------------
void CollisionBlockSide(D3DXVECTOR3 *pMove, COLLISIONINFO info)
{
	switch (info)
	{// �v���C���[�̂Ƃ��ړ��ʂ�0�ɂ���
	case COLLISIONINFO_PLAYER:
		pMove->x = 0.0f;
		break;
		// �t���[�c�̂Ƃ����˂���
	case COLLISIONINFO_FRUITS:
		pMove->x *= -1;
		break;
		// �G�̂Ƃ����˂���
	case COLLISIONINFO_ENEMY:
		pMove->x *= -1;
		break;
	}
}

//-----------------------------------------------------------------
// �u���b�N���m�̓����蔻��
//-----------------------------------------------------------------
bool ColBlock(int nCntBlock)
{
	// �ϐ��錾
	bool bHit = false;		// �������Ă��邩�ǂ���

	// �ǂ̃u���b�N�ɓ������Ă��邩
	for (int nCntCollisionBlock = 0; nCntCollisionBlock < MAX_BLOCK; nCntCollisionBlock++)
	{
		// �܂��̓u���b�N���g���Ă��邩����
		if (g_aBlock[nCntCollisionBlock].bUse == true)
		{
			// �����g���Ă���Ȃ獡�����Ă���u���b�N�ƈႤ�u���b�N���ǂ�������
			if (nCntBlock != nCntCollisionBlock)
			{
				// �����Ⴄ�Ȃ�͂�ł���u���b�N�Ǝg���Ă���u���b�N���������Ă��邩����
				if (g_aBlock[nCntBlock].pos.x <= g_aBlock[nCntCollisionBlock].pos.x + g_aBlock[nCntCollisionBlock].fWidth &&
					g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth >= g_aBlock[nCntCollisionBlock].pos.x &&
					g_aBlock[nCntBlock].pos.y <= g_aBlock[nCntCollisionBlock].pos.y + g_aBlock[nCntCollisionBlock].fHeight &&
					g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight >= g_aBlock[nCntCollisionBlock].pos.y)
				{
					// �����������Ă���Ȃ�true��Ԃ�
					bHit = true;

					break;
				}
			}
		}
	}

	return bHit;
}

//-------------------------------------------------------------------------------
//	�u���b�N�̐ݒ�
//-------------------------------------------------------------------------------
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, BLOCKTYPE type)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			g_aBlock[nCntBlock].pos = pos;					//�ʒu

			g_aBlock[nCntBlock].fWidth = fWidth;			//��

			g_aBlock[nCntBlock].fHeight = fHeight;			//����

			g_aBlock[nCntBlock].bUse = true;				//�g���Ă���

			g_aBlock[nCntBlock].type = type;

			//���_���W(pos�ɑ������)(x�̓u���b�N�̕��Ay�͍���)
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);

			//���_���̐ݒ�(�n�ʂ���)
			pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
			pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
			pVtx[2].tex = D3DXVECTOR2(g_aBlock[nCntBlock].fWidth / g_aBlock[nCntBlock].fHeight, 1.0);
			pVtx[3].tex = D3DXVECTOR2(g_aBlock[nCntBlock].fWidth / g_aBlock[nCntBlock].fHeight, 0.0);
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}
