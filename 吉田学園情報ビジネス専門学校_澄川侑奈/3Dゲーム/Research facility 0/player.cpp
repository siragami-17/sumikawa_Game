//--------------------------------------------------------------------------------
//
//	�v���C���[�̏��� [player.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "player.h"					// �v���C���[
#include "keyboard.h"				// �L�[�{�[�h
#include "camera.h"					// �J����
#include "Goal.h"					// �S�[��
#include "meshfild.h"				// �n��
#include "shadow.h"					// �e

//--------------------------------------------------------------------------------
//	�}�N����`
//--------------------------------------------------------------------------------
#define MAX_MOVE		(0.3f)		// �ړ���
#define MAX_ROT			(0.1f)		// ����

#define MAX_FLAME		(40)		// �Đ��t���[����
#define MAX_COUNTER		(10)		// ���[�V�����J�E���^�[

#define MAX_JUMP		(2)		// �W�����v

#define MAX_PLAYER		(20)		// ���f����

//--------------------------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------------------------
Player g_player;					// �v���C���[�̏��	
Model g_Model;						// �v���C���[�̏��
											
//--------------------------------------------------------------------------------
// ����������
//--------------------------------------------------------------------------------
HRESULT InitPlayer(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v���C���[�̍ŏ��̃��[�V����
	g_player.motionType = MOTION_NONE;

	// �v���C���[�\���̂̏�����
	g_player.pos =D3DXVECTOR3 (0.0f,0.0f,0.0f);						// ���̈ʒu
	g_player.posOld =D3DXVECTOR3 (0.0f,0.0f,0.0f);					// �̂̈ʒu
	g_player.rot = D3DXVECTOR3 (0.0f,0.0f,0.0f);					// ����
	g_player.rotDest = D3DXVECTOR3(0.0f,0.0f,0.0f) ;				// �ړI�̌���
	g_player.move =  D3DXVECTOR3(0.0f,0.0f,0.0f) ;					// �ړ���
	g_player.bJump = false;											// �W�����v�����ǂ���
	g_player.bGetKey = false;										// ���������Ă��邩
	g_player.nIdx = SetShadow(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		// �e
	g_player.oldmotionType = MOTION_NONE;


	// ���f���̓ǂݍ���
	// �e�L�X�g�t�@�C���ǂݍ���
	FILE *pfile = fopen("data/TEXT/motion.txt", "r");
	char string[255][255];

	// ���f�����̓ǂݍ���(�p�[�c)
	while (fgets(string[0], 255, pfile) != NULL)
	{// NULL����Ȃ�������
		fscanf(pfile, "%s", string[0]);

		if (strcmp(string[0], "NUM_MODEL") == 0)
		{//�@strcmp������͈�v������
			fscanf(pfile, "%s %d", &string[0], &g_player.nNumModel);
			break;
		}
	}

	// X�t�@�C�����̓ǂݍ���
	for (int nCntNumModel = 0; nCntNumModel < g_player.nNumModel; nCntNumModel++)
	{
		while (fgets(string[0], 255, pfile) != NULL)
		{
			if (strstr(string[0], "MODEL_FILENAME"))
			{
				sscanf(string[0], "%s %s %s %*s %*s\n", string[1], string[2], &g_player.aModel[nCntNumModel].sModelFailName);
				break;
			}
		}
		// X�t�@�B���̓ǂݍ���
		D3DXLoadMeshFromX(g_player.aModel[nCntNumModel].sModelFailName,			// �ǂݍ���X�t�@�C����
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[nCntNumModel].pBuffMat,							// �}�e���A��(���_���)
			NULL,
			&g_player.aModel[nCntNumModel].nNumMat,								// �}�e���A����
			&g_player.aModel[nCntNumModel].pMesh);								// ���b�V��(���_���)
	}
	for (int nCntNumModel = 0; nCntNumModel < g_player.nNumModel; nCntNumModel++)
	{
		// �K�w�\��
		while (fgets(string[0], 255, pfile) != NULL)
		{
			if (strstr(string[0], "INDEX"))
			{
				sscanf(string[0], "%s %s %d", string[0], string[1], &g_player.aModel[nCntNumModel].nIdxModelNum);		// �C���f�b�N�X���
				fscanf(pfile, "%s%s%d%*s%*s", string[1], string[2], &g_player.aModel[nCntNumModel].nIdModelParent);
				fscanf(pfile, "%s%s%f%f%f", string[3], string[4], &g_player.aModel[nCntNumModel].pos.x, &g_player.aModel[nCntNumModel].pos.y, &g_player.aModel[nCntNumModel].pos.z);
				fscanf(pfile, "%s%s%f%f%f", string[5], string[6], &g_player.aModel[nCntNumModel].rot.x, &g_player.aModel[nCntNumModel].rot.y, &g_player.aModel[nCntNumModel].rot.z);
				break;
			}
		}

		// �}�e���A���f�[�^���擾����
		g_player.aModel[nCntNumModel].pMat = (D3DXMATERIAL*)g_player.aModel[nCntNumModel].pBuffMat->GetBufferPointer();
		g_player.aModel[nCntNumModel].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ������

																				// ���_�����擾����
		g_player.aModel[nCntNumModel].nNumVtx = g_player.aModel[nCntNumModel].pMesh->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
		g_player.aModel[nCntNumModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_player.aModel[nCntNumModel].pVtxBuff);

		for (int nCntvtx = 0; nCntvtx < g_player.aModel[nCntNumModel].nNumVtx; nCntvtx++)
		{
			g_player.aModel[nCntNumModel].vtx = *(D3DXVECTOR3*)g_player.aModel[nCntNumModel].pVtxBuff;		// ���_���W�̑��

																											// x�̍ő�l�̔�r
			if (g_player.aModel[nCntNumModel].vtx.x >= g_player.aModel[nCntNumModel].vtxMax.x)
			{
				g_player.aModel[nCntNumModel].vtxMax.x = g_player.aModel[nCntNumModel].vtx.x;
			}

			// y�̍ő�l�̔�r
			if (g_player.aModel[nCntNumModel].vtx.y >= g_player.aModel[nCntNumModel].vtxMax.y)
			{
				g_player.aModel[nCntNumModel].vtxMax.y = g_player.aModel[nCntNumModel].vtx.y;
			}

			// z�̍ő�l�̔�r
			if (g_player.aModel[nCntNumModel].vtx.z >= g_player.aModel[nCntNumModel].vtxMax.z)
			{
				g_player.aModel[nCntNumModel].vtxMax.z = g_player.aModel[nCntNumModel].vtx.z;
			}

			// x�̍ŏ��l�̔�r
			if (g_player.aModel[nCntNumModel].vtx.x <= g_player.aModel[nCntNumModel].vtxMax.x)
			{
				g_player.aModel[nCntNumModel].vtxMax.x = g_player.aModel[nCntNumModel].vtx.x;
			}

			// y�̍ŏ��l�̔�r
			if (g_player.aModel[nCntNumModel].vtx.y <= g_player.aModel[nCntNumModel].vtxMax.y)
			{
				g_player.aModel[nCntNumModel].vtxMax.y = g_player.aModel[nCntNumModel].vtx.y;
			}

			// z�̍ŏ��l�̔�r
			if (g_player.aModel[nCntNumModel].vtx.z <= g_player.aModel[nCntNumModel].vtxMax.z)
			{
				g_player.aModel[nCntNumModel].vtxMax.z = g_player.aModel[nCntNumModel].vtx.z;
			}
			// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			g_player.aModel[nCntNumModel].pVtxBuff += g_player.aModel[nCntNumModel].sizeFVF;
		}
		//���_�o�b�t�@���A�����b�N
		g_player.aModel[nCntNumModel].pMesh->UnlockVertexBuffer();
	}

	//�L�[���
	for (int nCnt1 = 0; nCnt1 < MOTION_MAX; nCnt1++)
	{// ���[�V�����ǂݍ���
	 // �L�[���̎擾
		while (fgets(string[0], 255, pfile) != NULL)
		{
			if (strstr(string[0], "MOTIONSET"))
			{
				fscanf(pfile, "%s%s%d%*s%*s%*s%*s", string[1], string[2], &g_player.aMotionInfo[nCnt1].nLoop);
				fscanf(pfile, "%s%s%d", string[3], string[4], &g_player.aMotionInfo[nCnt1].nMaxKey);
				break;
			}
		}
		for (int nCnt2 = 0; nCnt2 < g_player.aMotionInfo[nCnt1].nMaxKey; nCnt2++)
		{
			while (fgets(string[0], 255, pfile) != NULL)
			{
				if (strstr(string[0], "KEYSET"))
				{
					fscanf(pfile, "%s%s%d", string[1], string[2], &g_player.aMotionInfo[nCnt1].aKeyInfo[nCnt2].nFrame);
					break;
				}
			}
			for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
			{
				while (fgets(string[0], 255, pfile) != NULL)
				{
					if (strstr(string[0], "KEY"))
					{
						fscanf(pfile, "%s%s%f%f%f", string[1], string[2], &g_player.aMotionInfo[nCnt1].aKeyInfo[nCnt2].aKey[nCnt].fPosKeyX,
							&g_player.aMotionInfo[nCnt1].aKeyInfo[nCnt2].aKey[nCnt].fPosKeyY,
							&g_player.aMotionInfo[nCnt1].aKeyInfo[nCnt2].aKey[nCnt].fPosKeyZ);

						fscanf(pfile, "%s%s%f%f%f%*s", string[3], string[4], &g_player.aMotionInfo[nCnt1].aKeyInfo[nCnt2].aKey[nCnt].fRotKeyX,
							&g_player.aMotionInfo[nCnt1].aKeyInfo[nCnt2].aKey[nCnt].fRotKeyY,
							&g_player.aMotionInfo[nCnt1].aKeyInfo[nCnt2].aKey[nCnt].fRotKeyZ);
						break;
					}
				}
			}

			while (fgets(string[0], 255, pfile) != NULL)
			{
				if (strstr(string[0], "END_KEYSET"))
				{
					break;
				}
			}
		}
		while (fgets(string[0], 255, pfile) != NULL)
		{
			if (strstr(string[0], "END_MOTIONSET"))
			{
				break;
			}
		}
	}
	// ���_�ɂ���pos�ƃ��f�����Ƃɂ���pos�����������ɍ��̂�����
	for (int nCntMotion = 0; nCntMotion < MOTION_MAX; nCntMotion++)
	{
		for (int nCntKey = 0; nCntKey < g_player.aMotionInfo[nCntMotion].nMaxKey; nCntKey++)
		{
			for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
			{
				g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fPosKeyX += g_player.aModel[nCnt].pos.x;
				g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fPosKeyY += g_player.aModel[nCnt].pos.y;
				g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fPosKeyZ += g_player.aModel[nCnt].pos.z;

				g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fRotKeyX += g_player.aModel[nCnt].rot.x;
				g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fRotKeyY += g_player.aModel[nCnt].rot.y;
				g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fRotKeyZ += g_player.aModel[nCnt].rot.z;
			}
		}
	}
	fclose(pfile);
	return S_OK;
}

//--------------------------------------------------------------------------------
// �I������
//--------------------------------------------------------------------------------
void UninitPlayer(void)
{
	for (int nCutModel = 0; nCutModel < g_player.nNumModel; nCutModel++)
	{
		// ���b�V���̊J��
		if (g_player.aModel[nCutModel].pMesh != NULL)
		{
			g_player.aModel[nCutModel].pMesh->Release();
			g_player.aModel[nCutModel].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_player.aModel[nCutModel].pBuffMat != NULL)
		{
			g_player.aModel[nCutModel].pBuffMat->Release();
			g_player.aModel[nCutModel].pBuffMat = NULL;
		}
	}
}

//--------------------------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------------------------
void UpdatePlayer(void)
{
	// �J�����̏������炤
	Camera * pCamera;
	pCamera = GetCamera();

	// �S�[���̏��
	Goal *pGoal = GetGoal();




	// �v���C���[�̈ړ�����
	if (GetkeyboardPress(DIK_W) == true)
	{// W�L�[��������

		g_player.motionType = MOTION_WORK;

		if (GetkeyboardPress(DIK_D) == true)
		{// D�L�[��������
			g_player.move.x += sinf(pCamera->rot.y + D3DX_PI * 3 / 4) * MAX_MOVE;
			g_player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 3 / 4) * MAX_MOVE;
			g_player.rotDest.y = -D3DX_PI * 3 / 4 - pCamera->rot.y;

		}
		else if (GetkeyboardPress(DIK_A) == true)
		{// A�L�[��������
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 3 / 4) * MAX_MOVE;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 3 / 4) * MAX_MOVE;
			g_player.rotDest.y = D3DX_PI * 3 / 4 - pCamera->rot.y;

		}
		else
		{
			g_player.move.x += sinf(pCamera->rot.y + D3DX_PI) * MAX_MOVE;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI) * MAX_MOVE;
			g_player.rotDest.y = D3DX_PI - pCamera->rot.y;
		}
	}
	else if (GetkeyboardPress(DIK_S) == true)
	{
		g_player.motionType = MOTION_WORK;

		if (GetkeyboardPress(DIK_A) == true)
		{
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 1 / 4) * MAX_MOVE;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 1 / 4) * MAX_MOVE;
			g_player.rotDest.y = D3DX_PI * 1 / 4 - pCamera->rot.y;

		}
		else if (GetkeyboardPress(DIK_D) == true)
		{
			g_player.move.x += sinf(pCamera->rot.y + D3DX_PI * 1 / 4) * MAX_MOVE;
			g_player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 1 / 4) * MAX_MOVE;
			g_player.rotDest.y = -D3DX_PI * 1 / 4 - pCamera->rot.y;
		}
		else
		{
			g_player.move.x -= sinf(pCamera->rot.y + D3DX_PI) * MAX_MOVE;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI) * MAX_MOVE;
			g_player.rotDest.y = 0.0f - pCamera->rot.y;
		}
	}
	else if (GetkeyboardPress(DIK_A) == true)		// �E�ړ��E���ړ�
	{// A�L�[��������
		g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 2 / 4) * MAX_MOVE;
		g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 2 / 4) * MAX_MOVE;
		g_player.rotDest.y = D3DX_PI * 2 / 4 - pCamera->rot.y;

		g_player.motionType = MOTION_WORK;
	}
	else if (GetkeyboardPress(DIK_D) == true)
	{// D�L�[��������
		g_player.move.x += sinf(pCamera->rot.y + D3DX_PI * 2 / 4) * MAX_MOVE;
		g_player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 2 / 4) * MAX_MOVE;
		g_player.rotDest.y = -D3DX_PI * 2 / 4 - pCamera->rot.y;

		g_player.motionType = MOTION_WORK;
	}
	else if (GetkeyboardPress(DIK_W) == false)
	{// �L�[���͂���ĂȂ�������
		g_player.motionType = MOTION_NONE;
	}
	else if (GetkeyboardPress(DIK_A) == false)
	{
		g_player.motionType = MOTION_NONE;
	}
	else if (GetkeyboardPress(DIK_S) == false)
	{
		g_player.motionType = MOTION_NONE;
	}
	else if (GetkeyboardPress(DIK_D) == false)
	{
		g_player.motionType = MOTION_NONE;
	}

	// ���[�V����
	MotionPlayer(g_player.motionType);

	// ���V�t�g��������
	if (GetkeyboardPress(DIK_LSHIFT) == true)
	{// ����]
		g_player.rot.y -= MAX_ROT;
	}

	// �E�V�t�g��������
	if (GetkeyboardPress(DIK_RSHIFT) == true)
	{// �E��]
		g_player.rot.y += MAX_ROT;
	}


	// �d��
