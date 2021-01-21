////--------------------------------------------------------------------------------
////
////	カーソルの処理 [mark.cpp]
////	Author:Yuna Sumikawa
////
////--------------------------------------------------------------------------------
//#include "mark.h"
//#include "Game_00.h"
//#include "keyboard.h"
//#include "fade.h"
//#include "sound.h"
//#include "block.h"
//
////-------------------------------------------------------------------------------
////	マクロ定義
////-------------------------------------------------------------------------------
//#define MAX_POLYGON				(1)			//ポリゴン数
//#define ATTENUATION				(0.30f)		//減衰
//
//#define MAX_STOPX				(50)		//カーソルのX
//#define MAX_STOPY				(50)		//カーソルのY
//#define MAX_ANIMATION_COUNTER	(60.0f)		//カーソル(移動)
//#define MAX_ANIMATION_PATTERN	(3)			//カーソル(個数)
//
//
////-------------------------------------------------------------------------------
////	グローバル変数
////-------------------------------------------------------------------------------
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMark = NULL;
//
//LPDIRECT3DTEXTURE9 g_pHnd = NULL;					//カーソル
//D3DXVECTOR3 g_posAnimationHnd;						//X,Y,Zを決める
//int g_nCountersAnimationHnd;						//カーソル(コマ数の切り替え)
//int g_nCountersAnimationCntHnd;						//カーソル(カウンタ更新)
//
//MARK g_Mark;										//ストップの情報
////-------------------------------------------------------------------------------
////	ストップ初期化処理
////-------------------------------------------------------------------------------
//HRESULT InitMark(void)
//{
//	//デバイスの取得
//	LPDIRECT3DDEVICE9 pDevice;
//	pDevice = GetDevice();
//
//	//変数宣言
//	VERTEX_2D *pVtx;
//
//	//テクスチャの読み込み
//	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/hnd.png", &g_pHnd);		//カーソル
//
//	//ストップの構造体の初期化処理
//	g_Mark.pos = D3DXVECTOR3(615.0f, 365.0f, 0.0f);									//位置
//	g_Mark.bUse = false;
//	g_Mark.bGrab = false;
//
//	//頂点バッファの生成
//	if (FAILED(pDevice->CreateVertexBuffer
//	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		//確保するバッファサイズ
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,							//頂点フォーマット
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffMark,
//		NULL)))
//	{
//		return E_FAIL;
//	}
//
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffMark->Lock(0, 0, (void**)&pVtx, 0);
//
//	//頂点座標
//	pVtx[0].pos = D3DXVECTOR3(g_Mark.pos.x - 0, g_Mark.pos.y + 50, 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(g_Mark.pos.x - 0, g_Mark.pos.y - 0, 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(g_Mark.pos.x + 50, g_Mark.pos.y + 50, 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(g_Mark.pos.x + 50, g_Mark.pos.y - 0, 0.0f);
//
//
//	//カラー用のswitch(頂点カラー.col)
//	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//
//	//アニメーション用のswitch(頂点情報.tex)
//	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);	//左下
//	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);	//左上
//	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);	//右下
//	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);	//右上
//
//	//rhwの設定
//	pVtx[0].rhw = 1.0f;
//	pVtx[1].rhw = 1.0f;
//	pVtx[2].rhw = 1.0f;
//	pVtx[3].rhw = 1.0f;
//
//	//頂点バッファをアンロックする
//	g_pVtxBuffMark->Unlock();
//
//	return S_OK;
//}
//
////-------------------------------------------------------------------------------
////	ストップの終了処理
////-------------------------------------------------------------------------------
//void UninitMark(void)
//{
//	//頂点バッファの開放
//	if (g_pVtxBuffMark != NULL)
//	{
//		g_pVtxBuffMark->Release();
//		g_pVtxBuffMark = NULL;
//	}
//
//	//テクスチャの開放(カーソル)
//	if (g_pHnd != NULL)
//	{
//		g_pHnd->Release();
//		g_pHnd = NULL;
//	}
//}
//
////-------------------------------------------------------------------------------
////	ストップの更新処理
////-------------------------------------------------------------------------------
//void UpdateMark(void)
//{
//	//変数宣言
//	VERTEX_2D *pVtx;
//	BLOCK * pBlock;
//
//	//ブロックの情報をもらう
//	pBlock = GetBlock();
//
//	//カーソル(選択)
//	g_nCountersAnimationHnd = 0;
//
//	if (g_Mark.bGrab == true)
//	{//掴んだ時
//		//カーソル(掴んだ)
//		g_nCountersAnimationHnd = 2;
//	}
//
//	//カーソルの移動処理
//	if (GetkeyboardTrgger(DIK_W) == true)
//	{//上
//		g_Mark.pos.y -= MAX_ANIMATION_COUNTER;
//	}
//
//	if (GetkeyboardTrgger(DIK_A) == true)
//	{//左
//		g_Mark.pos.x -= MAX_ANIMATION_COUNTER;
//	}
//
//	if (GetkeyboardTrgger(DIK_S) == true)
//	{//下
//		g_Mark.pos.y += MAX_ANIMATION_COUNTER;
//	}
//
//	if (GetkeyboardTrgger(DIK_D) == true)
//	{//右
//		g_Mark.pos.x += MAX_ANIMATION_COUNTER;
//	}
//
//	//カーソルと画面の当たり判定
//	if (g_Mark.pos.x + MAX_STOPX > SCREEN_WIDTH - 15.0f)
//	{//右
//		g_Mark.pos.x = SCREEN_WIDTH - MAX_STOPX - 15.0f;
//	}
//
//	if (g_Mark.pos.x < 15.0f)
//	{//左
//		g_Mark.pos.x = 15.0f;
//	}
//
//	if (g_Mark.pos.y < 125.0f)
//	{//上
//		g_Mark.pos.y = 125.0f;
//	}
//
//	if (g_Mark.pos.y + MAX_STOPY > SCREEN_HEIGHT - 5.0f)
//	{//下
//		g_Mark.pos.y = SCREEN_HEIGHT - MAX_STOPY - 5.0f;
//	}
//
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffMark->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCntMark = 0; nCntMark < MAX_BLOCK; nCntMark++, pBlock++)
//	{//全てのブロックに判定
//		if (g_Mark.bUse == false)	//使用しているかどうか
//		{
//			if (pBlock->pos.x - (60 / 3) < g_Mark.pos.x + (MAX_STOPX / 3) &&
//				pBlock->pos.x + (60 / 3) > g_Mark.pos.x - (MAX_STOPX / 3) &&
//				pBlock->pos.y - (60 / 3) < g_Mark.pos.y + (MAX_STOPY / 3) &&
//				pBlock->pos.y + (60 / 3) > g_Mark.pos.y - (MAX_STOPY / 3))
//			{
//				//掴む処理
//				if (GetkeyboardTrgger(DIK_RETURN) == true)
//				{//エンターキーを押した
//				 //掴める
//					g_Mark.bGrab = g_Mark.bGrab ? false : true;
//				}
//
//				//ブロックがあった
//				pBlock->bUse = true;
//
//				if (g_Mark.bGrab == false)
//				{
//					//カーソル(持てる)
//					g_nCountersAnimationHnd = 1;
//				}
//				//動かせる
//				pBlock->bBlock = true;
//			}
//		}
//	}
//
//	//アニメーション(カーソル)
//	g_nCountersAnimationHnd = g_nCountersAnimationHnd % MAX_ANIMATION_PATTERN;	//アニメーションのコマ数
//
//	//アニメーションの頂点情報の設定
//	pVtx[0].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationHnd * 0.33f, 1.0f);
//	pVtx[1].tex = D3DXVECTOR2(0.0f + g_nCountersAnimationHnd * 0.33f, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(0.33f + g_nCountersAnimationHnd * 0.33f, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(0.33f + g_nCountersAnimationHnd * 0.33f, 0.0f);
//
//	pVtx[0].pos = D3DXVECTOR3(g_Mark.pos.x - 0, g_Mark.pos.y + 50, 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(g_Mark.pos.x - 0, g_Mark.pos.y - 0, 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(g_Mark.pos.x + 50, g_Mark.pos.y + 50, 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(g_Mark.pos.x + 50, g_Mark.pos.y - 0, 0.0f);
//
//	//頂点バッファをアンロックする
//	g_pVtxBuffMark->Unlock();	
//}
//
////-------------------------------------------------------------------------------
////	ストップの描画処理
////-------------------------------------------------------------------------------
//void DrawMark(void)
//{
//	//デバイスの取得
//	LPDIRECT3DDEVICE9 pDevice;
//	pDevice = GetDevice();
//
//	BLOCK * pBlock;
//
//	//ブロックの情報をもらう
//	pBlock = GetBlock();
//
//	//頂点バッファをデータストーリに設定
//	pDevice->SetStreamSource(0, g_pVtxBuffMark, 0, sizeof(VERTEX_2D));
//
//	//頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//カーソルテクスチャの設定
//	pDevice->SetTexture(0, g_pHnd);
//
//	//カーソルの描画
//	pDevice->DrawPrimitive
//	(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
//		0,						//描画を開始する頂点インデックス
//		2);						//描画するプリミティブ数
//}
//
////--------------------------------------------------------------------------------
////	カーソルの取得
////--------------------------------------------------------------------------------
//MARK * GetMark(void)
//{
//	return &g_Mark;		//カーソルの情報の先頭アドレスを返す
//}





