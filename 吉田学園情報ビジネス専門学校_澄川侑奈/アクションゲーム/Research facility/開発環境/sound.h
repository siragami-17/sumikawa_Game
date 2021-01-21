//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,			// BGM0(タイトル)
	SOUND_LABEL_BGM001,				// BGM1(チュートリアル)
	SOUND_LABEL_BGM002,				// BGM2(ゲーム)
	SOUND_LABEL_BGM003,				// BGM3(クリア)
	SOUND_LABEL_BGM004,				// BGM4(ゲームオーバー)
	SOUND_LABEL_SE_CHOICE,			// 選択
	SOUND_LABEL_SE_DAMAGE,			// ダメージ
	SOUND_LABEL_SE_GET,				// ゲット
	SOUND_LABEL_SE_JUMP,			// ジャンプ
	SOUND_LABEL_SE_OFF,				// オフ
	SOUND_LABEL_SE_ON,				// オン
	SOUND_LABEL_SE_WALK,			// 歩く


	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
