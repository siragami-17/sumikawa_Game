//--------------------------------------------------------------------------------
//
//	エフェクトの処理 [effect.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "effect.h"		// エフェクト

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define MAX_EFFECT			(256)						// エフェクトの最大数

#define MAX_EFFECT_X		(20.0f)						// X軸
#define MAX_EFFECT_Y		(20.0f)						// Y軸

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;		// バッファへのポインタ

LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;				// テクスチャへのポインタ

Effect g_aEffect[MAX_EFFECT];							// エフェクト情報

//-------------------------------------------------------------------------------
//	エフェクトの初期化処理
//-------------------------------------------------------------------------------
HRESULT InitEffect(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 変数宣言
	VERTEX_2D *pVtx;

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		// エフェクトの構造体の初期化
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 位置
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 移動
		g_aEffect[nCntEffect].size = D3DXVECTOR3(MAX_EFFECT_X, MAX_EFFECT_Y, 0.0f);		// サイズ
		g_aEffect[nCntEffect].color = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);				// カラー
		g_aEffect[nCntEffect].bUse = false;												// 使われているか
	}
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/star.png", &g_pTextureEffect);		// エフェクト画像

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,		// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		// 頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 0, g_aEffect[nCntEffect].pos.y + MAX_EFFECT_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 0, g_aEffect[nCntEffect].pos.y + 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + MAX_EFFECT_X, g_aEffect[nCntEffect].pos.y + MAX_EFFECT_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + MAX_EFFECT_X, g_aEffect[nCntEffect].pos.y + 0, 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラー設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		// 頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	エフェクトの終了処理
//-------------------------------------------------------------------------------
void UninitEffect(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}

	// テクスチャの開放
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
}

//-------------------------------------------------------------------------------
//	エフェクトの更新処理
//-------------------------------------------------------------------------------
void UpdateEffect(void)
{
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{// エフェクトが使われた時
			g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;	// 更新されるたびに動かす

			g_aEffect[nCntEffect].color.a -= 0.1f;						// 透明にする

			SetColor(g_aEffect[nCntEffect].color, nCntEffect);			// 反映

			SetVertexEffect(nCntEffect);

			// 寿命の処理
			if (g_aEffect[nCntEffect].color.a <= 0.0f)
			{// カラーのアルファ値が0.0f以下になった時
				g_aEffect[nCntEffect].bUse = false;						// エフェクトを完全に消す
			}
		}
	}
}

//-------------------------------------------------------------------------------
//	エフェクトの描画処理
//-------------------------------------------------------------------------------
void DrawEffect(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストーリに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// 複数化
		if (g_aEffect[nCntEffect].bUse == true)
		{// bUseがtrueの時描画する
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect);
			// エフェクトの描画
			pDevice->DrawPrimitive
			(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
				nCntEffect * 4,			// 描画を開始する頂点インデックス
				2);						// 描画するプリミティブ数
		}
	}
}

//-------------------------------------------------------------------------------
//	エフェクト情報の取得
//-------------------------------------------------------------------------------
Effect *GetEffect(void)
{
	return &g_aEffect[0];			// エフェクトの情報の先頭アドレスを返す
}

//-------------------------------------------------------------------------------
//	エフェクトの設定
//-------------------------------------------------------------------------------
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// 複数化
		if (g_aEffect[nCntEffect].bUse == false)
		{// 使っていない時
			g_aEffect[nCntEffect].pos = pos;										// 位置

			g_aEffect[nCntEffect].move = move;										// 移動量

			g_aEffect[nCntEffect].color = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);		// カラー

			g_aEffect[nCntEffect].bUse = true;										// 使っている

			break;
		}
	}
}

//-------------------------------------------------------------------------------
//	エフェクトの頂点座標
//-------------------------------------------------------------------------------
void SetVertexEffect(int nIdx)
{
	// 変数宣言
	float ShaikingMove = 0.0f;

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	// 弾の情報を次にうつす
	pVtx += nIdx * 4;

	// 頂点座標の設定	
	pVtx[0].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x, g_aEffect[nIdx].pos.y + g_aEffect[nIdx].size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x, g_aEffect[nIdx].pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x + g_aEffect[nIdx].size.x, g_aEffect[nIdx].pos.y + g_aEffect[nIdx].size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x + g_aEffect[nIdx].size.x, g_aEffect[nIdx].pos.y, 0.0f);

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//-------------------------------------------------------------------------------
//	エフェクトのカラー
//-------------------------------------------------------------------------------
void SetColor(D3DXCOLOR color, int nIdx)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点座標の設定	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	// カラーの情報を次にうつす
	pVtx += nIdx * 4;

	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	// 頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//-------------------------------------------------------------------------------
//	花火みたいなエフェクト
//	[引数]
//	pos			位置
//	speed		移動量
//	nNum		表示したい個数
//-------------------------------------------------------------------------------
void SetBom(D3DXVECTOR3 pos, float speed, int nNum)
{
	for (int nCntEffect = 0; nCntEffect < nNum; nCntEffect++)
	{// 複数化
		float fAngle = float(rand() % 314 / 100.0f)  - float(rand() % 314 / 100.0f) ;		// 角度をランダムする

		D3DXVECTOR3 move = D3DXVECTOR3(sinf(fAngle)*speed, cosf(fAngle)*speed, 0.0f);

	//D3DXVECTOR3 move;
	//if (nCntEffect == 0)
	//{
	//	move = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//}
	//else
	//{
	//	move = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	//
	//}
		//g_aEffect[0].move = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		//g_aEffect[1].move = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		//g_aEffect[2].move = D3DXVECTOR3(0.0f, 4.0f, 0.0f);
		//g_aEffect[3].move = D3DXVECTOR3(0.0f, 6.0f, 0.0f);
		//g_aEffect[4].move = D3DXVECTOR3(0.0f, 8.0f, 0.0f);
		//g_aEffect[5].move = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		//g_aEffect[6].move = D3DXVECTOR3(0.0f, 12.0f, 0.0f);
		//g_aEffect[7].move = D3DXVECTOR3(0.0f, -14.0f, 0.0f);

		SetEffect(pos, move);
	}
}