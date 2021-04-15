//--------------------------------------------------------------------------------
//
//	ブロックの処理 [block.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "block.h"
#include "Mark.h"			//カーソル
#include "keyboard.h"		//キーボード
#include "Game_00.h"
#include "sound.h"
#include "Effect.h"		// エフェクト

//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define MAX_BLOCK		(256)		//ブロックの最大数	
#define MAX_BLOCKTYPE		(2)


#define BLOCK_SIZE			(60.0f)		// ブロックの大きさ
#define SMALL_BLOOCK		(2.0f)		//ブロックをつかんでいるとき小さくする

#define NORMAL_BLOCK		(43.0f)
#define FLOAT_BLOCK			(10.0f)
#define RIFT_BLOCK			(5.0f)

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;			// ブロックのテクスチャのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBlock[MAX_BLOCKTYPE] = {};	// ブロックの頂点バッファのポインタ
BLOCK g_aBlock[MAX_BLOCK];								// ブロックの情報

//-----------------------------------------------------------------
// ブロックの初期化処理
//-----------------------------------------------------------------
HRESULT InitBlock(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block000.png", &g_pTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block001.png", &g_pTextureBlock[1]);

	// 弾情報の初期化
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].posOld = g_aBlock[nCntBlock].pos;
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].nTimer = 0;
		g_aBlock[nCntBlock].fWidth = BLOCK_SIZE;
		g_aBlock[nCntBlock].fHeight = BLOCK_SIZE;
		g_aBlock[nCntBlock].fTexU = 1.0f;
		g_aBlock[nCntBlock].fTexV = 1.0f;
		g_aBlock[nCntBlock].state = BLOCKSTATE_NORMAL;
		g_aBlock[nCntBlock].type = BLOCKTYPE_CATCH;
		g_aBlock[nCntBlock].bChach = false;
		g_aBlock[nCntBlock].bUse = false;
	}

	//頂点バッファの生成5
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,		//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	for (int nCntBullet = 0; nCntBullet < MAX_BLOCK; nCntBullet++)
	{
		// 頂点座標の設定
		SetVertexBlock(nCntBullet);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// 弾の情報を次にうつす
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// ブロックの終了処理
//-----------------------------------------------------------------
void UninitBlock(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}

	// テクスチャの開放
	for (int nCntTexture = 0; nCntTexture < MAX_BLOCKTYPE; nCntTexture++)
	{
		if (g_pTextureBlock[nCntTexture] != NULL)
		{
			g_pTextureBlock[nCntTexture]->Release();
			g_pTextureBlock[nCntTexture] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// ブロックの更新処理
//-----------------------------------------------------------------
void UpdateBlock(void)
{
	// 構造体のポインタ変数
	BLOCK *pBlock = &g_aBlock[0];
	MARKER *pMarker = GetMarker();

	// エフェクトの情報
	Effect * pEffect = GetEffect();

	// 変数宣言
	bool bStop = GetStop();		// 押しているどうか

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		if (pBlock->bUse == true)

		{// Lキーを押してあるなら処理
			if (bStop == true)
			{
				pMarker->nCntPatternAnim = 0;

				// ブロックを掴んでいるかつ掴まれている状態のとき処理
				if (pBlock->bChach == true && pMarker->state == MARKERSTATE_CHACHING)
				{
					pMarker->nCntPatternAnim = 2;

					// ブロックの位置をマーカーの中心座標に変更
					pBlock->pos.x = pMarker->pos.x - (pBlock->fWidth / 2.0f);
					pBlock->pos.y = pMarker->pos.y - (pBlock->fHeight / 2.0f);

					// 掴んでいるブロックが他のブロックに当たっているか
					bool bHit = ColBlock(nCntBlock);

					// 掴むor離すキーを押したとき
					if (GetkeyboardTrgger(DIK_RETURN) == true)
					{

						if (bHit == false)
						{// 当たっていないとき
							pBlock->fWidth = BLOCK_SIZE;											// サイズを元に戻す
							pBlock->fHeight = BLOCK_SIZE;											// サイズを元に戻す
							pBlock->pos.x = pMarker->pos.x - (pBlock->fWidth / SMALL_BLOOCK);		// 元の位置から少しずれているので中心座標の設定
							pBlock->pos.y = pMarker->pos.y - (pBlock->fHeight / SMALL_BLOOCK);		// 元の位置から少しずれているので中心座標の設定
							pMarker->state = MARKERSTATE_NORMAL;									// マーカーの状態をつかんでいないときにする
							pBlock->bChach = false;													// 掴んでいないときにする

							// SEの追加
							PlaySound(SOUND_LABEL_SE_SET_1);										// OFF

							// エフェクト
							SetBom(pBlock->pos+D3DXVECTOR3(0.f,15.f,0.f), 10.0f, 10);
							
						}
					}
					else if (bHit == true)
					{// 当たっているとき
						pMarker->pos = pMarker->posOld;		// マーカーを前回の位置にする
					}
				}
				else if (pBlock->bChach == false && pMarker->state == MARKERSTATE_NORMAL)
				{// ブロックが掴まれていないかつマーカーが通常のとき
					// 掴むor離すキーを押したとき
					if (pBlock->pos.x <= pMarker->pos.x &&
						pBlock->pos.x + pBlock->fWidth >= pMarker->pos.x &&
						pBlock->pos.y <= pMarker->pos.y &&
						pBlock->pos.y + pBlock->fHeight >= pMarker->pos.y)
					{// マーカーの中心座標がブロックの範囲内にあるなら処理

						pMarker->nCntPatternAnim = 1;
						if (GetkeyboardTrgger(DIK_RETURN) == true)
						{

							if (pBlock->type == BLOCKTYPE_CATCH)
							{
								pBlock->fWidth = BLOCK_SIZE / SMALL_BLOOCK;		// ブロックのサイズを小さくする
								pBlock->fHeight = BLOCK_SIZE / SMALL_BLOOCK;	// ブロックのサイズを小さくする
								pMarker->state = MARKERSTATE_CHACHING;			// マーカーの状態を掴んでいる状態にする
								pBlock->bChach = true;							// ブロックを掴まえている状態にする

								PlaySound(SOUND_LABEL_SE_ON);					//SEの追加(オン)

							
							}
						}
					}
				}
				if (bStop == false)
				{
					pBlock->bChach = false;

		
				}
			}

			// 画面外に出ないようにする
			if (pBlock->pos.y  < 0)
			{// 一番上に到達したとき処理
				pBlock->pos.y = 0;
			}
			if (pBlock->pos.y + pBlock->fHeight > SCREEN_HEIGHT)
			{// 一番下に到達したとき処理
				pBlock->pos.y = SCREEN_HEIGHT - pBlock->fHeight;
			}
			if (pBlock->pos.x <= 0)
			{// 一番左に到達したとき処理
				pBlock->pos.x = 0;
			}
			if (pBlock->pos.x + pBlock->fWidth >= SCREEN_WIDTH)
			{// 一番右に到達したとき処理
				pBlock->pos.x = SCREEN_WIDTH - pBlock->fWidth;
			}

			// 頂点座標の更新
			SetVertexBlock(nCntBlock);
		}
	}

}

//-----------------------------------------------------------------
// ブロックの描画処理
//-----------------------------------------------------------------
void DrawBlock(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// 弾の描画
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{// 弾が使われているとき処理
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].type]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
		}
	}
}

