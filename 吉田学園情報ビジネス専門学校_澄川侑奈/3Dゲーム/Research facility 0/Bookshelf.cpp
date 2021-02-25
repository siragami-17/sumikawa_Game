//--------------------------------------------------------------------------------
//
//	�{�I�̏��� [goal.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Bookshelf.h"			// �{�I
#include "fade.h"				// �t�F�[�h
#include "keyboard.h"			// �L�[�{�[�h

//-------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------
#define MAX_POLYGON	(1)			// �|���S����

#define MAX_BOOK_X	(208)		// �{�I�̕�
#define MAX_BOOK_Y	(142)		// �{�I�̍���
#define BOOK_X	(150)			// �{�I�̕�(�����蔻��)
#define BOOK_Y	(120)			// �{�I�̍���(�����蔻��)

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBookshelf = NULL;

LPDIRECT3DTEXTURE9 g_pTextureBookshelf = NULL;							//�{�I

Bookshelf g_Door;													//�{�I�̏��

//-------------------------------------------------------------------------------
//	�{�I�̏���������
//-------------------------------------------------------------------------------
HRESULT InitBookshelf(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ϐ��錾
	VERTEX_2D *pVtx;

	// �{�I�̍\���̂̏�����
	g_Door.pos = D3DXVECTOR3(500.0f, 420.0f, 0.0f);		// �ʒu
	g_Door.bUse = true;										// �g�p���Ă��邩�ǂ���

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/book.png", &g_pTextureBookshelf);		// �{�I

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffBookshelf,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBookshelf->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCunDoor = 0; nCunDoor < MAX_POLYGON; nCunDoor++)
	{
		switch (nCunDoor)
		{	// ���_���W
		case 0:
			pVtx[0].pos = D3DXVECTOR3(g_Door.pos.x , g_Door.pos.y + (MAX_BOOK_Y ), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Door.pos.x , g_Door.pos.y , 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Door.pos.x + (MAX_BOOK_X ), g_Door.pos.y + (MAX_BOOK_Y ), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Door.pos.x + (MAX_BOOK_X ), g_Door.pos.y, 0.0f);
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
	g_pVtxBuffBookshelf->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�{�I�̏I������
//-------------------------------------------------------------------------------
void UninitBookshelf(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBookshelf != NULL)
	{
		g_pVtxBuffBookshelf->Release();
		g_pVtxBuffBookshelf = NULL;
	}

	// �e�N�X�`���̊J��
	// �{�I
	if (g_pTextureBookshelf != NULL)
	{
		g_pTextureBookshelf->Release();
		g_pTextureBookshelf = NULL;
	}
}

//-------------------------------------------------------------------------------
//	�{�I�̍X�V����
//-------------------------------------------------------------------------------
void UpdateBookshelf(void)
{

}

//-------------------------------------------------------------------------------
//	�{�I�̕`�揈��
//-------------------------------------------------------------------------------
void DrawBookshelf(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBookshelf, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCunDoor = 0; nCunDoor < MAX_POLYGON; nCunDoor++)
	{
		switch (nCunDoor)
		{

		case 0:
			//�w�i�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBookshelf);
			break;

		}


		//�X�g�b�v�w�i�̕`��
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
			nCunDoor * 4,		// �`����J�n���钸�_�C���f�b�N�X
			NUM_POLYGON);			// �`�悷��v���~�e�B�u��
	}
}