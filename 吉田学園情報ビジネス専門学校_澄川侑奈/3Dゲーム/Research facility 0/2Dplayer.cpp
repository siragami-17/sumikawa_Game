//--------------------------------------------------------------------------------
//
//	2D�v���C���[�̏��� [2D2DPlayer.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "2DPlayer.h"			// 2D�v���C���[
#include "keyboard.h"			// �L�[����
#include "fade.h"				// �t�F�[�h
#include "sound.h"				// �T�E���h
#include "Xcontroller.h"		// Xinput

//--------------------------------------------------------------------------------
//	�}�N����`
//--------------------------------------------------------------------------------
#define MAX_POLYGON				(1)			//�e�N�X�`����
#define MAX_ATTENUATION			(0.25f)		//����
#define MAX_ANIMATION_PATTERN	(4)			//�v���C���[(��)
#define TEXTURE_PLAYER_Y		(2)			//����(��)
#define MAX_ANIMATION_COUNTER	(5)			//�v���C���[(�X�s�[�h)
#define MAX_JUMP				(-20)		//�W�����v
#define MAX_PLAYER_X			(41)		//�v���C���[�̕�(�����蔻��)
#define MAX_PLAYER_Y			(117)		//�v���C���[�̍���(�����蔻��)
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
	g_2DPlayer.pos = D3DXVECTOR3(50.0f, 650.0f, 0.0f);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player.png", &g_pTexture2DPlayer);		//�v���C���[

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
	pVtx[0].tex = D3DXVECTOR2(0.0, 0.1);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.1, 0.1);
	pVtx[3].tex = D3DXVECTOR2(0.1, 0.0);


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
//	�v���C���[�̎擾
//--------------------------------------------------------------------------------
PLAYER * Get2DPlayer(void)
{
	return &g_2DPlayer;		//�v���C���[�̏��̐擪�A�h���X��Ԃ�
}