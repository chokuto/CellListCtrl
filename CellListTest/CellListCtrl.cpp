// CellListCtrl.cpp : 実装ファイル
//

#include "stdafx.h"
#include "CellListCtrl.h"
#include <algorithm>

namespace {
	inline bool IsValueInRange(int value, int min, int max)
	{
		return (min <= value) && (value <= max);
	}
}

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


int CCellListCtrl::GetColumnCount() const
{
	return static_cast<int>(m_columns.size());
}

int CCellListCtrl::GetColumnWidth(int index) const
{
	return m_columns[index].Width;
}

CString CCellListCtrl::GetColumnHeadingText(int index) const
{
	return m_columns[index].HeadingText;
}

bool CCellListCtrl::InsertColumn(int index, LPCTSTR headingText, int width)
{
	if (!IsValueInRange(index, 0, GetColumnCount())) {
		return false;
	}

	Column column = {};
	column.HeadingText = headingText;
	column.Width = width;
	m_columns.insert(m_columns.begin() + index, column);

	int itemCount = GetItemCount();
	for (int iItem = 0; iItem < itemCount; ++iItem) {
		m_items[iItem].Text.resize(m_columns.size());
	}

	return true;
}

bool CCellListCtrl::DeleteColumn(int index)
{
	if (!IsValidColumn(index)) {
		return false;
	}

	m_columns.erase(m_columns.begin() + index);

	return true;
}

int CCellListCtrl::GetItemCount() const
{
	return static_cast<int>(m_items.size());
}

CString CCellListCtrl::GetItemText(int iItem, int iColumn) const
{
	if (!IsValidItem(iItem) || !IsValidColumn(iColumn)) {
		AfxThrowInvalidArgException();
	}
	const std::vector<CString>& texts = m_items[iItem].Text;
	return (iColumn < static_cast<int>(texts.size())) ? texts[iColumn] : CString();
}

bool CCellListCtrl::InsertItem(int index, LPCTSTR text)
{
	if (!IsValueInRange(index, 0, GetItemCount())) {
		return false;
	}

	Item item;
	item.Text.resize((std::max)(1, GetColumnCount()));
	item.Text[0] = text;
	m_items.insert(m_items.begin() + index, item);

	return true;
}

bool CCellListCtrl::DeleteItem(int index)
{
	if (!IsValidItem(index)) {
		return false;
	}

	m_items.erase(m_items.begin() + index);
	return true;
}

bool CCellListCtrl::SetItemText(int iItem, int iColumn, LPCTSTR text)
{
	if (!IsValidItem(iItem) || !IsValidColumn(iColumn)) {
		return false;
	}

	m_items[iItem].Text[iColumn] = text;
	return true;
}


BEGIN_MESSAGE_MAP(CCellListCtrl, CWnd)
END_MESSAGE_MAP()

// CCellListCtrl メッセージ ハンドラー

int CCellListCtrl::GetItemHeightInPixel(CDC* pDC) const
{
	TEXTMETRIC textMetric = {};
	pDC->GetTextMetrics(&textMetric);
	return textMetric.tmHeight;
}

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

bool CCellListCtrl::IsValidColumn(int index) const
{
	return (0 <= index && index < GetColumnCount());
}

bool CCellListCtrl::IsValidItem(int index) const
{
	return (0 <= index && index < GetItemCount());
}