//	g_player.pos.y--;

	//// �v���C���[�̈ʒu��0�ȉ��̎�
	//if (g_player.pos.y <= 0)
	//{
	//	if (GetkeyboardTrgger(DIK_SPACE) == true && g_player.bJump == false)
	//	{//�W�����v�̏���(2�i�W�����v�̐���)
	//		g_player.move.y = MAX_JUMP;
	//		g_player.bJump = true;

	//		g_player.motionType = MOTION_JUMP;
	//	}
	//}




	// �ʒu�̍X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;
	g_player.pos.z += g_player.move.z;

	// �ړI��]����
	if ((g_player.rotDest.y - g_player.rot.y) > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}
	if ((g_player.rotDest.y - g_player.rot.y) < (-D3DX_PI))
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}

	// �����Ă����
	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.1f;

	// ��]����
	if (g_player.rot.y < (-D3DX_PI))
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}
	if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}

	// �ړ��E��]�ʂ̌����@�����ňړ��ʂ��O�܂Ō��炷
	g_player.move.x += (0 - g_player.move.x) * 0.08f;		
	g_player.move.y += (0 - g_player.move.y) * 0.05f;
	g_player.move.z += (0 - g_player.move.z) * 0.08f;


	// �e���Z�b�g����
	SetPositionShadow(g_player.nIdx, D3DXVECTOR3(g_player.pos.x, 0.0f, g_player.pos.z));


}

