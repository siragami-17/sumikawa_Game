//--------------------------------------------------------------------------------
//
//	ブロックの処理 [block.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "block.h"			// ブロック
#include "manager.h"		// マネージャー
#include "renderer.h"		// レンダラ
#include "scene2D.h"		// 2Dポリゴン
#include "player.h"			// プレイヤー
#include "playerAI.h"		// プレイヤーAI
#include "game.h"			// ゲーム

//-------------------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------------------
#define MAX_COUNTER		(50)		// カウンター

//-------------------------------------------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CBlock::m_apTexture = {};

//-------------------------------------------------------------------------------
// テクスチャの読み込み
//-------------------------------------------------------------------------------
HRESULT CBlock::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block.png", &m_apTexture);

	return S_OK;
}

//-------------------------------------------------------------------------------
// テクスチャを破棄
//-------------------------------------------------------------------------------
void CBlock::Unload(void)
{
	//テクスチャの開放
	if (m_apTexture != NULL)
	{
		m_apTexture->Release();
		m_apTexture = NULL;
	}
}

//-------------------------------------------------------------------------------
// ブロックの生成
//-------------------------------------------------------------------------------
CBlock *CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 変数宣言
	CBlock *pBlock = NULL;

	if (pBlock == NULL)
	{// 中にデータが何もなかったら
		// 動的確保
		pBlock = new CBlock;

		if (pBlock != NULL)
		{// 中にデータがあったら
			// 初期化処理を呼び出す
			pBlock->Init(pos, size);

			// テクスチャを割り当てる
			pBlock->BindTexture(m_apTexture);
		}
	}
	// 値を返す
	return pBlock;
}

//-------------------------------------------------------------------------------
// コンストラク
//-------------------------------------------------------------------------------
CBlock::CBlock(PRIORITY nPriority) :CScene2D(nPriority)
{
	// 初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounter = 0;
}

//-------------------------------------------------------------------------------
// デストラクタ
//-------------------------------------------------------------------------------
CBlock::~CBlock()
{
}

//-------------------------------------------------------------------------------
// 初期化処理
//-------------------------------------------------------------------------------
HRESULT CBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// 代入
	m_size = scale;
	m_pos = pos;

	// 2Dポリゴンの初期化処理を呼び出す
	CScene2D::Init(pos, scale);

	// オブジェクトタイプを敵に設定する
	SetObjType(CScene::OBJTYPE_BLOCK);

	return S_OK;
}

//-------------------------------------------------------------------------------
// ポリゴンの終了処理
//-------------------------------------------------------------------------------
void CBlock::Uninit(void)
{
	// 2Dポリゴンの終了処理を呼び出す
	CScene2D::Uninit();
}

//-------------------------------------------------------------------------------
// ポリゴンの更新処理
//-------------------------------------------------------------------------------
void CBlock::Update(void)
{
	// 位置の取得
	D3DXVECTOR3 Pos;
	Pos = GetPosition();

	// プレイヤーの移動量取得
	D3DXVECTOR3 PlayerAIMove;
	CPlayerAI *pPlayerAI;
	pPlayerAI = CGame::GetPlayerAI();
	PlayerAIMove = pPlayerAI->GetMove();

	// 代入
	m_pos = Pos;

	// プレイヤーの過去情報
	pPlayerAI->GetPosOld();

	// ブロックとプレイヤーの当たり判定
	Collision();

	// ブロックの位置情報を2Dポリゴンに渡す
	CScene2D::SetPosition(Pos, m_size);
}

//-------------------------------------------------------------------------------
// ポリゴンの描画処理
//-------------------------------------------------------------------------------
void CBlock::Draw(void)
{
	// 2Dポリゴンの描画処理を呼び出す
	CScene2D::Draw();
}

