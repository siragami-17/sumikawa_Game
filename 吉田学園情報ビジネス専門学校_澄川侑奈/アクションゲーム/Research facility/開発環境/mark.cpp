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
#define MAX_POLYGON				(1)					//ポリゴン数

#define MARKER_SIZE				(50.0f)				// マーカーのサイズ

#define MOVE_MARKER				(3.0f)
#define PI_QUARTER				(D3DX_PI / 4)		// 円周率の1/4(斜め移動で使う)

#define MAX_ANIMATION_COUNTER	(60.0f)				//カーソル(移動)
#define MAX_ANIMATION_PATTERN	(3)					//カーソル(個数)

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