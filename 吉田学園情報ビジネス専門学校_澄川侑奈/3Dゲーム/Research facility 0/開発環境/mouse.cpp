//--------------------------------------------------------------------------------
//
//	mausu�̏��� [bullet.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include <windows.h>
#include "mouse.h"

int mainMouse(void)
{

	POINT pt;
	//�}�E�X�̌��݂̍��W���擾����
	GetCursorPos(&pt);

	//�}�E�X�̈ʒu��+10�ړ�����
	SetCursorPos(pt.x + 10, pt.y + 10);

	//�}�E�X�̍��{�^���������@�E��MOUSEEVENTF_RIGHTDOWN�@������MOUSEEVENTF_MIDDLEDOWN
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

	//�}�E�X�̍��{�^���𗣂�
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

	//�z�C�[�����������ɉ�
	mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -1, 0);

	//�z�C�[����������ɉ�
	mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 1, 0);

	//���������
	//HWND hWnd = WindowFromPoint(pt);
	//SendMessage(hWnd,WM_SETTEXT,0,(LPARAM)"������");

	return 0;
}