//-------------------------------------------------------------------------------
// ブロックとオブジェクトの当たり判定
//-------------------------------------------------------------------------------
bool CBlock::Collision()
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			// シーン関係
			CScene *pScene;
			pScene = CScene::GetScene(nCntPriority, nCntScene);

			// ブロックとプレイヤーの当たり判定
			if (pScene != NULL)
			{// オブジェクトがNULLじゃなかったら
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				if (objType == CScene::OBJTYPE_PLAYER)
				{// ブロックに当たったオブジェクトタイプがプレイヤーだったら	
					// 変数宣言
					D3DXVECTOR3 PosPlayer;			// 位置
					D3DXVECTOR3 PosOldPlayer;		// 過去の位置
					D3DXVECTOR3 SizePlayer;			// 大きさ
					D3DXVECTOR3 MovePlayer;			// 移動量
					bool JumpPlayer;				// ジャンプしているか

					// プレイヤー関係
					CPlayer *pPlayer = NULL;
					pPlayer = (CPlayer*)pScene;		// キャスト

					// 代入
					PosPlayer = pPlayer->GetPosition();
					SizePlayer = pPlayer->GetSize();
					MovePlayer = pPlayer->GetMove();
					PosOldPlayer = pPlayer->GetPosOld();
					JumpPlayer = pPlayer->GetJump();

					if (PosPlayer.x + SizePlayer.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
						PosPlayer.x - SizePlayer.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
						PosPlayer.y + SizePlayer.y / 2.0f >= m_pos.y - m_size.y / 2.0f &&
						PosOldPlayer.y + SizePlayer.y / 2.0f <= m_pos.y - m_size.y / 2.0f)	// 過去のposがあたってない時
					{// プレイヤーが上から当たったら
						PosPlayer.y = m_pos.y - m_size.y / 2.0f - SizePlayer.y / 2.0f;

						MovePlayer.y = 0.0f;

						pPlayer->SetMove(MovePlayer);
						JumpPlayer = false;

						// ジャンプの情報を渡す
						pPlayer->SetJump(JumpPlayer);

						// プレイヤーの位置を設定
						pPlayer->SetPos(PosPlayer);
					}
				}

				if (objType == CScene::OBJTYPE_PLAYERAI)
				{// ブロックに当たったオブジェクトタイプがプレイヤーAIだったら	
					// 変数宣言
					D3DXVECTOR3 PosPlayerAI;			// 位置
					D3DXVECTOR3 PosOldPlayerAI;			// 過去の位置
					D3DXVECTOR3 SizePlayerAI;			// 大きさ
					D3DXVECTOR3 MovePlayerAI;			// 移動量

					// プレイヤー関係
					CPlayerAI *pPlayerAI = NULL;
					pPlayerAI = (CPlayerAI*)pScene;		// キャスト

					// 代入
					PosPlayerAI = pPlayerAI->GetPosition();
					SizePlayerAI = pPlayerAI->GetSize();
					MovePlayerAI = pPlayerAI->GetMove();
					PosOldPlayerAI = pPlayerAI->GetPosOld();

					if (PosPlayerAI.x + SizePlayerAI.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
						PosPlayerAI.x - SizePlayerAI.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
						PosPlayerAI.y + SizePlayerAI.y / 2.0f >= m_pos.y - m_size.y / 2.0f &&
						PosOldPlayerAI.y + SizePlayerAI.y / 2.0f <= m_pos.y - m_size.y / 2.0f)	// 過去のposがあたってない時
					{// プレイヤーAIが上から当たったら
						PosPlayerAI.y = m_pos.y - m_size.y / 2.0f - SizePlayerAI.y / 2.0f;

						MovePlayerAI.y = 0.0f;

						pPlayerAI->SetMove(MovePlayerAI);

						

						// プレイヤーAIの位置を設定
						pPlayerAI->SetPosition(PosPlayerAI, SizePlayerAI);

						return true;
					}
				}
			}
		}
	}
	return false;
}

