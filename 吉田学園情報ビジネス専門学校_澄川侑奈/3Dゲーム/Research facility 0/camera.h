//--------------------------------------------------------------------------------
//
//	カメラの処理 [camera.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _CAMERA_H_
#define	_CAMERA_H_

#include "main.h"

//--------------------------------------------------------------------------------
// カメラの構造体
//--------------------------------------------------------------------------------
typedef struct 
{					
	D3DVIEWPORT9 viewport;			// ビューポート
	D3DXVECTOR3 posV;				// 現在の視点(見ている位置)
	D3DXVECTOR3 posVDest;			// 目的の視点
	D3DXVECTOR3 posR;				// 現在の注視点(中心としてみている)
	D3DXVECTOR3 posRDest;			// 目的の注視点
	D3DXVECTOR3 vecU;				// 上方向ベクトル
	D3DXVECTOR3 rot;				// カメラの向き
	D3DXMATRIX mtxProjection;		// プロジェクションマトリックス
	D3DXMATRIX mtxView;				// ビューマトリックス
}Camera;									

//--------------------------------------------------------------------------------
// プロトタイプ宣言
//--------------------------------------------------------------------------------
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int nldx);
Camera * GetCamera(void);

#endif