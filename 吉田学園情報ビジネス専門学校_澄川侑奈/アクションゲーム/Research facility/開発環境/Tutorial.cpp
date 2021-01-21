//--------------------------------------------------------------------------------
//
//	チュートリアル画面の処理 [Tutorial.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Tutorial.h"										// チュートリアル
#include "keyboard.h"										// キーボード
#include "fade.h"											// フェード
#include "sound.h"											// サウンド

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define MAX_POLYGON					(6)						// ポリゴン数

#define PLAYER_X					(428)					// 少女の幅
#define PLAYER_Y					(430)					// 少女の高さ
#define MAX_ANIMATION_COUNTER_GIRL	(5)						// スピード
#define MAX_ANIMATION_PATTERN_GIRL	(20)					// 画像コマ数
#define DIVISION_GIRL				(0.05f)					// 割り算

#define HELP_X						(50 + HELP_POS_X)		// お助けくんの幅
#define HELP_Y						(120 + HELP_POS_Y)		// お助けくんの高さ
#define HELP_POS_X					(750)					// 位置(X)
#define HELP_POS_Y					(450)					// 位置(Y)

#define UI_X						(690 + UI_POS_X)		// チュートリアルの幅
#define UI_Y						(171 + UI_POS_Y)		// チュートリアルの高さ
#define UI_POS_X					(300)					// 位置(X)
#define UI_POS_Y					(20)					// 位置(Y)
#define MAX_ANIMATION_COUNTER		(6)						// スピード
#define MAX_ANIMATION_PATTERN		(8)						// 画像コマ数
#define DIVISION					(0.125f)				// 割り算

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;

LPDIRECT3DTEXTURE9 g_pTextureGirl = NULL;				// 少女
int g_nCountersAnimation_Girl;							// コマ数の切り替え
int g_nCountersAnimationCnt_Girl;						// カウンタ更新

LPDIRECT3DTEXTURE9 g_pTextureHelp = NULL;				// お助けくん
D3DXVECTOR3 g_posHelp;									// 位置

LPDIRECT3DTEXTURE9 g_pTextureFframe = NULL;				// 枠

LPDIRECT3DTEXTURE9 g_pTextureGround = NULL;				// 地面

LPDIRECT3DTEXTURE9 g_pTextureUI = NULL;					// UI
D3DXVECTOR3 g_posUI;									// 位置
int g_nCountersAnimation_UI;							// コマ数の切り替え
int g_nCountersAnimationCnt_UI;							// カウンタ更新

LPDIRECT3DTEXTURE9 g_pTextureBall = NULL;				// 玉


