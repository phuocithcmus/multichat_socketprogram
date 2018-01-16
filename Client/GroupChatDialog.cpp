// GroupChatDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"

#include "GroupChatDialog.h"
#include "afxdialogex.h"


// CGroupChatDialog dialog

//IMPLEMENT_DYNAMIC(CGroupChatDialog, CDialogEx)

CGroupChatDialog::CGroupChatDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CGroupChatDialog::~CGroupChatDialog()
{
}

void CGroupChatDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, text_BoxChat);
	DDX_Control(pDX, IDC_EDIT2, textBox_Data);
	DDX_Control(pDX, IDC_EDIT3, textBox_User);
}


BEGIN_MESSAGE_MAP(CGroupChatDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CGroupChatDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGroupChatDialog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CGroupChatDialog::OnBnClickedButton3)
END_MESSAGE_MAP()


// CGroupChatDialog message handlers
BOOL CGroupChatDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

									// TODO: Add extra initialization here
	CString cs(this->Group_Name.c_str());
	SetWindowText(cs);
	cTh = AfxBeginThread(
		StaticThreadFunc,
		this);

	//cTh->m_bAutoDelete = FALSE;
	m_Thread_handle = cTh->m_hThread;
	// TODO: Add your control notification handler code here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGroupChatDialog::OnPaint()
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
HCURSOR CGroupChatDialog::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGroupChatDialog::ShowServerInfo(string sValue)
{
	CString strLine(sValue.c_str());
	// add CR/LF to text
	//MessageBox(sValue.c_str());
	AppendTextToEditCtrl(text_BoxChat, strLine);
	//DoModal();
	//UpdateData(TRUE);
}

void CGroupChatDialog::AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText)
{
	// get the initial text length
	int nLength = edit.GetWindowTextLength();
	// put the selection at the end of text
	edit.SetSel(nLength, nLength);
	// replace the selection
	edit.ReplaceSel(pszText);
}



void CGroupChatDialog::OnBnClickedButton1()
{

	CString sTextData;
	textBox_Data.GetWindowTextW(sTextData);

	CT2CA CStringToAscii(sTextData);
	// TODO: Add your control notification handler code here

	string sResultedString(CStringToAscii);
	if (m_pClient != NULL)
		m_pClient->SendData(sResultedString);

	//	CClientDlg::cTh = AfxBeginThread(
	//	StaticThreadFunc,
	//	this);

	//cTh->m_bAutoDelete = FALSE;
	//m_Thread_handle = cTh->m_hThread;
	// TODO: Add your control notification handler code here
}

UINT __cdecl CGroupChatDialog::StaticThreadFunc(LPVOID pParam)
{
	CGroupChatDialog *pYourClass = reinterpret_cast<CGroupChatDialog*>(pParam);
	UINT retCode = pYourClass->ThreadFunc();

	return retCode;
}

UINT CGroupChatDialog::ThreadFunc()
{
	// Do your thing, this thread now has access to all the classes member variables
	m_pClient = new Client_GroupChat(this);

	// construct a std::string using the LPCSTR input

	m_pClient->StartConnect(this->sUser, "127.0.0.1", 1234);
	return 0;
}

void CGroupChatDialog::OnBnClickedButton2()
{
	CString sTextData;
	textBox_User.GetWindowTextW(sTextData);

	CT2CA CStringToAscii(sTextData);
	// TODO: Add your control notification handler code here

	string sResultedString(CStringToAscii);
	if (m_pClient != NULL)
		m_pClient->SendDataMemName(sResultedString, this->Group_Name);
	// TODO: Add your control notification handler code here
}


void CGroupChatDialog::CreateGroupChat(string sUserName, string sGroupName) {
	CGroupChatDialog* m_GroupChat = new CGroupChatDialog();
	m_GroupChat->sUser = sUserName;
	m_GroupChat->Group_Name = sGroupName;
	m_GroupChat->DoModal();
}

void CGroupChatDialog::OnBnClickedButton3()
{
	closesocket(m_pClient->s);
	OnOK();
	// TODO: Add your control notification handler code here
}
