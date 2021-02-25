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
// 構造体
//--------------------------------------------------------------------------------
#define MOTION_MAX	(20)		//	最大数

//--------------------------------------------------------------------------------
// モーションタイプの列挙型
//--------------------------------------------------------------------------------
typedef enum
{
	MOTION_NONE = 0,
	MOTION_WORK,			// 歩く
	MOTION_ATTACK,			// アクション
	MOTION_JUMP,			// ジャンプ
}MOTION_STATE;

//--------------------------------------------------------------------------------
// キーの構造体
//--------------------------------------------------------------------------------
typedef struct
{
	float fPosKeyX;		// キーで設定する位置情報
	float fPosKeyY;		// キーで設定する位置情報
	float fPosKeyZ;		// キーで設定する位置情報
	float fRotKeyX;		// キーで設定する位置情報
	float fRotKeyY;		// キーで設定する位置情報
	float fRotKeyZ;		// キーで設定する位置情報

}Key;

//--------------------------------------------------------------------------------
// キー情報の構造体
//--------------------------------------------------------------------------------
typedef struct
{
	int nFrame;							// 再生フレーム
	Key aKey[MOTION_MAX];				// 各モデルキー要素
}Key_Info;

//--------------------------------------------------------------------------------
// モーションの構造体
//--------------------------------------------------------------------------------
typedef struct
{
	int nLoop;							// ループするか
	int nMaxKey;						// キーの総数
	Key_Info  aKeyInfo[MOTION_MAX];		// キー情報

}Motion_Info;

//--------------------------------------------------------------------------------
// モデルの構造体
//--------------------------------------------------------------------------------
typedef struct
{
	LPD3DXMESH pMesh;				// メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMat;			// マテリアルへのポインタ
	DWORD nNumMat;					// マテリアルの数
	D3DXVECTOR3 pos;				// 位置(オフセット)
	D3DXVECTOR3 rot;				// 向き
	D3DXVECTOR3 g_VtxMinModel;		// モデルの最小値
	D3DXVECTOR3	g_VtxMaxModel;		// モデルの最大値
	D3DXMATRIX mtxWorld;			// ワールドマトリックス
	int nIdModelParent;				// 親のモデルのインデックス
	int nIdxModelNum;				// モデルのインデックス

	char sModelFailName[256];		// モデルファイルの名前

	int nNumVtx;					// 頂点数
	DWORD sizeFVF;					// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;					// 頂点バッファへのポインタ
	D3DXMATERIAL *pMat;				// マテリアルデータのポインタ
	D3DXVECTOR3 vtx;				// バーテックス
	D3DXVECTOR3 vtxMax, vtxMin;		// プレイヤーの大きさ最大数,最小数

}Model;

//--------------------------------------------------------------------------------
// プレイヤーの構造体
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;							// 今の位置
	D3DXVECTOR3 posOld;							// 昔の位置
	D3DXVECTOR3 rot;							// 向き
	D3DXVECTOR3 size;							// サイズ
	D3DXVECTOR3 rotDest;						// 目的の向き
	D3DXVECTOR3 move;							// 移動量
	D3DXMATRIX mtxWorld;						// ワールドマトリックス

	Model aModel[14];							// モデル(パーツ)
	int nNumModel;								// モデル(パーツ)数

	MOTION_STATE motionType;					// モーションタイプ
	MOTION_STATE oldmotionType;					// 前回のモーションタイプ

	Motion_Info aMotionInfo[MOTION_MAX];		// モーション情報
	int nNumMotion;								// モーションカウンター

	int nNumKey;								// 現在のキー数

	bool bJump;									// ジャンプ中かどうか
	bool bGetKey;								// 鍵を持っているか

	int nIdx;									// 影

}Player;

//--------------------------------------------------------------------------------
// プロトタイプ宣言
//--------------------------------------------------------------------------------
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

Player *GetPlayer(void);

void MotionPlayer(MOTION_STATE motionType);		// モーション

void Setcollision(void);						// 床との当たり判定

#endif