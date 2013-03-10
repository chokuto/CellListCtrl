#pragma once
#include <vector>

// CCellListCtrl

// コントロールのウィンドウクラス名
const LPCTSTR CELLLISTCTRL_CLASSNAME = _T("CellListCtrl");

// データソース定義
class CCellListDataSource {
public:
	virtual int GetItem() const;
};

const DWORD CELLLIST_GRIDLINE_NONE = 0;
const DWORD CELLLIST_GRIDLINE_SOLID_HORZ = 1;
const DWORD CELLLIST_GRIDLINE_SOLID_VERT = 2;
const DWORD CELLLIST_GRIDLINE_SOLID = CELLLIST_GRIDLINE_SOLID_HORZ | CELLLIST_GRIDLINE_SOLID_VERT;

// カスタムコントロールクラス定義
class CCellListCtrl : public CWnd
{
	DECLARE_DYNAMIC(CCellListCtrl)

public:
	CCellListCtrl();
	virtual ~CCellListCtrl();

	int GetColumnCount() const;
	CString GetColumnHeadingText(int index) const;
	int GetColumnWidth(int index) const;
	bool InsertColumn(int index, LPCTSTR headingText, int width);
	bool DeleteColumn(int index);
	void DeleteAllColumns();
	bool SetColumnHeadingText(int index, LPCTSTR headingText);

	int GetItemCount() const;
	CString GetItemText(int iItem, int iColumn = 0) const;
	bool InsertItem(int index, LPCTSTR text);
	bool DeleteItem(int index);
	void DeleteAllItems();
	bool SetItemText(int iItem, int iColumn, LPCTSTR text);

	void SetTextColor(COLORREF textColor);
	COLORREF GetTextColor() const;

	void SetBackColor(COLORREF backColor);
	COLORREF GetBackColor() const;

	void SetHeadingTextColor(COLORREF textColor);
	COLORREF GetHeadingTextColor() const;

	void SetHeadingBackColor(COLORREF backColor);
	COLORREF GetHeadingBackColor() const;

	void SetGridlineStyle(DWORD style);
	DWORD GetGridlineStyle() const;

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnGetFont(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();

private:
	void DrawItem(CDC *pDC, int itemIndex, const CRect& itemArea) const;
	int GetItemHeightInPixel(CDC* pDC) const;
	bool RegisterWindowClass();
	bool IsValidColumn(int index) const;
	bool IsValidItem(int index) const;

	class CColumnImpl {
	public:
		CColumnImpl(const CString& text, int width);
		CString HeadingText() const;
		void SetHeadingText(const CString& text);
		int Width() const;
		void SetWidth(int width);
	private:
		CString m_headingText;
		int m_width;
	};
	std::vector<CColumnImpl> m_columns;

	class CItemImpl {
	public:
		explicit CItemImpl(const CString& itemText);
		CString Text(int index) const;
		void SetText(int index, const CString& itemText);
	private:
		std::vector<CString> m_texts;
	};
	std::vector<CItemImpl> m_items;

	HFONT m_hFont;
	COLORREF m_textColor;
	COLORREF m_backColor;
	COLORREF m_headingTextColor;
	COLORREF m_headingBackColor;
	DWORD m_gridlineStyle;
};