//--------------------------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------------------------
void DrawPlayer(void)
{
	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾:
	D3DXMATRIX mtxRot, mtxTrans;					// �v�Z�p�̃}�g���b�N�X
	D3DMATERIAL9 matDef;							// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;								// �}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorld);

	// �����𔽉f(y,x,z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCutModel = 0; nCutModel < g_player.nNumModel; nCutModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;		// �v�Z�p�}�g���b�N�X

		D3DXMATRIX mtxParent;						// �e�̃}�g���b�N�X

		// �e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player.aModel[nCutModel].mtxWorld);

		// �����𔽉f(y,x,z)
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCutModel].rot.y, g_player.aModel[nCutModel].rot.x, g_player.aModel[nCutModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCutModel].mtxWorld, &g_player.aModel[nCutModel].mtxWorld, &mtxRotModel);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCutModel].pos.x, g_player.aModel[nCutModel].pos.y, g_player.aModel[nCutModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCutModel].mtxWorld, &g_player.aModel[nCutModel].mtxWorld, &mtxTransModel);
		
		// �e�p�[�c�̐e�̃}�g���b�N�X��ݒ�
		if (g_player.aModel[nCutModel].nIdModelParent != -1)		// p:�v���C���[ m:���f�� nld:�ԍ�
		{
			mtxParent = g_player.aModel[g_player.aModel[nCutModel].nIdModelParent].mtxWorld;
		}
		else
		{// �e�ȊO
			// �v���C���[�̃}�g���b�N�X��ݒ�
			mtxParent = g_player.mtxWorld;
		}

		//�e�ǂݍ���
		D3DXMatrixMultiply(&g_player.aModel[nCutModel].mtxWorld,
						   &g_player.aModel[nCutModel].mtxWorld,
						   &mtxParent);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCutModel].mtxWorld);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[nCutModel].pBuffMat->GetBufferPointer();

		for (int nCutMat = 0; nCutMat < (int)g_player.aModel[nCutModel].nNumMat; nCutMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			// ���f��(�p�[�c)�̕`��
			g_player.aModel[nCutModel].pMesh->DrawSubset(nCutMat);
		}
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//--------------------------------------------------------------------------------
//	�v���C���[�̎擾
//--------------------------------------------------------------------------------
Player *GetPlayer(void)
{
	return &g_player;			// �v���C���[�̏��̐擪�A�h���X��Ԃ�
}