//-------------------------------------------------------------------------------
//	チュートリアルの初期化処理
//-------------------------------------------------------------------------------
HRESULT InitTutorial(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 変数宣言
	VERTEX_2D *pVtx;

	// BGMの追加
	PlaySound(SOUND_LABEL_BGM001);		// チュートリアルBGM

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Tutorial_Girl.png", &g_pTextureGirl);			// 少女
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Tutorial_Help.png", &g_pTextureHelp);			// お助けくん
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Tutorial_Frame.png", &g_pTextureFframe);		// 枠
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Tutorial_Ground.png", &g_pTextureGround);		// 地面
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Tutorial_UI.png", &g_pTextureUI);				// UI
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Tutorial_Ball.png", &g_pTextureBall);			// 玉

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL)))
	{
		return E_FAIL;
	}


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCunTutorial = 0; nCunTutorial < MAX_POLYGON; nCunTutorial++)
	{
		// 頂点座標の設定
		switch (nCunTutorial)
		{
		case 0:						// 地面
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
			break;

		case 1:						// 枠
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
			break;

		case 2:						// 少女
			pVtx[0].pos = D3DXVECTOR3(0 + PLAYER_X, 275 + PLAYER_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0 + PLAYER_X, 0 + PLAYER_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(203 + PLAYER_X, 275 + PLAYER_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(203 + PLAYER_X, 0 + PLAYER_Y, 0.0f);
			break;

		case 3:						// お助けくん
			pVtx[0].pos = D3DXVECTOR3(g_posHelp.x + HELP_POS_X, g_posHelp.y + HELP_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posHelp.x + HELP_POS_X, g_posHelp.y + HELP_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posHelp.x + HELP_X, g_posHelp.y + HELP_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posHelp.x + HELP_X, g_posHelp.y + HELP_POS_Y, 0.0f);
			break;

		case 4:						// UI 
			pVtx[0].pos = D3DXVECTOR3(g_posUI.x + UI_POS_X, g_posUI.y + UI_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posUI.x + UI_POS_X, g_posUI.y + UI_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posUI.x + UI_X, g_posUI.y + UI_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posUI.x + UI_X, g_posUI.y + UI_POS_Y, 0.0f);
			break;

		case 5:						// 玉 
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
			break;	    
		}

		// 頂点情報の設定
		switch (nCunTutorial)
		{// アニメーションする
		case 2:						// 少女
			pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
			pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
			pVtx[2].tex = D3DXVECTOR2(DIVISION_GIRL, 1.0);
			pVtx[3].tex = D3DXVECTOR2(DIVISION_GIRL, 0.0);
			break;

		case 4:						// UI
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(DIVISION, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(DIVISION, 0.0f);
			break;

		// アニメーションしない
		default:
			pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
			pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
			pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
			pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);
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

		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTutorial->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	チュートリアルの終了処理
//-------------------------------------------------------------------------------
void UninitTutorial(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

	// テクスチャの開放
	// 地面
	if (g_pTextureGround != NULL)
	{
		g_pTextureGround->Release();
		g_pTextureGround = NULL;
	}

	// 枠
	if (g_pTextureFframe != NULL)
	{
		g_pTextureFframe->Release();
		g_pTextureFframe = NULL;
	}

	// 少女
	if (g_pTextureGirl != NULL)
	{
		g_pTextureGirl->Release();
		g_pTextureGirl = NULL;
	}

	// お助けくん
	if (g_pTextureHelp != NULL)
	{
		g_pTextureHelp->Release();
		g_pTextureHelp = NULL;
	}

	// UI
	if (g_pTextureUI != NULL)
	{
		g_pTextureUI->Release();
		g_pTextureUI = NULL;
	}

	// 玉
	if (g_pTextureBall != NULL)
	{
		g_pTextureBall->Release();
		g_pTextureBall = NULL;
	}

	// 音止める
	StopSound();
}

//-------------------------------------------------------------------------------
//	ステージ1の更新処理
//-------------------------------------------------------------------------------
void UpdateTutorial(void)
{
	// 変数宣言
	VERTEX_2D *pVtx;

	int nFade = GetFade();

	if (nFade == FADE_NONE)
	{// フェード中は動かない
		if (GetkeyboardTrgger(DIK_RETURN) == true)
		{// エンターキーを押した
		 // ステージ1に移動
			SetFade(FADE_OUT, MODE_GAME_00);
		}
	}

	g_nCountersAnimationCnt_UI++;
	g_nCountersAnimationCnt_Girl++;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	// アニメーションの処理
	// 少女
	if ((g_nCountersAnimationCnt_Girl %MAX_ANIMATION_COUNTER_GIRL) == 0)	// アニメーションのカウント
	{
		g_nCountersAnimation_Girl = (g_nCountersAnimation_Girl + 1) % MAX_ANIMATION_PATTERN_GIRL;	// アニメーションのコマ数

		// アニメーションの頂点情報の設定
		pVtx[8].tex = D3DXVECTOR2(0.0f + g_nCountersAnimation_Girl * DIVISION_GIRL, 1.0f);
		pVtx[9].tex = D3DXVECTOR2(0.0f + g_nCountersAnimation_Girl * DIVISION_GIRL, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(DIVISION_GIRL + g_nCountersAnimation_Girl * DIVISION_GIRL, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(DIVISION_GIRL + g_nCountersAnimation_Girl * DIVISION_GIRL, 0.0f);
	}

	// UI
	if ((g_nCountersAnimationCnt_UI %MAX_ANIMATION_COUNTER) == 0)	// アニメーションのカウント
	{
		g_nCountersAnimation_UI = (g_nCountersAnimation_UI + 1) % MAX_ANIMATION_PATTERN;	// アニメーションのコマ数

		// アニメーションの頂点情報の設定
		pVtx[16].tex = D3DXVECTOR2(0.0f + g_nCountersAnimation_UI * DIVISION, 1.0f);
		pVtx[17].tex = D3DXVECTOR2(0.0f + g_nCountersAnimation_UI * DIVISION, 0.0f);
		pVtx[18].tex = D3DXVECTOR2(DIVISION + g_nCountersAnimation_UI * DIVISION, 1.0f);
		pVtx[19].tex = D3DXVECTOR2(DIVISION + g_nCountersAnimation_UI * DIVISION, 0.0f);
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTutorial->Unlock();

}

//-------------------------------------------------------------------------------
//	ステージ1の描画処理
//-------------------------------------------------------------------------------
void DrawTutorial(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストーリに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCunTutorial = 0; nCunTutorial < MAX_POLYGON; nCunTutorial++)
	{
		switch (nCunTutorial)
		{// テクスチャの設定
		case 0:
			// 地面
			pDevice->SetTexture(0, g_pTextureGround);
			break;
		case 1:
			// 枠
			pDevice->SetTexture(0, g_pTextureFframe);
			break;

		case 2:
			// 少女
			pDevice->SetTexture(0, g_pTextureGirl);
			break;

		case 3:
			// お助けくん
			pDevice->SetTexture(0, g_pTextureHelp);
			break;

		case 4:
			// UI
			pDevice->SetTexture(0, g_pTextureUI);
			break;

		case 5:
			// 玉
			pDevice->SetTexture(0, g_pTextureBall);
			break;
		}
			// チュートリアルの描画
			pDevice->DrawPrimitive
			(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
				nCunTutorial * 4,		// 描画を開始する頂点インデックス
				NUM_POLYGON);			// 描画するプリミティブ数
	}
}