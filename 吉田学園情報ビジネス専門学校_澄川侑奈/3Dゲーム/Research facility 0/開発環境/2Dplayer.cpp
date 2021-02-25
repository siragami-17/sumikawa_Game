//--------------------------------------------------------------------------------
//
//	プレイヤーの処理 [2DPlayer.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "2Dplayer.h"
#include "keyboard.h"


#include "fade.h"
#include "Result.h"
#include "sound.h"
#include "Xcontroller.h"

//--------------------------------------------------------------------------------
//	マクロ定義
//--------------------------------------------------------------------------------
#define MAX_POLYGON				(1)			//テクスチャ数
#define MAX_ATTENUATION			(0.25f)		//減衰
#define MAX_ANIMATION_PATTERN	(4)			//プレイヤー(個数)
#define TEXTURE_PLAYER_Y		(2)			//分割(ｙ)
#define MAX_ANIMATION_COUNTER	(5)			//プレイヤー(スピード)
#define MAX_JUMP				(-20)		//ジャンプ
#define MAX_PLAYER_X			(161/6)		//プレイヤーの幅(当たり判定)
#define MAX_PLAYER_Y			(304/5)		//プレイヤーの高さ(当たり判定)
#define PLAYER_VR				(0.5f)		//f2DPlayerVに代入する数値(右)
#define PLAYER_VL				(0.0f)		//f2DPlayerVに代入する数値(左)

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTexture2DPlayer = NULL;				//プレイヤー
D3DXVECTOR3 g_posAnimation2DPlayer;						//X,Y,Zを決める
int g_nCountersAnimation2DPlayer;							//プレイヤー(コマ数の切り替え)
int g_nCountersAnimationCnt2DPlayer;						//プレイヤー(カウンタ更新)
int g_nCountersAnimationCun;							//カウント制御(カウンタ更新を遅くする)
float g_fTexY;											// テクスチャy座標
int g_nCnt2DPlayer;

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;
D3DXVECTOR3 g_movePolygon;								//移動量

PLAYER g_2DPlayer;										//プレイヤーの情報

//-------------------------------------------------------------------------------
//	プレイヤー初期化処理
//-------------------------------------------------------------------------------
HRESULT Init2DPlayer(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//変数宣言
	VERTEX_2D *pVtx;

	//プレイヤーの構造体の初期化
	g_2DPlayer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//現在の情報(位置)
	g_2DPlayer.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//古い情報(位置)
	g_2DPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
	g_2DPlayer.nLife = 3;										//消えるまでの長さ
	g_2DPlayer.nCunt = 0;										//硬直時間
	g_2DPlayer.fWidth = 0.0f;									//幅
	g_2DPlayer.fHeight = 0.0f;								//高さ
	g_2DPlayer.f2DPlayerU = 0;									//U
	g_2DPlayer.f2DPlayerV = 0;									//V
	g_2DPlayer.bMove = false;									//移動量
	g_2DPlayer.bUse = false;									//使用しているかどうか
	g_2DPlayer.bJump = false;									//ジャンプ中かどうか
	g_2DPlayer.bGetKey = false;								//鍵を持っているか
	g_2DPlayer.bFall = false;									//落下

	//自機がスタートする位置
	g_2DPlayer.pos = D3DXVECTOR3(50.0f, 500.0f, 0.0f);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_2.png", &g_pTexture2DPlayer);		//プレイヤー

	//頂点バッファの生成5
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_2DPlayer.pos.x - MAX_PLAYER_SIZE_X, g_2DPlayer.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_2DPlayer.pos.x - MAX_PLAYER_SIZE_X, g_2DPlayer.pos.y - MAX_PLAYER_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_2DPlayer.pos.x + MAX_PLAYER_SIZE_X, g_2DPlayer.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_2DPlayer.pos.x + MAX_PLAYER_SIZE_X, g_2DPlayer.pos.y - MAX_PLAYER_SIZE_Y, 0.0f);
	
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


	//頂点バッファをアンロックする
	g_pVtxBuffPolygon->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	プレイヤーの終了処理
//-------------------------------------------------------------------------------
void Uninit2DPlayer(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}

	//テクスチャの開放
	if (g_pTexture2DPlayer != NULL)
	{
		g_pTexture2DPlayer->Release();
		g_pTexture2DPlayer = NULL;
	}
}

