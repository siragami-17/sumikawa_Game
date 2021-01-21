////--------------------------------------------------------------------------------
////
////	�J�[�\���̏��� [mark.cpp]
////	Author:Yuna Sumikawa
////
////--------------------------------------------------------------------------------
//#include "mark.h"
//#include "Game_00.h"
//#include "keyboard.h"
//#include "fade.h"
//#include "sound.h"
//#include "block.h"
//
////-------------------------------------------------------------------------------
////	�}�N����`
////-------------------------------------------------------------------------------
//#define MAX_POLYGON				(1)			//�|���S����
//#define ATTENUATION				(0.30f)		//����
//
//#define MAX_STOPX				(50)		//�J�[�\����X
//#define MAX_STOPY				(50)		//�J�[�\����Y
//#define MAX_ANIMATION_COUNTER	(60.0f)		//�J�[�\��(�ړ�)
//#define MAX_ANIMATION_PATTERN	(3)			//�J�[�\��(��)
//
//
////-------------------------------------------------------------------------------
////	�O���[�o���ϐ�
////-------------------------------------------------------------------------------
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMark = NULL;
//
//LPDIRECT3DTEXTURE9 g_pHnd = NULL;					//�J�[�\��
//D3DXVECTOR3 g_posAnimationHnd;						//X,Y,Z�����߂�
//int g_nCountersAnimationHnd;						//�J�[�\��(�R�}���̐؂�ւ�)
//int g_nCountersAnimationCntHnd;						//�J�[�\��(�J�E���^�X�V)
//
//MARK g_Mark;										//�X�g�b�v�̏��
////-------------------------------------------------------------------------------
////	�X�g�b�v����������
////-------------------------------------------------------------------------------
//HRESULT InitMark(void)
//{
//	//�f�o�C�X�̎擾
//	LPDIRECT3DDEVICE9 pDevice;
//	pDevice = GetDevice();
//
//	//�ϐ��錾
//	VERTEX_2D *pVtx;
//
//	//�e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/hnd.png", &g_pHnd);		//�J�[�\��
//
//	//�X�g�b�v�̍\���̂̏���������
//	g_Mark.pos = D3DXVECTOR3(615.0f, 365.0f, 0.0f);									//�ʒu
//	g_Mark.bUse = false;
//	g_Mark.bGrab = false;
//
//	//���_�o�b�t�@�̐���
//	if (FAILED(pDevice->CreateVertexBuffer
//	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		//�m�ۂ���o�b�t�@�T�C�Y
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,							//���_�t�H�[�}�b�g
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffMark,
//		NULL)))
//	{
//		return E_FAIL;
//	}
//
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffMark->Lock(0, 0, (void**)&pVtx, 0);
//
//	//���_���W
//	pVtx[0].pos = D3DXVECTOR3(g_Mark.pos.x - 0, g_Mark.pos.y + 50, 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(g_Mark.pos.x - 0, g_Mark.pos.y - 0, 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(g_Mark.pos.x + 50, g_Mark.pos.y + 50, 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(g_Mark.pos.x + 50, g_Mark.pos.y - 0, 0.0f);
//
//
//	//�J���[�p��switch(���_�J���[.col)
//	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//
//	//�A�j���[�V�����p��switch(���_���.tex)
//	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);	//����
//	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);	//����
//	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);	//�E��
//	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);	//�E��
//
//	//rhw�̐ݒ�
//	pVtx[0].rhw = 1.0f;
//	pVtx[1].rhw = 1.0f;
//	pVtx[2].rhw = 1.0f;
//	pVtx[3].rhw = 1.0f;
//
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffMark->Unlock();
//
//	return S_OK;
//}
//
////-------------------------------------------------------------------------------
////	�X�g�b�v�̏I������
////-------------------------------------------------------------------------------
//void UninitMark(void)
//{
//	//���_�o�b�t�@�̊J��
//	if (g_pVtxBuffMark != NULL)
//	{
//		g_pVtxBuffMark->Release();
//		g_pVtxBuffMark = NULL;
//	}
//
//	//�e�N�X�`���̊J��(�J�[�\��)
//	if (g_pHnd != NULL)
//	{
//		g_pHnd->Release();
//		g_pHnd = NULL;
//	}
//}
//
////-------------------------------------------------------------------------------
////	�X�g�b�v�̍X�V����
////-------------------------------------------------------------------------------
//void UpdateMark(void)
//{
//	//�ϐ��錾
//	VERTEX_2D *pVtx;
//	BLOCK * pBlock;
//
//	//�u���b�N�̏������炤
//	pBlock = GetBlock();
//
//	//�J�[�\��(�I��)
//	g_nCountersAnimationHnd = 0;
//
//	if (g_Mark.bGrab == true)
//	{//�͂񂾎�
//		//�J�[�\��(�͂�)
//		g_nCountersAnimationHnd = 2;
//	}
//
//	//�J�[�\���̈ړ�����
//	if (GetkeyboardTrgger(DIK_W) == true)
//	{//��
//		g_Mark.pos.y -= MAX_ANIMATION_COUNTER;
//	}
//
//	if (GetkeyboardTrgger(DIK_A) == true)
//	{//��
//		g_Mark.pos.x -= MAX_ANIMATION_COUNTER;
//	}
//
//	if (GetkeyboardTrgger(DIK_S) == true)
//	{//��
//		g_Mark.pos.y += MAX_ANIMATION_COUNTER;
//	}
//
//	if (GetkeyboardTrgger(DIK_D) == true)
//	{//�E
//		g_Mark.pos.x += MAX_ANIMATION_COUNTER;
//	}
//
//	//�J�[�\���Ɖ�ʂ̓����蔻��
//	if (g_Mark.pos.x + MAX_STOPX > SCREEN_WIDTH - 15.0f)
//	{//�E
//		g_Mark.pos.x = SCREEN_WIDTH - MAX_STOPX - 15.0f;
//	}
//
//	if (g_Mark.pos.x < 15.0f)
//	{//��
//		g_Mark.pos.x = 15.0f;
//	}
//
//	if (g_Mark.pos.y < 125.0f)
//	{//��
//		g_Mark.pos.y = 125.0f;
//	}
//
//	if (g_Mark.pos.y + MAX_STOPY > SCREEN_HEIGHT - 5.0f)
//	{//��
//		g_Mark.pos.y = SCREEN_HEIGHT - MAX_STOPY - 5.0f;
//	}
//
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffMark->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCntMark = 0; nCntMark < MAX_BLOCK; nCntMark++, pBlock++)
//	{//�S�Ẵu���b�N�ɔ���
//		if (g_Mark.bUse == false)	//�g�p���Ă��邩�ǂ���
//		{
//			if (pBlock->pos.x - (60 / 3) < g_Mark.pos.x + (MAX_STOPX / 3) &&
//				pBlock->pos.x + (60 / 3) > g_Mark.pos.x - (MAX_STOPX / 3) &&
//				pBlock->pos.y - (60 / 3) < g_Mark.pos.y + (MAX_STOPY / 3) &&
//				pBlock->pos.y + (60 / 3) > g_Mark.pos.y - (MAX_STOPY / 3))
//			{
//				//�͂ޏ���
//				if (GetkeyboardTrgger(DIK_RETURN) == true)
//				{//�G���^�[�L�[��������
//				 //�͂߂�
//					g_Mark.bGrab = g_Mark.bGrab ? false : true;
//				}
//
//				//�u���b�N��������
//				pBlock->bUse = true;
//
//				if (g_Mark.bGrab == false)
//				{
//					//�J�[�\��(���Ă�)
//					g_nCountersAnimationHnd = 1;
//				}
//				//��������
//				pBlock->bBlock = true;
//			}
//		}
//	}
//
//	//�A�j���[�V����(�J�[�\��)
//	g_nCountersAnimationHnd = g_nCountersAnimationHnd % MAX_ANIMATION_PATTERN;	//�A�j���[�V�����̃R�}��
//
//	//�A�j���[�V�����̒��_���̐ݒ�
//	pVtx[0].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationHnd * 0.33f, 1.0f);
//	pVtx[1].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationHnd * 0.33f, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(0.33f + g_nCountersAnimationHnd * 0.33f, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(0.33f + g_nCountersAnimationHnd * 0.33f, 0.0f);
//
//	pVtx[0].pos = D3DXVECTOR3(g_Mark.pos.x - 0, g_Mark.pos.y + 50, 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(g_Mark.pos.x - 0, g_Mark.pos.y - 0, 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(g_Mark.pos.x + 50, g_Mark.pos.y + 50, 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(g_Mark.pos.x + 50, g_Mark.pos.y - 0, 0.0f);
//
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffMark->Unlock();	
//}
//
////-------------------------------------------------------------------------------
////	�X�g�b�v�̕`�揈��
////-------------------------------------------------------------------------------
//void DrawMark(void)
//{
//	//�f�o�C�X�̎擾
//	LPDIRECT3DDEVICE9 pDevice;
//	pDevice = GetDevice();
//
//	BLOCK * pBlock;
//
//	//�u���b�N�̏������炤
//	pBlock = GetBlock();
//
//	//���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
//	pDevice->SetStreamSource(0, g_pVtxBuffMark, 0, sizeof(VERTEX_2D));
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//�J�[�\���e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, g_pHnd);
//
//	//�J�[�\���̕`��
//	pDevice->DrawPrimitive
//	(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
//		0,						//�`����J�n���钸�_�C���f�b�N�X
//		2);						//�`�悷��v���~�e�B�u��
//}
//
////--------------------------------------------------------------------------------
////	�J�[�\���̎擾
////--------------------------------------------------------------------------------
//MARK * GetMark(void)
//{
//	return &g_Mark;		//�J�[�\���̏��̐擪�A�h���X��Ԃ�
//}





