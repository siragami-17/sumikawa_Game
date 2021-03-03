//--------------------------------------------------------------------------------
//
//	ブロックの処理 [object.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _OBJECT_1_H_
#define	_OBJECT_1_H_

#include "main.h"

//--------------------------------------------------------------------------------
//	マクロ定義
//--------------------------------------------------------------------------------
#define MAX_OBJECT_1		(10)		// 読み込むパーツ数

//--------------------------------------------------------------------------------
// ブロックの構造体
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	D3DXVECTOR3 blockVec;			// ブロックとプレイヤーのベクトル
	D3DXVECTOR3 rot;				// 向き
	D3DXVECTOR3 move;				// 移動量
	D3DXVECTOR3 size;				// サイズ
	D3DXMATRIX mtxWorld;			// ワールドマトリックス

	float fWidth;					// 幅
	float fHeight;					// 高さ
	float fLength;					// 長さ
	float fRadius;					// 半径

	bool bUse;						// 使用しているかどうか

}Object_1;

//--------------------------------------------------------------------------------
// プロトタイプ宣言
//--------------------------------------------------------------------------------
HRESULT InitObject_1(void);
void UninitObject_1(void);
void UpdateObject_1(void);
void DrawObject_1(void);

Object_1 *Getobject_1(void);				// オブジェクトの情報

void SetObject_1(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);		// オブジェクトの設定

#endif