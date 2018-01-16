#pragma once
#include "Client_GroupChat.h"
#include "Client_Imple.h"
#include "afxwin.h"
#include"ClientDlg.h"
// CGroupChatDialog dialog

class CGroupChatDialog : public CDialogEx
{
	//DECLARE_DYNAMIC(CGroupChatDialog)

public:
	CGroupChatDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGroupChatDialog();
	void ShowServerInfo(string sValue);
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
														// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	Client_GroupChat *m_pClient;
	static UINT __cdecl StaticThreadFunc(LPVOID pParam);
	UINT ThreadFunc();
	void AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText);
	void CreateGroupChat(string sUserName, string sGroupName);
	string Group_Name,sUser, codegroup;
	CEdit text_BoxChat;
	afx_msg void OnBnClickedButton1();
private:
	HANDLE m_Thread_handle;
	CWinThread *cTh;
public:
	CEdit textBox_Data;
	CEdit textBox_User;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