//-----------------------------------------------------------------
// ブロックの設定
//-----------------------------------------------------------------
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, float fTexU, float fTexV,BLOCKSTATE state, BLOCKTYPE type)
{
	// 構造体のポインタ変数
	BLOCK *pBlock;

	// 変数の受け渡し
	pBlock = &g_aBlock[0];

	// 弾の設定
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		if (pBlock->bUse == false)
		{// 位置設定
			pBlock->pos = pos;

			// 移動量の設定
			pBlock->move = move;

			// 幅の設定
			pBlock->fWidth = fWidth;

			// 高さの設定
			pBlock->fHeight = fHeight;

			// テクスチャ座標Uの設定
			pBlock->fTexU = fTexU;

			// テクスチャ座標Vの設定
			pBlock->fTexV = fTexV;

			// ブロックの状態の設定
			pBlock->state = state;

			// ブロックの状態の設定
			pBlock->type = type;

			// trueで返す
			pBlock->bUse = true;

			break;
		}
	}
}

//-----------------------------------------------------------------
// ブロック情報の取得
//-----------------------------------------------------------------
BLOCK *GetBlock(void)
{
	return &g_aBlock[0];
}

//-----------------------------------------------------------------
// ブロックの頂点座標
//-----------------------------------------------------------------
void SetVertexBlock(int nIdx)
{
	// 変数宣言
	float ShaikingMove = 0.0f;

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	// 弾の情報を次にうつす
	pVtx += nIdx * 4;

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x , g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x , g_aBlock[nIdx].pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y, 0.0f);

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, g_aBlock[nIdx].fTexV);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aBlock[nIdx].fTexU, g_aBlock[nIdx].fTexV);
	pVtx[3].tex = D3DXVECTOR2(g_aBlock[nIdx].fTexU, 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//-----------------------------------------------------------------
// ブロックの当たり判定
//-----------------------------------------------------------------
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, COLLISIONINFO info)
{
	// 構造体のポインタ変数
	BLOCK *pBlock = &g_aBlock[0];
	bool bLand = false;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++,pBlock++)
	{
		if (pBlock->bUse == true)
		{// ブロックが使われているとき
			if (pBlock->type == BLOCKTYPE_CATCH)
			{// 当たり判定があるブロックの時処理
				if ((pPos->x - fWidth * 0.7f) < (pBlock->pos.x + pBlock->fWidth) &&
					(pPos->x + fWidth * 0.7f) > pBlock->pos.x)
				{// プレイヤーがブロックの中にいるとき
					if (pPosOld->y + fHeight <= pBlock->pos.y)
					{// プレイヤーがブロックの上にいるとき
						if (pPos->y + fHeight > (pBlock->pos.y - 2.0f))
						{// めり込んだら処理
							LandBlock(nCntBlock, pPos, pMove, fHeight);
							bLand = true;
						}
					}
					else if ((pPosOld->y - fHeight) >= (pBlock->pos.y + pBlock->fHeight))
					{// プレイヤーがブロックの下にいるとき
						if ((pPos->y - fHeight) < (pBlock->pos.y + pBlock->fHeight))
						{// めり込んだらブロックの下の座標にする
							pPos->y = (pBlock->pos.y + pBlock->fHeight + fHeight);
							pMove->y = 1.0f;
						}
					}
				}
				if ((pPos->y + fHeight) > pBlock->pos.y && (pPos->y - fHeight) < (pBlock->pos.y + pBlock->fHeight))
				{// プレイヤーがブロックのY幅にいるとき
					if ((pPosOld->x + fWidth * 0.7f) <= pBlock->pos.x)
					{// プレイヤーがブロックの左側にいるとき
						if ((pPos->x + fWidth * 0.7f) > pBlock->pos.x)
						{// めり込んだらブロックの左の座標にする
							pPos->x = pBlock->pos.x - (fWidth * 0.7f) + pBlock->move.x;
							CollisionBlockSide(pMove, info);
						}
					}
					else if ((pPosOld->x - fWidth * 0.7f) >= (pBlock->pos.x + pBlock->fWidth))
					{// プレイヤーがブロックの右側にいるとき
						if ((pPos->x - fWidth * 0.7f) < (pBlock->pos.x + pBlock->fWidth))
						{// めり込んだらブロックの右の座標にする
							pPos->x = pBlock->pos.x + pBlock->fWidth + (fWidth * 0.7f) + pBlock->move.x;
							CollisionBlockSide(pMove, info);
						}
					}
				}
			}
		}
	}
	// 乗っているか返す
	return bLand;
}