//--------------------------------------------------------------------------------
//
//	�J�[�\���̏��� [mark.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "mark.h"
#include "Game_00.h"
#include "keyboard.h"
#include "fade.h"
#include "sound.h"
#include "block.h"


//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define MAX_POLYGON				(1)			//�|���S����

#define MARKER_SIZE (50.0f)			// �}�[�J�[�̃T�C�Y

#define MOVE_MARKER	(3.0f)
#define PI_QUARTER	(D3DX_PI / 4)	// �~������1/4(�΂߈ړ��Ŏg��)

#define MAX_ANIMATION_COUNTER	(60.0f)		//�J�[�\��(�ړ�)
#define MAX_ANIMATION_PATTERN	(3)			//�J�[�\��(��)

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMarker = NULL;	// �}�[�J�[�̃e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMarker = NULL;			// �}�[�J�[�̒��_�o�b�t�@�̃|�C���^
MARKER g_Marker;									// �}�[�J�[�̏��

int g_nCountersAnimationHnd;						//�J�[�\��(�R�}���̐؂�ւ�)
int g_nCountersAnimationCntHnd;						//�J�[�\��(�J�E���^�X�V)

//-----------------------------------------------------------------
// �}�[�J�[�̏���������
//-----------------------------------------------------------------
HRESULT InitMarker(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/hnd.png", &g_pTextureMarker);

	// �e���̏�����
	g_Marker.pos = D3DXVECTOR3(640.0f, 390.0f, 0.0f);
	g_Marker.posOld = g_Marker.pos;
	g_Marker.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Marker.fWidth = MARKER_SIZE;
	g_Marker.fHeight = MARKER_SIZE;
	g_Marker.state = MARKERSTATE_NORMAL;
	g_Marker.nCntPatternAnim = 0;
	g_Marker.bUse = false;

	//���_�o�b�t�@�̐���5
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4,		//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffMarker,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMarker->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Marker.pos.x - 0, g_Marker.pos.y + 50, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Marker.pos.x - 0, g_Marker.pos.y - 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Marker.pos.x + 50, g_Marker.pos.y + 50, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Marker.pos.x + 50, g_Marker.pos.y - 0, 0.0f);

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

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f + (float)g_Marker.nCntPatternAnim * 0.33f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (float)g_Marker.nCntPatternAnim * 0.33f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.33f + (float)g_Marker.nCntPatternAnim * 0.33f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.33f + (float)g_Marker.nCntPatternAnim * 0.33f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMarker->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �}�[�J�[�̏I������
//-----------------------------------------------------------------
void UninitMarker(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMarker != NULL)
	{
		g_pVtxBuffMarker->Release();
		g_pVtxBuffMarker = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureMarker != NULL)
	{
		g_pTextureMarker->Release();
		g_pTextureMarker = NULL;
	}
}

//-----------------------------------------------------------------
// �}�[�J�[�̍X�V����
//-----------------------------------------------------------------
void UpdateMarker(void)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;
	BLOCK *pBlock = GetBlock();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMarker->Lock(0, 0, (void**)&pVtx, 0);

	// �ʒu���̕ۑ�
	g_Marker.posOld = g_Marker.pos;

	// �ړ�����
	if (GetkeyboardTrgger(DIK_W) == true)
	{// ��ړ�
		g_Marker.pos.y -= 60.0f;
	}
	else if (GetkeyboardTrgger(DIK_S) == true)
	{// ���ړ�
		g_Marker.pos.y += 60.0f;
	}
	else if (GetkeyboardTrgger(DIK_D) == true)
	{// �E�ړ�
		g_Marker.pos.x += 60.0f;
	}
	else if (GetkeyboardTrgger(DIK_A) == true)
	{// ���ړ�
		g_Marker.pos.x -= 60.0f;
	}

	// ��ʊO�ɏo�Ȃ��悤�ɂ���
	if (g_Marker.pos.y < 150.0f)
	{// ��ԏ�ɓ��B�����Ƃ�����
		g_Marker.pos.y = 150.0f;
	}
	if (g_Marker.pos.y > SCREEN_HEIGHT - 30.0f)
	{// ��ԉ��ɓ��B�����Ƃ�����
		g_Marker.pos.y = SCREEN_HEIGHT - 30.0f;
	}
	if (g_Marker.pos.x <= 40.0f)
	{// ��ԍ��ɓ��B�����Ƃ�����
		g_Marker.pos.x = 40.0f;
	}
	if (g_Marker.pos.x >= SCREEN_WIDTH - 40.0f)
	{// ��ԉE�ɓ��B�����Ƃ�����
		g_Marker.pos.x = SCREEN_WIDTH - 40.0f;
	}

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Marker.pos.x - g_Marker.fWidth, g_Marker.pos.y + g_Marker.fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Marker.pos.x - g_Marker.fWidth, g_Marker.pos.y - g_Marker.fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Marker.pos.x + g_Marker.fWidth, g_Marker.pos.y + g_Marker.fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Marker.pos.x + g_Marker.fWidth, g_Marker.pos.y - g_Marker.fHeight, 0.0f);

	// �ړ��ʂ̌���(����)
	g_Marker.move.x = 0.0f;
	g_Marker.move.y = 0.0f;

	//�A�j���[�V�����̒��_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + (float)g_Marker.nCntPatternAnim * 0.33f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (float)g_Marker.nCntPatternAnim * 0.33f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.33f + (float)g_Marker.nCntPatternAnim * 0.33f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.33f + (float)g_Marker.nCntPatternAnim * 0.33f, 0.0f);

	pVtx[0].pos = D3DXVECTOR3(g_Marker.pos.x - 0, g_Marker.pos.y + 50, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Marker.pos.x - 0, g_Marker.pos.y - 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Marker.pos.x + 50, g_Marker.pos.y + 50, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Marker.pos.x + 50, g_Marker.pos.y - 0, 0.0f);
	
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMarker->Unlock();
}

//-----------------------------------------------------------------
// �}�[�J�[�̕`�揈��
//-----------------------------------------------------------------
void DrawMarker(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMarker, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̕`��
	pDevice->SetTexture(0, g_pTextureMarker);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);
}

//-----------------------------------------------------------------
// �}�[�J�[���̎擾
//-----------------------------------------------------------------
MARKER *GetMarker(void)
{
	return &g_Marker;
}