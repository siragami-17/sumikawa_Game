//--------------------------------------------------------------------------------
//
//	�v���C���[�̏��� [Player.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Player.h"
#include "keyboard.h"
#include "block.h"
#include "goal.h"
#include "fade.h"
#include "Result.h"
#include "sound.h"
#include "Xcontroller.h"
#include "sound.h"

//--------------------------------------------------------------------------------
//	�}�N����`
//--------------------------------------------------------------------------------
#define MAX_POLYGON				(1)			//�e�N�X�`����
#define MAX_ATTENUATION			(0.25f)		//����
#define MAX_ANIMATION_PATTERN	(4)			//�v���C���[(��)
#define TEXTURE_PLAYER_Y		(2)			//����(��)
#define MAX_ANIMATION_COUNTER	(5)			//�v���C���[(�X�s�[�h)
#define MAX_JUMP				(-20)		//�W�����v
#define MAX_PLAYER_X			(161/6)		//�v���C���[�̕�(�����蔻��)
#define MAX_PLAYER_Y			(304/5)		//�v���C���[�̍���(�����蔻��)
#define PLAYER_VR				(0.5f)		//fPlayerV�ɑ�����鐔�l(�E)
#define PLAYER_VL				(0.0f)		//fPlayerV�ɑ�����鐔�l(��)

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;				//�v���C���[
D3DXVECTOR3 g_posAnimationPlayer;						//X,Y,Z�����߂�
int g_nCountersAnimationPlayer;							//�v���C���[(�R�}���̐؂�ւ�)
int g_nCountersAnimationCntPlayer;						//�v���C���[(�J�E���^�X�V)
int g_nCountersAnimationCun;							//�J�E���g����(�J�E���^�X�V��x������)
float g_fTexY;											// �e�N�X�`��y���W
int g_nCntPlayer;

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;
D3DXVECTOR3 g_movePolygon;								//�ړ���

PLAYER g_Player;										//�v���C���[�̏��

//-------------------------------------------------------------------------------
//	�v���C���[����������
//-------------------------------------------------------------------------------
HRESULT InitPlayer(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�ϐ��錾
	VERTEX_2D *pVtx;

	//�v���C���[�̍\���̂̏�����
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���݂̏��(�ʒu)
	g_Player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�Â����(�ʒu)
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
	g_Player.nLife = 3;										//������܂ł̒���
	g_Player.nCunt = 0;										//�d������
	g_Player.fWidth = 0.0f;									//��
	g_Player.fHeight = 0.0f;								//����
	g_Player.fPlayerU = 0;									//U
	g_Player.fPlayerV = 0;									//V
	g_Player.bMove = false;									//�ړ���
	g_Player.bUse = false;									//�g�p���Ă��邩�ǂ���
	g_Player.bJump = false;									//�W�����v�����ǂ���
	g_Player.bGetKey = false;								//���������Ă��邩
	g_Player.bFall = false;									//����

	//���@���X�^�[�g����ʒu
	g_Player.pos = D3DXVECTOR3(50.0f, 650.0f, 0.0f);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_2.png", &g_pTexturePlayer);		//�v���C���[

	//���_�o�b�t�@�̐���5
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - MAX_PLAYER_SIZE_X, g_Player.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x - MAX_PLAYER_SIZE_X, g_Player.pos.y - MAX_PLAYER_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x + MAX_PLAYER_SIZE_X, g_Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + MAX_PLAYER_SIZE_X, g_Player.pos.y - MAX_PLAYER_SIZE_Y, 0.0f);
	
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


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPolygon->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�v���C���[�̏I������
//-------------------------------------------------------------------------------
void UninitPlayer(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}

//-------------------------------------------------------------------------------
//	�v���C���[�̍X�V����
//-------------------------------------------------------------------------------
void UpdatePlayer(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	BLOCK * pBlock;

	//�u���b�N�̏������炤
	pBlock = GetBlock();

	MovePlayer();

	//posOld��pos��������
	g_Player.posOld = g_Player.pos;

	if (GetkeyboardTrgger(DIK_SPACE) == true && g_Player.bJump == false)
	{//�W�����v�̏���(2�i�W�����v�̐���)
		g_Player.move.y = MAX_JUMP;
		g_Player.bJump = true;
		//�W�����v�����Ƃ������J���Ă�悤�ɂ���
	//	g_nCountersAnimationCntPlayer = 1;

		//SE�̒ǉ�
		PlaySound(SOUND_LABEL_SE_JUMP);	//�W�����v
	}

	//�d��
	g_Player.move.y += +2;

	//���Z���Ă����Ă�(�������邱�Ƃłʂ�ʂ铮��)
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;

	//�ړ��ʂ̌���(move�����炵�Ă���)
	g_Player.move.x += (0.0f - g_Player.move.x)*0.25f;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//�v���C���[�A�j���[�V����
//	g_nCountersAnimationPlayer = g_nCountersAnimationCntPlayer % MAX_ANIMATION_PATTERN;	//�}�N���̓A�j���[�V�����̃R�}��

	//�v���C���[�̈ړ�����
	if (GetkeyboardPress(DIK_A) == true)
	{//���̈ړ�
		//�ړ���
		g_Player.move.x += -1.5;
		//����
	//	g_nCountersAnimationCun++;
		//fPlayerV�ɐ��l��������
		g_Player.fPlayerV = PLAYER_VR;
		//�W�����v
		g_Player.bMove = true;
	}
	
	if (GetkeyboardPress(DIK_D) == true)
	{//�E�Ɉړ�
		//�ړ���
		g_Player.move.x += +1.5;
		//����
	//	g_nCountersAnimationCun++;
		//fPlayerV�ɐ��l��������
		g_Player.fPlayerV = PLAYER_VL;
		//�W�����v����
		g_Player.bMove = true;
	}
	
	//A��D��������ĂȂ��Ƃ�
	if (GetkeyboardPress(DIK_A) == false && GetkeyboardPress(DIK_D) == false)
	{//�����J���Ȃ��悤�ɂ���
		g_Player.bMove = false;
		g_nCountersAnimationCntPlayer = 0;
	}

	//�v���C���[�����蔻��
	if (g_Player.pos.x + MAX_PLAYER_X > SCREEN_WIDTH)
	{//�E
		g_Player.pos.x = SCREEN_WIDTH - MAX_PLAYER_X;
	}

	if (g_Player.pos.x - MAX_PLAYER_X < 0)
	{//��
		g_Player.pos.x = 0 + MAX_PLAYER_X;
	}

	if (g_Player.pos.y - MAX_PLAYER_Y < 170)
	{//��
		g_Player.pos.y = 170 + MAX_PLAYER_Y;
	}

	if (g_Player.pos.y + 0 > SCREEN_HEIGHT)
	{//��
		g_Player.pos.y = SCREEN_HEIGHT - 0;
	}

	for (int nCunPlyer = 0; nCunPlyer < 255; nCunPlyer++, pBlock++)
	{//�u���b�N�𑝂₷
		if (pBlock->bUse == true)
		{//�u���b�N������
			if (g_Player.pos.x - (MAX_PLAYER_X) < pBlock->pos.x + pBlock->fWidth &&		//�u���b�N�̉E�[
				g_Player.pos.x + (MAX_PLAYER_X) > pBlock->pos.x)						//�u���b�N�̍��[
			{//���@��X�����u���b�N���E�ɐU�ꂽ��
				if (g_Player.posOld.y <= pBlock->pos.y)
				{//�ォ�玩�@���u���b�N�ɓ����锻��
					if (g_Player.pos.y > pBlock->pos.y)
					{//�u���b�N�̏�ɏ����
						g_Player.pos.y = pBlock->pos.y;
						g_Player.move.y = 0.0f;		//�d�͂̏�����
						g_Player.bJump = false;
					}
				}
				else if (g_Player.posOld.y - MAX_PLAYER_SIZE_Y >= pBlock->pos.y + pBlock->fHeight)
				{//���̓����蔻��
					if (g_Player.pos.y - MAX_PLAYER_SIZE_Y < pBlock->pos.y + pBlock->fHeight)
					{//�u���b�N�ɓ�������
						g_Player.pos.y = pBlock->pos.y + pBlock->fHeight + MAX_PLAYER_SIZE_Y;
						g_Player.move.y = 1.0f;		//�d�͂̏�����
					}
				}
			}

			if (g_Player.pos.y - (MAX_PLAYER_SIZE_Y) < pBlock->pos.y + pBlock->fHeight &&		//�u���b�N�̉��[�v���C���[�̏�[
				g_Player.pos.y > pBlock->pos.y)													//�u���b�N�̏�[
			{//���@��X�����u���b�N���E�ɐU�ꂽ��
				if (g_Player.posOld.x + MAX_PLAYER_X <= pBlock->pos.x)
				{//���̓����蔻��
					if (g_Player.pos.x + MAX_PLAYER_X > pBlock->pos.x)
					{//�u���b�N�ɓ�������
						g_Player.pos.x = pBlock->pos.x - MAX_PLAYER_X;
						g_Player.move.x = 0.0f;		//�d�͂̏�����
					}
				}
				else if (g_Player.posOld.x - MAX_PLAYER_X >= pBlock->pos.x + pBlock->fWidth)
				{//�E�̓����蔻��
					if (g_Player.pos.x - MAX_PLAYER_X < pBlock->pos.x + pBlock->fWidth)
					{//�u���b�N�ɓ�������
						g_Player.pos.x = pBlock->pos.x + pBlock->fWidth + MAX_PLAYER_X;
						g_Player.move.x = 0.0f;		//�d�͂̏�����
					}
				}
			}
		}
	}

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - MAX_PLAYER_SIZE_X, g_Player.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x - MAX_PLAYER_SIZE_X, g_Player.pos.y - MAX_PLAYER_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x + MAX_PLAYER_SIZE_X, g_Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + MAX_PLAYER_SIZE_X, g_Player.pos.y - MAX_PLAYER_SIZE_Y, 0.0f);

	if (g_Player.move.y >= 20 && g_Player.bJump == true)
	{//�u���b�N2�i�ȏォ�痎�������Ɏ��S�t���O�����Ă�
		g_Player.bFall = true;
	}

	//���S�t���O�������Ă��鎞����
	if (g_Player.bFall == true && g_Player.bJump == false)
	{//�v���C���[���u���b�N�̏�ɏ����
		HitPlayer(1);		//�_���[�W1

		//SE�̒ǉ�
		PlaySound(SOUND_LABEL_SE_DAMAGE);	//�_���[�W
	}

	if ((g_nCountersAnimationPlayer + 1) % 5 == 0)
	{// �l�Ԗڂ܂ŗ����珉���ɖ߂�
		g_nCountersAnimationPlayer = 0;
	}

	// �e�N�X�`���̒��_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(1.0f / MAX_ANIMATION_PATTERN * ((float)g_nCountersAnimationPlayer), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY + 1));
	pVtx[1].tex = D3DXVECTOR2(1.0f / MAX_ANIMATION_PATTERN * ((float)g_nCountersAnimationPlayer), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY));
	pVtx[2].tex = D3DXVECTOR2(1.0f / MAX_ANIMATION_PATTERN * ((float)g_nCountersAnimationPlayer + 1), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY + 1));
	pVtx[3].tex = D3DXVECTOR2(1.0f / MAX_ANIMATION_PATTERN * ((float)g_nCountersAnimationPlayer + 1), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY));

	if (g_Player.state == PLAYERSTATE_DAMAGE)
	{
		g_Player.nCounterState--;//�_�ł��钷��

		if (g_Player.nCounterState == 0)
		{//�v���C���[�̐F�����ǂ�
			//���_�J���[�ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPolygon->Unlock();
}

//-------------------------------------------------------------------------------
//	�v���C���[�̕`�揈��
//-------------------------------------------------------------------------------
void DrawPlayer(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	//�v���C���[�̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,					//�`����J�n���钸�_�C���f�b�N�X
		2);					//�`�悷��v���~�e�B�u��
}

