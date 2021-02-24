//--------------------------------------------------------------------------------
//
//	�v���C���[�̏��� [2DPlayer.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "2Dplayer.h"
#include "keyboard.h"


#include "fade.h"
#include "Result.h"
#include "sound.h"
#include "Xcontroller.h"

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
#define PLAYER_VR				(0.5f)		//f2DPlayerV�ɑ�����鐔�l(�E)
#define PLAYER_VL				(0.0f)		//f2DPlayerV�ɑ�����鐔�l(��)

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTexture2DPlayer = NULL;				//�v���C���[
D3DXVECTOR3 g_posAnimation2DPlayer;						//X,Y,Z�����߂�
int g_nCountersAnimation2DPlayer;							//�v���C���[(�R�}���̐؂�ւ�)
int g_nCountersAnimationCnt2DPlayer;						//�v���C���[(�J�E���^�X�V)
int g_nCountersAnimationCun;							//�J�E���g����(�J�E���^�X�V��x������)
float g_fTexY;											// �e�N�X�`��y���W
int g_nCnt2DPlayer;

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;
D3DXVECTOR3 g_movePolygon;								//�ړ���

PLAYER g_2DPlayer;										//�v���C���[�̏��

//-------------------------------------------------------------------------------
//	�v���C���[����������
//-------------------------------------------------------------------------------
HRESULT Init2DPlayer(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�ϐ��錾
	VERTEX_2D *pVtx;

	//�v���C���[�̍\���̂̏�����
	g_2DPlayer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���݂̏��(�ʒu)
	g_2DPlayer.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�Â����(�ʒu)
	g_2DPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
	g_2DPlayer.nLife = 3;										//������܂ł̒���
	g_2DPlayer.nCunt = 0;										//�d������
	g_2DPlayer.fWidth = 0.0f;									//��
	g_2DPlayer.fHeight = 0.0f;								//����
	g_2DPlayer.f2DPlayerU = 0;									//U
	g_2DPlayer.f2DPlayerV = 0;									//V
	g_2DPlayer.bMove = false;									//�ړ���
	g_2DPlayer.bUse = false;									//�g�p���Ă��邩�ǂ���
	g_2DPlayer.bJump = false;									//�W�����v�����ǂ���
	g_2DPlayer.bGetKey = false;								//���������Ă��邩
	g_2DPlayer.bFall = false;									//����

	//���@���X�^�[�g����ʒu
	g_2DPlayer.pos = D3DXVECTOR3(50.0f, 500.0f, 0.0f);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_2.png", &g_pTexture2DPlayer);		//�v���C���[

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
	pVtx[0].pos = D3DXVECTOR3(g_2DPlayer.pos.x - MAX_PLAYER_SIZE_X, g_2DPlayer.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_2DPlayer.pos.x - MAX_PLAYER_SIZE_X, g_2DPlayer.pos.y - MAX_PLAYER_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_2DPlayer.pos.x + MAX_PLAYER_SIZE_X, g_2DPlayer.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_2DPlayer.pos.x + MAX_PLAYER_SIZE_X, g_2DPlayer.pos.y - MAX_PLAYER_SIZE_Y, 0.0f);
	
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
void Uninit2DPlayer(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTexture2DPlayer != NULL)
	{
		g_pTexture2DPlayer->Release();
		g_pTexture2DPlayer = NULL;
	}
}

