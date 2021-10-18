//--------------------------------------------------------------------------------
//
//	�G�̏��� [enemy.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "enemy.h"
#include "block.h"
#include "Player.h"

//--------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//--------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_apTextureEnemy[ENEMYTYPE_MAX] = {};	//�e�N�X�`�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;				//���_�o�b�t�@�̃|�C���^
ENEMY g_aEnemy[MAX_ENEMY];									//�G�̏��
D3DXVECTOR3 g_posAnimationEnemy;							//X,Y,Z�����߂�
int g_nCountersAnimationEnemy;								//�v���C���[(�R�}���̐؂�ւ�)
int g_nCountersAnimationCntEnemy;							//�v���C���[(�J�E���^�X�V)
int g_nCountersAnimationCunEnemy;							//�J�E���g����(�J�E���^�X�V��x������)

//-------------------------------------------------------------------------------
//	�G�̏���������
//-------------------------------------------------------------------------------
HRESULT InitEnemy(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy_00.png", &g_apTextureEnemy[ENEMYTYPE_000]);	//�G

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���݂̏��(�ʒu)
		g_aEnemy[nCntEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�Â����(�ʒu)
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
		g_aEnemy[nCntEnemy].nLife = 0;										//������܂ł̒���
		g_aEnemy[nCntEnemy].nCunt = 0;										//�d������
		g_aEnemy[nCntEnemy].fWidth = MAX_ENEMY_SIZE_X;						//��
		g_aEnemy[nCntEnemy].fHeight = MAX_ENEMY_SIZE_Y;						//����
		g_aEnemy[nCntEnemy].fEnemyU = 0;									//U
		g_aEnemy[nCntEnemy].fEnemyV = 0;									//V
		g_aEnemy[nCntEnemy].bMove = false;									//�ړ���
		g_aEnemy[nCntEnemy].type = ENEMYTYPE_000;							//���
		g_aEnemy[nCntEnemy].bJump;											//�W�����v�����ǂ���
		g_aEnemy[nCntEnemy].bUse = false;									//�g�p���Ă��邩�ǂ���

		//�G���X�^�[�g����ʒu
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(500.0f, 650.0f, 0.0f);
	}

	//���_���̐ݒ�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL)))
	{
		return E_FAIL;
	}

	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//�G�̒��_���W�̐ݒ�
		SetVertexEnemy(nCntEnemy);

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE_X, g_aEnemy[nCntEnemy].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE_X, g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE_X, g_aEnemy[nCntEnemy].pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE_X, g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE_Y, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.5);
		pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.25, 0.5);
		pVtx[3].tex = D3DXVECTOR2(0.25, 0.0);

		pVtx += NUM_VERTEX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�I������
//-------------------------------------------------------------------------------
void UninitEnemy(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}

	//�e�N�X�`���̊J��(������)
	for (int nCntEnemy = 0; nCntEnemy < ENEMYTYPE_MAX; nCntEnemy++)
	{
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}
}

