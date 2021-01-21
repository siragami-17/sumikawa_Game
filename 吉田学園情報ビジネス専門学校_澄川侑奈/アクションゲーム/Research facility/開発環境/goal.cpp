//--------------------------------------------------------------------------------
//
//	�S�[���̏��� [goal.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "goal.h"				// �S�[��
#include "Player.h"				// �v���C���[
#include "fade.h"				// �t�F�[�h
#include "Result.h"				// ���U���g
#include "keyboard.h"			// �L�[�{�[�h

//-------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------
#define MAX_POLYGON	(2)			// �|���S����
								   
#define MAX_DOOR_X	(310/3)		// ���̕�
#define MAX_DOOR_Y	(380/3)		// ���̍���
#define DOOR_X	(20)			// ���̕�(�����蔻��)
#define DOOR_Y	(20)			// ���̍���(�����蔻��)

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffdoor = NULL;

LPDIRECT3DTEXTURE9 g_pTexturedoor = NULL;							//��
LPDIRECT3DTEXTURE9 g_pTextureEnter= NULL;							//�G���^�[�L�[

DOOR g_Door;														//���̏��

//-------------------------------------------------------------------------------
//	�S�[���̏���������
//-------------------------------------------------------------------------------
HRESULT Initdoor(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); 

	// �ϐ��錾
	VERTEX_2D *pVtx;

	// ���̍\���̂̏�����
	g_Door.pos = D3DXVECTOR3(1100.0f, 240.0f, 0.0f);		// �ʒu
	g_Door.bUse = true;										// �g�p���Ă��邩�ǂ���

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/door_00.png", &g_pTexturedoor);		// ��
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Enter.png", &g_pTextureEnter);			// �G���^�[�L�[

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,						   
		FVF_VERTEX_2D,							// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,						   
		&g_pVtxBuffdoor,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffdoor->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCunDoor = 0; nCunDoor < MAX_POLYGON; nCunDoor++)
	{
		switch (nCunDoor)
		{	// ���_���W
		case 0:
			pVtx[0].pos = D3DXVECTOR3(g_Door.pos.x - (MAX_DOOR_X / 2), g_Door.pos.y + (MAX_DOOR_Y / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Door.pos.x - (MAX_DOOR_X / 2), g_Door.pos.y - (MAX_DOOR_Y / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Door.pos.x + (MAX_DOOR_X / 2), g_Door.pos.y + (MAX_DOOR_Y / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Door.pos.x + (MAX_DOOR_X / 2), g_Door.pos.y - (MAX_DOOR_Y / 2), 0.0f);
			break;

		case 1:
			pVtx[0].pos = D3DXVECTOR3(0  /2+1150,139/2+200,0.0f);
			pVtx[1].pos = D3DXVECTOR3(0  /2+1150,0  /2+200, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(161/2+1150,139/2+200, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(161/2+1150,0  /2+200, 0.0f);
			break;
		}
	
		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// ���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffdoor->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�S�[���̏I������
//-------------------------------------------------------------------------------
void Uninitdoor(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffdoor != NULL)
	{
		g_pVtxBuffdoor->Release();
		g_pVtxBuffdoor = NULL;
	}

	// �e�N�X�`���̊J��
	// ��
	if (g_pTexturedoor != NULL)
	{
		g_pTexturedoor->Release();
		g_pTexturedoor = NULL;
	}

	// �G���^�[�L�[
	if (g_pTextureEnter != NULL)
	{
		g_pTextureEnter->Release();
		g_pTextureEnter = NULL;
	}
}

//-------------------------------------------------------------------------------
//	�S�[���̍X�V����
//-------------------------------------------------------------------------------
void Updatedoor(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	PLAYER * pPlayer;

	int nFade = GetFade();

	//�v���C���[�̏��
	pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffdoor->Lock(0, 0, (void**)&pVtx, 0);

	//���ƃv���C���[�̓����蔻��
	if (g_Door.bUse == true)
	{	//�g�p���Ă��邩�ǂ���
		if (pPlayer->pos.x - (MAX_PLAYER_SIZE_X / 2) < g_Door.pos.x + (DOOR_X / 2) &&		//��
			pPlayer->pos.x + (MAX_PLAYER_SIZE_X / 2) > g_Door.pos.x - (DOOR_X / 2) &&		//�E
			pPlayer->pos.y - MAX_PLAYER_SIZE_Y < g_Door.pos.y + (DOOR_Y / 2) &&				//��
			pPlayer->pos.y > g_Door.pos.y - (DOOR_Y / 2))									//��
		{
			g_Door.bUse = true;

			if (nFade == FADE_NONE)
			{//�t�F�[�h���͓����Ȃ�
				if (pPlayer->bGetKey == true)
				{//���������Ă�����
					if (GetkeyboardTrgger(DIK_RETURN) == true)
					{// �G���^�[�L�[��������
						//���U���g��ʂɈړ�
						SetResult(true);
						SetFade(FADE_OUT, MODE_RESULT);
					}
	
				}
			}

		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffdoor->Unlock();
}

//-------------------------------------------------------------------------------
//	�S�[���̕`�揈��
//-------------------------------------------------------------------------------
void Drawdoor(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	PLAYER * pPlayer;

	//���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffdoor, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCunDoor = 0; nCunDoor < MAX_POLYGON; nCunDoor++)
	{
		switch (nCunDoor)
		{

		case 0:
			//�w�i�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturedoor);
			break;

			if(pPlayer->bGetKey == true)
			{

		case 1:
			//�w�i�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEnter);
			break;
			}
		}


		//�X�g�b�v�w�i�̕`��
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
			nCunDoor * 4,		// �`����J�n���钸�_�C���f�b�N�X
			NUM_POLYGON);			// �`�悷��v���~�e�B�u��
	}
}