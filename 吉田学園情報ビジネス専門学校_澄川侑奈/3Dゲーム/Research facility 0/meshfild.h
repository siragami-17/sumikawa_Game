//--------------------------------------------------------------------------------
//
//	地面の処理 [meshfild.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _MESHFILD_H_
#define	_MESHFILD_H_

#include "main.h"

//--------------------------------------------------------------------------------
// 地面の構造体
//--------------------------------------------------------------------------------
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffMeshfild = NULL;		// ポリゴンの頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 pIdxBuffMeshField = NULL;		// インデックスのバッファのポインタ
	LPDIRECT3DTEXTURE9 pTextureMeshfild = NULL;				// テクスチャのポインタ

	D3DXVECTOR3 pos;								// 位置
	D3DXVECTOR3 rot;								// 法線ベクトル(向き)
	D3DXMATRIX mtxWorld;							// ワールドマトリックス

	bool bUse;												// 使用しているか

}Meshfild;

//--------------------------------------------------------------------------------
// プロトタイプ宣言
//--------------------------------------------------------------------------------
HRESULT InitMeshfild(void);
void UninitMeshfild(void);
void UpdateMeshfild(void);
void DrawMeshfild(void);

Meshfild *GetMeshfild(void);

#endif