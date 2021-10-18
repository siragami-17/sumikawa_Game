//--------------------------------------------------------------------------------
//
//	プレイヤーの処理 [Player.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Player.h"
#include "keyboard.h"
#include "block.h"
#include "goal.h"
#include "fade.h"
#include "Result.h"
#include "sound.h"
#include "Xcontroller.h"
#include "sound.h"

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
#define PLAYER_VR				(0.5f)		//fPlayerVに代入する数値(右)
#define PLAYER_VL				(0.0f)		//fPlayerVに代入する数値(左)

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;				//プレイヤー
D3DXVECTOR3 g_posAnimationPlayer;						//X,Y,Zを決める
int g_nCountersAnimationPlayer;							//プレイヤー(コマ数の切り替え)
int g_nCountersAnimationCntPlayer;						//プレイヤー(カウンタ更新)
int g_nCountersAnimationCun;							//カウント制御(カウンタ更新を遅くする)
float g_fTexY;											// テクスチャy座標
int g_nCntPlayer;

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;
D3DXVECTOR3 g_movePolygon;								//移動量

PLAYER g_Player;										//プレイヤーの情報

//-------------------------------------------------------------------------------
//	プレイヤー初期化処理
//-------------------------------------------------------------------------------
HRESULT InitPlayer(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//変数宣言
	VERTEX_2D *pVtx;

	//プレイヤーの構造体の初期化
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//現在の情報(位置)
	g_Player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//古い情報(位置)
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
	g_Player.nLife = 3;										//消えるまでの長さ
	g_Player.nCunt = 0;										//硬直時間
	g_Player.fWidth = 0.0f;									//幅
	g_Player.fHeight = 0.0f;								//高さ
	g_Player.fPlayerU = 0;									//U
	g_Player.fPlayerV = 0;									//V
	g_Player.bMove = false;									//移動量
	g_Player.bUse = false;									//使用しているかどうか
	g_Player.bJump = false;									//ジャンプ中かどうか
	g_Player.bGetKey = false;								//鍵を持っているか
	g_Player.bFall = false;									//落下

	//自機がスタートする位置
	g_Player.pos = D3DXVECTOR3(50.0f, 650.0f, 0.0f);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_2.png", &g_pTexturePlayer);		//プレイヤー

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
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - MAX_PLAYER_SIZE_X, g_Player.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x - MAX_PLAYER_SIZE_X, g_Player.pos.y - MAX_PLAYER_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x + MAX_PLAYER_SIZE_X, g_Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + MAX_PLAYER_SIZE_X, g_Player.pos.y - MAX_PLAYER_SIZE_Y, 0.0f);
	
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
void UninitPlayer(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}

	//テクスチャの開放
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}

