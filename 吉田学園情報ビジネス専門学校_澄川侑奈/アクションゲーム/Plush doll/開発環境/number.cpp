//--------------------------------------------------------------------------------
//
//	�i���o�[���� [manager.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "number.h"			// �i���o�[
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_�����O
#include "scene2D.h"		// 2D�|���S��

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//�e�N�X�`���̍��W

//-------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//-------------------------------------------------------------------------------
// �R���X�g���N
//-------------------------------------------------------------------------------
CNumber::CNumber()
{
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CNumber::~CNumber()
{
}

//-------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-------------------------------------------------------------------------------
HRESULT CNumber::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &m_pTexture);

	return S_OK;
}

//-------------------------------------------------------------------------------
// �e�N�X�`����j��
//-------------------------------------------------------------------------------
void CNumber::Unload(void)
{
	//�e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//-------------------------------------------------------------------------------
// �i���o�[�̐���
//-------------------------------------------------------------------------------
CNumber *CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CNumber *pNumber = NULL;

	if (pNumber == NULL)
	{// NULL��������
	 // ���I�m��
		pNumber = new CNumber;

		if (pNumber != NULL)
		{// NULL����Ȃ�������
			pNumber->Init(pos, scale);
		}
	}

	return pNumber;
}

//-------------------------------------------------------------------------------
// ����������
//-------------------------------------------------------------------------------
HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4,					// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,						// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(pos.x - scale.x / 2.0f, pos.y + scale.y / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x + scale.x / 2.0f, pos.y + scale.y / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x - scale.x / 2.0f, pos.y - scale.y / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + scale.x / 2.0f, pos.y - scale.y / 2.0f, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
// �|���S���̏I������
//-------------------------------------------------------------------------------
void CNumber::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//-------------------------------------------------------------------------------
// �|���S���̍X�V����
//-------------------------------------------------------------------------------
void CNumber::Update(void)
{
}

//-------------------------------------------------------------------------------
// �|���S���̕`�揈��
//-------------------------------------------------------------------------------
void CNumber::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g�[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �e�N�X�`���̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,						// �`����J�n���钸�_�C���f�b�N�X
		2);						// �`�悷��v���~�e�B�u��
}

//-------------------------------------------------------------------------------
// �i���o�[�̐ݒ�
//-------------------------------------------------------------------------------
void CNumber::SetNumber(int nNumber)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �i���o�[�̏���
	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f*nNumber), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (0.1f*nNumber), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f + (0.1f*nNumber), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f*nNumber), 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}