//-------------------------------------------------------------------------------
//	�X�V����
//-------------------------------------------------------------------------------
void UpdateEnemy(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	BLOCK * pBlock;
	PLAYER * pPlayer;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//�u���b�N�̏������炤
	pBlock = GetBlock();

	//�v���C���[�̏������炤
	pPlayer = GetPlayer();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pBlock++)
	{//�u���b�N�𑝂₷
		if (pBlock->bUse == true)
		{//�u���b�N������
			if (g_aEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE_X) < pBlock->pos.x + pBlock->fWidth &&		//�u���b�N�̉E�[
				g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE_X) > pBlock->pos.x)							//�u���b�N�̍��[
			{//���@��X�����u���b�N���E�ɐU�ꂽ��
				if (g_aEnemy[nCntEnemy].posOld.y <= pBlock->pos.y)
				{//�ォ�玩�@���u���b�N�ɓ����锻��
					if (g_aEnemy[nCntEnemy].pos.y > pBlock->pos.y)
					{//�u���b�N�̏�ɏ����
						g_aEnemy[nCntEnemy].pos.y = pBlock->pos.y;
						g_aEnemy[nCntEnemy].move.y = 0.0f;		//�d�͂̏�����
					}
				}
				else if (g_aEnemy[nCntEnemy].posOld.y - MAX_ENEMY_SIZE_Y >= pBlock->pos.y + pBlock->fHeight)
				{//���̓����蔻��
					if (g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE_Y < pBlock->pos.y + pBlock->fHeight)
					{//�u���b�N�ɓ�������
						g_aEnemy[nCntEnemy].pos.y = pBlock->pos.y + pBlock->fHeight + MAX_ENEMY_SIZE_Y;
						g_aEnemy[nCntEnemy].move.y = 1.0f;		//�d�͂̏�����
					}
				}
			}

			if (g_aEnemy[nCntEnemy].pos.y - (MAX_ENEMY_SIZE_Y) < pBlock->pos.y + pBlock->fHeight &&		//�u���b�N�̉��[�v���C���[�̏�[
				g_aEnemy[nCntEnemy].pos.y > pBlock->pos.y)													//�u���b�N�̏�[
			{//���@��X�����u���b�N���E�ɐU�ꂽ��
				if (g_aEnemy[nCntEnemy].posOld.x + MAX_ENEMY_SIZE_X <= pBlock->pos.x)
				{//���̓����蔻��
					if (g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE_X > pBlock->pos.x)
					{//�u���b�N�ɓ�������
						g_aEnemy[nCntEnemy].pos.x = pBlock->pos.x - MAX_ENEMY_SIZE_X;
						g_aEnemy[nCntEnemy].move.x = 0.0f;		//�d�͂̏�����
					}
				}
				else if (g_aEnemy[nCntEnemy].posOld.x - MAX_ENEMY_SIZE_X >= pBlock->pos.x + pBlock->fWidth)
				{//�E�̓����蔻��
					if (g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE_X < pBlock->pos.x + pBlock->fWidth)
					{//�u���b�N�ɓ�������
						g_aEnemy[nCntEnemy].pos.x = pBlock->pos.x + pBlock->fWidth + MAX_ENEMY_SIZE_X;
						g_aEnemy[nCntEnemy].move.x = 0.0f;		//�d�͂̏�����
					}
				}
				//���_���W
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE_X, g_aEnemy[nCntEnemy].pos.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE_X, g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE_X, g_aEnemy[nCntEnemy].pos.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE_X, g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE_Y, 0.0f);
			}
		}

		if ((g_nCountersAnimationCunEnemy % 5) == 0 && g_aEnemy[nCntEnemy].bJump == false && g_aEnemy[nCntEnemy].bMove == true)//%���͊��鐔)==���͂��܂�
		{//�J�E���g����
			g_nCountersAnimationCntEnemy++;

			//�A�j���[�V�����̒��_���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationEnemy * 0.25f, 0.5f + g_aEnemy[nCntEnemy].fEnemyV);//+ g_aEnemy[nCntEnemy].fEnemyV���������Ƃō��E���ł���
			pVtx[1].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationEnemy * 0.25f, 0.0f + g_aEnemy[nCntEnemy].fEnemyV);
			pVtx[2].tex = D3DXVECTOR2(0.25f + g_nCountersAnimationEnemy * 0.25f, 0.5f + g_aEnemy[nCntEnemy].fEnemyV);
			pVtx[3].tex = D3DXVECTOR2(0.25f + g_nCountersAnimationEnemy * 0.25f, 0.0f + g_aEnemy[nCntEnemy].fEnemyV);
		}

		//�G�ƃv���C���[�̓����蔻��
		if (g_aEnemy[nCntEnemy].bUse == true)
		{	//�g�p���Ă��邩�ǂ���
			if (pPlayer->pos.x - (MAX_PLAYER_SIZE_X / 2) < g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE_X / 2) &&		//��
				pPlayer->pos.x + (MAX_PLAYER_SIZE_X / 2) > g_aEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE_X / 2) &&		//�E
				pPlayer->pos.y - MAX_PLAYER_SIZE_Y      <  g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE_Y / 2) &&		//��
				pPlayer->pos.y >						   g_aEnemy[nCntEnemy].pos.y - (MAX_ENEMY_SIZE_Y / 2))			//��
			{
				//HitPlayer(nCntEnemy, DAMAGE_PAPER);	//�v���C���[�̏��,�_���[�W��()
				pPlayer->bUse = false;
			}
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffEnemy->Unlock();
	}
}

//-------------------------------------------------------------------------------
//	�G�̕`�揈��
//-------------------------------------------------------------------------------
void DrawEnemy(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].type]);

		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive
			(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
			nCntEnemy * NUM_VERTEX,		//�`����J�n���钸�_�C���f�b�N�X
			NUM_POLYGON);				//�`�悷��v���~�e�B�u��
		}
	}
}

//-------------------------------------------------------------------------------
//	�G�̐ݒ�
//-------------------------------------------------------------------------------
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMYTYPE type, int nLife)
{
	//�ϐ��錾
	ENEMY * pEnemy;
	pEnemy = &g_aEnemy[0];
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == false)
		{
			pEnemy->pos = pos;				//�ʒu

			pEnemy->type = type;			//���
		
			SetVertexEnemy(nCntEnemy);		//�G�̒��_���W�̐ݒ�

			pEnemy->move = move;			//�ړ���

			pEnemy->nLife = nLife;			//�G�̗̑�

			pEnemy->bUse = true;

			break;
		}
		pVtx += NUM_VERTEX;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//--------------------------------------------------------------------------------
//	�G�̎擾
//--------------------------------------------------------------------------------
ENEMY * GetEnemy(void)
{
	return &g_aEnemy[0];	//�G�̏��̐擪�A�h���X��Ԃ�
}

//-------------------------------------------------------------------------------
//	�G�̒��_���W�̐ݒ�
//-------------------------------------------------------------------------------
void SetVertexEnemy(int nCntEnemy)
{
	VERTEX_2D * pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[nCntEnemy * NUM_VERTEX + 0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE_X / 2, g_aEnemy[nCntEnemy].pos.y + MAX_ENEMY_SIZE_Y/ 2, 0.0f);	//����
	pVtx[nCntEnemy * NUM_VERTEX + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE_X / 2, g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE_Y/ 2, 0.0f);	//����
	pVtx[nCntEnemy * NUM_VERTEX + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE_X / 2, g_aEnemy[nCntEnemy].pos.y + MAX_ENEMY_SIZE_Y/ 2, 0.0f);	//�E��
	pVtx[nCntEnemy * NUM_VERTEX + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE_X / 2, g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE_Y/ 2, 0.0f);	//�E��

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//-------------------------------------------------------------------------------
//	�G�̏�Ԑݒ�
//	nIdx:�G���Ԗڂ��̏��
//-------------------------------------------------------------------------------