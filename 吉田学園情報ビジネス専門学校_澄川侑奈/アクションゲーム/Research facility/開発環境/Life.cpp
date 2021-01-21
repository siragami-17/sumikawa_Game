//--------------------------------------------------------------------------------
//
//	ライフの処理 [Life.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Life.h"		// ライフ
#include "Player.h"		// プレイヤー

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define MAX_POLYGON			(3)			// ポリゴン数
										   
#define MAX_LIFE_X			(55)		// ライフの幅
#define MAX_LIFE_Y			(85)		// ライフの高さ
#define MAX_LIFE_COUNTER	(8)			// ライフのスピード
#define MAX_LIFE_PATTERN	(5)			// ライフの個数

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;

LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;						// ライフテクスチャ

int g_nCountersAnimationLife[MAX_POLYGON];						// ライフのコマ数切り替え
int g_nCountersAnimationCntLife[MAX_POLYGON];					// ライフのカウンタ更新

//-------------------------------------------------------------------------------
//	ライフ初期化処理
//-------------------------------------------------------------------------------
HRESULT InitLife(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 変数宣言
	VERTEX_2D *pVtx;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Life.png", &g_pTextureLife);		// ライフ

	//配列の初期化
	for (int nCutLife = 0; nCutLife < MAX_POLYGON; nCutLife++)
	{
		g_nCountersAnimationLife[nCutLife] = 0;											// ライフのコマ数切り替え
		g_nCountersAnimationCntLife[nCutLife] = 0;										// ライフのカウンタ更新
	}

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCutLife = 0; nCutLife < MAX_POLYGON; nCutLife++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3((float)nCutLife * 60, MAX_LIFE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((float)nCutLife * 60, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(MAX_LIFE_X + (float)nCutLife * 60, MAX_LIFE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(MAX_LIFE_X + (float)nCutLife * 60, 0, 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラー設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// 頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.2f, 1.0);
		pVtx[3].tex = D3DXVECTOR2(0.2f, 0.0);

		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	ライフの終了処理
//-------------------------------------------------------------------------------
void UninitLife(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}

	// テクスチャの開放
	// ライフ
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}
}

//-------------------------------------------------------------------------------
//	ライフの更新処理
//-------------------------------------------------------------------------------
void UpdateLife(void)
{
	// 変数宣言
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCutLife = 0; nCutLife < MAX_POLYGON; nCutLife++)
	{
		g_nCountersAnimationCntLife[nCutLife]++;

		// アニメーション
		if ((g_nCountersAnimationCntLife[nCutLife] %MAX_LIFE_COUNTER) == 0)										// アニメーションのカウント
		{
			g_nCountersAnimationLife[nCutLife] = (g_nCountersAnimationLife[nCutLife] + 1) % MAX_LIFE_PATTERN;	// アニメーションのコマ数

			// アニメーションの頂点情報の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + nCutLife * 60 + g_nCountersAnimationLife[nCutLife] * 0.2f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f + nCutLife * 60 + g_nCountersAnimationLife[nCutLife] * 0.2f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.2f + nCutLife * 60 + g_nCountersAnimationLife[nCutLife] * 0.2f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.2f + nCutLife * 60 + g_nCountersAnimationLife[nCutLife] * 0.2f, 0.0f);
		}
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();
}

//-------------------------------------------------------------------------------
//	ライフの描画処理
//-------------------------------------------------------------------------------
void DrawLife(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// プレイヤーの情報
	PLAYER * pPlayer = GetPlayer();

	// 頂点バッファをデータストーリに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCutLife = 0; nCutLife < MAX_POLYGON; nCutLife++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureLife);		// ライフ

		// ライフの描画
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,						// プリミティブの種類
			nCutLife * 4,							// 描画を開始する頂点インデックス
			NUM_POLYGON);							// 描画するプリミティブ数
	}
}