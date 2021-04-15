//-------------------------------------------------------------------
//
// ブロックヘッダー (block.h)
// Author:Yuna Sumikawa
//
//-------------------------------------------------------------------
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//-------------------------------------------------------------------
// ブロックの状態
//-------------------------------------------------------------------
typedef enum
{
	BLOCKSTATE_NORMAL = 0,	// 地面
	BLOCKSTATE_FLOAT,		// 浮いてる床
	BLOCKSTATE_RIFT,		// 上下に動く床
	BLOCKSTATE_MAX,
}BLOCKSTATE;

//-------------------------------------------------------------------
// ブロックの種類
//-------------------------------------------------------------------
typedef enum
{
	BLOCKTYPE_CATCH = 0,		// 掴める
	BLOCKTYPE_NOT_CATCH,		// 掴めない
	BLOCKTYPE_MAX,
}BLOCKTYPE;

//-------------------------------------------------------------------
// 衝突したのは何か
//-------------------------------------------------------------------
typedef enum
{
	COLLISIONINFO_PLAYER = 0,	// プレイヤー
	COLLISIONINFO_FRUITS,		// フルーツ
	COLLISIONINFO_ENEMY,		// 敵
	COLLISIONINFO_MAX,
}COLLISIONINFO;

//-------------------------------------------------------------------
// 構造体の定義
//-------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// 座標
	D3DXVECTOR3 posOld;	// 前の座標
	D3DXVECTOR3 move;	// 移動量
	int nTimer;			// 時間で折り返す
	float fWidth;		// 幅
	float fHeight;		// 高さ
	float fTexU;		// テクスチャ座標Uの値
	float fTexV;		// テクスチャ座標Vの値
	BLOCKSTATE state;	// ブロックの状態
	BLOCKTYPE type;		// ブロックの種類
	bool bChach;		// つかまれているどうか
	bool bUse;			// 使用しているかどうか
}BLOCK;

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitBlock(void);															// ブロックの初期化処理
void UninitBlock(void);																// ブロックの終了処理
void UpdateBlock(void);																// ブロックの更新処理
void DrawBlock(void);																// ブロックの描画処理
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight,
	float fTexU, float fTexV, BLOCKSTATE state, BLOCKTYPE type);					// ブロックの配置
void SetVertexBlock(int nIdx);														// 頂点座標の設定
BLOCK *GetBlock(void);																// ブロック情報の取得
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove,
	float fWidth, float fHeight, COLLISIONINFO info);								// ブロックの当たり判定
void LandBlock(int nCntBlock, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, float fHeight);	// 何のブロックの上に乗っているか
void CollisionBlockSide(D3DXVECTOR3 *pMove, COLLISIONINFO info);					// ブロックの横に当たったとき

void SetBlock(D3DXVECTOR3 pos,
	float fWidth,
	float fHeight,
	BLOCKTYPE type);

bool ColBlock(int nCntBlock);

#endif
