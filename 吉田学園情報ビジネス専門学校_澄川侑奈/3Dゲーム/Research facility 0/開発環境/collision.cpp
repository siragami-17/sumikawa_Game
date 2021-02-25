//--------------------------------------------------------------------------------
//
//	当たり判定の処理 [collision.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "collision.h"			// 当たり判定

//--------------------------------------------------------------------------------
// 当たり判定の設定
//--------------------------------------------------------------------------------
bool SetCollision(D3DXVECTOR3 * pPos1, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 size1, D3DXVECTOR3 * pPos2, D3DXVECTOR3 size2)
{
	bool isGround = false;// 乗っているかどうか

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / 2, size1.y, size1.z / 2) + *pPos1;          //ぶつかる側の最大値
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / 2, 0.0f, -size1.z / 2) + *pPos1;           //ぶつかる側の最小値
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / 2, size2.y, size2.z / 2) + *pPos2;         //ぶつかられる側の最大値
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / 2, 0.0f, -size2.z / 2) + *pPos2;         //ぶつかられる側の最小値

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x&&
		box1Max.z > box2Min.z&&
		box1Min.z < box2Max.z)
	{
		if (box1Max.y > box2Min.y&&
			pPosOld->y + size1.y / 2 < box2Min.y)
		{//y軸の下
			pPos1->y = box2Min.y - size1.y;
		}
		if (box1Min.y < box2Max.y&&
			pPosOld->y >= box2Max.y)
		{//y軸の上
			pPos1->y = box2Max.y;
			isGround = true;
		}
		if (box1Max.x > box2Min.x&&
			pPosOld->x + size1.x / 2 <= box2Min.x)
		{//X軸の左
			pPos1->x = box2Min.x - size1.x / 2;
		}
		if (box1Min.x < box2Max.x&&
			pPosOld->x - size1.x / 2 >= box2Max.x)
		{//x軸の右
			pPos1->x = box2Max.x + size1.x / 2;
		}
		if (box1Max.z > box2Min.z&&
			pPosOld->z + size1.z / 2 <= box2Min.z)
		{//z軸の手前
			pPos1->z = box2Min.z - size1.z / 2;
		}
		if (box1Min.z < box2Max.z&&
			pPosOld->z - size1.z / 2 >= box2Max.z)
		{//z軸の奥
			pPos1->z = box2Max.z + size1.z / 2;
		}
	}
	return isGround;
}