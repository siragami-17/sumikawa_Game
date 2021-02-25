//--------------------------------------------------------------------------------
//
//	オブジェクトの処理 [block.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "object.h"			// オブジェクト
#include "keyboard.h"		// キー入力
#include "player.h"			// プレイヤー
#include "result.h"			// リザルト
#include "fade.h"			// フェード
#include "collision.h"		// 当たり判定

//--------------------------------------------------------------------------------
//	マクロ定義
//--------------------------------------------------------------------------------
#define MAX_SIZE_OBJECT_X	(400.0f)		// サイズ_x
#define MAX_SIZE_OBJECT_Y	(400.0f)		// サイズ_y
#define MAX_SIZE_OBJECT_Z	(10.0f)		// サイズ_z

//--------------------------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------------------------
LPD3DXMESH g_pMeshObject = NULL;				// メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatbject = NULL;			// マテリアルへのポインタ
D3DXMATRIX g_mtxWorldObject;					// ワールドマトリックス
DWORD g_nNumMatObject = 0;						// マテリアル数

Object g_object;					// オブジェクトの情報	
												
//--------------------------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------------------------
HRESULT InitObject(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


		// オブジェクト構造体の初期化
		g_object.pos = D3DXVECTOR3(0.0f, 0.0f, 490.0f);											// 位置
		g_object.blockVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										// 位置
		g_object.size = D3DXVECTOR3(MAX_SIZE_OBJECT_X, MAX_SIZE_OBJECT_Y, MAX_SIZE_OBJECT_Z);	// サイズ
		g_object.fWidth = 0.0f;																	// 幅
		g_object.fHeight = 0.0f;																// 高さ
		g_object.fLength = 0.0f;																// 長さ
		g_object.fRadius = 50.0f;																// 半径
		g_object.bUse = true;																	// 使用しているかどうか
	

	// Xファイルの読み込み
	// オブジェクト
	D3DXLoadMeshFromX("data/MODEL/wall.x",														// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatbject,																		// マテリアル(頂点情報)
		NULL,	
		&g_nNumMatObject,																		// マテリアル数
		&g_pMeshObject);																		// メッシュ(頂点情報)

	return S_OK;
}

//--------------------------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------------------------
void UninitObject(void)
{
	// メッシュの開放
	if (g_pMeshObject != NULL)
	{		 
		g_pMeshObject->Release();
		g_pMeshObject = NULL;
	}				  

	// マテリアルの開放
	if (g_pBuffMatbject != NULL)
	{	
		g_pBuffMatbject->Release();
		g_pBuffMatbject = NULL;
	}
}

//--------------------------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------------------------
void UpdateObject(void)
{

}

//--------------------------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------------------------
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;					// 計算用のマトリックス
	D3DMATERIAL9 matDef;							// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;								// マテリアルデータへのポインタ

	if (g_object.bUse == true)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_object.mtxWorld);

		// 向きを反映(y,x,z)
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_object.rot.y, g_object.rot.x, g_object.rot.z);
		D3DXMatrixMultiply(&g_object.mtxWorld, &g_object.mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_object.pos.x, g_object.pos.y, g_object.pos.z);
		D3DXMatrixMultiply(&g_object.mtxWorld, &g_object.mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_object.mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatbject->GetBufferPointer();

		for (unsigned int nCutMat = 0; nCutMat < g_nNumMatObject; nCutMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, NULL);

			// モデル(パーツ)の描画
			g_pMeshObject->DrawSubset(nCutMat);
		}

		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//--------------------------------------------------------------------------------
//	オブジェクト情報の取得
//--------------------------------------------------------------------------------
Object *Getobject(void)
{
	return &g_object;			// オブジェクト情報の先頭アドレスを返す
}

//--------------------------------------------------------------------------------
//	オブジェクト情報の取得
//--------------------------------------------------------------------------------
