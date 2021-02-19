//--------------------------------------------------------------------------------
//
//	ライトの処理 [light.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "light.h"

//--------------------------------------------------------------------------------
//	マクロ定義
//--------------------------------------------------------------------------------
#define MAX_LIGHT	(3)			// ライトの最大数
#define LIGHT_X		(0.2f)		// ライトの方向X
#define LIGHT_Y		(-0.8f)		// ライトの方向Y
#define LIGHT_Z		(-0.4f)		// ライトの方向Z

//--------------------------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------------------------
D3DLIGHT9 g_alight[MAX_LIGHT];		// ライトの情報

//--------------------------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------------------------
HRESULT InitLight(void)
{
	
	LPDIRECT3DDEVICE9 pDevice;		// デバイスのポインタ

	D3DXVECTOR3 vecDir;				// 設定用方向ベクトル

	// デバイスの取得
	pDevice = GetDevice();

	// ライト0
	// ライトをクリアにする(ごみを取り除く)
	ZeroMemory(&g_alight[0], sizeof(D3DLIGHT9));

	// ライトの種類を設定
	g_alight[0].Type = D3DLIGHT_DIRECTIONAL;		// 垂直のライト

	// ライトの拡散光を設定
	g_alight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);

	// ライトの方向を設定
	vecDir = D3DXVECTOR3(LIGHT_X, LIGHT_Y, LIGHT_Z);
	D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化にする(これをすることでライトがいい感じになる)

	g_alight[0].Direction = vecDir;

	// ライトを設定する
	pDevice->SetLight(0, &g_alight[0]);				// 数字は何番目のライトかという意味

	// ライトを有効する(ライトのスイッチON!)
	pDevice->LightEnable(0, TRUE);


	// ライト1
	// ライトをクリアにする(ごみを取り除く)
	ZeroMemory(&g_alight[1], sizeof(D3DLIGHT9));

	// ライトの種類を設定
	g_alight[1].Type = D3DLIGHT_DIRECTIONAL;		// 垂直のライト

	// ライトの拡散光を設定
	g_alight[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);

	// ライトの方向を設定
	vecDir = D3DXVECTOR3(-0.1f, 0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化にする(これをすることでライトがいい感じになる)

	g_alight[1].Direction = vecDir;

	// ライトを設定する
	pDevice->SetLight(1, &g_alight[1]);				// 数字は何番目のライトかという意味

	// ライトを有効する(ライトのスイッチON!)
	pDevice->LightEnable(1, TRUE);


	// ライト2
	// ライトをクリアにする(ごみを取り除く)
	ZeroMemory(&g_alight[2], sizeof(D3DLIGHT9));

	// ライトの種類を設定
	g_alight[2].Type = D3DLIGHT_DIRECTIONAL;		// 垂直のライト

	// ライトの拡散光を設定
	g_alight[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ライトの方向を設定
	vecDir = D3DXVECTOR3(0.8f, -0.1f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化にする(これをすることでライトがいい感じになる)

	g_alight[2].Direction = vecDir;

	// ライトを設定する
	pDevice->SetLight(2, &g_alight[2]);				// 数字は何番目のライトかという意味

	// ライトを有効する(ライトのスイッチON!)
	pDevice->LightEnable(2, TRUE);
	// 値を返す
	return S_OK;							


	//	for (int nLight = 0; nLight < MAX_LIGHT; nLight++)
	//{
	//	// ライトをクリアにする(ごみを取り除く)
	//	ZeroMemory(&g_alight[nLight], sizeof(D3DLIGHT9));

	//	// ライトの種類を設定
	//	g_alight[nLight].Type = D3DLIGHT_DIRECTIONAL;		// 垂直のライト

	//	// ライトの拡散光を設定
	//	g_alight[nLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//	// ライトの方向を設定
	//	vecDir = D3DXVECTOR3(LIGHT_X, LIGHT_Y, LIGHT_Z);
	//	vecDir = D3DXVECTOR3(-0.1f, 0.8f, -0.4f);
	//	vecDir = D3DXVECTOR3(0.8f, -0.1f, 0.4f);
	//	D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化にする(これをすることでライトがいい感じになる)

	//	g_alight[nLight].Direction = vecDir;

	//	// ライトを設定する
	//	pDevice->SetLight(nLight, &g_alight[nLight]);				// 数字は何番目のライトかという意味

	//													// ライトを有効する(ライトのスイッチON!)
	//	pDevice->LightEnable(nLight, TRUE);

	//}
}

//--------------------------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------------------------
void UninitLight(void)
{

}

//--------------------------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------------------------
void UpdateLight(void)
{

}