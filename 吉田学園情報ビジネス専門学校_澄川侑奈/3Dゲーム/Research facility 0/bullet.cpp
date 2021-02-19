//--------------------------------------------------------------------------------
//
//	弾の処理 [bullet.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "keyboard.h"								// キーボード
#include "bullet.h"									// 弾
#include "player.h"									// プレイヤー

//--------------------------------------------------------------------------------
//	マクロ定義
//--------------------------------------------------------------------------------
#define MAX_BULLET			(256)					// 弾の最大数
#define MAX_BULLET_SIZE_X	(10)					// 弾の幅
#define MAX_BULLET_SIZE_Y	(10)					// 弾の高さ
#define MAX_SPEED			(10)					// 弾の速さ

//--------------------------------------------------------------------------------
//	弾の構造体
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXMATRIX mtxWorldBullet;						// ワールドマトリックス
	D3DXVECTOR3 pos;								// 位置
	D3DXVECTOR3 move;								// 移動量
	D3DXVECTOR3 rot;								// 向き
	int nLife;										// 消えるまでの長さ
	bool bUse;										// 使用しているかどうか
} BULLET;

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			// 弾のテクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBullet = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;

BULLET g_aBullet[MAX_BULLET];						// 弾の情報	

//-------------------------------------------------------------------------------
//	初期化処理
//-------------------------------------------------------------------------------
HRESULT InitBullet(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 変数宣言
	VERTEX_3D *pVtx;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet000.png", &g_pTextureBullet);

	// 弾情報の初期化
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * 4 * MAX_BULLET,		// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,							// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// 頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_BULLET_SIZE_X, g_aBullet[nCntBullet].pos.y + MAX_BULLET_SIZE_Y, g_aBullet[nCntBullet].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_BULLET_SIZE_X, g_aBullet[nCntBullet].pos.y + MAX_BULLET_SIZE_Y, g_aBullet[nCntBullet].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_BULLET_SIZE_X, g_aBullet[nCntBullet].pos.y - MAX_BULLET_SIZE_Y, g_aBullet[nCntBullet].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_BULLET_SIZE_X, g_aBullet[nCntBullet].pos.y - MAX_BULLET_SIZE_Y, g_aBullet[nCntBullet].pos.z);

		// 法線ベクトルの設定(見ている方向)
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
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	終了処理
//-------------------------------------------------------------------------------
void UninitBullet(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	// テクスチャの開放(弾)
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}

//-------------------------------------------------------------------------------
//	更新処理
//-------------------------------------------------------------------------------
void UpdateBullet(void)
{
	// 変数宣言
	BULLET *pBullet;
	pBullet = &g_aBullet[0];

	// プレイヤーの情報
	Player * pPlayer;
	pPlayer = GetPlayer();

	// スペースキーを押した
	if (GetkeyboardPress(DIK_SPACE) == true)
	{
		SetBullet(pPlayer->pos, D3DXVECTOR3(sinf(pPlayer->rot.y)*MAX_SPEED, 0.0f, cosf(pPlayer->rot.y)*MAX_SPEED), 100);		// ),100)の100はライフ
	}

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			// 位置の更新
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			// 寿命チェック　
			g_aBullet[nCntBullet].nLife--;

			// 弾が画面外に行ったら消す処理
			if (SCREEN_HEIGHT > g_aBullet[nCntBullet].pos.z ||
				SCREEN_WIDTH > g_aBullet[nCntBullet].pos.x ||
				g_aBullet[nCntBullet].pos.z < 0 ||
				g_aBullet[nCntBullet].pos.x < 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}

		}
	}
}

//-------------------------------------------------------------------------------
//	弾の描画処理
//-------------------------------------------------------------------------------
void DrawBullet(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxView;												// ビューマトリックスの取得
	D3DXMATRIX mtxRot, mtxTrans;									// 計算用のマトリックス

	// アルファテストの有効/無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			// 有効にする

	// アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);		// より大きい

	// アルファ値の参照値
	pDevice->SetRenderState(D3DRS_ALPHAREF,120);

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorldBullet);

			// ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_aBullet[nCntBullet].mtxWorldBullet, NULL, &mtxView);		// 逆行列を求める
			g_aBullet[nCntBullet].mtxWorldBullet._41 = 0.0f;
			g_aBullet[nCntBullet].mtxWorldBullet._42 = 0.0f;
			g_aBullet[nCntBullet].mtxWorldBullet._43 = 0.0f;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorldBullet, &g_aBullet[nCntBullet].mtxWorldBullet, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorldBullet);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);

			// ポリゴンの描画
			pDevice->DrawPrimitive
			(D3DPT_TRIANGLESTRIP,			// プリミティブの種類
				nCntBullet * NUM_VERTEX,	// 描画を開始する頂点インデックス
				NUM_POLYGON);				// 描画するプリミティブ数
		}
	}
	// ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// アルファテストの有効/無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_ALWAYS);

	// アルファ値の参照値
	pDevice->SetRenderState(D3DRS_ALPHAREF,0x00);
}

//-------------------------------------------------------------------------------
//	弾の設定
//-------------------------------------------------------------------------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	//変数宣言
	BULLET * pBullet;
	pBullet = &g_aBullet[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{
			//位置
			pBullet->pos = pos;

			//移動量
			pBullet->move = move;

			//寿命
			pBullet->nLife = nLife;

			//使用しているか
			pBullet->bUse = true;

			break;
		}
	}
}