//-------------------------------------------------------------------------------
//	プレイヤーの更新処理
//-------------------------------------------------------------------------------
void UpdatePlayer(void)
{
	//変数宣言
	VERTEX_2D *pVtx;
	BLOCK * pBlock;

	//ブロックの情報をもらう
	pBlock = GetBlock();

	MovePlayer();

	//posOldにposを代入する
	g_Player.posOld = g_Player.pos;

	if (GetkeyboardTrgger(DIK_SPACE) == true && g_Player.bJump == false)
	{//ジャンプの処理(2段ジャンプの制御)
		g_Player.move.y = MAX_JUMP;
		g_Player.bJump = true;
		//ジャンプしたとき足を開いてるようにする
	//	g_nCountersAnimationCntPlayer = 1;

		//SEの追加
		PlaySound(SOUND_LABEL_SE_JUMP);	//ジャンプ
	}

	//重力
	g_Player.move.y += +2;

	//加算してあげてる(そうすることでぬるぬる動く)
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;

	//移動量の減衰(moveを減らしている)
	g_Player.move.x += (0.0f - g_Player.move.x)*0.25f;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//プレイヤーアニメーション
//	g_nCountersAnimationPlayer = g_nCountersAnimationCntPlayer % MAX_ANIMATION_PATTERN;	//マクロはアニメーションのコマ数

	//プレイヤーの移動処理
	if (GetkeyboardPress(DIK_A) == true)
	{//左の移動
		//移動量
		g_Player.move.x += -1.5;
		//減衰
	//	g_nCountersAnimationCun++;
		//fPlayerVに数値を代入する
		g_Player.fPlayerV = PLAYER_VR;
		//ジャンプ
		g_Player.bMove = true;
	}
	
	if (GetkeyboardPress(DIK_D) == true)
	{//右に移動
		//移動量
		g_Player.move.x += +1.5;
		//減衰
	//	g_nCountersAnimationCun++;
		//fPlayerVに数値を代入する
		g_Player.fPlayerV = PLAYER_VL;
		//ジャンプする
		g_Player.bMove = true;
	}
	
	//AとDが押されてないとき
	if (GetkeyboardPress(DIK_A) == false && GetkeyboardPress(DIK_D) == false)
	{//足を開かないようにする
		g_Player.bMove = false;
		g_nCountersAnimationCntPlayer = 0;
	}

	//プレイヤー当たり判定
	if (g_Player.pos.x + MAX_PLAYER_X > SCREEN_WIDTH)
	{//右
		g_Player.pos.x = SCREEN_WIDTH - MAX_PLAYER_X;
	}

	if (g_Player.pos.x - MAX_PLAYER_X < 0)
	{//左
		g_Player.pos.x = 0 + MAX_PLAYER_X;
	}

	if (g_Player.pos.y - MAX_PLAYER_Y < 170)
	{//上
		g_Player.pos.y = 170 + MAX_PLAYER_Y;
	}

	if (g_Player.pos.y + 0 > SCREEN_HEIGHT)
	{//下
		g_Player.pos.y = SCREEN_HEIGHT - 0;
	}

	for (int nCunPlyer = 0; nCunPlyer < 255; nCunPlyer++, pBlock++)
	{//ブロックを増やす
		if (pBlock->bUse == true)
		{//ブロックがある
			if (g_Player.pos.x - (MAX_PLAYER_X) < pBlock->pos.x + pBlock->fWidth &&		//ブロックの右端
				g_Player.pos.x + (MAX_PLAYER_X) > pBlock->pos.x)						//ブロックの左端
			{//自機のX軸がブロック左右に振れた時
				if (g_Player.posOld.y <= pBlock->pos.y)
				{//上から自機がブロックに当たる判定
					if (g_Player.pos.y > pBlock->pos.y)
					{//ブロックの上に乗った
						g_Player.pos.y = pBlock->pos.y;
						g_Player.move.y = 0.0f;		//重力の初期化
						g_Player.bJump = false;
					}
				}
				else if (g_Player.posOld.y - MAX_PLAYER_SIZE_Y >= pBlock->pos.y + pBlock->fHeight)
				{//下の当たり判定
					if (g_Player.pos.y - MAX_PLAYER_SIZE_Y < pBlock->pos.y + pBlock->fHeight)
					{//ブロックに当たった
						g_Player.pos.y = pBlock->pos.y + pBlock->fHeight + MAX_PLAYER_SIZE_Y;
						g_Player.move.y = 1.0f;		//重力の初期化
					}
				}
			}

			if (g_Player.pos.y - (MAX_PLAYER_SIZE_Y) < pBlock->pos.y + pBlock->fHeight &&		//ブロックの下端プレイヤーの上端
				g_Player.pos.y > pBlock->pos.y)													//ブロックの上端
			{//自機のX軸がブロック左右に振れた時
				if (g_Player.posOld.x + MAX_PLAYER_X <= pBlock->pos.x)
				{//左の当たり判定
					if (g_Player.pos.x + MAX_PLAYER_X > pBlock->pos.x)
					{//ブロックに当たった
						g_Player.pos.x = pBlock->pos.x - MAX_PLAYER_X;
						g_Player.move.x = 0.0f;		//重力の初期化
					}
				}
				else if (g_Player.posOld.x - MAX_PLAYER_X >= pBlock->pos.x + pBlock->fWidth)
				{//右の当たり判定
					if (g_Player.pos.x - MAX_PLAYER_X < pBlock->pos.x + pBlock->fWidth)
					{//ブロックに当たった
						g_Player.pos.x = pBlock->pos.x + pBlock->fWidth + MAX_PLAYER_X;
						g_Player.move.x = 0.0f;		//重力の初期化
					}
				}
			}
		}
	}

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - MAX_PLAYER_SIZE_X, g_Player.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x - MAX_PLAYER_SIZE_X, g_Player.pos.y - MAX_PLAYER_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x + MAX_PLAYER_SIZE_X, g_Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + MAX_PLAYER_SIZE_X, g_Player.pos.y - MAX_PLAYER_SIZE_Y, 0.0f);

	if (g_Player.move.y >= 20 && g_Player.bJump == true)
	{//ブロック2段以上から落ちた時に死亡フラグをたてる
		g_Player.bFall = true;
	}

	//死亡フラグがたっている時だけ
	if (g_Player.bFall == true && g_Player.bJump == false)
	{//プレイヤーがブロックの上に乗った
		HitPlayer(1);		//ダメージ1

		//SEの追加
		PlaySound(SOUND_LABEL_SE_DAMAGE);	//ダメージ
	}

	if ((g_nCountersAnimationPlayer + 1) % 5 == 0)
	{// 四番目まで来たら初期に戻す
		g_nCountersAnimationPlayer = 0;
	}

	// テクスチャの頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(1.0f / MAX_ANIMATION_PATTERN * ((float)g_nCountersAnimationPlayer), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY + 1));
	pVtx[1].tex = D3DXVECTOR2(1.0f / MAX_ANIMATION_PATTERN * ((float)g_nCountersAnimationPlayer), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY));
	pVtx[2].tex = D3DXVECTOR2(1.0f / MAX_ANIMATION_PATTERN * ((float)g_nCountersAnimationPlayer + 1), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY + 1));
	pVtx[3].tex = D3DXVECTOR2(1.0f / MAX_ANIMATION_PATTERN * ((float)g_nCountersAnimationPlayer + 1), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY));

	if (g_Player.state == PLAYERSTATE_DAMAGE)
	{
		g_Player.nCounterState--;//点滅する長さ

		if (g_Player.nCounterState == 0)
		{//プレイヤーの色をもどす
			//頂点カラー設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPolygon->Unlock();
}

//-------------------------------------------------------------------------------
//	プレイヤーの描画処理
//-------------------------------------------------------------------------------
void DrawPlayer(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayer);

	//プレイヤーの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,					//描画を開始する頂点インデックス
		2);					//描画するプリミティブ数
}

