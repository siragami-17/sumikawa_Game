//--------------------------------------------------------------------------------
//
//	敵の処理 [enemy.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "enemy.h"
#include "block.h"
#include "Player.h"

//--------------------------------------------------------------------------------
//	グローバル変数
//--------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_apTextureEnemy[ENEMYTYPE_MAX] = {};	//テクスチへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;				//頂点バッファのポインタ
ENEMY g_aEnemy[MAX_ENEMY];									//敵の情報
D3DXVECTOR3 g_posAnimationEnemy;							//X,Y,Zを決める
int g_nCountersAnimationEnemy;								//プレイヤー(コマ数の切り替え)
int g_nCountersAnimationCntEnemy;							//プレイヤー(カウンタ更新)
int g_nCountersAnimationCunEnemy;							//カウント制御(カウンタ更新を遅くする)

//-------------------------------------------------------------------------------
//	敵の初期化処理
//-------------------------------------------------------------------------------
HRESULT InitEnemy(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy_00.png", &g_apTextureEnemy[ENEMYTYPE_000]);	//敵

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//現在の情報(位置)
		g_aEnemy[nCntEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//古い情報(位置)
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
		g_aEnemy[nCntEnemy].nLife = 0;										//消えるまでの長さ
		g_aEnemy[nCntEnemy].nCunt = 0;										//硬直時間
		g_aEnemy[nCntEnemy].fWidth = MAX_ENEMY_SIZE_X;						//幅
		g_aEnemy[nCntEnemy].fHeight = MAX_ENEMY_SIZE_Y;						//高さ
		g_aEnemy[nCntEnemy].fEnemyU = 0;									//U
		g_aEnemy[nCntEnemy].fEnemyV = 0;									//V
		g_aEnemy[nCntEnemy].bMove = false;									//移動量
		g_aEnemy[nCntEnemy].type = ENEMYTYPE_000;							//種類
		g_aEnemy[nCntEnemy].bJump;											//ジャンプ中かどうか
		g_aEnemy[nCntEnemy].bUse = false;									//使用しているかどうか

		//敵がスタートする位置
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(500.0f, 650.0f, 0.0f);
	}

	//頂点情報の設定
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL)))
	{
		return E_FAIL;
	}

	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//敵の頂点座標の設定
		SetVertexEnemy(nCntEnemy);

		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE_X, g_aEnemy[nCntEnemy].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE_X, g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE_X, g_aEnemy[nCntEnemy].pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE_X, g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE_Y, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.5);
		pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.25, 0.5);
		pVtx[3].tex = D3DXVECTOR2(0.25, 0.0);

		pVtx += NUM_VERTEX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	終了処理
//-------------------------------------------------------------------------------
void UninitEnemy(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}

	//テクスチャの開放(かたす)
	for (int nCntEnemy = 0; nCntEnemy < ENEMYTYPE_MAX; nCntEnemy++)
	{
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}
}

