
// ClientDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "Client_Imple.h"
#include "GroupChatDialog.h"
#include "ChatOnlyPerson.h"

// CClientDlg dialog
class CClientDlg : public CDialogEx
{
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor
	void ShowServerInfo(string sValue);
	void ShowFileInfo(string sValue);
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENT_DIALOG };
#endif

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
public:
	Client_Imple *m_pClient = NULL;
	string sUser;
	static UINT __cdecl StaticThreadFunc(LPVOID pParam);
	static UINT __cdecl StaticThreadFuncRegister(LPVOID pParam);
	static UINT __cdecl StaticThreadFuncRequestGroupChat(LPVOID pParam);
	UINT RegisterThreadFunc();
	UINT RequestGroupChatThreadFunc();
	UINT ThreadFunc();
	void AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText);
	void CreateGroupChat(string sUserName, string sGroupName, string send_client);
	void CreateChatOnly(string sUserName, string sGroupName, string send_client);
	void CheckLogin(string sUserName);
private:
	HANDLE m_Thread_handle;
	CWinThread *cTh;
public:
	CEdit textUser;
	CEdit textData;
	afx_msg void OnBnClickedButton3();
	CEdit textBox;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	CButton send_button;
	CEdit text_User;
	afx_msg void OnBnClickedButton4();
	CEdit text_Group_Name;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton5();
	CEdit textBox_AddMem;
	afx_msg void OnEnChangeEdit6();
	CEdit textBox_UserNameChat;
	afx_msg void OnBnClickedButton7();
};
