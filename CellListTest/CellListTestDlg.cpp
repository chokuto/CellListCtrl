
// CellListTestDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "CellListTest.h"
#include "CellListTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCellListTestDlg ダイアログ

CCellListTestDlg::CCellListTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCellListTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCellListTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CELL_LIST, m_List);
}

BEGIN_MESSAGE_MAP(CCellListTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CCellListTestDlg メッセージ ハンドラー

BOOL CCellListTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	InitializeListCtrl();

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CCellListTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CCellListTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCellListTestDlg::InitializeListCtrl()
{
	{
		LOGFONT lf = {};
		lf.lfHeight = 21;
		_tcscpy_s(lf.lfFaceName, _T("Arial"));
		ENSURE(m_Font.CreateFontIndirect(&lf));
	}
	m_List.SetFont(&m_Font);
	ASSERT(m_List.GetFont() == &m_Font);

	m_List.SetHeadingTextColor(RGB(0,255,0));
	ASSERT(m_List.GetHeadingTextColor() == RGB(0,255,0));
	m_List.SetHeadingBackColor(RGB(255,0,255));
	ASSERT(m_List.GetHeadingBackColor() == RGB(255,0,255));

	m_List.SetTextColor(RGB(255,0,0));
	ASSERT(m_List.GetTextColor() == RGB(255,0,0));
	m_List.SetBackColor(RGB(0,255,255));
	ASSERT(m_List.GetBackColor() == RGB(0,255,255));

	m_List.InsertColumn(0, _T("Column 1"), 120);
	m_List.InsertColumn(1, _T("Column 2"), 160);
	m_List.InsertColumn(2, _T("Column 3"), 200);

	m_List.InsertItem(0, _T("Item 1-1"));
	m_List.SetItemText(0, 1, _T("Item 1-2"));

	for (int i = 1; i < 12; ++i) {
		CString str;
		str.Format(_T("Item %d-1"), i + 1);
		m_List.InsertItem(i, str);
	}
}