//--------------------------------------------------------------------------------
//
//	カーソルの処理 [mark.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "mark.h"
#include "Game_00.h"
#include "keyboard.h"
#include "fade.h"
#include "sound.h"
#include "block.h"


//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define MAX_POLYGON				(1)			//ポリゴン数

#define MARKER_SIZE (50.0f)			// マーカーのサイズ

#define MOVE_MARKER	(3.0f)
#define PI_QUARTER	(D3DX_PI / 4)	// 円周率の1/4(斜め移動で使う)

#define MAX_ANIMATION_COUNTER	(60.0f)		//カーソル(移動)
#define MAX_ANIMATION_PATTERN	(3)			//カーソル(個数)

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMarker = NULL;	// マーカーのテクスチャのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMarker = NULL;			// マーカーの頂点バッファのポインタ
MARKER g_Marker;									// マーカーの情報

int g_nCountersAnimationHnd;						//カーソル(コマ数の切り替え)
int g_nCountersAnimationCntHnd;						//カーソル(カウンタ更新)

//-----------------------------------------------------------------
// マーカーの初期化処理
//-----------------------------------------------------------------
HRESULT InitMarker(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/hnd.png", &g_pTextureMarker);

	// 弾情報の初期化
	g_Marker.pos = D3DXVECTOR3(640.0f, 390.0f, 0.0f);
	g_Marker.posOld = g_Marker.pos;
	g_Marker.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Marker.fWidth = MARKER_SIZE;
	g_Marker.fHeight = MARKER_SIZE;
	g_Marker.state = MARKERSTATE_NORMAL;
	g_Marker.nCntPatternAnim = 0;
	g_Marker.bUse = false;

	//頂点バッファの生成5
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4,		//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffMarker,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMarker->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Marker.pos.x - 0, g_Marker.pos.y + 50, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Marker.pos.x - 0, g_Marker.pos.y - 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Marker.pos.x + 50, g_Marker.pos.y + 50, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Marker.pos.x + 50, g_Marker.pos.y - 0, 0.0f);

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

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f + (float)g_Marker.nCntPatternAnim * 0.33f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (float)g_Marker.nCntPatternAnim * 0.33f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.33f + (float)g_Marker.nCntPatternAnim * 0.33f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.33f + (float)g_Marker.nCntPatternAnim * 0.33f, 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffMarker->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// マーカーの終了処理
//-----------------------------------------------------------------
void UninitMarker(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffMarker != NULL)
	{
		g_pVtxBuffMarker->Release();
		g_pVtxBuffMarker = NULL;
	}

	// テクスチャの開放
	if (g_pTextureMarker != NULL)
	{
		g_pTextureMarker->Release();
		g_pTextureMarker = NULL;
	}
}

