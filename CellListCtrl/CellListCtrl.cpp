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
	: m_hFont(NULL)
	, m_textColor(::GetSysColor(COLOR_WINDOWTEXT))
	, m_backColor(::GetSysColor(COLOR_WINDOW))
	, m_headingTextColor(::GetSysColor(COLOR_WINDOWTEXT))
	, m_headingBackColor(::GetSysColor(COLOR_WINDOW))
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

const CCellListCtrl::CColumn& CCellListCtrl::Column(int index) const
{
	if (!IsValidColumn(index)) {
		AfxThrowInvalidArgException();
	}
	return m_columns[index];
}

bool CCellListCtrl::InsertColumn(int index, LPCTSTR headingText, int width)
{
	if (!IsValueInRange(index, 0, GetColumnCount())) {
		return false;
	}

	m_columns.insert(m_columns.begin() + index, CColumnImpl(headingText, width));

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

void CCellListCtrl::DeleteAllColumns()
{
	m_columns.clear();
}

bool CCellListCtrl::SetColumnHeadingText(int index, LPCTSTR headingText)
{
	if (!IsValidColumn(index)) {
		return false;
	}

	m_columns[index].SetHeadingText(headingText);
	return true;
}

int CCellListCtrl::GetItemCount() const
{
	return static_cast<int>(m_items.size());
}

const CCellListCtrl::CItem& CCellListCtrl::Item(int index) const
{
	if (!IsValidItem(index)) {
		AfxThrowInvalidArgException();
	}
	return m_items[index];
}

bool CCellListCtrl::InsertItem(int index, LPCTSTR text)
{
	if (!IsValueInRange(index, 0, GetItemCount())) {
		return false;
	}

	m_items.insert(m_items.begin() + index, CItemImpl(text));

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

void CCellListCtrl::DeleteAllItems()
{
	m_items.clear();
}

bool CCellListCtrl::SetItemText(int iItem, int iColumn, LPCTSTR text)
{
	if (!IsValidItem(iItem) || !IsValidColumn(iColumn)) {
		return false;
	}

	m_items[iItem].SetText(iColumn, text);
	return true;
}

void CCellListCtrl::SetTextColor(COLORREF textColor)
{
	m_textColor = textColor;
}

COLORREF CCellListCtrl::GetTextColor() const
{
	return m_textColor;
}

void CCellListCtrl::SetBackColor(COLORREF backColor)
{
	m_backColor = backColor;
}

COLORREF CCellListCtrl::GetBackColor() const
{
	return m_backColor;
}

void CCellListCtrl::SetHeadingTextColor(COLORREF textColor)
{
	m_headingTextColor = textColor;
}

COLORREF CCellListCtrl::GetHeadingTextColor() const
{
	return m_headingTextColor;
}

void CCellListCtrl::SetHeadingBackColor(COLORREF backColor)
{
	m_headingBackColor = backColor;
}

COLORREF CCellListCtrl::GetHeadingBackColor() const
{
	return m_headingBackColor;
}

BEGIN_MESSAGE_MAP(CCellListCtrl, CWnd)
	ON_MESSAGE(WM_GETFONT, &CCellListCtrl::OnGetFont)
	ON_MESSAGE(WM_SETFONT, &CCellListCtrl::OnSetFont)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CCellListCtrl メッセージ ハンドラー
LRESULT CCellListCtrl::OnGetFont(WPARAM wParam, LPARAM /*lParam*/)
{
	return reinterpret_cast<LRESULT>(m_hFont);
}

LRESULT CCellListCtrl::OnSetFont(WPARAM wParam, LPARAM /*lParam*/)
{
	m_hFont = reinterpret_cast<HFONT>(wParam);
	return 0;
}

void CCellListCtrl::OnPaint()
{
	CPaintDC dc(this);

	int dcStateID = dc.SaveDC();

	if (m_hFont != NULL) {
		dc.SelectObject(CFont::FromHandle(m_hFont));
	}

	dc.SetTextColor(m_headingTextColor);
	dc.SetBkColor(m_headingBackColor);

	CRect rcClient(0,0,0,0);
	GetClientRect(&rcClient);

	CRect rcLine(0, 0, rcClient.right, GetItemHeightInPixel(&dc));
	DrawItem(&dc, -1, &rcLine);

	dc.SetTextColor(m_textColor);
	dc.SetBkColor(m_backColor);

	int itemCount = GetItemCount();
	for (int iItem = 0; iItem < itemCount; ++iItem) {
		rcLine.OffsetRect(0, rcLine.Height());
		DrawItem(&dc, iItem, rcLine);
	}

	dc.RestoreDC(dcStateID);
}

void CCellListCtrl::DrawItem(CDC *pDC, int iItem, const CRect& rcLine) const
{
	pDC->FillSolidRect(&rcLine, pDC->GetBkColor());

	int currentCellLeft = 0;
	int columnCount = GetColumnCount();
	for (int iColumn = 0; iColumn < columnCount; ++iColumn) {
		int eachWidth = Column(iColumn).Width();
		CRect rcCell(currentCellLeft, rcLine.top, currentCellLeft + eachWidth, rcLine.bottom);
		CString strText = (iItem < 0) ? Column(iColumn).HeadingText() : Item(iItem).Text(iColumn);
		pDC->DrawText(strText, -1, &rcCell, DT_LEFT | DT_NOPREFIX);
		currentCellLeft += eachWidth;
	}
}

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


CCellListCtrl::CColumnImpl::CColumnImpl(const CString& text, int width) : m_headingText(text), m_width(width)
{
}

CString CCellListCtrl::CColumnImpl::HeadingText() const
{
	return m_headingText;
}

void CCellListCtrl::CColumnImpl::SetHeadingText(const CString& text)
{
	m_headingText = text;
}

int CCellListCtrl::CColumnImpl::Width() const
{
	return m_width;
}

void CCellListCtrl::CColumnImpl::SetWidth(int width)
{
	m_width = width;
}

CCellListCtrl::CItemImpl::CItemImpl(const CString& itemText)
{
	m_texts.push_back(itemText);
}

CString CCellListCtrl::CItemImpl::Text(int index) const
{
	return (static_cast<size_t>(index) < m_texts.size()) ? m_texts[index] : CString();
}

void CCellListCtrl::CItemImpl::SetText(int index, const CString& text)
{
	if (static_cast<size_t>(index) < m_texts.size()) {
		m_texts[index] = text;
	} else {
		m_texts.resize(index + 1);
		m_texts[index] = text;
	}
}