//-------------------------------------------------------------------------------
//	更新処理
//-------------------------------------------------------------------------------
void UpdateEnemy(void)
{
	//変数宣言
	VERTEX_2D *pVtx;
	BLOCK * pBlock;
	PLAYER * pPlayer;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//ブロックの情報をもらう
	pBlock = GetBlock();

	//プレイヤーの情報をもらう
	pPlayer = GetPlayer();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pBlock++)
	{//ブロックを増やす
		if (pBlock->bUse == true)
		{//ブロックがある
			if (g_aEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE_X) < pBlock->pos.x + pBlock->fWidth &&		//ブロックの右端
				g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE_X) > pBlock->pos.x)							//ブロックの左端
			{//自機のX軸がブロック左右に振れた時
				if (g_aEnemy[nCntEnemy].posOld.y <= pBlock->pos.y)
				{//上から自機がブロックに当たる判定
					if (g_aEnemy[nCntEnemy].pos.y > pBlock->pos.y)
					{//ブロックの上に乗った
						g_aEnemy[nCntEnemy].pos.y = pBlock->pos.y;
						g_aEnemy[nCntEnemy].move.y = 0.0f;		//重力の初期化
					}
				}
				else if (g_aEnemy[nCntEnemy].posOld.y - MAX_ENEMY_SIZE_Y >= pBlock->pos.y + pBlock->fHeight)
				{//下の当たり判定
					if (g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE_Y < pBlock->pos.y + pBlock->fHeight)
					{//ブロックに当たった
						g_aEnemy[nCntEnemy].pos.y = pBlock->pos.y + pBlock->fHeight + MAX_ENEMY_SIZE_Y;
						g_aEnemy[nCntEnemy].move.y = 1.0f;		//重力の初期化
					}
				}
			}

			if (g_aEnemy[nCntEnemy].pos.y - (MAX_ENEMY_SIZE_Y) < pBlock->pos.y + pBlock->fHeight &&		//ブロックの下端プレイヤーの上端
				g_aEnemy[nCntEnemy].pos.y > pBlock->pos.y)													//ブロックの上端
			{//自機のX軸がブロック左右に振れた時
				if (g_aEnemy[nCntEnemy].posOld.x + MAX_ENEMY_SIZE_X <= pBlock->pos.x)
				{//左の当たり判定
					if (g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE_X > pBlock->pos.x)
					{//ブロックに当たった
						g_aEnemy[nCntEnemy].pos.x = pBlock->pos.x - MAX_ENEMY_SIZE_X;
						g_aEnemy[nCntEnemy].move.x = 0.0f;		//重力の初期化
					}
				}
				else if (g_aEnemy[nCntEnemy].posOld.x - MAX_ENEMY_SIZE_X >= pBlock->pos.x + pBlock->fWidth)
				{//右の当たり判定
					if (g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE_X < pBlock->pos.x + pBlock->fWidth)
					{//ブロックに当たった
						g_aEnemy[nCntEnemy].pos.x = pBlock->pos.x + pBlock->fWidth + MAX_ENEMY_SIZE_X;
						g_aEnemy[nCntEnemy].move.x = 0.0f;		//重力の初期化
					}
				}
				//頂点座標
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE_X, g_aEnemy[nCntEnemy].pos.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE_X, g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE_X, g_aEnemy[nCntEnemy].pos.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE_X, g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE_Y, 0.0f);
			}
		}

		if ((g_nCountersAnimationCunEnemy % 5) == 0 && g_aEnemy[nCntEnemy].bJump == false && g_aEnemy[nCntEnemy].bMove == true)//%○は割る数)==○はあまり
		{//カウント制御
			g_nCountersAnimationCntEnemy++;

			//アニメーションの頂点情報の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationEnemy * 0.25f, 0.5f + g_aEnemy[nCntEnemy].fEnemyV);//+ g_aEnemy[nCntEnemy].fEnemyVをたすことで左右ができる
			pVtx[1].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationEnemy * 0.25f, 0.0f + g_aEnemy[nCntEnemy].fEnemyV);
			pVtx[2].tex = D3DXVECTOR2(0.25f + g_nCountersAnimationEnemy * 0.25f, 0.5f + g_aEnemy[nCntEnemy].fEnemyV);
			pVtx[3].tex = D3DXVECTOR2(0.25f + g_nCountersAnimationEnemy * 0.25f, 0.0f + g_aEnemy[nCntEnemy].fEnemyV);
		}

		//敵とプレイヤーの当たり判定
		if (g_aEnemy[nCntEnemy].bUse == true)
		{	//使用しているかどうか
			if (pPlayer->pos.x - (MAX_PLAYER_SIZE_X / 2) < g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE_X / 2) &&		//左
				pPlayer->pos.x + (MAX_PLAYER_SIZE_X / 2) > g_aEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE_X / 2) &&		//右
				pPlayer->pos.y - MAX_PLAYER_SIZE_Y      <  g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE_Y / 2) &&		//上
				pPlayer->pos.y >						   g_aEnemy[nCntEnemy].pos.y - (MAX_ENEMY_SIZE_Y / 2))			//下
			{
				//HitPlayer(nCntEnemy, DAMAGE_PAPER);	//プレイヤーの情報,ダメージ数()
				pPlayer->bUse = false;
			}
		}
		//頂点バッファをアンロックする
		g_pVtxBuffEnemy->Unlock();
	}
}

//-------------------------------------------------------------------------------
//	敵の描画処理
//-------------------------------------------------------------------------------
void DrawEnemy(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].type]);

		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive
			(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
			nCntEnemy * NUM_VERTEX,		//描画を開始する頂点インデックス
			NUM_POLYGON);				//描画するプリミティブ数
		}
	}
}

//-------------------------------------------------------------------------------
//	敵の設定
//-------------------------------------------------------------------------------
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMYTYPE type, int nLife)
{
	//変数宣言
	ENEMY * pEnemy;
	pEnemy = &g_aEnemy[0];
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == false)
		{
			pEnemy->pos = pos;				//位置

			pEnemy->type = type;			//種類
		
			SetVertexEnemy(nCntEnemy);		//敵の頂点座標の設定

			pEnemy->move = move;			//移動量

			pEnemy->nLife = nLife;			//敵の体力

			pEnemy->bUse = true;

			break;
		}
		pVtx += NUM_VERTEX;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//--------------------------------------------------------------------------------
//	敵の取得
//--------------------------------------------------------------------------------
ENEMY * GetEnemy(void)
{
	return &g_aEnemy[0];	//敵の情報の先頭アドレスを返す
}

//-------------------------------------------------------------------------------
//	敵の頂点座標の設定
//-------------------------------------------------------------------------------
void SetVertexEnemy(int nCntEnemy)
{
	VERTEX_2D * pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[nCntEnemy * NUM_VERTEX + 0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE_X / 2, g_aEnemy[nCntEnemy].pos.y + MAX_ENEMY_SIZE_Y/ 2, 0.0f);	//左上
	pVtx[nCntEnemy * NUM_VERTEX + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE_X / 2, g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE_Y/ 2, 0.0f);	//左下
	pVtx[nCntEnemy * NUM_VERTEX + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE_X / 2, g_aEnemy[nCntEnemy].pos.y + MAX_ENEMY_SIZE_Y/ 2, 0.0f);	//右下
	pVtx[nCntEnemy * NUM_VERTEX + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE_X / 2, g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE_Y/ 2, 0.0f);	//右上

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//-------------------------------------------------------------------------------
//	敵の状態設定
//	nIdx:敵何番目かの情報
//-------------------------------------------------------------------------------