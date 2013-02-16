
// CellListTestDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "CellListTest.h"
#include "CellListTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCellListTestDlg �_�C�A���O

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


// CCellListTestDlg ���b�Z�[�W �n���h���[

BOOL CCellListTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B
	BasicTest();

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CCellListTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CCellListTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCellListTestDlg::BasicTest()
{
	ASSERT(0 == m_List.GetColumnCount());
	ASSERT(0 == m_List.GetItemCount());

	ASSERT(false == m_List.InsertColumn(-1, _T("Column 1"), 60));
	ASSERT(false == m_List.InsertColumn(1, _T("Column 1"), 60));

	ASSERT(true == m_List.InsertColumn(0, _T("Column 1"), 60));
	ASSERT(1 == m_List.GetColumnCount());
	ASSERT(_T("Column 1") == m_List.GetColumnHeadingText(0));
	ASSERT(60 == m_List.GetColumnWidth(0));

	ASSERT(true == m_List.InsertColumn(1, _T("Column 2"), 80));
	ASSERT(true == m_List.InsertColumn(2, _T("Column 3"), 100));
	ASSERT(3 == m_List.GetColumnCount());

	ASSERT(false == m_List.InsertItem(-1, _T("Item 1")));
	ASSERT(false == m_List.InsertItem(1, _T("Item 1")));
	ASSERT(true == m_List.InsertItem(0, _T("Item 1")));
	ASSERT(_T("Item 1") == m_List.GetItemText(0));
	ASSERT(true == m_List.SetItemText(0, 0, _T("Item 1-1")));
	ASSERT(_T("Item 1-1") == m_List.GetItemText(0));
	ASSERT(true == m_List.SetItemText(0, 1, _T("Item 1-2")));
	ASSERT(true == m_List.SetItemText(0, 2, _T("Item 1-3")));

	m_List.InsertItem(1, _T("Item 2-1"));
	m_List.SetItemText(1, 1, _T("Item 2-2"));

	m_List.InsertItem(2, _T("Item 3-1"));
	m_List.SetItemText(2, 1, _T("Item 3-2"));
}