//-------------------------------------------------------------------------------
//	プレイヤーの更新処理
//-------------------------------------------------------------------------------
void Update2DPlayer(void)
{
	//変数宣言
	VERTEX_2D *pVtx;


	Move2DPlayer();

	//posOldにposを代入する
	g_2DPlayer.posOld = g_2DPlayer.pos;

	if (GetkeyboardTrgger(DIK_SPACE) == true && g_2DPlayer.bJump == false)
	{//ジャンプの処理(2段ジャンプの制御)
		g_2DPlayer.move.y = MAX_JUMP;
		g_2DPlayer.bJump = true;
		//ジャンプしたとき足を開いてるようにする
	//	g_nCountersAnimationCnt2DPlayer = 1;

		//SEの追加
		PlaySound(SOUND_LABEL_SE_JUMP);	//ジャンプ
	}

	//重力
	g_2DPlayer.move.y += +2;

	//加算してあげてる(そうすることでぬるぬる動く)
	g_2DPlayer.pos.x += g_2DPlayer.move.x;
	g_2DPlayer.pos.y += g_2DPlayer.move.y;

	//移動量の減衰(moveを減らしている)
	g_2DPlayer.move.x += (0.0f - g_2DPlayer.move.x)*0.25f;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//プレイヤーアニメーション
//	g_nCountersAnimation2DPlayer = g_nCountersAnimationCnt2DPlayer % MAX_ANIMATION_PATTERN;	//マクロはアニメーションのコマ数

	//プレイヤーの移動処理
	if (GetkeyboardPress(DIK_A) == true)
	{//左の移動
		//移動量
		g_2DPlayer.move.x += -1.5;
		//減衰
	//	g_nCountersAnimationCun++;
		//f2DPlayerVに数値を代入する
		g_2DPlayer.f2DPlayerV = PLAYER_VR;
		//ジャンプ
		g_2DPlayer.bMove = true;
	}
	
	if (GetkeyboardPress(DIK_D) == true)
	{//右に移動
		//移動量
		g_2DPlayer.move.x += +1.5;
		//減衰
	//	g_nCountersAnimationCun++;
		//f2DPlayerVに数値を代入する
		g_2DPlayer.f2DPlayerV = PLAYER_VL;
		//ジャンプする
		g_2DPlayer.bMove = true;
	}
	
	//AとDが押されてないとき
	if (GetkeyboardPress(DIK_A) == false && GetkeyboardPress(DIK_D) == false)
	{//足を開かないようにする
		g_2DPlayer.bMove = false;
		g_nCountersAnimationCnt2DPlayer = 0;
	}

	//プレイヤー当たり判定
	if (g_2DPlayer.pos.x + MAX_PLAYER_X > SCREEN_WIDTH)
	{//右
		g_2DPlayer.pos.x = SCREEN_WIDTH - MAX_PLAYER_X;
	}

	if (g_2DPlayer.pos.x - MAX_PLAYER_X < 0)
	{//左
		g_2DPlayer.pos.x = 0 + MAX_PLAYER_X;
	}

	if (g_2DPlayer.pos.y - MAX_PLAYER_Y < 170)
	{//上
		g_2DPlayer.pos.y = 170 + MAX_PLAYER_Y;
	}

	if (g_2DPlayer.pos.y + 0 > SCREEN_HEIGHT)
	{//下
		g_2DPlayer.pos.y = SCREEN_HEIGHT - 0;
	}


#if 0
	for (int nCunPlyer = 0; nCunPlyer < 255; nCunPlyer++, pBlock++)
	{//ブロックを増やす
		if (pBlock->bUse == true)
		{//ブロックがある
			if (g_2DPlayer.pos.x - (MAX_PLAYER_X) < pBlock->pos.x + pBlock->fWidth &&		//ブロックの右端
				g_2DPlayer.pos.x + (MAX_PLAYER_X) > pBlock->pos.x)						//ブロックの左端
			{//自機のX軸がブロック左右に振れた時
				if (g_2DPlayer.posOld.y <= pBlock->pos.y)
				{//上から自機がブロックに当たる判定
					if (g_2DPlayer.pos.y > pBlock->pos.y)
					{//ブロックの上に乗った
						g_2DPlayer.pos.y = pBlock->pos.y;
						g_2DPlayer.move.y = 0.0f;		//重力の初期化
						g_2DPlayer.bJump = false;
					}
				}
				else if (g_2DPlayer.posOld.y - MAX_PLAYER_SIZE_Y >= pBlock->pos.y + pBlock->fHeight)
				{//下の当たり判定
					if (g_2DPlayer.pos.y - MAX_PLAYER_SIZE_Y < pBlock->pos.y + pBlock->fHeight)
					{//ブロックに当たった
						g_2DPlayer.pos.y = pBlock->pos.y + pBlock->fHeight + MAX_PLAYER_SIZE_Y;
						g_2DPlayer.move.y = 1.0f;		//重力の初期化
					}
				}
			}

			if (g_2DPlayer.pos.y - (MAX_PLAYER_SIZE_Y) < pBlock->pos.y + pBlock->fHeight &&		//ブロックの下端プレイヤーの上端
				g_2DPlayer.pos.y > pBlock->pos.y)													//ブロックの上端
			{//自機のX軸がブロック左右に振れた時
				if (g_2DPlayer.posOld.x + MAX_PLAYER_X <= pBlock->pos.x)
				{//左の当たり判定
					if (g_2DPlayer.pos.x + MAX_PLAYER_X > pBlock->pos.x)
					{//ブロックに当たった
						g_2DPlayer.pos.x = pBlock->pos.x - MAX_PLAYER_X;
						g_2DPlayer.move.x = 0.0f;		//重力の初期化
					}
				}
				else if (g_2DPlayer.posOld.x - MAX_PLAYER_X >= pBlock->pos.x + pBlock->fWidth)
				{//右の当たり判定
					if (g_2DPlayer.pos.x - MAX_PLAYER_X < pBlock->pos.x + pBlock->fWidth)
					{//ブロックに当たった
						g_2DPlayer.pos.x = pBlock->pos.x + pBlock->fWidth + MAX_PLAYER_X;
						g_2DPlayer.move.x = 0.0f;		//重力の初期化
					}
				}
			}
		}
	}

#endif

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_2DPlayer.pos.x - MAX_PLAYER_SIZE_X, g_2DPlayer.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_2DPlayer.pos.x - MAX_PLAYER_SIZE_X, g_2DPlayer.pos.y - MAX_PLAYER_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_2DPlayer.pos.x + MAX_PLAYER_SIZE_X, g_2DPlayer.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_2DPlayer.pos.x + MAX_PLAYER_SIZE_X, g_2DPlayer.pos.y - MAX_PLAYER_SIZE_Y, 0.0f);


	if ((g_nCountersAnimation2DPlayer + 1) % 5 == 0)
	{// 四番目まで来たら初期に戻す
		g_nCountersAnimation2DPlayer = 0;
	}

	// テクスチャの頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(1.0f / MAX_ANIMATION_PATTERN * ((float)g_nCountersAnimation2DPlayer), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY + 1));
	pVtx[1].tex = D3DXVECTOR2(1.0f / MAX_ANIMATION_PATTERN * ((float)g_nCountersAnimation2DPlayer), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY));
	pVtx[2].tex = D3DXVECTOR2(1.0f / MAX_ANIMATION_PATTERN * ((float)g_nCountersAnimation2DPlayer + 1), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY + 1));
	pVtx[3].tex = D3DXVECTOR2(1.0f / MAX_ANIMATION_PATTERN * ((float)g_nCountersAnimation2DPlayer + 1), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY));



	//頂点バッファをアンロックする
	g_pVtxBuffPolygon->Unlock();
}

