//--------------------------------------------------------------------------------
//
//	�X�N���[���̏��� [scroll.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "scroll.h"			// �i���o�[
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_�����O

#include "scene.h"
#include "game.h"
#include "player.h"
#include "PlayerAI.h"
#include "block.h"
#include "bg.h"
#include "enemy.h"
#include "item.h"
#include "bg.h"

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// �R���X�g���N
//-------------------------------------------------------------------------------
CScroll::CScroll()
{

}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CScroll::~CScroll()
{
}

//-------------------------------------------------------------------------------
// �X�N���[����ۑ�����
//-------------------------------------------------------------------------------
void CScroll::UpdateMoveObject(D3DXVECTOR3 move)
{
	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		// �G�֌W
		CScene *pScene;
		pScene = CScene::GetScene(CScene::PRIORITY_ENEMY, nCntScene);

		// �u���b�N�֌W
		CScene *pSceneBlock;
		pSceneBlock = CScene::GetScene(CScene::PRIORITY_BLOCK, nCntScene);

		// �A�C�e���֌W
		CScene *pSceneItem;
		pSceneItem = CScene::GetScene(CScene::PRIORITY_ITEM, nCntScene);

		// �w�i�֌W
		CScene *pSceneBgBehig;
		CScene *pSceneBgFront;
		pSceneBgBehig = CScene::GetScene(CScene::PRIORITY_BGBEHING, nCntScene);
		pSceneBgFront = CScene::GetScene(CScene::PRIORITY_BGFRONT, nCntScene);

		// �G
		if (pScene != NULL)
		{
			CEnemy *pEnemy = (CEnemy*)pScene;

			D3DXVECTOR3 pos = pEnemy->GetPosition();
			D3DXVECTOR3 scale = pEnemy->GetScale();
			pos.x -= move.x;

			pEnemy->SetPosition(pos, scale);
		}


		if (!CItem::GetBItem())
		{// �S�[������ʂɏo�Ă�����
			// �u���b�N
			if (pSceneBlock != NULL)
			{
				CBlock *pBlock = (CBlock*)pSceneBlock;

				D3DXVECTOR3 pos = pBlock->GetPosition();
				D3DXVECTOR3 scale = pBlock->GetScale();
				pos.x -= move.x;

				pBlock->SetPosition(pos, scale);
			}

			// �A�C�e��
			if (pSceneItem != NULL)
			{
				CItem *pItem = (CItem*)pSceneItem;

				D3DXVECTOR3 pos = pItem->GetPosition();
				D3DXVECTOR3 scale = pItem->GetScale();
				pos.x -= move.x;

				pItem->SetPosition(pos, scale);
			}

			//// �A�C�e��
			//if (pSceneBgBehig != NULL)
			//{
			//	CBg *pBg = (CItem*)pSceneBgBehig;

			//	D3DXVECTOR3 pos = pBg->GetPosition();
			//	D3DXVECTOR3 scale = pBg->GetScale();
			//	pos.x -= move.x;

			//	pBg->SetPosition(pos, scale);
			//}
		}
	}
}