//-------------------------------------------------------------------------------
//	�v���C���[�̃��C�t
//-------------------------------------------------------------------------------
bool HitPlayer(int nDamage)
{
	g_Player.nLife -= nDamage;

	if (g_Player.nLife <= 0)
	{//�v���C���[������
		g_Player.bUse = false;

		//�v���C���[�̃��C�t��0�ɂȂ����烊�U���g���
		SetResult(false);
		SetFade(FADE_OUT, MODE_RESULT);		//�Q�[���I�[�o���

		return true;
	}
	else
	{//�v���C���[�����ȂȂ�������
		g_Player.state = PLAYERSTATE_DAMAGE;
		g_Player.bFall = false;
		g_Player.nCounterState = 5;//�_�ł��钷��

		VERTEX_2D *pVtx;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

		//�_���[�W���(�F)
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPolygon->Unlock();

		return false;
	}
}

//--------------------------------------------------------------------------------
// �v���C���[�̈ړ�
//--------------------------------------------------------------------------------
void MovePlayer(void)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	if (GetkeyboardPress(DIK_D) == true)
	{// �E
		g_fTexY = 0;							// �A�j���e�N�X�`��Y
		if (g_Player.bJump == false)
		{// �A�j���[�V�����J�E���^�[�J�n
			g_nCountersAnimationCntPlayer += 1;								// �A�j���[�V�����J�E���^�[
			if ((g_nCountersAnimationCntPlayer % 5) == 0)
			{// �A�j���[�V�������x
				g_nCountersAnimationPlayer += 1;						// �A�j���e�N�X�`��X
			}
		}
	}
	else if (GetkeyboardPress(DIK_A) == true)
	{// ��
		g_fTexY = 1;							// �A�j���e�N�X�`��Y

		if (g_Player.bJump == false)
		{// �A�j���[�V�����J�E���^�[�J�n
			g_nCountersAnimationCntPlayer += 1;								// �A�j���[�V�����J�E���^�[
			if ((g_nCountersAnimationCntPlayer % 5) == 0)
			{// �A�j���[�V�������x
				g_nCountersAnimationPlayer += 1;						// �A�j���e�N�X�`��X
			}
		}
	}
	else if (GetkeyboardPress(DIK_A) == false)
	{// �~�܂�����
		g_nCountersAnimationPlayer = 0;									// �A�j���[�V�����X�g�b�v
	}
	else if (GetkeyboardPress(DIK_D) == false)
	{// �~�܂�����
		g_nCountersAnimationPlayer = 0;									// �A�j���[�V�����X�g�b�v
	}
	if (g_Player.bJump == false)
	{// �󒆂ɂ��Ȃ��Ƃ�
		if (GetkeyboardTrgger(DIK_J) == true)
		{// �W�����v�J�n
			g_Player.move.y -= 20.0f;						// �W�����v��
			g_Player.bJump = true;							// �W�����v��
		}
	}
	if (g_Player.bJump == true)
	{// �󒆂ɂ���Ƃ�
		g_nCountersAnimationPlayer = 1;									// �A�j���[�V�����X�g�b�v
	}
	if (g_Player.move.y != 0.0f)
	{// �W�����v�s��
		g_Player.bJump = true;								// ��
	}
}
//--------------------------------------------------------------------------------
//	�v���C���[�̎擾
//--------------------------------------------------------------------------------
PLAYER * GetPlayer(void)
{
	return &g_Player;		//�v���C���[�̏��̐擪�A�h���X��Ԃ�
}