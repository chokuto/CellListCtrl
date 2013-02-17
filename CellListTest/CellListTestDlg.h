
// CellListTestDlg.h : ヘッダー ファイル
//

#pragma once
#include "CellListCtrl.h"


// CCellListTestDlg ダイアログ
class CCellListTestDlg : public CDialogEx
{
// コンストラクション
public:
	CCellListTestDlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
	enum { IDD = IDD_CELLLISTTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CCellListCtrl m_List;
};
