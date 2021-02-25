//--------------------------------------------------------------------------------
//
//	鍵の処理 [billboard.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Key.h"
#include "player.h"
#include "shadow.h"

//--------------------------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------------------------
#define MAX_KEY			(1)			// テクスチャの最大数
#define MAX_KEY_COUNTER	(10)		// 鍵のスピード
#define MAX_KEY_PATTERN	(5)			// 鍵の個数
#define MAX_KEY_X		(50/2)		// 鍵X
#define MAX_KEY_Y		(60/2)		// 鍵Y

//--------------------------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------------------------
KEY g_Key;											// 鍵の情報

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffKey = NULL;		// ビルボードの頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureKey = NULL;			// テクスチャのポインタ


D3DXMATRIX g_mtxWorldKey;							// ワールドマトリックス

int g_nCountersAnimationKey;						//鍵のコマ数切り替え
int g_nCountersAnimationCnt;						//鍵のカウンタ更新

//--------------------------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------------------------
HRESULT InitKey(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 変数宣言
	VERTEX_3D *pVtx;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Key.png", &g_pTextureKey);

	// 構造体の初期化
	g_Key.pos = D3DXVECTOR3(100.0f, 30.0f, 0.0f);				// 位置
	g_Key.keyVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 位置
	g_Key.fWidth = 0.0f;										// 幅
	g_Key.fHeight = 0.0f;										// 高さ
	g_Key.fLength = 0.0f;										// 長さ
	g_Key.fRadius = (float)MAX_KEY_X;							// 半径
	g_Key.nIdx = SetShadow(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		// 影
	g_Key.bUse = true;											// 使用しているかどうか

   // 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * 4,										// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,											// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffKey,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffKey->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標(X.Y.Z)
	pVtx[0].pos = D3DXVECTOR3(-MAX_KEY_X,MAX_KEY_Y , 0.0f);
	pVtx[1].pos = D3DXVECTOR3( MAX_KEY_X,MAX_KEY_Y , 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-MAX_KEY_X,-MAX_KEY_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3( MAX_KEY_X,-MAX_KEY_Y, 0.0f);

	// 法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// 頂点カラー設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// 頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.2f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffKey->Unlock();

	return S_OK;
}

//--------------------------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------------------------
void UninitKey(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffKey != NULL)
	{
		g_pVtxBuffKey->Release();
		g_pVtxBuffKey = NULL;
	}

	// テクスチャの開放(ビルボード)
	if (g_pTextureKey != NULL)
	{
		g_pTextureKey->Release();
		g_pTextureKey = NULL;
	}
}

//--------------------------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------------------------
void UpdateKey(void)
{
	VERTEX_3D *pVtx;

	// プレイヤーの情報
	Player * pPlayer = GetPlayer();

	// 影の情報
	Shadow * pShadow = GetShadow();

	// 鍵とプレイヤーの当たり判定
	if (g_Key.bUse == true)
	{// 使用しているかどうか
		g_Key.keyVec = pPlayer->pos - g_Key.pos;														// 鍵のベクトルを求める
		g_Key.fLength = sqrtf((g_Key.keyVec.x*g_Key.keyVec.x) + (g_Key.keyVec.z*g_Key.keyVec.z));		// 鍵とプレイヤーの距離

		if (g_Key.fLength < g_Key.fRadius)
		{// 長さが半径より小さくなった

			//鍵を消す
			g_Key.bUse = false;

			// 鍵をゲットした
			pPlayer->bGetKey = true;

			// 影を消す
			pShadow->bUse = false;
		}
	}

	// アニメーションの処理
	g_nCountersAnimationCnt++;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffKey->Lock(0, 0, (void**)&pVtx, 0);

	//アニメーション鍵
	if ((g_nCountersAnimationCnt %MAX_KEY_COUNTER) == 0)	//アニメーションのカウント
	{
		g_nCountersAnimationKey = (g_nCountersAnimationKey + 1) % MAX_KEY_PATTERN;	//アニメーションのコマ数

		//アニメーションの頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationKey * 0.2f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.2f + g_nCountersAnimationKey * 0.2f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationKey * 0.2f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.2f + g_nCountersAnimationKey * 0.2f, 1.0f);
	}

	SetPositionShadow(g_Key.nIdx, D3DXVECTOR3(g_Key.pos.x, 2.0f, g_Key.pos.z));

	//頂点バッファをアンロックする
	g_pVtxBuffKey->Unlock();
}

//--------------------------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------------------------
void DrawKey(void)
{
	LPDIRECT3DDEVICE9 pDevice;			// デバイスへのポインタ
	D3DXMATRIX mtxView;					// ビューマトリックスの取得
	D3DXMATRIX mtxRot, mtxTrans;		// 計算用のマトリックス

	// デバイスの取得
	pDevice = GetDevice();

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 120);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldKey);

	// ビューマトリックスの取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&g_mtxWorldKey, NULL, &mtxView);		// 逆行列を求める
	g_mtxWorldKey._41 = 0.0f;
	g_mtxWorldKey._42 = 0.0f;
	g_mtxWorldKey._43 = 0.0f;

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Key.pos.x, g_Key.pos.y, g_Key.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldKey, &g_mtxWorldKey, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldKey);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffKey, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ビルボードのテクスチャの設定
	pDevice->SetTexture(0, g_pTextureKey);

	if (g_Key.bUse == true)
	{
		// ビルボードの描画
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
			0,						// 描画を開始する頂点インデックス
			2);						// 描画するプリミティブ数
	}

	// アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}