//--------------------------------------------------------------------------------
//
//	ウインドウの処理 [main.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_

// インクルードファイル	
#include <windows.h>
#include <XInput.h>		// Xinputに必要
#include "d3dx9.h"
#include "xaudio2.h"	// サウンド再生に必要5

// キーボード入力処理
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"

// ライブラリファイル
#pragma	comment(lib,"dinput8.lib")
#pragma comment(lib,"winmm.lib")

// ライブラリのリンク
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "xinput.lib")

//-------------------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------------------
#define SCREEN_WIDTH (1280)														// ゲーム画面の幅
#define SCREEN_HEIGHT (720)														// ゲーム画面の高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)				// テクスチャの座標(2D)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)		// テクスチャの座標(3D)
#define NUM_VERTEX (4)															// 頂点数
#define NUM_POLYGON (2)															// ポリゴン数(プリミティブ)

//-------------------------------------------------------------------------------
// 頂点フォーマットに合わせた構造体(2D)
//-------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 1.0で固定
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
}VERTEX_2D;

//-------------------------------------------------------------------------------
// 頂点フォーマットに合わせた構造体(3D)
//-------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線ベクトル
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
}VERTEX_3D;

//-------------------------------------------------------------------------------
// モードの種類
//-------------------------------------------------------------------------------
typedef enum
{
	MODE_TITLE = 0,					// タイトル画面
	MODE_TUTORIAL,					// チュートリアル画面
	MODE_BEGINNING,					// 初めの画面
	MODE_GAME,						// ゲーム
	MODE_RESULT,					// リザルト画面
	MODE_RANKING,					// ランキング画面
	MODE_MAX
}MODE;

//-------------------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE * GetMode(void);

#endif 