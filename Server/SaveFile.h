
// ServerDlg.h : header file
//

#pragma once
#include "ServerFile.h"
#include <string.h>
#include <string>
#include <Windows.h>
#include "afxwin.h"
#include <iostream>
#include "ServerDlg.h"
using namespace std;
// CServerDlg dialog
class CSaveFile : public CDialogEx
{
	// Construction
public:
	CSaveFile(CWnd* pParent = NULL);	// standard constructor
	void ShowServerInfo(string sValue);
	// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


														// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	ServerFile *m_pServer;
	static UINT __cdecl StaticThreadFunc(LPVOID pParam);
	UINT ThreadFunc();
	void AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText);
private:
	HANDLE m_Thread_handle;
	CWinThread *cTh;
public:
	CEdit textBox;
};