//-------------------------------------------------------------------------------
//	プレイヤーの描画処理
//-------------------------------------------------------------------------------
void Draw2DPlayer(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture2DPlayer);

	//プレイヤーの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,					//描画を開始する頂点インデックス
		2);					//描画するプリミティブ数
}

//--------------------------------------------------------------------------------
// プレイヤーの移動
//--------------------------------------------------------------------------------
void Move2DPlayer(void)
{
	PLAYER *p2DPlayer;
	p2DPlayer = Get2DPlayer();

	if (GetkeyboardPress(DIK_D) == true)
	{// 右
		g_fTexY = 0;							// アニメテクスチャY
		if (g_2DPlayer.bJump == false)
		{// アニメーションカウンター開始
			g_nCountersAnimationCnt2DPlayer += 1;								// アニメーションカウンター
			if ((g_nCountersAnimationCnt2DPlayer % 5) == 0)
			{// アニメーション速度
				g_nCountersAnimation2DPlayer += 1;						// アニメテクスチャX
			}
		}
	}
	else if (GetkeyboardPress(DIK_A) == true)
	{// 左
		g_fTexY = 1;							// アニメテクスチャY

		if (g_2DPlayer.bJump == false)
		{// アニメーションカウンター開始
			g_nCountersAnimationCnt2DPlayer += 1;								// アニメーションカウンター
			if ((g_nCountersAnimationCnt2DPlayer % 5) == 0)
			{// アニメーション速度
				g_nCountersAnimation2DPlayer += 1;						// アニメテクスチャX
			}
		}
	}
	else if (GetkeyboardPress(DIK_A) == false)
	{// 止まった時
		g_nCountersAnimation2DPlayer = 0;									// アニメーションストップ
	}
	else if (GetkeyboardPress(DIK_D) == false)
	{// 止まった時
		g_nCountersAnimation2DPlayer = 0;									// アニメーションストップ
	}
	if (g_2DPlayer.bJump == false)
	{// 空中にいないとき
		if (GetkeyboardTrgger(DIK_J) == true)
		{// ジャンプ開始
			g_2DPlayer.move.y -= 20.0f;						// ジャンプ力
			g_2DPlayer.bJump = true;							// ジャンプ中
		}
	}
	if (g_2DPlayer.bJump == true)
	{// 空中にいるとき
		g_nCountersAnimation2DPlayer = 1;									// アニメーションストップ
	}
	if (g_2DPlayer.move.y != 0.0f)
	{// ジャンプ不可
		g_2DPlayer.bJump = true;								// 空中
	}
}
//--------------------------------------------------------------------------------
//	プレイヤーの取得
//--------------------------------------------------------------------------------
PLAYER * Get2DPlayer(void)
{
	return &g_2DPlayer;		//プレイヤーの情報の先頭アドレスを返す
}