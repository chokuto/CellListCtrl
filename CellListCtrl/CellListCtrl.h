#pragma once
#include <vector>

// CCellListCtrl

// コントロールのウィンドウクラス名
const LPCTSTR CELLLISTCTRL_CLASSNAME = _T("CellListCtrl");

// カスタムコントロールクラス定義
class CCellListCtrl : public CWnd
{
	DECLARE_DYNAMIC(CCellListCtrl)

public:
	CCellListCtrl();
	virtual ~CCellListCtrl();

	class CColumn {
	public:
		virtual CString HeadingText() const = 0;
		virtual int Width() const = 0;
	};
	const CColumn& Columns(int index) const;

	int GetColumnCount() const;
	bool InsertColumn(int index, LPCTSTR headingText, int width);
	bool DeleteColumn(int index);
	void DeleteAllColumns();
	bool SetColumnHeadingText(int index, LPCTSTR headingText);

	class CItem {
	};
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

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnGetFont(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();

private:
	int GetItemHeightInPixel(CDC* pDC) const;
	bool RegisterWindowClass();
	bool IsValidColumn(int index) const;
	bool IsValidItem(int index) const;

	class CColumnImpl : public CColumn {
	public:
		CColumnImpl(const CString& text, int width);
		virtual CString HeadingText() const;
		void SetHeadingText(const CString& text);
		virtual int Width() const;
		void SetWidth(int width);
	private:
		CString m_headingText;
		int m_width;
	};
	std::vector<CColumnImpl> m_columns;

	struct Item {
		std::vector<CString> Text;
	};
	std::vector<Item> m_items;

	HFONT m_hFont;
	COLORREF m_textColor;
	COLORREF m_backColor;
};


