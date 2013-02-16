// CellListCtrl.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "CellListCtrl.h"

// CCellListCtrl

IMPLEMENT_DYNAMIC(CCellListCtrl, CWnd)

CCellListCtrl::CCellListCtrl()
{
	if (!RegisterWindowClass()) {
		AfxThrowResourceException();
	}
}

CCellListCtrl::~CCellListCtrl()
{
}


BEGIN_MESSAGE_MAP(CCellListCtrl, CWnd)
END_MESSAGE_MAP()



// CCellListCtrl ���b�Z�[�W �n���h���[

// �R���g���[���̃E�B���h�E�N���X�o�^
bool CCellListCtrl::RegisterWindowClass()
{
	HINSTANCE hInstance = AfxGetInstanceHandle();
	WNDCLASS wndclass = {};
	if (::GetClassInfo(hInstance, CELLLISTCTRL_CLASSNAME, &wndclass)) {
		// ���ɓo�^�ς݂Ȃ牽�����Ȃ�
		return true;
	}

	wndclass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = ::DefWindowProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = NULL;
	wndclass.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_3DFACE + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = CELLLISTCTRL_CLASSNAME;

	if (!AfxRegisterClass(&wndclass)) {
		return false;
	}

	return true;
}
