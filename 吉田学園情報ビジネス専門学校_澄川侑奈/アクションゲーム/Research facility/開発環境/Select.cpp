//--------------------------------------------------------------------------------
//
//	セレクトの処理 [Select.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Select.h"
#include "keyboard.h"
#include "fade.h"
#include "sound.h"

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define MAX_POLYGON			(5)				//ポーズ数
#define MERU_DISTANCE		(150)			//セレクトロゴの間距離
#define MAX_BACKGROUND_X	(440)			//セレクト背景の幅
#define MAX_BACKGROUND_Y	(460)			//セレクト背景の高さ

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelect = NULL;

LPDIRECT3DTEXTURE9 g_pTextureSelect = NULL;						//背景

LPDIRECT3DTEXTURE9 g_apSelectLogo[SELECT_MENU_MAX] = {};		//セレクトロゴ1～3

LPDIRECT3DTEXTURE9 g_pCursor = NULL;							//カーソル
D3DXVECTOR3 g_posCursor;	//X,Y,Zを決める

int g_nCountSelect;

//-------------------------------------------------------------------------------
//	ポーズ初期化処理
//-------------------------------------------------------------------------------
HRESULT InitSelect(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//カーソルと選択内容の初期化
	g_posCursor.y = 0;
	g_nCountSelect = SELECT_MENU_TUTORIAL;

	//変数宣言
	VERTEX_2D *pVtx;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Slect.png", &g_pTextureSelect);									//背景
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Tutorial.png", &g_apSelectLogo[SELECT_MENU_TUTORIAL]);				//チュートリアル
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/GameStart.png", &g_apSelectLogo[SELECT_MENU_GAMESTART]);			//ゲームスタート
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/CharacterChange.png", &g_apSelectLogo[SELECT_MODE_END]);			//キャラクター変更
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Cursor.png", &g_pCursor);											//カーソル

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelect,
		NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountSelect = 0; nCountSelect < MAX_POLYGON; nCountSelect++)
	{
		switch (nCountSelect)	//ポジションの設定
		{
		case 0:
			//背景
			pVtx[0].pos = D3DXVECTOR3(0				   + 210, MAX_BACKGROUND_Y + 150, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0				   + 210, 0			       + 150, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(MAX_BACKGROUND_X + 210, MAX_BACKGROUND_Y + 150, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(MAX_BACKGROUND_X + 210, 0			       + 150, 0.0f);

			break;

		case 4:
			//カーソル
			pVtx[0].pos = D3DXVECTOR3(0  + 350, 50  + 375, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0  + 350, 0   + 375, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(50 + 350, 50 + 375, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(50 + 350, 0  + 375, 0.0f);

			break;

		default:	//上記以外

			//セレクトロゴ1～3
			pVtx[0].pos = D3DXVECTOR3(0	  + 280, 180  + 100.0f * nCountSelect + 50, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0   + 280, 120  + 100.0f * nCountSelect + 50, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(320 + 280, 180  + 100.0f * nCountSelect + 50, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(320 + 280, 120  + 100.0f * nCountSelect + 50, 0.0f);

			break;
		}

		//頂点カラー設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		switch (nCountSelect)	//アニメーション用のswitch(頂点情報.tex)
		{//アニメーションする

		case 4:		//カーソル

			pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);	//左上
			pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);	//左下
			pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);	//右下
			pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);	//右上
			break;

		default:	//アニメーションしない

			pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);	//左上
			pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);	//左下
			pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);	//右下
			pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);	//右上
			break;
		}

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffSelect->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	ポーズの終了処理
//-------------------------------------------------------------------------------
void UninitSelect(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffSelect != NULL)
	{
		g_pVtxBuffSelect->Release();
		g_pVtxBuffSelect = NULL;
	}

	//テクスチャの開放(背景)
	if (g_pTextureSelect != NULL)
	{
		g_pTextureSelect->Release();
		g_pTextureSelect = NULL;
	}

	//テクスチャの開放(セレクトロゴ1～3)
	for (int nCntSelect = 0; nCntSelect < SELECT_MENU_MAX; nCntSelect++)
	{
		if (g_apSelectLogo[nCntSelect] != NULL)
		{
			g_apSelectLogo[nCntSelect]->Release();
			g_apSelectLogo[nCntSelect] = NULL;
		}
	}

	//テクスチャの開放(カーソル)
	if (g_pCursor != NULL)
	{
		g_pCursor->Release();
		g_pCursor = NULL;
	}

}

