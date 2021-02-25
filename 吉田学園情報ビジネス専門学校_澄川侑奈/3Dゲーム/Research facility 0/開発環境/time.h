//--------------------------------------------------------------------------------
//
//	タイマーの処理 [time.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _TIME_H_
#define	_TIME_H_

#include "main.h"


//-------------------------------------------------------------------------------
// 構造体
//-------------------------------------------------------------------------------
typedef struct
{
	LPDIRECT3DTEXTURE9 pTextureTime = NULL;				//テクスチへのポインタ
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffTime = NULL;		//頂点バッファのポインタ
	D3DXVECTOR3 aTimepos[3];							//タイムの画像

	int nTime;											//現在のタイム
	int nCountTime;										//カウントタイム

}Time;

//-------------------------------------------------------------------------------
//プロトタイプ宣言
//-------------------------------------------------------------------------------
HRESULT InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
void SetVertexTime(int nidx, int nNumber);

Time *GetTime(void);

#endif