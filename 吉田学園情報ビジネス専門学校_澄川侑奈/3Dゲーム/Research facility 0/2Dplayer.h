//--------------------------------------------------------------------------------
//
//	プレイヤーの処理 [2DPlayer.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _2DPLAYER_H_
#define	_2DPLAYER_H_

#include "main.h"

//--------------------------------------------------------------------------------
//	マクロ定義
//--------------------------------------------------------------------------------
#define MAX_PLAYER_SIZE_X		(168/4.5)		//プレイヤーの幅
#define MAX_PLAYER_SIZE_Y		(304/2.5)	//プレイヤーの高さ
#define MAX_PLAYER				(1)			//プレイヤーの人数

//--------------------------------------------------------------------------------
//	プレイヤーの状態列挙型
//--------------------------------------------------------------------------------
typedef enum
{
	PLAYERSTATE_NORMA = 0,	//通常状態
	PLAYERSTATE_DAMAGE,		//ダメージ状態
	PLAYERSTATE_MAX
}PLAYERSTATE;

//--------------------------------------------------------------------------------
//	プレイヤーの構造体
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		//現在の情報(位置)
	D3DXVECTOR3 posOld;		//古い情報(位置)
	D3DXVECTOR3 move;		//移動量
	PLAYERSTATE state;		//状態
	int nLife;				//消えるまでの長さ
	int nCunt;				//硬直時間
	int nCounterState;		//状態カウンタ
	float fWidth;			//幅
	float fHeight;			//高さ
	float f2DPlayerU;			//U
	float f2DPlayerV;			//V
	bool bMove;				//移動量
	bool bUse;				//使用しているかどうか
	bool bJump;				//ジャンプ中かどうか
	bool bGetKey;			//鍵を持っているか
	bool bFall;				//死亡フラグ
} PLAYER;

//-------------------------------------------------------------------------------
//プロトタイプ宣言
//-------------------------------------------------------------------------------
HRESULT Init2DPlayer(void);
void Uninit2DPlayer(void);
void Update2DPlayer(void);
void Draw2DPlayer(void);

void Move2DPlayer(void);
PLAYER * Get2DPlayer(void);

#endif