//-------------------------------------------------------------------------------
//	ポーズの更新処理
//-------------------------------------------------------------------------------
void UpdateSelect(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	int nFade = GetFade();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);


	if (nFade == FADE_NONE)
	{//フェード中は動けない
		if (GetkeyboardTrgger(DIK_W) == true)
		{//↑に移動
			g_nCountSelect -= 1;

			g_posCursor.y -= 100;

			if (g_nCountSelect < SELECT_MENU_TUTORIAL)
			{//メニューの最大数に移動
				g_nCountSelect = SELECT_MODE_END;
			}
		}

		if (GetkeyboardTrgger(DIK_S) == true)
		{//↓に移動
			g_nCountSelect += 1;

			g_posCursor.y += 100;

			if (g_nCountSelect > SELECT_MODE_END)
			{//メニューの最小数に移動
				g_nCountSelect = SELECT_MENU_TUTORIAL;
			}
		}

		if (GetkeyboardTrgger(DIK_RETURN) == true)
		{//エンターキーを押した
			if (g_nCountSelect == SELECT_MENU_TUTORIAL)
			{//チュートリアルの時	

				//チュートリアル画面に移動
				SetFade(FADE_OUT, MODE_TUTORIAL);

			}
			else if (g_nCountSelect == SELECT_MENU_GAMESTART)
			{//ゲームスタートの時	

				//ゲーム画面に移動
				SetFade(FADE_OUT, MODE_GAME_00);
			}
			else if (g_nCountSelect == SELECT_MODE_END)
			{//ゲーム終了の時	

				//警告を出す
				//SetMode(MODE_END);
				//ESCと同じ
			}
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffSelect->Unlock();

	if (g_posCursor.y < 0)
	{//カーソルが選択1にいったとき
		g_posCursor.y = 200;				//選択3に移動
	}

	if (g_posCursor.y > 200)
	{//カーソルが選択3にいったとき
		g_posCursor.y = 0;					//選択1に移動
	}

	//頂点座標(カーソル)
	pVtx[16].pos = D3DXVECTOR3(0  + 250, 50 + 270 + g_posCursor.y, 0.0f);
	pVtx[17].pos = D3DXVECTOR3(0  + 250, 0  + 270  + g_posCursor.y, 0.0f);
	pVtx[18].pos = D3DXVECTOR3(50 + 250, 50 + 270 + g_posCursor.y, 0.0f);
	pVtx[19].pos = D3DXVECTOR3(50 + 250, 0  + 270  + g_posCursor.y, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffSelect->Unlock();
}

//-------------------------------------------------------------------------------
//	ポーズの描画処理
//-------------------------------------------------------------------------------
void DrawSelect(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファをデータストーリに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSelect, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < MAX_POLYGON; nCntTitle++)
	{
		switch (nCntTitle)
		{
		case 0:
			//セレクト背景のテクスチャの設定
			pDevice->SetTexture(0, g_pTextureSelect);
			break;

		case 1:
			//チュートリアルのテクスチャの設定
			pDevice->SetTexture(0, g_apSelectLogo[SELECT_MENU_TUTORIAL]);
			break;

		case 2:
			//ゲームスタートのテクスチャの設定
			pDevice->SetTexture(0, g_apSelectLogo[SELECT_MENU_GAMESTART]);
			break;

		case 3:
			//キャラクター変更のテクスチャの設定
			pDevice->SetTexture(0, g_apSelectLogo[SELECT_MODE_END]);
			break;

		case 4:
			//カーソルのテクスチャの設定
			pDevice->SetTexture(0, g_pCursor);
			break;
		}
		//セレクトの描画
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
			nCntTitle * 4,			//描画を開始する頂点インデックス
			2);						//描画するプリミティブ数
	}
}