//-------------------------------------------------------------------------------
//	�v���C���[�̍X�V����
//-------------------------------------------------------------------------------
void Update2DPlayer(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;


	Move2DPlayer();

	//posOld��pos��������
	g_2DPlayer.posOld = g_2DPlayer.pos;

	if (GetkeyboardTrgger(DIK_SPACE) == true && g_2DPlayer.bJump == false)
	{//�W�����v�̏���(2�i�W�����v�̐���)
		g_2DPlayer.move.y = MAX_JUMP;
		g_2DPlayer.bJump = true;
		//�W�����v�����Ƃ������J���Ă�悤�ɂ���
	//	g_nCountersAnimationCnt2DPlayer = 1;

		//SE�̒ǉ�
		PlaySound(SOUND_LABEL_SE_JUMP);	//�W�����v
	}

	//�d��
	g_2DPlayer.move.y += +2;

	//���Z���Ă����Ă�(�������邱�Ƃłʂ�ʂ铮��)
	g_2DPlayer.pos.x += g_2DPlayer.move.x;
	g_2DPlayer.pos.y += g_2DPlayer.move.y;

	//�ړ��ʂ̌���(move�����炵�Ă���)
	g_2DPlayer.move.x += (0.0f - g_2DPlayer.move.x)*0.25f;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//�v���C���[�A�j���[�V����
//	g_nCountersAnimation2DPlayer = g_nCountersAnimationCnt2DPlayer % MAX_ANIMATION_PATTERN;	//�}�N���̓A�j���[�V�����̃R�}��

	//�v���C���[�̈ړ�����
	if (GetkeyboardPress(DIK_A) == true)
	{//���̈ړ�
		//�ړ���
		g_2DPlayer.move.x += -1.5;
		//����
	//	g_nCountersAnimationCun++;
		//f2DPlayerV�ɐ��l��������
		g_2DPlayer.f2DPlayerV = PLAYER_VR;
		//�W�����v
		g_2DPlayer.bMove = true;
	}
	
	if (GetkeyboardPress(DIK_D) == true)
	{//�E�Ɉړ�
		//�ړ���
		g_2DPlayer.move.x += +1.5;
		//����
	//	g_nCountersAnimationCun++;
		//f2DPlayerV�ɐ��l��������
		g_2DPlayer.f2DPlayerV = PLAYER_VL;
		//�W�����v����
		g_2DPlayer.bMove = true;
	}
	
	//A��D��������ĂȂ��Ƃ�
	if (GetkeyboardPress(DIK_A) == false && GetkeyboardPress(DIK_D) == false)
	{//�����J���Ȃ��悤�ɂ���
		g_2DPlayer.bMove = false;
		g_nCountersAnimationCnt2DPlayer = 0;
	}

	//�v���C���[�����蔻��
	if (g_2DPlayer.pos.x + MAX_PLAYER_X > SCREEN_WIDTH)
	{//�E
		g_2DPlayer.pos.x = SCREEN_WIDTH - MAX_PLAYER_X;
	}

	if (g_2DPlayer.pos.x - MAX_PLAYER_X < 0)
	{//��
		g_2DPlayer.pos.x = 0 + MAX_PLAYER_X;
	}

	if (g_2DPlayer.pos.y - MAX_PLAYER_Y < 170)
	{//��
		g_2DPlayer.pos.y = 170 + MAX_PLAYER_Y;
	}

	if (g_2DPlayer.pos.y + 0 > SCREEN_HEIGHT)
	{//��
		g_2DPlayer.pos.y = SCREEN_HEIGHT - 0;
	}


#if 0
	for (int nCunPlyer = 0; nCunPlyer < 255; nCunPlyer++, pBlock++)
	{//�u���b�N�𑝂₷
		if (pBlock->bUse == true)
		{//�u���b�N������
			if (g_2DPlayer.pos.x - (MAX_PLAYER_X) < pBlock->pos.x + pBlock->fWidth &&		//�u���b�N�̉E�[
				g_2DPlayer.pos.x + (MAX_PLAYER_X) > pBlock->pos.x)						//�u���b�N�̍��[
			{//���@��X�����u���b�N���E�ɐU�ꂽ��
				if (g_2DPlayer.posOld.y <= pBlock->pos.y)
				{//�ォ�玩�@���u���b�N�ɓ����锻��
					if (g_2DPlayer.pos.y > pBlock->pos.y)
					{//�u���b�N�̏�ɏ����
						g_2DPlayer.pos.y = pBlock->pos.y;
						g_2DPlayer.move.y = 0.0f;		//�d�͂̏�����
						g_2DPlayer.bJump = false;
					}
				}
				else if (g_2DPlayer.posOld.y - MAX_PLAYER_SIZE_Y >= pBlock->pos.y + pBlock->fHeight)
				{//���̓����蔻��
					if (g_2DPlayer.pos.y - MAX_PLAYER_SIZE_Y < pBlock->pos.y + pBlock->fHeight)
					{//�u���b�N�ɓ�������
						g_2DPlayer.pos.y = pBlock->pos.y + pBlock->fHeight + MAX_PLAYER_SIZE_Y;
						g_2DPlayer.move.y = 1.0f;		//�d�͂̏�����
					}
				}
			}

			if (g_2DPlayer.pos.y - (MAX_PLAYER_SIZE_Y) < pBlock->pos.y + pBlock->fHeight &&		//�u���b�N�̉��[�v���C���[�̏�[
				g_2DPlayer.pos.y > pBlock->pos.y)													//�u���b�N�̏�[
			{//���@��X�����u���b�N���E�ɐU�ꂽ��
				if (g_2DPlayer.posOld.x + MAX_PLAYER_X <= pBlock->pos.x)
				{//���̓����蔻��
					if (g_2DPlayer.pos.x + MAX_PLAYER_X > pBlock->pos.x)
					{//�u���b�N�ɓ�������
						g_2DPlayer.pos.x = pBlock->pos.x - MAX_PLAYER_X;
						g_2DPlayer.move.x = 0.0f;		//�d�͂̏�����
					}
				}
				else if (g_2DPlayer.posOld.x - MAX_PLAYER_X >= pBlock->pos.x + pBlock->fWidth)
				{//�E�̓����蔻��
					if (g_2DPlayer.pos.x - MAX_PLAYER_X < pBlock->pos.x + pBlock->fWidth)
					{//�u���b�N�ɓ�������
						g_2DPlayer.pos.x = pBlock->pos.x + pBlock->fWidth + MAX_PLAYER_X;
						g_2DPlayer.move.x = 0.0f;		//�d�͂̏�����
					}
				}
			}
		}
	}

#endif

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_2DPlayer.pos.x - MAX_PLAYER_SIZE_X, g_2DPlayer.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_2DPlayer.pos.x - MAX_PLAYER_SIZE_X, g_2DPlayer.pos.y - MAX_PLAYER_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_2DPlayer.pos.x + MAX_PLAYER_SIZE_X, g_2DPlayer.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_2DPlayer.pos.x + MAX_PLAYER_SIZE_X, g_2DPlayer.pos.y - MAX_PLAYER_SIZE_Y, 0.0f);


	if ((g_nCountersAnimation2DPlayer + 1) % 5 == 0)
	{// �l�Ԗڂ܂ŗ����珉���ɖ߂�
		g_nCountersAnimation2DPlayer = 0;
	}

	// �e�N�X�`���̒��_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(1.0f / MAX_ANIMATION_PATTERN * ((float)g_nCountersAnimation2DPlayer), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY + 1));
	pVtx[1].tex = D3DXVECTOR2(1.0f / MAX_ANIMATION_PATTERN * ((float)g_nCountersAnimation2DPlayer), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY));
	pVtx[2].tex = D3DXVECTOR2(1.0f / MAX_ANIMATION_PATTERN * ((float)g_nCountersAnimation2DPlayer + 1), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY + 1));
	pVtx[3].tex = D3DXVECTOR2(1.0f / MAX_ANIMATION_PATTERN * ((float)g_nCountersAnimation2DPlayer + 1), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY));



	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPolygon->Unlock();
}

