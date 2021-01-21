//--------------------------------------------------------------------------------
//
//	リザルト画面の処理 tResult.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Result.h"
#include "keyboard.h"
#include "fade.h"
#include "sound.h"

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define MAX_RESULT	(2)	//ポリゴン数

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;				//クリア画面

LPDIRECT3DTEXTURE9 g_pGameOver = NULL;					//ゲームオーバ画面

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;

bool g_bClear = false;									//クリアかゲームオーバーか

bool g_bRetry = false;									//リトライ中かどうか

//-------------------------------------------------------------------------------
//	リザルト初期化処理
//-------------------------------------------------------------------------------
HRESULT InitResult(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//変数宣言
	VERTEX_2D *pVtx;

	//テクスチャの設定
	if (g_bClear == true)
	{//クリア画面
		 //BGMの追加
		PlaySound(SOUND_LABEL_BGM003);	//クリアBGM
	}
	else if (g_bClear == false)
	{//ゲームオーバ画面
		 //BGMの追加
		PlaySound(SOUND_LABEL_BGM004);	//ゲームオーバーBGM
	}


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Result.png", &g_pTextureResult);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gameover.png", &g_pGameOver);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4,						//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標(クリア画面)
	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	リザルトの終了処理
//-------------------------------------------------------------------------------
void UninitResult(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	//テクスチャの開放(クリア画面)
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//テクスチャの開放(ゲームオーバ画面)
	if (g_pGameOver != NULL)
	{
		g_pGameOver->Release();
		g_pGameOver = NULL;
	}

	StopSound();//音止める

}

//-------------------------------------------------------------------------------
//	リザルトの更新処理
//-------------------------------------------------------------------------------
void UpdateResult(void)
{
	//フェード
	int nFade = GetFade();

	if (nFade == FADE_NONE)
	{//フェード中は動けない
		if (GetkeyboardTrgger(DIK_RETURN) == true)
		{	//ENTERキーを押したらタイトル画面へ
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}
}

//-------------------------------------------------------------------------------
//	リザルトの描画処理
//-------------------------------------------------------------------------------
void DrawResult(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファをデータストーリに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	if (g_bClear == true)
	{//クリア画面
		pDevice->SetTexture(0, g_pTextureResult);
	}
	else if (g_bClear == false)
	{//ゲームオーバ画面
		pDevice->SetTexture(0, g_pGameOver);
	}

	//リザルトの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
		0,							//描画を開始する頂点インデックス
		2);							//描画するプリミティブ数
}

//-------------------------------------------------------------------------------
//	リザルト画面(クリアかゲームオーバか)
//-------------------------------------------------------------------------------
void SetResult(bool bClear)
{
	g_bClear = bClear;	//画面変更
}