//-------------------------------------------------------------------------------
//	プレイヤーのライフ
//-------------------------------------------------------------------------------
bool HitPlayer(int nDamage)
{
	g_Player.nLife -= nDamage;

	if (g_Player.nLife <= 0)
	{//プレイヤーが死んだ
		g_Player.bUse = false;

		//プレイヤーのライフが0になったらリザルト画面
		SetResult(false);
		SetFade(FADE_OUT, MODE_RESULT);		//ゲームオーバ画面

		return true;
	}
	else
	{//プレイヤーが死ななかったら
		g_Player.state = PLAYERSTATE_DAMAGE;
		g_Player.bFall = false;
		g_Player.nCounterState = 5;//点滅する長さ

		VERTEX_2D *pVtx;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

		//ダメージ状態(色)
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		//頂点バッファをアンロックする
		g_pVtxBuffPolygon->Unlock();

		return false;
	}
}

//--------------------------------------------------------------------------------
// プレイヤーの移動
//--------------------------------------------------------------------------------
void MovePlayer(void)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	if (GetkeyboardPress(DIK_D) == true)
	{// 右
		g_fTexY = 0;							// アニメテクスチャY
		if (g_Player.bJump == false)
		{// アニメーションカウンター開始
			g_nCountersAnimationCntPlayer += 1;								// アニメーションカウンター
			if ((g_nCountersAnimationCntPlayer % 5) == 0)
			{// アニメーション速度
				g_nCountersAnimationPlayer += 1;						// アニメテクスチャX
			}
		}
	}
	else if (GetkeyboardPress(DIK_A) == true)
	{// 左
		g_fTexY = 1;							// アニメテクスチャY

		if (g_Player.bJump == false)
		{// アニメーションカウンター開始
			g_nCountersAnimationCntPlayer += 1;								// アニメーションカウンター
			if ((g_nCountersAnimationCntPlayer % 5) == 0)
			{// アニメーション速度
				g_nCountersAnimationPlayer += 1;						// アニメテクスチャX
			}
		}
	}
	else if (GetkeyboardPress(DIK_A) == false)
	{// 止まった時
		g_nCountersAnimationPlayer = 0;									// アニメーションストップ
	}
	else if (GetkeyboardPress(DIK_D) == false)
	{// 止まった時
		g_nCountersAnimationPlayer = 0;									// アニメーションストップ
	}
	if (g_Player.bJump == false)
	{// 空中にいないとき
		if (GetkeyboardTrgger(DIK_J) == true)
		{// ジャンプ開始
			g_Player.move.y -= 20.0f;						// ジャンプ力
			g_Player.bJump = true;							// ジャンプ中
		}
	}
	if (g_Player.bJump == true)
	{// 空中にいるとき
		g_nCountersAnimationPlayer = 1;									// アニメーションストップ
	}
	if (g_Player.move.y != 0.0f)
	{// ジャンプ不可
		g_Player.bJump = true;								// 空中
	}
}
//--------------------------------------------------------------------------------
//	プレイヤーの取得
//--------------------------------------------------------------------------------
PLAYER * GetPlayer(void)
{
	return &g_Player;		//プレイヤーの情報の先頭アドレスを返す
}