//-------------------------------------------------------------------------------
// ブロックとオブジェクトの当たり判定
// posobject:オブジェクトの位置	sizeobject:オブジェクトの大きさ	posoldobject:オブジェクトの過去の位置
//-------------------------------------------------------------------------------
bool CBlock::Collision(D3DXVECTOR3 posobject, D3DXVECTOR3 posoldobject, D3DXVECTOR3 sizeobject)
{
	//// プレイヤーの移動量取得
	//D3DXVECTOR3 PlayerMove;
	//CPlayer *pPlayer;
	//pPlayer = CGame::GetPlayer();
	//PlayerMove = pPlayer->GetMove();

	//// プレイヤーAIの移動量取得
	//D3DXVECTOR3 PlayerAIMove;
	//CPlayerAI *pPlayerAI;
	//pPlayerAI = CGame::GetPlayerAI();
	//PlayerAIMove = pPlayerAI->GetMove();

	//// ブロックの情報
	//D3DXVECTOR3 posBlock = GetPosition();
	//D3DXVECTOR3 sizeBlock = m_size;

	//// ブロックに乗っているか
	//bool bLand = false;

	//for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	//{
	//	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	//	{
	//		// シーン関係
	//		CScene *pScene;
	//		pScene = CScene::GetScene(nCntPriority, nCntScene);

	//		// ブロックとプレイヤーの当たり判定
	//		if (pScene != NULL)
	//		{// オブジェクトがNULLじゃなかったら
	//			CScene::OBJTYPE objType;
	//			objType = pScene->GetObjType();

	//			if (objType == CScene::OBJTYPE_PLAYER)
	//			{// ブロックに当たったオブジェクトタイプがプレイヤーだったら					
	//				// プレイヤーとブロック(上)の当たり判定
	//				if (posobject.x + sizeobject.x / 2.0f > posBlock.x - sizeBlock.x / 2.0f &&
	//					posobject.x - sizeobject.x / 2.0f < posBlock.x + sizeBlock.x / 2.0f)
	//				{// ブロックの間にいるかどうか
	//					if (posobject.y + sizeobject.y / 2.0f > posBlock.y - sizeBlock.y / 2.0f &&
	//						posoldobject.y + sizeobject.y / 2.0f <= posBlock.y - sizeBlock.y / 2.0f)
	//					{// 過去のposBlockがあたってない時
	//						posobject.y = posBlock.y - BLOCK_Y / 2.0f - sizeobject.y / 2.0f;

	//						// プレイヤーの位置を設定
	//						pPlayer->SetPos(posobject);
	//						pPlayer->SetJump(false);
	//						pPlayer->SetMove(D3DXVECTOR3(PlayerAIMove.x, 0.0f, 0.0f));

	//						// プレイヤーAIの位置を設定
	//						pPlayerAI->SetPos(posobject);
	//						pPlayerAI->SetMove(D3DXVECTOR3(PlayerAIMove.x, 0.0f, 0.0f));

	//						// ブロックに乗っている
	//						bLand =  true;
	//					}
	//					else if (posobject.y - sizeobject.y / 2.0f < posBlock.y + sizeBlock.y / 2.0f &&
	//						posoldobject.y - sizeobject.y / 2.0f >= posBlock.y + sizeBlock.y / 2.0f)
	//					{// プレイヤーとブロック(下)の当たり判定
	//						posobject.y = posBlock.y + BLOCK_Y / 2.0f + sizeobject.y / 2.0f;

	//						// プレイヤーの位置を設定
	//						pPlayer->SetPos(posobject);

	//						pPlayer->SetMove(D3DXVECTOR3(PlayerMove.x, 0.0f, 0.0f));
	//					}
	//				}

	//				// プレイヤーとブロック(左)の当たり判定
	//				if (posobject.y + sizeobject.y / 2.0f > posBlock.y - sizeBlock.y / 2.0f &&
	//					posobject.y - sizeobject.y / 2.0f < posBlock.y + sizeBlock.y / 2.0f)
	//				{// ブロックの間にいるかどうか

	//					//posBlock.x += PlayerMove.x;

	//					if ((posobject.x + sizeobject.x / 2.0f) > (posBlock.x - sizeBlock.x / 2.0f) &&
	//						(posoldobject.x + sizeobject.x / 2.0f) <= (posBlock.x - sizeBlock.x / 2.0f) + PlayerMove.x)
	//					{// 過去のposBlockがあたってない時
	//						
	//						posobject.x = posBlock.x - BLOCK_X / 2.0f - sizeobject.x / 2.0f;
	//						posoldobject.x = posobject.x - PlayerMove.x;

	//						// プレイヤーの位置を設定
	//						pPlayer->SetPos(posobject);
	//						pPlayer->SetPosOld(posoldobject);
	//							
	//						pPlayer->SetMove(D3DXVECTOR3(0.0f, PlayerAIMove.y, 0.0f));
	//					}
	//					/*else if((posobject.x - sizeobject.x / 2.0f) > (posBlock.x + sizeBlock.x / 2.0f) &&
	//							(posoldobject.x - sizeobject.x / 2.0f) <= (posBlock.x + sizeBlock.x / 2.0f))
	//					{
	//						posobject.x = posBlock.x + BLOCK_X / 2.0f + sizeobject.x / 2.0f;

	//						// プレイヤーの位置を設定
	//						pPlayer->SetPos(posobject);
	//						pPlayer->SetMove(D3DXVECTOR3(0.0f, PlayerMove.y, 0.0f));		// 初期化
	//					}*/
	//				}
	//			}
	//		}
	//	}
	//}
	return false;
}