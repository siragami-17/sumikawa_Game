//--------------------------------------------------------------------------------
//
//	オブジェクトの処理 [block.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "object_1.h"		// オブジェクト
#include "keyboard.h"		// キー入力
#include "player.h"			// プレイヤー
#include "result.h"			// リザルト
#include "fade.h"			// フェード
#include "collision.h"		// 当たり判定

//--------------------------------------------------------------------------------
//	マクロ定義
//--------------------------------------------------------------------------------
#define MAX_SIZE_OBJECT_1_X	(1000.0f)		// サイズ_x
#define MAX_SIZE_OBJECT_1_Y	(400.0f)		// サイズ_y
#define MAX_SIZE_OBJECT_1_Z	(10.0f)			// サイズ_z

//--------------------------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------------------------
LPD3DXMESH g_pMeshObject_1 = NULL;				// メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatbject_1 = NULL;			// マテリアルへのポインタ
D3DXMATRIX g_mtxWorldObject_1;					// ワールドマトリックス
DWORD g_nNumMatObject_1 = 0;						// マテリアル数

Object_1 g_object[MAX_OBJECT_1];					// オブジェクトの情報	
												
//--------------------------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------------------------
HRESULT InitObject_1(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntObject_1 = 0; nCntObject_1 < MAX_OBJECT_1; nCntObject_1++)
	{
		// オブジェクト構造体の初期化
		g_object[nCntObject_1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);												// 位置
		g_object[nCntObject_1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);												// 向き
		g_object[nCntObject_1].blockVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);											// 位置
		g_object[nCntObject_1].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// サイズ
		g_object[nCntObject_1].fWidth = 0.0f;																		// 幅
		g_object[nCntObject_1].fHeight = 0.0f;																	// 高さ
		g_object[nCntObject_1].fLength = 0.0f;																	// 長さ
		g_object[nCntObject_1].fRadius = 50.0f;																	// 半径
		g_object[nCntObject_1].bUse = false;																		// 使用しているかどうか
	}

	// Xファイルの読み込み
	// オブジェクト
	D3DXLoadMeshFromX("data/MODEL/Block_2.x",														// 読み込むXファイル名
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatbject_1,																		// マテリアル(頂点情報)
		NULL,	
		&g_nNumMatObject_1,																		// マテリアル数
		&g_pMeshObject_1);																		// メッシュ(頂点情報)

		// オブジェクトの設置
		SetObject_1(D3DXVECTOR3(100.0f, 0.0f, -420.0f),D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f), D3DXVECTOR3(15.0f, 400.0f, 150.0f));
		SetObject_1(D3DXVECTOR3(-100.0f, 0.0f, -420.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f), D3DXVECTOR3(15.0f, 400.0f, 150.0f));

		SetObject_1(D3DXVECTOR3(-170.0f, 0.0f, -350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(150.0f, 400.0f, 15.0f));

		

	return S_OK;
}

//--------------------------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------------------------
void UninitObject_1(void)
{
	// メッシュの開放
	if (g_pMeshObject_1 != NULL)
	{
		g_pMeshObject_1->Release();
		g_pMeshObject_1 = NULL;
	}


	// マテリアルの開放
	if (g_pBuffMatbject_1 != NULL)
	{
		g_pBuffMatbject_1->Release();
		g_pBuffMatbject_1 = NULL;
	}

}

//--------------------------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------------------------
void UpdateObject_1(void)
{

}

//--------------------------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------------------------
void DrawObject_1(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;					// 計算用のマトリックス
	D3DMATERIAL9 matDef;							// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;								// マテリアルデータへのポインタ

	for (int nCntObject_1 = 0; nCntObject_1 < MAX_OBJECT_1; nCntObject_1++)
	{
		if (g_object[nCntObject_1].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_object[nCntObject_1].mtxWorld);

			// 向きを反映(y,x,z)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_object[nCntObject_1].rot.y, g_object[nCntObject_1].rot.x, g_object[nCntObject_1].rot.z);
			D3DXMatrixMultiply(&g_object[nCntObject_1].mtxWorld, &g_object[nCntObject_1].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_object[nCntObject_1].pos.x, g_object[nCntObject_1].pos.y, g_object[nCntObject_1].pos.z);
			D3DXMatrixMultiply(&g_object[nCntObject_1].mtxWorld, &g_object[nCntObject_1].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_object[nCntObject_1].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatbject_1->GetBufferPointer();


			for (unsigned int nCutMat = 0; nCutMat < g_nNumMatObject_1; nCutMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, NULL);

				// モデル(パーツ)の描画
				g_pMeshObject_1->DrawSubset(nCutMat);
			}

			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//--------------------------------------------------------------------------------
//	オブジェクト情報の取得
//--------------------------------------------------------------------------------
Object_1 *Getobject_1(void)
{
	return &g_object[0];		// オブジェクト情報の先頭アドレスを返す
}

//--------------------------------------------------------------------------------
//	オブジェクト情報の取得
//--------------------------------------------------------------------------------
void SetObject_1(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	for (int nCntObject_1 = 0; nCntObject_1 < MAX_OBJECT_1; nCntObject_1++)
	{
		if (g_object[nCntObject_1].bUse == false)
		{// オブジェクトを使っていないとき
			g_object[nCntObject_1].pos = pos;

			g_object[nCntObject_1].rot = rot;

			g_object[nCntObject_1].size = size;

			g_object[nCntObject_1].bUse = true;

			return;
		}
	}
}