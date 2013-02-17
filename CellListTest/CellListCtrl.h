#pragma once
#include <vector>

// CCellListCtrl

// �R���g���[���̃E�B���h�E�N���X��
const LPCTSTR CELLLISTCTRL_CLASSNAME = _T("CellListCtrl");

// �J�X�^���R���g���[���N���X��`
class CCellListCtrl : public CWnd
{
	DECLARE_DYNAMIC(CCellListCtrl)

public:
	CCellListCtrl();
	virtual ~CCellListCtrl();

	int GetColumnCount() const;
	int GetColumnWidth(int index) const;
	CString GetColumnHeadingText(int index) const;
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

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

private:
	int GetItemHeightInPixel(CDC* pDC) const;
	bool RegisterWindowClass();
	bool IsValidColumn(int index) const;
	bool IsValidItem(int index) const;

	struct Column {
		CString HeadingText;
		int Width;
	};
	std::vector<Column> m_columns;

	struct Item {
		std::vector<CString> Text;
	};
	std::vector<Item> m_items;
};