//-----------------------------------------------------------------
// 何のブロックに乗っているか
//-----------------------------------------------------------------
void LandBlock(int nCntBlock, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, float fHeight)
{
	// 構造体のポインタ変数
	BLOCK *pBlock = &g_aBlock[0];
	
	// 何番目か
	pBlock += nCntBlock;

	if (pBlock->state == BLOCKSTATE_NORMAL || pBlock->state == BLOCKSTATE_FLOAT)
	{// ブロックの状態が床か浮いている床のとき
		pPos->y = pBlock->pos.y - fHeight;
	}
	else if (pBlock->state == BLOCKSTATE_RIFT)
	{// ブロックの状態が上下に動く床のとき
		if (pBlock->move.y >= 0)
		{// 上から下の時
			pPos->y = pBlock->pos.y - fHeight;
		}
		else if (pBlock->move.y < 0)
		{// 下から上の時
			pPos->y = pBlock->pos.y + pBlock->move.y - fHeight;
		}
	}
}

//-----------------------------------------------------------------
// ブロックの横に当たったとき
//-----------------------------------------------------------------
void CollisionBlockSide(D3DXVECTOR3 *pMove, COLLISIONINFO info)
{
	switch (info)
	{// プレイヤーのとき移動量を0にする
	case COLLISIONINFO_PLAYER:
		pMove->x = 0.0f;
		break;
		// フルーツのとき反射する
	case COLLISIONINFO_FRUITS:
		pMove->x *= -1;
		break;
		// 敵のとき反射する
	case COLLISIONINFO_ENEMY:
		pMove->x *= -1;
		break;
	}
}

