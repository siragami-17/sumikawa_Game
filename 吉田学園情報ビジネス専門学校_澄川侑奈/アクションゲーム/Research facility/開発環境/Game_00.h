//--------------------------------------------------------------------------------
//
//	�X�e�[�W1�̏��� [Game_00.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _GAME_00_H_
#define	_GAME_00_H_

#include "main.h"

//-------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//-------------------------------------------------------------------------------
HRESULT InitGame_00(void);
void UninitGame_00(void);
void UpdateGame_00(void);
void DrawGame_00(void);
void SetStop(bool bStop);
void SetPause(bool bPause);
bool GetStop(void);
#endif