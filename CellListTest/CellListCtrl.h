#pragma once

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

protected:
	DECLARE_MESSAGE_MAP()

private:
	bool RegisterWindowClass();
};


