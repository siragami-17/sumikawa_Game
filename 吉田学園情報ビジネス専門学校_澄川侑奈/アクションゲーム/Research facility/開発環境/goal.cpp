//--------------------------------------------------------------------------------
//
//	ゴールの処理 [goal.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "goal.h"				// ゴール
#include "Player.h"				// プレイヤー
#include "fade.h"				// フェード
#include "Result.h"				// リザルト
#include "keyboard.h"			// キーボード

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define MAX_POLYGON	(2)			// ポリゴン数
								   
#define MAX_DOOR_X	(310/3)		// 扉の幅
#define MAX_DOOR_Y	(380/3)		// 扉の高さ
#define DOOR_X	(20)			// 扉の幅(当たり判定)
#define DOOR_Y	(20)			// 扉の高さ(当たり判定)

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffdoor = NULL;

LPDIRECT3DTEXTURE9 g_pTexturedoor = NULL;							//扉
LPDIRECT3DTEXTURE9 g_pTextureEnter= NULL;							//エンターキー

DOOR g_Door;														//扉の情報

//-------------------------------------------------------------------------------
//	ゴールの初期化処理
//-------------------------------------------------------------------------------
HRESULT Initdoor(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); 

	// 変数宣言
	VERTEX_2D *pVtx;

	// 扉の構造体の初期化
	g_Door.pos = D3DXVECTOR3(1100.0f, 240.0f, 0.0f);		// 位置
	g_Door.bUse = true;										// 使用しているかどうか

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/door_00.png", &g_pTexturedoor);		// 扉
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Enter.png", &g_pTextureEnter);			// エンターキー

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,						   
		FVF_VERTEX_2D,							// 頂点フォーマット
		D3DPOOL_MANAGED,						   
		&g_pVtxBuffdoor,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffdoor->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCunDoor = 0; nCunDoor < MAX_POLYGON; nCunDoor++)
	{
		switch (nCunDoor)
		{	// 頂点座標
		case 0:
			pVtx[0].pos = D3DXVECTOR3(g_Door.pos.x - (MAX_DOOR_X / 2), g_Door.pos.y + (MAX_DOOR_Y / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Door.pos.x - (MAX_DOOR_X / 2), g_Door.pos.y - (MAX_DOOR_Y / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Door.pos.x + (MAX_DOOR_X / 2), g_Door.pos.y + (MAX_DOOR_Y / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Door.pos.x + (MAX_DOOR_X / 2), g_Door.pos.y - (MAX_DOOR_Y / 2), 0.0f);
			break;

		case 1:
			pVtx[0].pos = D3DXVECTOR3(0  /2+1150,139/2+200,0.0f);
			pVtx[1].pos = D3DXVECTOR3(0  /2+1150,0  /2+200, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(161/2+1150,139/2+200, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(161/2+1150,0  /2+200, 0.0f);
			break;
		}
	
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
		pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffdoor->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	ゴールの終了処理
//-------------------------------------------------------------------------------
void Uninitdoor(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffdoor != NULL)
	{
		g_pVtxBuffdoor->Release();
		g_pVtxBuffdoor = NULL;
	}

	// テクスチャの開放
	// 扉
	if (g_pTexturedoor != NULL)
	{
		g_pTexturedoor->Release();
		g_pTexturedoor = NULL;
	}

	// エンターキー
	if (g_pTextureEnter != NULL)
	{
		g_pTextureEnter->Release();
		g_pTextureEnter = NULL;
	}
}

//-------------------------------------------------------------------------------
//	ゴールの更新処理
//-------------------------------------------------------------------------------
void Updatedoor(void)
{
	//変数宣言
	VERTEX_2D *pVtx;
	PLAYER * pPlayer;

	int nFade = GetFade();

	//プレイヤーの情報
	pPlayer = GetPlayer();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffdoor->Lock(0, 0, (void**)&pVtx, 0);

	//扉とプレイヤーの当たり判定
	if (g_Door.bUse == true)
	{	//使用しているかどうか
		if (pPlayer->pos.x - (MAX_PLAYER_SIZE_X / 2) < g_Door.pos.x + (DOOR_X / 2) &&		//左
			pPlayer->pos.x + (MAX_PLAYER_SIZE_X / 2) > g_Door.pos.x - (DOOR_X / 2) &&		//右
			pPlayer->pos.y - MAX_PLAYER_SIZE_Y < g_Door.pos.y + (DOOR_Y / 2) &&				//上
			pPlayer->pos.y > g_Door.pos.y - (DOOR_Y / 2))									//下
		{
			g_Door.bUse = true;

			if (nFade == FADE_NONE)
			{//フェード中は動けない
				if (pPlayer->bGetKey == true)
				{//鍵を持っていたら
					if (GetkeyboardTrgger(DIK_RETURN) == true)
					{// エンターキーを押した
						//リザルト画面に移動
						SetResult(true);
						SetFade(FADE_OUT, MODE_RESULT);
					}
	
				}
			}

		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffdoor->Unlock();
}

//-------------------------------------------------------------------------------
//	ゴールの描画処理
//-------------------------------------------------------------------------------
void Drawdoor(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	PLAYER * pPlayer;

	//頂点バッファをデータストーリに設定
	pDevice->SetStreamSource(0, g_pVtxBuffdoor, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCunDoor = 0; nCunDoor < MAX_POLYGON; nCunDoor++)
	{
		switch (nCunDoor)
		{

		case 0:
			//背景テクスチャの設定
			pDevice->SetTexture(0, g_pTexturedoor);
			break;

			if(pPlayer->bGetKey == true)
			{

		case 1:
			//背景テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEnter);
			break;
			}
		}


		//ストップ背景の描画
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
			nCunDoor * 4,		// 描画を開始する頂点インデックス
			NUM_POLYGON);			// 描画するプリミティブ数
	}
}