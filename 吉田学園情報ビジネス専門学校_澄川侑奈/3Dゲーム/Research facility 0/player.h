//--------------------------------------------------------------------------------
//
//	プレイヤーの処理 [player.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _PLAYER_H_
#define	_PLAYER_H_

#include "main.h"

//--------------------------------------------------------------------------------
// モデルの構造体
//--------------------------------------------------------------------------------
typedef struct
{
	LPD3DXMESH pMesh;			// メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMat;		// マテリアルへのポインタ
	DWORD nNumMat;				// マテリアルの数
	D3DXVECTOR3 pos;			// 位置(オフセット)
	D3DXVECTOR3 rot;			// 向き
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	int nIdModelParent;			// 親のモデルのインデックス
}Model;

//--------------------------------------------------------------------------------
// プレイヤーの構造体
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;			// 今の位置
	D3DXVECTOR3 posOld;			// 昔の位置
	D3DXVECTOR3 rot;			// 向き
	D3DXVECTOR3 move;			// 移動量
	D3DXMATRIX mtxWorld;		// ワールドマトリックス

	bool bJump;				//ジャンプ中かどうか

	Model aModel[14];			// モデル(パーツ)
	int nNumModel;				// モデル(パーツ)数
}Player;

//--------------------------------------------------------------------------------
// プロトタイプ宣言
//--------------------------------------------------------------------------------
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

Player *GetPlayer(void);

#endif