//--------------------------------------------------------------------------------
//
//	�����蔻��̏��� [collision.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "collision.h"			// �����蔻��

//--------------------------------------------------------------------------------
// �����蔻��̐ݒ�
//--------------------------------------------------------------------------------
bool SetCollision(D3DXVECTOR3 * pPos1, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 size1, D3DXVECTOR3 * pPos2, D3DXVECTOR3 size2)
{
	bool isGround = false;// ����Ă��邩�ǂ���

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / 2, size1.y, size1.z / 2) + *pPos1;          //�Ԃ��鑤�̍ő�l
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / 2, 0.0f, -size1.z / 2) + *pPos1;           //�Ԃ��鑤�̍ŏ��l
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / 2, size2.y, size2.z / 2) + *pPos2;         //�Ԃ����鑤�̍ő�l
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / 2, 0.0f, -size2.z / 2) + *pPos2;         //�Ԃ����鑤�̍ŏ��l

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x&&
		box1Max.z > box2Min.z&&
		box1Min.z < box2Max.z)
	{
		if (box1Max.y > box2Min.y&&
			pPosOld->y + size1.y / 2 < box2Min.y)
		{//y���̉�
			pPos1->y = box2Min.y - size1.y;
		}
		if (box1Min.y < box2Max.y&&
			pPosOld->y >= box2Max.y)
		{//y���̏�
			pPos1->y = box2Max.y;
			isGround = true;
		}
		if (box1Max.x > box2Min.x&&
			pPosOld->x + size1.x / 2 <= box2Min.x)
		{//X���̍�
			pPos1->x = box2Min.x - size1.x / 2;
		}
		if (box1Min.x < box2Max.x&&
			pPosOld->x - size1.x / 2 >= box2Max.x)
		{//x���̉E
			pPos1->x = box2Max.x + size1.x / 2;
		}
		if (box1Max.z > box2Min.z&&
			pPosOld->z + size1.z / 2 <= box2Min.z)
		{//z���̎�O
			pPos1->z = box2Min.z - size1.z / 2;
		}
		if (box1Min.z < box2Max.z&&
			pPosOld->z - size1.z / 2 >= box2Max.z)
		{//z���̉�
			pPos1->z = box2Max.z + size1.z / 2;
		}
	}
	return isGround;
}