//-----------------------------------------------------------------
// ブロック同士の当たり判定
//-----------------------------------------------------------------
bool ColBlock(int nCntBlock)
{
	// 変数宣言
	bool bHit = false;		// 当たっているかどうか

	// どのブロックに当たっているか
	for (int nCntCollisionBlock = 0; nCntCollisionBlock < MAX_BLOCK; nCntCollisionBlock++)
	{
		// まずはブロックが使われているか判別
		if (g_aBlock[nCntCollisionBlock].bUse == true)
		{
			// もし使われているなら今持っているブロックと違うブロックかどうか判別
			if (nCntBlock != nCntCollisionBlock)
			{
				// もし違うなら掴んでいるブロックと使われているブロックが当たっているか判別
				if (g_aBlock[nCntBlock].pos.x <= g_aBlock[nCntCollisionBlock].pos.x + g_aBlock[nCntCollisionBlock].fWidth &&
					g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth >= g_aBlock[nCntCollisionBlock].pos.x &&
					g_aBlock[nCntBlock].pos.y <= g_aBlock[nCntCollisionBlock].pos.y + g_aBlock[nCntCollisionBlock].fHeight &&
					g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight >= g_aBlock[nCntCollisionBlock].pos.y)
				{
					// もし当たっているならtrueを返す
					bHit = true;

					break;
				}
			}
		}
	}

	return bHit;
}

//-------------------------------------------------------------------------------
//	ブロックの設定
//-------------------------------------------------------------------------------
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, BLOCKTYPE type)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			g_aBlock[nCntBlock].pos = pos;					//位置

			g_aBlock[nCntBlock].fWidth = fWidth;			//幅

			g_aBlock[nCntBlock].fHeight = fHeight;			//高さ

			g_aBlock[nCntBlock].bUse = true;				//使っている

			g_aBlock[nCntBlock].type = type;

			//頂点座標(posに代入する)(xはブロックの幅、yは高さ)
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);

			//頂点情報の設定(地面ため)
			pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
			pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
			pVtx[2].tex = D3DXVECTOR2(g_aBlock[nCntBlock].fWidth / g_aBlock[nCntBlock].fHeight, 1.0);
			pVtx[3].tex = D3DXVECTOR2(g_aBlock[nCntBlock].fWidth / g_aBlock[nCntBlock].fHeight, 0.0);
			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}