//--------------------------------------------------------------------------------
//	���[�V�����̏���
//--------------------------------------------------------------------------------
void MotionPlayer(MOTION_STATE motionType)
{
	float fPosDiffX[MAX_PLAYER];		// �ʒu���̍���
	float fPosDiffY[MAX_PLAYER];		// �ʒu���̍���
	float fPosDiffZ[MAX_PLAYER];		// �ʒu���̍���
	float fRotDiffX[MAX_PLAYER];		// �ʒu���̍���
	float fRotDiffY[MAX_PLAYER];		// �ʒu���̍���
	float fRotDiffZ[MAX_PLAYER];		// �ʒu���̍���
	float fPosXAsk[MAX_PLAYER];			// ���߂�l�ʒuX
	float fPosYAsk[MAX_PLAYER];			// ���߂�l�ʒuY
	float fPosZAsk[MAX_PLAYER];			// ���߂�l�ʒuZ
	float fRotXAsk[MAX_PLAYER];			// ���߂�l�ʒuX
	float fRotYAsk[MAX_PLAYER];			// ���߂�l�ʒuY
	float fRotZAsk[MAX_PLAYER];			// ���߂�l�ʒuZ

	// �O��̃��[�V�����ƌ��݂̃��[�V������r
	if (g_player.oldmotionType != motionType)
	{
		g_player.nNumKey = 0;
	}

	// ���݂̃��[�V������ۑ�
	g_player.oldmotionType = motionType;

	// �ő�L�[�ɍs���܂ł̏���
	if (g_player.nNumKey < g_player.aMotionInfo[motionType].nMaxKey - 1)
	{
		for (int nCntKey = 0; g_player.nNumKey < g_player.aMotionInfo[motionType].nMaxKey - 1; nCntKey++)
		{
			for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
			{
				// ���������߂�
				fPosDiffX[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey + 1].aKey[nCnt].fPosKeyX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyX;
				fPosDiffY[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey + 1].aKey[nCnt].fPosKeyY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyY;
				fPosDiffZ[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey + 1].aKey[nCnt].fPosKeyZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyZ;

				fRotDiffX[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey + 1].aKey[nCnt].fRotKeyX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyX;
				fRotDiffY[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey + 1].aKey[nCnt].fRotKeyY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyY;
				fRotDiffZ[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey + 1].aKey[nCnt].fRotKeyZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyZ;

				// ���߂�l(�ʒu�{����*���[�V������/�t���[����)
				fPosXAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyX + fPosDiffX[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);
				fPosYAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyY + fPosDiffY[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);
				fPosZAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyZ + fPosDiffZ[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);

				fRotXAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyX + fRotDiffX[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);
				fRotYAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyY + fRotDiffY[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);
				fRotZAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyZ + fRotDiffZ[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);

				// ���f���̈ʒu�ɑ��
				g_player.aModel[nCnt].pos.x = fPosXAsk[nCnt];
				g_player.aModel[nCnt].pos.z = fPosZAsk[nCnt];
				g_player.aModel[nCnt].pos.y = fPosYAsk[nCnt];

				g_player.aModel[nCnt].rot.x = fRotXAsk[nCnt];
				g_player.aModel[nCnt].rot.y = fRotYAsk[nCnt];
				g_player.aModel[nCnt].rot.z = fRotZAsk[nCnt];


			}
			// ���[�V�����J�E���^�[�𖈃t���[�������Ƃɑ��₷
			g_player.nNumMotion += 1;

			if (g_player.nNumMotion >= g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame)
			{// ���[�V�����J�E���^�[���t���[�����𒴂�����
				if (g_player.nNumKey < g_player.aMotionInfo[motionType].nMaxKey - 1)
				{// ���[�v����
					g_player.nNumKey++;		// ���̃L�[�ɍs��
				}
				g_player.nNumMotion = 0;		// ���[�V�����J�E���^�[��������
			}
			else if (g_player.nNumMotion < g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame)
			{// ���[�v���Ȃ�
				break;
			}
		}
	}
	// �ő�L�[�̎��̏���
	if (g_player.nNumKey == g_player.aMotionInfo[motionType].nMaxKey - 1)
	{
		if (g_player.aMotionInfo[motionType].nLoop == 1)
		{// ���[�V�������[�v
			for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
			{
				// ���������߂�
				fPosDiffX[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fPosKeyX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyX;
				fPosDiffY[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fPosKeyY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyY;
				fPosDiffZ[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fPosKeyZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyZ;
																		
				fRotDiffX[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fRotKeyX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyX;
				fRotDiffY[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fRotKeyY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyY;
				fRotDiffZ[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[0].aKey[nCnt].fRotKeyZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyZ;

				// ���߂�l(�ʒu�{����*���[�V������/�t���[����)
				fPosXAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyX + fPosDiffX[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);
				fPosYAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyY + fPosDiffY[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);
				fPosZAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyZ + fPosDiffZ[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);

				fRotXAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyX + fRotDiffX[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);
				fRotYAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyY + fRotDiffY[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);
				fRotZAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyZ + fRotDiffZ[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].nFrame);

				// ���f���̈ʒu�ɑ��
				g_player.aModel[nCnt].pos.x = fPosXAsk[nCnt];
				g_player.aModel[nCnt].pos.z = fPosZAsk[nCnt];
				g_player.aModel[nCnt].pos.y = fPosYAsk[nCnt];

				g_player.aModel[nCnt].rot.x = fRotXAsk[nCnt];
				g_player.aModel[nCnt].rot.y = fRotYAsk[nCnt];
				g_player.aModel[nCnt].rot.z = fRotZAsk[nCnt];
			}
			// ���[�V�����J�E���^�[�𖈃t���[�������Ƃɑ��₷
			g_player.nNumMotion += 1;

			if (g_player.nNumMotion >= g_player.aMotionInfo[motionType].aKeyInfo[0].nFrame)
			{// ���[�V�����J�E���^�[���t���[�����𒴂�����
				g_player.nNumKey = 0;		// �L�[���Œ�	
				g_player.nNumMotion = 0;	// ���[�V�����J�E���^�[�ŏ��ɖ߂�
			}
		}
		else
		{// ���f�������[�v�����Ȃ�
			for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
			{
				// ���������߂�
				fPosDiffX[nCnt] = g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].aKey[nCnt].fPosKeyX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyX;
				fPosDiffY[nCnt] = g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].aKey[nCnt].fPosKeyY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyY;
				fPosDiffZ[nCnt] = g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].aKey[nCnt].fPosKeyZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyZ;

				fRotDiffX[nCnt] = g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].aKey[nCnt].fRotKeyX - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyX;
				fRotDiffY[nCnt] = g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].aKey[nCnt].fRotKeyY - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyY;
				fRotDiffZ[nCnt] = g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].aKey[nCnt].fRotKeyZ - g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyZ;

				// ���߂�l(�ʒu�{����*���[�V������/�t���[����)
				fPosXAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyX + fPosDiffX[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].nFrame);
				fPosYAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyY + fPosDiffY[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].nFrame);
				fPosZAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fPosKeyZ + fPosDiffZ[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].nFrame);

				fRotXAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyX + fRotDiffX[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].nFrame);
				fRotYAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyY + fRotDiffY[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].nFrame);
				fRotZAsk[nCnt] = g_player.aMotionInfo[motionType].aKeyInfo[g_player.nNumKey].aKey[nCnt].fRotKeyZ + fRotDiffZ[nCnt] * ((float)g_player.nNumMotion / (float)g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].nFrame);

				// ���f���̈ʒu�ɑ��
				g_player.aModel[nCnt].pos.x = fPosXAsk[nCnt];
				g_player.aModel[nCnt].pos.z = fPosZAsk[nCnt];
				g_player.aModel[nCnt].pos.y = fPosYAsk[nCnt];

				g_player.aModel[nCnt].rot.x = fRotXAsk[nCnt];
				g_player.aModel[nCnt].rot.y = fRotYAsk[nCnt];
				g_player.aModel[nCnt].rot.z = fRotZAsk[nCnt];
			}
			// ���[�V�����J�E���^�[�𖈃t���[�������Ƃɑ��₷
			g_player.nNumMotion += 1;

			// ���[�V�����J�E���^�[���t���[�����𒴂�����
			if (g_player.nNumMotion >= g_player.aMotionInfo[MOTION_NONE].aKeyInfo[0].nFrame)
			{

				g_player.nNumMotion = 0;	// ���[�V�����J�E���^�[�ŏ��ɖ߂�

				g_player.motionType = MOTION_NONE;
			}
		}

	}

}