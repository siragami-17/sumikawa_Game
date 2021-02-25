//--------------------------------------------------------------------------------
//
//	本棚の処理 [goal.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Bookshelf.h"			// 本棚
#include "fade.h"				// フェード
#include "keyboard.h"			// キーボード

//-------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------
#define MAX_POLYGON	(1)			// ポリゴン数

#define MAX_BOOK_X	(208)		// 本棚の幅
#define MAX_BOOK_Y	(142)		// 本棚の高さ
#define BOOK_X	(150)			// 本棚の幅(当たり判定)
#define BOOK_Y	(120)			// 本棚の高さ(当たり判定)

//-------------------------------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBookshelf = NULL;

LPDIRECT3DTEXTURE9 g_pTextureBookshelf = NULL;							//本棚

Bookshelf g_Door;													//本棚の情報

//-------------------------------------------------------------------------------
//	本棚の初期化処理
//-------------------------------------------------------------------------------
HRESULT InitBookshelf(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 変数宣言
	VERTEX_2D *pVtx;

	// 本棚の構造体の初期化
	g_Door.pos = D3DXVECTOR3(500.0f, 420.0f, 0.0f);		// 位置
	g_Door.bUse = true;										// 使用しているかどうか

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/book.png", &g_pTextureBookshelf);		// 本棚

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,		// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffBookshelf,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBookshelf->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCunDoor = 0; nCunDoor < MAX_POLYGON; nCunDoor++)
	{
		switch (nCunDoor)
		{	// 頂点座標
		case 0:
			pVtx[0].pos = D3DXVECTOR3(g_Door.pos.x , g_Door.pos.y + (MAX_BOOK_Y ), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Door.pos.x , g_Door.pos.y , 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Door.pos.x + (MAX_BOOK_X ), g_Door.pos.y + (MAX_BOOK_Y ), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Door.pos.x + (MAX_BOOK_X ), g_Door.pos.y, 0.0f);
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
	g_pVtxBuffBookshelf->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	本棚の終了処理
//-------------------------------------------------------------------------------
void UninitBookshelf(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBookshelf != NULL)
	{
		g_pVtxBuffBookshelf->Release();
		g_pVtxBuffBookshelf = NULL;
	}

	// テクスチャの開放
	// 本棚
	if (g_pTextureBookshelf != NULL)
	{
		g_pTextureBookshelf->Release();
		g_pTextureBookshelf = NULL;
	}
}

//-------------------------------------------------------------------------------
//	本棚の更新処理
//-------------------------------------------------------------------------------
void UpdateBookshelf(void)
{

}

//-------------------------------------------------------------------------------
//	本棚の描画処理
//-------------------------------------------------------------------------------
void DrawBookshelf(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストーリに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBookshelf, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCunDoor = 0; nCunDoor < MAX_POLYGON; nCunDoor++)
	{
		switch (nCunDoor)
		{

		case 0:
			//背景テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBookshelf);
			break;

		}


		//ストップ背景の描画
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
			nCunDoor * 4,		// 描画を開始する頂点インデックス
			NUM_POLYGON);			// 描画するプリミティブ数
	}
}