//-----------------------------------------------------------------
// マーカーの更新処理
//-----------------------------------------------------------------
void UpdateMarker(void)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;
	BLOCK *pBlock = GetBlock();

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMarker->Lock(0, 0, (void**)&pVtx, 0);

	// 位置情報の保存
	g_Marker.posOld = g_Marker.pos;

	// 移動処理
	if (GetkeyboardTrgger(DIK_W) == true)
	{// 上移動
		g_Marker.pos.y -= 60.0f;
	}
	else if (GetkeyboardTrgger(DIK_S) == true)
	{// 下移動
		g_Marker.pos.y += 60.0f;
	}
	else if (GetkeyboardTrgger(DIK_D) == true)
	{// 右移動
		g_Marker.pos.x += 60.0f;
	}
	else if (GetkeyboardTrgger(DIK_A) == true)
	{// 左移動
		g_Marker.pos.x -= 60.0f;
	}

	// 画面外に出ないようにする
	if (g_Marker.pos.y < 150.0f)
	{// 一番上に到達したとき処理
		g_Marker.pos.y = 150.0f;
	}
	if (g_Marker.pos.y > SCREEN_HEIGHT - 30.0f)
	{// 一番下に到達したとき処理
		g_Marker.pos.y = SCREEN_HEIGHT - 30.0f;
	}
	if (g_Marker.pos.x <= 40.0f)
	{// 一番左に到達したとき処理
		g_Marker.pos.x = 40.0f;
	}
	if (g_Marker.pos.x >= SCREEN_WIDTH - 40.0f)
	{// 一番右に到達したとき処理
		g_Marker.pos.x = SCREEN_WIDTH - 40.0f;
	}

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Marker.pos.x - g_Marker.fWidth, g_Marker.pos.y + g_Marker.fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Marker.pos.x - g_Marker.fWidth, g_Marker.pos.y - g_Marker.fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Marker.pos.x + g_Marker.fWidth, g_Marker.pos.y + g_Marker.fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Marker.pos.x + g_Marker.fWidth, g_Marker.pos.y - g_Marker.fHeight, 0.0f);

	// 移動量の減衰(慣性)
	g_Marker.move.x = 0.0f;
	g_Marker.move.y = 0.0f;

	//アニメーションの頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + (float)g_Marker.nCntPatternAnim * 0.33f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (float)g_Marker.nCntPatternAnim * 0.33f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.33f + (float)g_Marker.nCntPatternAnim * 0.33f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.33f + (float)g_Marker.nCntPatternAnim * 0.33f, 0.0f);

	pVtx[0].pos = D3DXVECTOR3(g_Marker.pos.x - 0, g_Marker.pos.y + 50, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Marker.pos.x - 0, g_Marker.pos.y - 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Marker.pos.x + 50, g_Marker.pos.y + 50, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Marker.pos.x + 50, g_Marker.pos.y - 0, 0.0f);
	
	// 頂点バッファをアンロックする
	g_pVtxBuffMarker->Unlock();
}

//-----------------------------------------------------------------
// マーカーの描画処理
//-----------------------------------------------------------------
void DrawMarker(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMarker, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの描画
	pDevice->SetTexture(0, g_pTextureMarker);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);
}

//-----------------------------------------------------------------
// マーカー情報の取得
//-----------------------------------------------------------------
MARKER *GetMarker(void)
{
	return &g_Marker;
}