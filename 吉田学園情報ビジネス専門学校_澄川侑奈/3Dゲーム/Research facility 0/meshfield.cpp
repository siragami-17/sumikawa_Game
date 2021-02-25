//--------------------------------------------------------------------------------
//
//	地面の処理 [meshfild.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "meshfild.h"		// 地面
#include "player.h"			// プレイヤー

//--------------------------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------------------------
#define MAX_VERTEX	(12)								// 頂点数
#define MAX_IDX		(22)								// インデックス数
#define MAX_SIZE	(500.0f)							// 地面のサイズ
#define MAX_SPEED	(2)									// プレイヤーの落ちる速度

//--------------------------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------------------------
Meshfild g_meshfild;									// 地面の情報

//--------------------------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------------------------
HRESULT InitMeshfild(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 変数宣言
	VERTEX_3D *pVtx;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/metal_00025.jpg", &g_meshfild.pTextureMeshfild);

	// 地面の構造体の初期化
	g_meshfild.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	g_meshfild.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
	bool bUse = false;									// 使用しているか

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * MAX_VERTEX,					// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,									// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_meshfild.pVtxBuffMeshfild,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_meshfild.pVtxBuffMeshfild->Lock(0, 0, (void**)&pVtx, 0);


		// 左から右設定
		// 頂点座標(X.Y.Z)
		pVtx[0].pos = D3DXVECTOR3(g_meshfild.pos.x - MAX_SIZE, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z + MAX_SIZE);
		pVtx[1].pos = D3DXVECTOR3(g_meshfild.pos.x + 0.0f, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z + MAX_SIZE);
		pVtx[2].pos = D3DXVECTOR3(g_meshfild.pos.x + MAX_SIZE, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z + MAX_SIZE);
		pVtx[3].pos = D3DXVECTOR3(g_meshfild.pos.x - MAX_SIZE, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z + 0.0f);
		pVtx[4].pos = D3DXVECTOR3(g_meshfild.pos.x + 0.0f, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z + 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_meshfild.pos.x + MAX_SIZE, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z + 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_meshfild.pos.x - MAX_SIZE, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z - MAX_SIZE);
		pVtx[7].pos = D3DXVECTOR3(g_meshfild.pos.x - 0.0f, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z - MAX_SIZE);
		pVtx[8].pos = D3DXVECTOR3(g_meshfild.pos.x + MAX_SIZE, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z - MAX_SIZE);
		pVtx[9].pos = D3DXVECTOR3(g_meshfild.pos.x - MAX_SIZE, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z - MAX_SIZE);
		pVtx[10].pos = D3DXVECTOR3(g_meshfild.pos.x - 0.0f, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z - MAX_SIZE);
		pVtx[11].pos = D3DXVECTOR3(g_meshfild.pos.x + MAX_SIZE, g_meshfild.pos.y + 0.0f, g_meshfild.pos.z - MAX_SIZE);

		// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[9].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[10].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[11].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラー設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// 頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(2.0, 0.0);
		pVtx[3].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[4].tex = D3DXVECTOR2(1.0, 1.0);
		pVtx[5].tex = D3DXVECTOR2(2.0, 1.0);
		pVtx[6].tex = D3DXVECTOR2(0.0, 2.0);
		pVtx[7].tex = D3DXVECTOR2(1.0, 2.0);
		pVtx[8].tex = D3DXVECTOR2(2.0, 2.0);
		pVtx[9].tex = D3DXVECTOR2(0.0, 3.0);
		pVtx[10].tex = D3DXVECTOR2(1.0, 3.0);
		pVtx[11].tex = D3DXVECTOR2(2.0, 3.0);
	


	// 頂点バッファをアンロックする
	g_meshfild.pVtxBuffMeshfild->Unlock();

	// インデックスバッファの生成
	if(FAILED(pDevice->CreateIndexBuffer(sizeof(WORD)*MAX_IDX,		//　必要なインデックス数
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_meshfild.pIdxBuffMeshField,
		NULL)))
	{
		return E_FAIL;
	}

	// 変数宣言
	WORD *pIdx;		// インデックス情報へのポインタ

	// インデックスバッファをロックし、番号データへのポインタを取得
	g_meshfild.pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	// 番号データの設定
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;
	pIdx[14] = 5;
	pIdx[15] = 9;
	pIdx[16] = 9;
	pIdx[17] = 6;
	pIdx[18] = 10;
	pIdx[19] = 7;
	pIdx[20] = 11;
	pIdx[21] = 8;

	// インデックスバッファをアンロックする
	g_meshfild.pIdxBuffMeshField->Unlock();

	return S_OK;
}

//--------------------------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------------------------
void UninitMeshfild(void)
{
	// テクスチャの開放(ポリゴン)
	if (g_meshfild.pTextureMeshfild != NULL)
	{
		g_meshfild.pTextureMeshfild->Release();
		g_meshfild.pTextureMeshfild = NULL;
	}

	// 頂点バッファの開放
	if (g_meshfild.pVtxBuffMeshfild != NULL)
	{
		g_meshfild.pVtxBuffMeshfild->Release();
		g_meshfild.pVtxBuffMeshfild = NULL;
	}
	
	// インデックスバッファの開放
	if (g_meshfild.pIdxBuffMeshField != NULL)
	{
		g_meshfild.pIdxBuffMeshField->Release();
		g_meshfild.pIdxBuffMeshField = NULL;
	}
}

//--------------------------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------------------------
void UpdateMeshfild(void)
{
	// プレイヤーの情報
	Player * pPlayer;
	pPlayer = GetPlayer();

	// 地面とプレイヤーの当たり判定
	if (g_meshfild.bUse == true)
	{// 地面があるとき
		if (pPlayer->pos.x - (150) < g_meshfild.pos.x + (500 * 6) &&		// 左
			pPlayer->pos.x + (150) > g_meshfild.pos.x - (500 * 6) &&		// 右
			pPlayer->pos.z - (150) < g_meshfild.pos.z + (500 * 6) &&		// 上
			pPlayer->pos.z + (150) > g_meshfild.pos.z - (500 * 6))			// 下
		{
			pPlayer->pos.y = 0;
		}
	}
//	else
//	{// 地面がない
//		pPlayer->pos.y -= MAX_SPEED;		// プレイヤーが落ちる
//	}





}

//--------------------------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------------------------
void DrawMeshfild(void)
{
	LPDIRECT3DDEVICE9 pDevice;			// デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;		// 計算用のマトリックス

	// デバイスの取得
	pDevice = GetDevice();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_meshfild.mtxWorld);

	// 向きを反映(y,x,z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshfild.rot.y, g_meshfild.rot.x, g_meshfild.rot.z);
	D3DXMatrixMultiply(&g_meshfild.mtxWorld, &g_meshfild.mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_meshfild.pos.x, g_meshfild.pos.y, g_meshfild.pos.z);
	D3DXMatrixMultiply(&g_meshfild.mtxWorld, &g_meshfild.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_meshfild.mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_meshfild.pVtxBuffMeshfild, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_meshfild.pIdxBuffMeshField);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンのテクスチャの設定
	pDevice->SetTexture(0, g_meshfild.pTextureMeshfild);
	//pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		MAX_VERTEX,										// 頂点数
		0,
		20);											// プリミティブ数
}

//--------------------------------------------------------------------------------
// 地面情報の取得
//--------------------------------------------------------------------------------
Meshfild *GetMeshfild(void)
{
	return &g_meshfild;		// 地面情報の先頭アドレスに返す
}