//-------------------------------------------------------------------------------
//	�v���C���[�̕`�揈��
//-------------------------------------------------------------------------------
void Draw2DPlayer(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture2DPlayer);

	//�v���C���[�̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,					//�`����J�n���钸�_�C���f�b�N�X
		2);					//�`�悷��v���~�e�B�u��
}

//--------------------------------------------------------------------------------
// �v���C���[�̈ړ�
//--------------------------------------------------------------------------------
void Move2DPlayer(void)
{
	PLAYER *p2DPlayer;
	p2DPlayer = Get2DPlayer();

	if (GetkeyboardPress(DIK_D) == true)
	{// �E
		g_fTexY = 0;							// �A�j���e�N�X�`��Y
		if (g_2DPlayer.bJump == false)
		{// �A�j���[�V�����J�E���^�[�J�n
			g_nCountersAnimationCnt2DPlayer += 1;								// �A�j���[�V�����J�E���^�[
			if ((g_nCountersAnimationCnt2DPlayer % 5) == 0)
			{// �A�j���[�V�������x
				g_nCountersAnimation2DPlayer += 1;						// �A�j���e�N�X�`��X
			}
		}
	}
	else if (GetkeyboardPress(DIK_A) == true)
	{// ��
		g_fTexY = 1;							// �A�j���e�N�X�`��Y

		if (g_2DPlayer.bJump == false)
		{// �A�j���[�V�����J�E���^�[�J�n
			g_nCountersAnimationCnt2DPlayer += 1;								// �A�j���[�V�����J�E���^�[
			if ((g_nCountersAnimationCnt2DPlayer % 5) == 0)
			{// �A�j���[�V�������x
				g_nCountersAnimation2DPlayer += 1;						// �A�j���e�N�X�`��X
			}
		}
	}
	else if (GetkeyboardPress(DIK_A) == false)
	{// �~�܂�����
		g_nCountersAnimation2DPlayer = 0;									// �A�j���[�V�����X�g�b�v
	}
	else if (GetkeyboardPress(DIK_D) == false)
	{// �~�܂�����
		g_nCountersAnimation2DPlayer = 0;									// �A�j���[�V�����X�g�b�v
	}
	if (g_2DPlayer.bJump == false)
	{// �󒆂ɂ��Ȃ��Ƃ�
		if (GetkeyboardTrgger(DIK_J) == true)
		{// �W�����v�J�n
			g_2DPlayer.move.y -= 20.0f;						// �W�����v��
			g_2DPlayer.bJump = true;							// �W�����v��
		}
	}
	if (g_2DPlayer.bJump == true)
	{// �󒆂ɂ���Ƃ�
		g_nCountersAnimation2DPlayer = 1;									// �A�j���[�V�����X�g�b�v
	}
	if (g_2DPlayer.move.y != 0.0f)
	{// �W�����v�s��
		g_2DPlayer.bJump = true;								// ��
	}
}
//--------------------------------------------------------------------------------
//	�v���C���[�̎擾
//--------------------------------------------------------------------------------
PLAYER * Get2DPlayer(void)
{
	return &g_2DPlayer;		//�v���C���[�̏��̐擪�A�h���X��Ԃ�
}