//--------------------------------------------------------------------------------
//
//	鍵の処理 [Key.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Key.h"
#include "Player.h"
#include "sound.h"

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define MAX_POLYGON		(1)			//ポリゴン数
#define MAX_KEY_X		(50)		//鍵X
#define MAX_KEY_Y		(60)		//鍵Y
#define MAX_KEY_COUNTER	(10)		//鍵のスピード
#define MAX_KEY_PATTERN	(5)			//鍵の個数

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffKey = NULL;

LPDIRECT3DTEXTURE9 g_pTextureKey = NULL;			//鍵
D3DXVECTOR3 g_posAnimationKey;						//X,Y,Zを決める
int g_nCountersAnimationKey;						//鍵のコマ数切り替え
int g_nCountersAnimationCnt;						//鍵のカウンタ更新

KEY g_Key;											//鍵の情報
//-------------------------------------------------------------------------------
//	鍵初期化処理
//-------------------------------------------------------------------------------
HRESULT InitKey(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	PLAYER *pPlayer;

	//プレイヤーの情報
	pPlayer = GetPlayer();

	//変数宣言
	VERTEX_2D *pVtx;

	//鍵の構造体の初期化
	g_Key.pos = D3DXVECTOR3(100.0f, 150.0f, 0.0f);		//位置
	g_Key.fWidth = 0.0f;								//幅
	g_Key.fHeight = 0.0f;								//高さ
	g_Key.bUse = true;									//使用しているかどうか

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Key.png", &g_pTextureKey);		//鍵

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffKey,
		NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffKey->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_Key.pos.x			 , g_Key.pos.y + MAX_KEY_Y , 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Key.pos.x			 , g_Key.pos.y			 , 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Key.pos.x + MAX_KEY_X, g_Key.pos.y + MAX_KEY_Y , 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Key.pos.x + MAX_KEY_X, g_Key.pos.y			 , 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.2f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.2f, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffKey->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	鍵の終了処理
//-------------------------------------------------------------------------------
void UninitKey(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffKey != NULL)
	{
		g_pVtxBuffKey->Release();
		g_pVtxBuffKey = NULL;
	}

	//テクスチャの開放(スコアアタック説明画面)
	if (g_pTextureKey != NULL)
	{
		g_pTextureKey->Release();
		g_pTextureKey = NULL;
	}
}

//-------------------------------------------------------------------------------
//	鍵の更新処理
//-------------------------------------------------------------------------------
void UpdateKey(void)
{
	VERTEX_2D *pVtx;
	PLAYER * pPlayer;

	//プレイヤーの情報
	pPlayer = GetPlayer();

	g_nCountersAnimationCnt++;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffKey->Lock(0, 0, (void**)&pVtx, 0);


	//鍵とプレイヤーの当たり判定
	if (g_Key.bUse == true)
	{	//使用しているかどうか
		if (pPlayer->pos.x - (MAX_PLAYER_SIZE_X / 2) < g_Key.pos.x + (MAX_KEY_X / 2) &&		//左
			pPlayer->pos.x + (MAX_PLAYER_SIZE_X / 2) > g_Key.pos.x - (MAX_KEY_X / 2) &&		//右
			pPlayer->pos.y - MAX_PLAYER_SIZE_Y < g_Key.pos.y + (MAX_KEY_Y / 2) &&			//上
			pPlayer->pos.y > g_Key.pos.y - (MAX_KEY_Y / 2))									//下
		{
			//鍵を手に入れた
			pPlayer->bGetKey = true;

			//SEの追加
			PlaySound(SOUND_LABEL_SE_GET);	//ゲット

			//鍵を見えなくする
			g_Key.bUse = false;

		}
	}

	//アニメーション鍵
	if ((g_nCountersAnimationCnt %MAX_KEY_COUNTER) == 0)	//アニメーションのカウント
	{
		g_nCountersAnimationKey = (g_nCountersAnimationKey + 1) % MAX_KEY_PATTERN;	//アニメーションのコマ数

																					//アニメーションの頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(g_Key.pos.x - 0.0f + g_nCountersAnimationKey * 0.2f, g_Key.pos.y + 1.0f);
		pVtx[1].tex = D3DXVECTOR2(g_Key.pos.x - 0.0f + g_nCountersAnimationKey * 0.2f, g_Key.pos.y - 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_Key.pos.x + 0.2f + g_nCountersAnimationKey * 0.2f, g_Key.pos.y + 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_Key.pos.x + 0.2f + g_nCountersAnimationKey * 0.2f, g_Key.pos.y - 0.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffKey->Unlock();
}

//-------------------------------------------------------------------------------
//	鍵の描画処理
//-------------------------------------------------------------------------------
void DrawKey(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファをデータストーリに設定
	pDevice->SetStreamSource(0, g_pVtxBuffKey, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_Key.bUse == true)
	{
		//鍵テクスチャの設定
		pDevice->SetTexture(0, g_pTextureKey);

		//鍵の描画
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
			0,						//描画を開始する頂点インデックス
			2);						//描画するプリミティブ数
	}


	
}