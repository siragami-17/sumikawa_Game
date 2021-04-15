//--------------------------------------------------------------------------------
//
//	エフェクトの処理 [effect.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _EFFECT_H_
#define	_EFFECT_H_

#include "main.h"

//-------------------------------------------------------------------------------
//	エフェクトの構造体
//-------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 size;		// サイズ
	D3DXCOLOR color;		// カラー

	bool bUse;				// 使用しているか

}Effect;

//-------------------------------------------------------------------------------
//プロトタイプ宣言
//-------------------------------------------------------------------------------
HRESULT InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

Effect *GetEffect(void);								// エフェクトの情報
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move);		// エフェクトの設置(nNam=個数)
void SetVertexEffect(int nIdx);							// エフェクトの頂点座標

void SetColor(D3DXCOLOR color, int nIdx);				// セットカラー

void SetBom(D3DXVECTOR3 pos, float speed , int nNum);	// 花火みたいなエフェクトにするあれ

#endif		// 1回だけ読み込むようにする
