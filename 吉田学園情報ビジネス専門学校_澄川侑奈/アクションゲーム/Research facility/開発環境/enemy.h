//--------------------------------------------------------------------------------
//
//	敵の処理 [enemy.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _ENEMY_H_
#define	_ENEMY_H_

#include "main.h"

//--------------------------------------------------------------------------------
//	マクロ定義
//--------------------------------------------------------------------------------
#define MAX_ENEMY			(256)			//敵の最大数
#define MAX_ENEMY_SIZE_X	(152/4)			//敵の幅
#define MAX_ENEMY_SIZE_Y	(284/2.5f)		//敵の高さ
#define ENEMMY_QUANTITY		(10)			//敵の個数
#define ENEMY_X				(120)			//敵のX
#define ENEMY_Y				(280)			//敵のY
#define DAMAGE_PAPER		(1)				//敵が与えるダメージ数

//--------------------------------------------------------------------------------
//	敵の列挙型
//--------------------------------------------------------------------------------
typedef enum
{
	ENEMYTYPE_000 = 0, 		//敵
	ENEMYTYPE_MAX,			//最大数
} ENEMYTYPE;

//--------------------------------------------------------------------------------
//	敵の状態列挙型
//--------------------------------------------------------------------------------
typedef enum
{
	ENEMYSTATE_NORMA = 0,	//通常状態
	ENEMYSTATE_DAMAGE,		//ダメージ状態
	ENEMYSTATE_MAX
}ENEMYSTATE;
//--------------------------------------------------------------------------------
//	敵の構造体
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		//現在の情報(位置)
	D3DXVECTOR3 posOld;		//古い情報(位置)
	D3DXVECTOR3 move;		//移動量
	ENEMYTYPE type;			//種類
	int nLife;				//消えるまでの長さ
	int nCunt;				//硬直時間
	float fWidth;			//幅
	float fHeight;			//高さ
	float fEnemyU;			//U
	float fEnemyV;			//V
	bool bMove;				//移動量
	bool bJump;				//ジャンプ中かどうか
	bool bUse;				//使用しているかどうか
} ENEMY;

//-------------------------------------------------------------------------------
//プロトタイプ宣言
//-------------------------------------------------------------------------------
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMYTYPE type, int nLife);
ENEMY * GetEnemy(void);
void SetVertexEnemy(int nCntEnemy);
bool HitEnemy(int nIdx, int nDamage);
#endif