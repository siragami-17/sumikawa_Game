//--------------------------------------------------------------------------------
//
//	2D�|���S������ [scene2D.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "renderer.h"			// �����_�����O
#include "scene2D.h"			// 2D�|���S��
#include "manager.h"			// �}�l�[�W���[
#include "Input_Keyboard.h"		// �L�[�{�[�h

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//�e�N�X�`���̍��W

//-------------------------------------------------------------------------------
// �R���X�g���N
//-------------------------------------------------------------------------------
CScene2D::CScene2D(PRIORITY nPriority):CScene(nPriority)
{
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CScene2D::~CScene2D()
{
}

//-------------------------------------------------------------------------------
// ����������
//-------------------------------------------------------------------------------
HRESULT CScene2D::Init(D3DXVECTOR3 pos,D3DXVECTOR3 scale)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 ,					// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							// ���_�t�H�[�}�b�g
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

	m_posPolygon = pos;
	m_scale = scale;

	pVtx[0].pos = D3DXVECTOR3(m_posPolygon.x - scale.x / 2.0f, m_posPolygon.y + scale.y / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_posPolygon.x + scale.x / 2.0f, m_posPolygon.y + scale.y / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_posPolygon.x - scale.x / 2.0f, m_posPolygon.y - scale.y / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_posPolygon.x + scale.x / 2.0f, m_posPolygon.y - scale.y / 2.0f, 0.0f);

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
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
// �|���S���̏I������
//-------------------------------------------------------------------------------
void CScene2D::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// �j������
	Release();
}

//-------------------------------------------------------------------------------
// �|���S���̍X�V����
//-------------------------------------------------------------------------------
void CScene2D::Update(void)
{

}

//-------------------------------------------------------------------------------
// �|���S���̕`�揈��
//-------------------------------------------------------------------------------
void CScene2D::Draw(void)
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
// �I�u�W�F�N�g�̐���
//-------------------------------------------------------------------------------
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CScene2D* pScene2D;
	pScene2D = new CScene2D;		// ���I�m��

	// NULL�`�F�b�N
	if (pScene2D != NULL)
	{// NULL����Ȃ�������
		pScene2D->Init(pos, scale);		// ������������ǂݍ���
	}
	// �l��Ԃ�
	return pScene2D;
}

//-------------------------------------------------------------------------------
// �ʒu��ݒ肷�鏈��
//-------------------------------------------------------------------------------
void CScene2D::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// ���
	m_posPolygon = pos;		
	m_scale = scale;

	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_posPolygon.x - scale.x / 2.0f, m_posPolygon.y + scale.y / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_posPolygon.x - scale.x / 2.0f, m_posPolygon.y - scale.y / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_posPolygon.x + scale.x / 2.0f, m_posPolygon.y + scale.y / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_posPolygon.x + scale.x / 2.0f, m_posPolygon.y - scale.y / 2.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �Ăяo��
	SetPos(pos);
	SetScale(scale);
}

//-------------------------------------------------------------------------------
// �v���C���[�̈ʒu���擾
//-------------------------------------------------------------------------------
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	// �l��Ԃ�(pos)
	return m_posPolygon;
}

//-------------------------------------------------------------------------------
// �e�N�X�`�����蓖�ď���
//-------------------------------------------------------------------------------
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//-------------------------------------------------------------------------------
// �e�N�X�`�����W�X�V����(����)
//-------------------------------------------------------------------------------
void CScene2D::SetTex(int m_nPatternAnim, int PatterMax)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + m_nPatternAnim*(1.0f / PatterMax), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + m_nPatternAnim*(1.0f / PatterMax), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f / PatterMax) + m_nPatternAnim*(1.0f / PatterMax), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / PatterMax) + m_nPatternAnim*(1.0f / PatterMax), 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//-------------------------------------------------------------------------------
// �e�N�X�`�����W�X�V����(�X�N���[��)
//-------------------------------------------------------------------------------
void CScene2D::SetTex(float TexU, float TexV)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �X�N���[���̏���
	pVtx[0].tex = D3DXVECTOR2(0.0f + TexU, 1.0f + TexV);
	pVtx[1].tex = D3DXVECTOR2(0.0f + TexU, 0.0f + TexV);
	pVtx[2].tex = D3DXVECTOR2(1.0f + TexU, 1.0f + TexV);
	pVtx[3].tex = D3DXVECTOR2(1.0f + TexU, 0.0f + TexV);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//-------------------------------------------------------------------------------
// �e�N�X�`�����W�X�V����(�v���C���[)
// CntPlace:�e�N�X�`���̂��܂���ꏊ	Tex:�e�N�X�`�����W(������)
//-------------------------------------------------------------------------------
void CScene2D::SetTex(D3DXVECTOR2 CntPlace, D3DXVECTOR2 Tex)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �X�N���[���̏���
	pVtx[0].tex = D3DXVECTOR2((CntPlace.x + 0.0f) / Tex.x, 1.0f + Tex.y);
	pVtx[1].tex = D3DXVECTOR2((CntPlace.x + 0.0f) / Tex.x, 0.0f + Tex.y);
	pVtx[2].tex = D3DXVECTOR2((CntPlace.x + 1.0f) / Tex.x, 1.0f + Tex.y);
	pVtx[3].tex = D3DXVECTOR2((CntPlace.x + 1.0f) / Tex.x, 0.0f + Tex.y);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//-------------------------------------------------------------------------------
// �J���[�̍X�V
//-------------------------------------------------------------------------------
void CScene2D::SetCol(D3DXCOLOR col)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//-------------------------------------------------------------------------------
// �e�N�X�`�����]
//-------------------------------------------------------------------------------
void CScene2D::SetInversion()
{
	// �ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//-------------------------------------------------------------------------------
// ���̃e�N�X�`��
//-------------------------------------------------------------------------------
void CScene2D::SetTex()
{
	// �ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

