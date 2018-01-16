#pragma once

#include "Client_ChatOnly.h"
#include "Client_Imple.h"
#include "afxwin.h"
#include"ClientDlg.h"
// CChatOnlyPerson dialog
class  CChatOnlyPerson : public CDialogEx
{
	//DECLARE_DYNAMIC(CGroupChatDialog)

public:
	CChatOnlyPerson(CWnd* pParent = NULL);   // standard constructor
	virtual ~CChatOnlyPerson();
	void ShowServerInfo(string sValue);
	void ShowFileInfo(string sValue);
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
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
	Client_ChatOnly *m_pClient;
	static UINT __cdecl StaticThreadFunc(LPVOID pParam);
	UINT ThreadFunc();
	void AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText);
	//void CreateGroupChat(string sUserName, string sGroupName);
	void CreateChatOnly(string sUserName, string sGroupName, string send_client);
	void LoadBitmapFile();
	string Group_Name, sUser, codeChat;
	afx_msg void OnBnClickedButton1();
private:
	HANDLE m_Thread_handle;
	CWinThread *cTh;
public:
	CEdit textBox_Chat;
	//afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit2();
	CEdit textBox_ChatInput;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnEnChangeEdit1();
	CEdit textBox_InforSendFile;
	afx_msg void OnBnClickedButton2();
	CStatic m_Anh;
	afx_msg void OnStnClickedAnh();
	string bmpFile;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
};
