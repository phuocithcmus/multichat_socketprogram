
// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientDlg dialog



CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, textUser);
	DDX_Control(pDX, IDC_EDIT3, textData);
	DDX_Control(pDX, IDC_EDIT1, textBox);
	DDX_Control(pDX, IDC_BUTTON3, send_button);
	DDX_Control(pDX, IDC_EDIT4, text_User);
	DDX_Control(pDX, IDC_EDIT6, text_Group_Name);
	//DDX_Control(pDX, IDC_EDIT7, textBox_AddMem);
	DDX_Control(pDX, IDC_EDIT7, textBox_UserNameChat);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CClientDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CClientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CClientDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CClientDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CClientDlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT6, &CClientDlg::OnEnChangeEdit6)
	ON_BN_CLICKED(IDC_BUTTON7, &CClientDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT __cdecl CClientDlg::StaticThreadFunc(LPVOID pParam)
{
	CClientDlg *pYourClass = reinterpret_cast<CClientDlg*>(pParam);
	UINT retCode = pYourClass->ThreadFunc();

	return retCode;
}

UINT __cdecl CClientDlg::StaticThreadFuncRegister(LPVOID pParam)
{
	CClientDlg *pYourClass = reinterpret_cast<CClientDlg*>(pParam);
	UINT retCode = pYourClass->RegisterThreadFunc();

	return retCode;
}

UINT __cdecl CClientDlg::StaticThreadFuncRequestGroupChat(LPVOID pParam) {
	CClientDlg *pYourClass = reinterpret_cast<CClientDlg*>(pParam);
	UINT retCode = pYourClass->RequestGroupChatThreadFunc();

	return retCode;
}


UINT CClientDlg::ThreadFunc()
{
	// Do your thing, this thread now has access to all the classes member variables

	CString username;
	textUser.GetWindowTextW(username);
	m_pClient = new Client_Imple(this);
	// construct a std::string using the LPCSTR input
	CT2CA CStringToAscii2(username);
	string sResultedString2(CStringToAscii2);

	this->sUser = sResultedString2;
	if (m_pClient != NULL) {
		m_pClient->StartConnect(sResultedString2, "127.0.0.1", 1234);
	}
	return 0;
}


UINT CClientDlg::RegisterThreadFunc()
{
	// Do your thing, this thread now has access to all the classes member variables

	CString Group_Name;
	text_User.GetWindowTextW(Group_Name);

	CT2CA CStringToAscii(Group_Name);
	// TODO: Add your control notification handler code here

	string sResultedString(CStringToAscii);

	m_pClient = new Client_Imple(this);

	// construct a std::string using the LPCSTR input

	/*CT2CA CStringToAscii2(username);

	string sResultedString2(CStringToAscii2);*/

	m_pClient->StartConnectToRegister(sResultedString, "127.0.0.1", 1234);
	return 0;
}

UINT CClientDlg::RequestGroupChatThreadFunc() {
	// Do your thing, this thread now has access to all the classes member variables

	CString sUser;
	text_Group_Name.GetWindowTextW(sUser);

	CT2CA CStringToAscii(sUser);
	// TODO: Add your control notification handler code here

	string sResultedString(CStringToAscii);

	m_pClient = new Client_Imple(this);

	// construct a std::string using the LPCSTR input

	/*CT2CA CStringToAscii2(username);

	string sResultedString2(CStringToAscii2);*/

	m_pClient->StartConnectToRequestGroupChat(sResultedString, "127.0.0.1", 1234);

	return 0;
}


void CClientDlg::OnBnClickedButton3()
{

	CString sTextData;
	textData.GetWindowTextW(sTextData);

	CT2CA CStringToAscii(sTextData);
	// TODO: Add your control notification handler code here

	string sResultedString(CStringToAscii);
	if (m_pClient != NULL)
		m_pClient->SendData(sResultedString);
	/*CWnd* pWnd = GetDlgItem(IDC_EDIT7);
	pWnd->SetWindowText(_T(""));*/
}


void CClientDlg::ShowServerInfo(string sValue)
{
	CString strLine(sValue.c_str());
	// add CR/LF to text
	//MessageBox(sValue.c_str());
	AppendTextToEditCtrl(textBox, strLine);
	//DoModal();
	//UpdateData(TRUE);
}


void CClientDlg::AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText)
{
	// get the initial text length
	int nLength = edit.GetWindowTextLength();
	// put the selection at the end of text
	edit.SetSel(nLength, nLength);
	// replace the selection
	edit.ReplaceSel(pszText);
}


void CClientDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here

	ShowServerInfo(m_pClient->m_pUser + " is logged out\n");
	delete m_pClient;
}


void CClientDlg::OnBnClickedButton1()
{
	cTh = AfxBeginThread(
		StaticThreadFunc,
		this);

	//cTh->m_bAutoDelete = FALSE;
	m_Thread_handle = cTh->m_hThread;
	// TODO: Add your control notification handler code here
}


void CClientDlg::OnBnClickedButton4()
{

	cTh = AfxBeginThread(
		StaticThreadFuncRegister,
		this);

	//cTh->m_bAutoDelete = FALSE;
	m_Thread_handle = cTh->m_hThread;
}



void CClientDlg::OnBnClickedButton6()
{
	CString sTextData;
	textBox_UserNameChat.GetWindowTextW(sTextData);

	CT2CA CStringToAscii(sTextData);
	// TODO: Add your control notification handler code here

	string sResultedString(CStringToAscii);
	CChatOnlyPerson* m_ConectChat = new CChatOnlyPerson();
	m_ConectChat->Group_Name = sResultedString;
	m_ConectChat->sUser = this->sUser;
	m_ConectChat->codeChat = this->sUser + sResultedString;
	if (m_pClient != NULL) {
		m_pClient->SendUsernameChatWith(sResultedString, this->sUser);
		m_ConectChat->DoModal();
	}
	else if (m_pClient == NULL) {
		::MessageBox(NULL, _T("Bạn phải đăng nhập để chat."), _T("Thông báo"), MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
	}
	// TODO: Add your control notification handler code here
}


void CClientDlg::OnBnClickedButton5()
{
	CString sGroup;
	text_Group_Name.GetWindowTextW(sGroup);

	CT2CA CStringToAscii(sGroup);
	string sResultedString(CStringToAscii);
	CGroupChatDialog* m_GroupChat = new CGroupChatDialog();
	
	//m_GroupChat->Create(IDD_DIALOG1, this);
	m_GroupChat->sUser = this->sUser;
	m_GroupChat->Group_Name = sResultedString;
	m_GroupChat->codegroup = sResultedString;
	//m_GroupChat->ShowWindow(SW_SHOW);
	if (m_pClient != NULL) {
		m_pClient->SendGroupName(sResultedString);
		m_GroupChat->DoModal();
	}
	else {
		::MessageBox(NULL, _T("Bạn phải đăng nhập để tạo nhóm."), _T("Thông báo"), MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
	}
	
	// TODO: Add your control notification handler code here
	
	
	//ShowWindow(SW_HIDE);//hide the dialog box 1st
	
	
	//cTh = AfxBeginThread(
	//	StaticThreadFuncRequestGroupChat,
	//	this);

	//////cTh->m_bAutoDelete = FALSE;
	//m_Thread_handle = cTh->m_hThread;
	
	// TODO: Add your control notification handler code here
}


void CClientDlg::OnEnChangeEdit6()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CClientDlg::CreateGroupChat(string sUserName, string sGroupName, string send_client) {
	CGroupChatDialog* m_GroupChat = new CGroupChatDialog();
	m_GroupChat->sUser = sUserName;
	m_GroupChat->Group_Name = sGroupName;
	m_GroupChat->codegroup = sGroupName;
	if (m_pClient != NULL)
		m_pClient->SendDataMemName(send_client);
	m_GroupChat->DoModal();
}

void CClientDlg::CreateChatOnly(string sUserName, string sGroupName, string send_client) {
	CChatOnlyPerson* m_ConectChat = new CChatOnlyPerson();
	m_ConectChat->sUser = sUserName;
	m_ConectChat->Group_Name = send_client;
	m_ConectChat->Group_Name.erase(0, 2);
	m_ConectChat->codeChat = m_ConectChat->Group_Name + sUserName;
	if (m_pClient != NULL)
		m_pClient->SendDataMemName(send_client);
	m_ConectChat->DoModal();
}

void CClientDlg::CheckLogin(string sUserName) {
	if (m_pClient != NULL)
		m_pClient->SendStatus(sUserName);
}


void CClientDlg::OnBnClickedButton7()
{
	closesocket(m_pClient->s);
	OnOK();
	// TODO: Add your control notification handler code here
}
