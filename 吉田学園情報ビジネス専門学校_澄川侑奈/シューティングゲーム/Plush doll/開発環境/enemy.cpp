//--------------------------------------------------------------------------------
//
//	敵の処理 [enemy.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "enemy.h"			// 敵
#include "manager.h"		// マネージャー
#include "renderer.h"		// レンダラ
#include "scene2D.h"		// 2Dポリゴン
#include "game.h"			// ゲーム
#include "PlayerAI.h"		// プレイヤーAI

//-------------------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------------------
#define MAX_COUNTER		(50)		// カウンター

//-------------------------------------------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture = {};

//-------------------------------------------------------------------------------
// テクスチャの読み込み
//-------------------------------------------------------------------------------
HRESULT CEnemy::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy01.png", &m_apTexture);

	return S_OK;
}

//-------------------------------------------------------------------------------
// テクスチャを破棄
//-------------------------------------------------------------------------------
void CEnemy::Unload(void)
{
	//テクスチャの開放
	if (m_apTexture != NULL)
	{
		m_apTexture->Release();
		m_apTexture = NULL;
	}
}

//-------------------------------------------------------------------------------
// 敵の生成
//-------------------------------------------------------------------------------
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move, ENEMYTYPE type)
{
	// 変数宣言
	CEnemy *pEnemy = NULL;

	if (pEnemy == NULL)
	{// 中にデータが何もなかったら
		// 動的確保
		pEnemy = new CEnemy;

		if (pEnemy != NULL)
		{// 中にデータがあったら
			// 初期化処理を呼び出す
			pEnemy->Init(pos, scale, move);

			// 敵のテクスチャを割り当てる
			pEnemy->BindTexture(m_apTexture);
		}
	}
	// 値を返す
	return pEnemy;
}

//-------------------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------------------
CEnemy::CEnemy(PRIORITY nPriority) :CScene2D(nPriority)
{
	// 初期化
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Colr = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nCounter = 0;
	m_nCntColr = 0;
	m_State = ENEMY_NONE;
}

//-------------------------------------------------------------------------------
// デストラクタ
//-------------------------------------------------------------------------------
CEnemy::~CEnemy()
{
}

//-------------------------------------------------------------------------------
// 初期化処理
//-------------------------------------------------------------------------------
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move)
{
	// 初期化
	m_Colr = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nCounter = 0;
	m_nCntColr = 0;
	m_State = ENEMY_NONE;

	// 代入
	m_scale = scale;
	m_move = move;

	// 2Dポリゴンの初期化処理を呼び出す
	CScene2D::Init(pos, scale);

	// オブジェクトタイプを敵に設定する
	SetObjType(CScene::OBJTYPE_ENEMY);

	// 敵の状態を通常にする
	SetState(ENEMY::ENEMY_NORMAL);

	return S_OK;
}

//-------------------------------------------------------------------------------
// ポリゴンの終了処理
//-------------------------------------------------------------------------------
void CEnemy::Uninit(void)
{
	// 2Dポリゴンの終了処理を呼び出す
	CScene2D::Uninit();
}

//-------------------------------------------------------------------------------
// ポリゴンの更新処理
//-------------------------------------------------------------------------------
void CEnemy::Update(void)
{
	// 位置の取得
	D3DXVECTOR3 Pos;
	Pos = GetPosition();

	D3DXVECTOR3 move = MoveSearch(m_move.x);

	// 移動量加算
	Pos += move;

	// 敵の動きを加算
	Pos.y += MoveSnake();




// 敵の位置情報を2Dポリゴンに渡す
	CScene2D::SetPosition(Pos, m_scale);

	//// 敵の状態
	//switch (m_State)
	//{
	//	// 通常
	//case CEnemy::ENEMY_NORMAL:
	//	m_Colr = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//	// 情報を格納
	//	SetCol(m_Colr);
	//	break;

	//	// ダメージ
	//case CEnemy::ENEMY_DAMAGE:
	//	m_Colr = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	//	if (m_nCntColr %2 == 0)
	//	{// 点滅
	//		CEnemy::ENEMY_NORMAL;
	//	}

	//	// 情報を格納
	//	SetCol(m_Colr);
	//	break;
	//}
}

//-------------------------------------------------------------------------------
// ポリゴンの描画処理
//-------------------------------------------------------------------------------
void CEnemy::Draw(void)
{
	// 2Dポリゴンの描画処理を呼び出す
	CScene2D::Draw();

	//for (int nCnt = 0; nCnt < ENEMYTYPE_MAX-1; nCnt++)
	//{
	//	switch (nCnt)
	//	{
	//	case 0:
	//		SetInversion();
	//		break;

	//	case 1:
	//		SetTex();
	//		break;
	//	}
	//}

}

//-------------------------------------------------------------------------------
// 敵の移動処理
//-------------------------------------------------------------------------------
float CEnemy::MoveSnake(void)
{
	// 移動量切替
	if (m_nCounter >= MAX_COUNTER*2)
	{// カウンターが20以上だったら
		m_nCounter = 0;			// カウンターを0にする
	}

	if (m_nCounter >= MAX_COUNTER)
	{// カウンターが10以上になったら
		m_move.y = 0.5f;		// y軸方向に5.0f
	}
	else
	{// カウンターが10以下になったら
		m_move.y = -0.5f;		// y軸方向に-5.0f
	}

	if (m_move.y == 0)
	{// 敵の移動量が0の時
	 // 代入
		m_move.y = 10.0f;		// 移動量を10.0fにする
	}

	m_nCounter++;

	// 値を返す
	return m_move.y;
}

//-------------------------------------------------------------------------------
// 敵の探索処理
//-------------------------------------------------------------------------------
D3DXVECTOR3 CEnemy::MoveSearch(float move)
{
	// 位置の取得
	D3DXVECTOR3 Pos;
	Pos = GetPosition();

	// AI関係
	D3DXVECTOR3 PosPlayerAI;
	CPlayerAI * pPlayerAI;
	PosPlayerAI = pPlayerAI->GetPos();

	// 保存用
	D3DXVECTOR3 moveAI;

	// 相対値を求める
	D3DXVECTOR3 vec = PosPlayerAI - Pos;

	// 角度計算
	float fAtan = atan2f(vec.x, vec.y);

	if (move < 0.0f)
	{
		move *= -1.0f;
	}
	moveAI.x = move * (float)sin(fAtan);
	moveAI.y = move * (float)cos(fAtan);

	return moveAI;
}