//--------------------------------------------------------------------------------
//
//	�|���S������ [scene.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "main.h"						// ���C��
#include "renderer.h"					// �����_�����O
#include "scene.h"						// �|���S��
#include "scene2D.h"					// 2D�|���S��
#include "manager.h"					// �}�l�[�W���[

//-------------------------------------------------------------------------------
// �ÓI�����o�֐�
//-------------------------------------------------------------------------------
CScene *CScene::m_apScene[PRIORITY_MAX][MAX_POLYGON] = {};		// ��ʂɕ\������I�u�W�F�N�g��
int CScene::m_nNumAll = 0;										// �ő吔

CScene *CScene::m_pTop[] = {};
CScene * CScene::m_pCur[] = {};

//-------------------------------------------------------------------------------
// �R���X�g���N
//-------------------------------------------------------------------------------
CScene::CScene(CScene::PRIORITY Priority)
{
	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		if (m_apScene[Priority][nCntScene] == NULL)
		{
			m_apScene[Priority][nCntScene] = this;
			m_nID = nCntScene;
			m_nNumAll++;
			m_Priority = Priority;
			break;
		}
	}

	//m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_Scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//// �ۑ�
	//m_Priority = Priority;

	//// �I�u�W�F�N�g�����X�g�ɒǉ�
	//if (m_pTop[m_Priority] != NULL)
	//{// NULL����Ȃ�
	//	// �V�����ł����I�u�W�F�N�g��CUR��n��
	//	m_pCur[m_Priority]->m_pNext = this;
	//	m_pNext = NULL;

	//	// �l�̌��
	//	this->m_pPrev = m_pCur[m_Priority];
	//}
	//else
	//{// NULL��������
	//	// �擪�Ɍ��݂̃|�C���^�����Ă�����
	//	m_pTop[m_Priority] = this;		// this(�l�|�C���^,���ψ����������܂���)

	//	// ������
	//	m_pNext = NULL;
	//	m_pPrev = NULL;
	//}
	//// CUR�̐ݒu
	//m_pCur[m_Priority] = this;
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CScene::~CScene()
{

}

////-------------------------------------------------------------------------------
//// ����������
////-------------------------------------------------------------------------------
//HRESULT CScene::Init(void)
//{
//}
//
////-------------------------------------------------------------------------------
//// �I������
////-------------------------------------------------------------------------------
//void CScene::Uninit(void)
//{
//}
//
////-------------------------------------------------------------------------------
//// �X�V����
////-------------------------------------------------------------------------------
//void CScene::Update(void)
//{
//}
//
////-------------------------------------------------------------------------------
//// �`�揈��
////-------------------------------------------------------------------------------
//void CScene::Draw(void)
//{
//}

//-------------------------------------------------------------------------------
// �S�Ă�j������
//-------------------------------------------------------------------------------
void CScene::ReleaseAll()
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{// NULL��������
			 // �I������
				if (nCntPriority != PRIORITY_FADE)
				{// �t�F�[�h�ȊO�j��
					m_apScene[nCntPriority][nCntScene]->Uninit();
					delete m_apScene[nCntPriority][nCntScene];
					m_apScene[nCntPriority][nCntScene] = NULL;
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------
// �S�Ă��X�V����
//-------------------------------------------------------------------------------
void CScene::UpdateAll()
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		if (CManager::GetPause() == true && nCntPriority == PRIORITY_PAUSE)
		{
			for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				if (m_apScene[nCntPriority][nCntScene] != NULL)
				{// NULL����Ȃ�������
				 // �`�揈��
					m_apScene[nCntPriority][nCntScene]->Update();
				}
			}
		}
		else if (CManager::GetPause() == false && nCntPriority != PRIORITY_PAUSE)
		{
			for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				if (m_apScene[nCntPriority][nCntScene] != NULL)
				{// NULL����Ȃ�������
				 // �`�揈��
					m_apScene[nCntPriority][nCntScene]->Update();
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------
// �S�Ă�`�悷��
//-------------------------------------------------------------------------------
void CScene::DrawAll()
{
	
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		if (CManager::GetPause() == true)
		{
			for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				if (m_apScene[nCntPriority][nCntScene] != NULL)
				{// NULL����Ȃ�������
				 // �`�揈��
					m_apScene[nCntPriority][nCntScene]->Draw();
				}
			}
		}
		else if (CManager::GetPause() == false && nCntPriority != PRIORITY_PAUSE)
		{
			for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				if (m_apScene[nCntPriority][nCntScene] != NULL)
				{// NULL����Ȃ�������
				 // �`�揈��
					m_apScene[nCntPriority][nCntScene]->Draw();
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------
// �j���̏���
//-------------------------------------------------------------------------------
void CScene::Release(void)
{

	if (m_apScene[m_Priority][m_nID] != NULL)
	{
		// �i�[
		int nID = m_nID;
		int nPriority = m_Priority;

		//�C���X�^���X�̔j��
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}

	//// �I�u�W�F�N�g(����)�����X�g����폜


	//// �I�u�W�F�N�g(����)��j��
	//delete this;
}

//-------------------------------------------------------------------------------
// �I�u�W�F�N�g�̎�ނ̐ݒ�
//-------------------------------------------------------------------------------
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//-------------------------------------------------------------------------------
// �`�揇�̐ݒ�
//-------------------------------------------------------------------------------
void CScene::SetPriority(CScene::PRIORITY priority)
{
	m_Priority = priority;
}

//-------------------------------------------------------------------------------
// �I�u�W�F�N�g�̎�ނ̎擾
//-------------------------------------------------------------------------------
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//-------------------------------------------------------------------------------
// �I�u�W�F�N�g�̎擾
//-------------------------------------------------------------------------------
CScene *CScene::GetScene(int nPriority,int nCntScene)
{
	return m_apScene[nPriority][nCntScene];
}

//-------------------------------------------------------------------------------
// �ʒu��ݒ�
//-------------------------------------------------------------------------------
void CScene::SetPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//-------------------------------------------------------------------------------
// �T�C�Y��ݒ�
//-------------------------------------------------------------------------------
void CScene::SetScale(D3DXVECTOR3 scale)
{
	m_Scale = scale;
}

//-------------------------------------------------------------------------------
// �ʒu���擾
//-------------------------------------------------------------------------------
D3DXVECTOR3 CScene::GetPos(void)
{
	return m_Pos;
}

//-------------------------------------------------------------------------------
// �T�C�Y���擾
//-------------------------------------------------------------------------------
D3DXVECTOR3 CScene::GetScale(void)
{
	return m_Scale;
}