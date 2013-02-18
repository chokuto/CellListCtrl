// CellListDataSourceTest.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "CellListDataSourceTest.h"
#include "gtest/gtest.h"
#include "../CellListCtrl/CellListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �B��̃A�v���P�[�V���� �I�u�W�F�N�g�ł��B

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// MFC �����������āA�G���[�̏ꍇ�͌��ʂ�������܂��B
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: �K�v�ɉ����ăG���[ �R�[�h��ύX���Ă��������B
			_tprintf(_T("�v���I�ȃG���[: MFC �̏��������ł��܂���ł����B\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: �A�v���P�[�V�����̓�����L�q����R�[�h�������ɑ}�����Ă��������B
			::testing::InitGoogleTest(&argc, argv);
			nRetCode = RUN_ALL_TESTS();
		}
	}
	else
	{
		// TODO: �K�v�ɉ����ăG���[ �R�[�h��ύX���Ă��������B
		_tprintf(_T("�v���I�ȃG���[: GetModuleHandle �����s���܂���\n"));
		nRetCode = 1;
	}

	return nRetCode;
}

class CCellListDataSourceTest : public ::testing::Test {
protected:
	void SetUp()
	{
		m_pList = new CCellListCtrl();
	}
	void TearDown()
	{
		delete m_pList;
		m_pList = NULL;
	}

	CCellListCtrl* m_pList;
};

TEST_F(CCellListDataSourceTest, InitialColumnCountIsZero)
{
	EXPECT_EQ(0, m_pList->GetColumnCount());
}

TEST_F(CCellListDataSourceTest, InitialItemCountIsZero)
{
	EXPECT_EQ(0, m_pList->GetItemCount());
}

TEST_F(CCellListDataSourceTest, ColumnInsertion)
{
	EXPECT_TRUE(m_pList->InsertColumn(0, _T("Column 1"), 60));
	EXPECT_EQ(1, m_pList->GetColumnCount());

	EXPECT_TRUE(m_pList->InsertColumn(1, _T("Column 2"), 80));
	EXPECT_EQ(2, m_pList->GetColumnCount());

	EXPECT_TRUE(m_pList->InsertColumn(2, _T("Column 3"), 100));
	EXPECT_EQ(3, m_pList->GetColumnCount());
}

TEST_F(CCellListDataSourceTest, ColumnTexts)
{
	m_pList->InsertColumn(0, _T("Column 1"), 60);
	m_pList->InsertColumn(1, _T("Column 2"), 80);
	m_pList->InsertColumn(2, _T("Column 3"), 100);

	EXPECT_STREQ(_T("Column 1"), m_pList->Columns(0).HeadingText());
	EXPECT_STREQ(_T("Column 2"), m_pList->Columns(1).HeadingText());
	EXPECT_STREQ(_T("Column 3"), m_pList->Columns(2).HeadingText());
}

TEST_F(CCellListDataSourceTest, ColumnWidths)
{
	m_pList->InsertColumn(0, _T("Column 1"), 60);
	m_pList->InsertColumn(1, _T("Column 2"), 80);
	m_pList->InsertColumn(2, _T("Column 3"), 100);

	EXPECT_EQ(60, m_pList->Columns(0).Width());
	EXPECT_EQ(80, m_pList->Columns(1).Width());
	EXPECT_EQ(100, m_pList->Columns(2).Width());
}

TEST_F(CCellListDataSourceTest, ColumnInsertionIndexOutOfRange)
{
	m_pList->InsertColumn(0, _T("Column 1"), 60);
	m_pList->InsertColumn(1, _T("Column 2"), 80);
	m_pList->InsertColumn(2, _T("Column 3"), 100);

	EXPECT_FALSE(m_pList->InsertColumn(-1, _T("Column 4"), 60));
	EXPECT_EQ(3, m_pList->GetColumnCount());

	EXPECT_FALSE(m_pList->InsertColumn(4, _T("Column 5"), 60));
	EXPECT_EQ(3, m_pList->GetColumnCount());
}

TEST_F(CCellListDataSourceTest, ItemInsertion)
{
	m_pList->InsertColumn(0, _T("Column 1"), 60);
	m_pList->InsertColumn(1, _T("Column 2"), 80);
	m_pList->InsertColumn(2, _T("Column 3"), 100);

	EXPECT_TRUE(m_pList->InsertItem(0, _T("Item 1")));
	EXPECT_EQ(1, m_pList->GetItemCount());
	EXPECT_STREQ(_T("Item 1"), m_pList->GetItemText(0));
	EXPECT_STREQ(_T("Item 1"), m_pList->GetItemText(0, 0));
	EXPECT_STREQ(_T(""), m_pList->GetItemText(0, 1));
	EXPECT_STREQ(_T(""), m_pList->GetItemText(0, 2));
}

TEST_F(CCellListDataSourceTest, ItemTextChange)
{
	m_pList->InsertColumn(0, _T("Column 1"), 60);
	m_pList->InsertColumn(1, _T("Column 2"), 80);
	m_pList->InsertColumn(2, _T("Column 3"), 100);
	m_pList->InsertItem(0, _T("Item 1"));
	m_pList->InsertItem(1, _T("Item 2"));

	EXPECT_TRUE(m_pList->SetItemText(0, 0, _T("Item 1-1")));
	EXPECT_TRUE(m_pList->SetItemText(0, 1, _T("Item 1-2")));
	EXPECT_TRUE(m_pList->SetItemText(0, 2, _T("Item 1-3")));
	EXPECT_TRUE(m_pList->SetItemText(1, 2, _T("Item 2-3")));

	EXPECT_STREQ(_T("Item 1-1"), m_pList->GetItemText(0, 0));
	EXPECT_STREQ(_T("Item 1-2"), m_pList->GetItemText(0, 1));
	EXPECT_STREQ(_T("Item 1-3"), m_pList->GetItemText(0, 2));

	EXPECT_STREQ(_T("Item 2"), m_pList->GetItemText(1, 0));
	EXPECT_STREQ(_T(""), m_pList->GetItemText(1, 1));
	EXPECT_STREQ(_T("Item 2-3"), m_pList->GetItemText(1, 2));
}

