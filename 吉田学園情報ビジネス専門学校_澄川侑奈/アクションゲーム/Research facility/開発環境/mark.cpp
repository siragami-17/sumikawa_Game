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
#define MAX_POLYGON				(1)					//�|���S����

#define MARKER_SIZE				(50.0f)				// �}�[�J�[�̃T�C�Y

#define MOVE_MARKER				(3.0f)
#define PI_QUARTER				(D3DX_PI / 4)		// �~������1/4(�΂߈ړ��Ŏg��)

#define MAX_ANIMATION_COUNTER	(60.0f)				//�J�[�\��(�ړ�)
#define MAX_ANIMATION_PATTERN	(3)					//�J�[�\��(��)

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