// CellListCtrl.cpp : 実装ファイル
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



// CCellListCtrl メッセージ ハンドラー

// コントロールのウィンドウクラス登録
bool CCellListCtrl::RegisterWindowClass()
{
	HINSTANCE hInstance = AfxGetInstanceHandle();
	WNDCLASS wndclass = {};
	if (::GetClassInfo(hInstance, CELLLISTCTRL_CLASSNAME, &wndclass)) {
		// 既に登録済みなら何もしない
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
