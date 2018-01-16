// ChatOnlyPerson.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ChatOnlyPerson.h"
#include "afxdialogex.h"


//CChatOnlyPerson dialog

//IMPLEMENT_DYNAMIC(CChatOnlyPerson, CDialogEx)

CChatOnlyPerson::CChatOnlyPerson(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CChatOnlyPerson::~CChatOnlyPerson()
{
}

void CChatOnlyPerson::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, textBox_Chat);
	DDX_Control(pDX, IDC_EDIT2, textBox_ChatInput);
	DDX_Control(pDX, IDC_EDIT3, textBox_InforSendFile);
	DDX_Control(pDX, IDC_ANH, m_Anh);
}


BEGIN_MESSAGE_MAP(CChatOnlyPerson, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CChatOnlyPerson::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT2, &CChatOnlyPerson::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON3, &CChatOnlyPerson::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CChatOnlyPerson::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_EDIT1, &CChatOnlyPerson::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CChatOnlyPerson::OnBnClickedButton2)
	ON_STN_CLICKED(IDC_ANH, &CChatOnlyPerson::OnStnClickedAnh)
	ON_BN_CLICKED(IDC_BUTTON6, &CChatOnlyPerson::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CChatOnlyPerson::OnBnClickedButton7)
END_MESSAGE_MAP()


// CGroupChatDialog message handlers
BOOL CChatOnlyPerson::OnInitDialog()
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

void CChatOnlyPerson::OnPaint()
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
HCURSOR CChatOnlyPerson::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChatOnlyPerson::ShowServerInfo(string sValue)
{
	CString strLine(sValue.c_str());
	// add CR/LF to text
	//MessageBox(sValue.c_str());
	AppendTextToEditCtrl(textBox_Chat, strLine);
	//DoModal();
	//UpdateData(TRUE);
}

void CChatOnlyPerson::ShowFileInfo(string sValue) {
	CString strLine(sValue.c_str());
	// add CR/LF to text
	//MessageBox(sValue.c_str());
	AppendTextToEditCtrl(textBox_InforSendFile, strLine);
	//DoModal();
	//UpdateData(TRUE);
}

void CChatOnlyPerson::AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText)
{
	// get the initial text length
	int nLength = edit.GetWindowTextLength();
	// put the selection at the end of text
	edit.SetSel(nLength, nLength);
	// replace the selection
	edit.ReplaceSel(pszText);
}



void CChatOnlyPerson::OnBnClickedButton1()
{

	CString sTextData;
	textBox_ChatInput.GetWindowTextW(sTextData);

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

UINT __cdecl CChatOnlyPerson::StaticThreadFunc(LPVOID pParam)
{
	CChatOnlyPerson *pYourClass = reinterpret_cast<CChatOnlyPerson*>(pParam);
	UINT retCode = pYourClass->ThreadFunc();

	return retCode;
}

UINT CChatOnlyPerson::ThreadFunc()
{
	// Do your thing, this thread now has access to all the classes member variables
	m_pClient = new Client_ChatOnly(this);

	// construct a std::string using the LPCSTR input

	m_pClient->StartConnect(this->sUser, "127.0.0.1", 1234);
	return 0;
}

void CChatOnlyPerson::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

//void CChatOnlyPerson::CreateChatOnly(string sUserName, string sGroupName, string send_client) {
//	CChatOnlyPerson* m_ConectChat = new CChatOnlyPerson();
//	m_ConectChat->sUser = sUserName;
//	m_ConectChat->Group_Name = sGroupName;
//	if (m_pClient != NULL)
//		m_pClient->SendDataMemName(send_client);
//	m_ConectChat->DoModal();
//}

void CChatOnlyPerson::OnBnClickedButton3()
{
	if (m_pClient != NULL)
		m_pClient->SendDataFilename();
	// TODO: Add your control notification handler code here
}


void CChatOnlyPerson::OnBnClickedButton4()
{
	if (m_pClient != NULL)
		m_pClient->RequestSendingFile();
	// TODO: Add your control notification handler code here
}


void CChatOnlyPerson::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CChatOnlyPerson::OnBnClickedButton2()
{
	closesocket(m_pClient->s);
	OnOK();
	// TODO: Add your control notification handler code here
}


void CChatOnlyPerson::OnStnClickedAnh()
{
	// TODO: Add your control notification handler code here
}


void CChatOnlyPerson::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
}


void CChatOnlyPerson::LoadBitmapFile() {
	string Image = bmpFile;
	CString t(Image.c_str());
	CStringW strw(t);
	LPCWSTR ptr = strw;
	CBitmap bmpfile;
	HBITMAP hBmp = (HBITMAP)LoadImage(AfxGetInstanceHandle(), ptr, IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	if (hBmp != NULL)
	{
		//bmTemp.DeleteObject();
		m_Anh.SetBitmap(hBmp);
		UpdateData(FALSE);
		//m_Bitmap là biến đại diện của control Picture Control

	}
	else {
		::MessageBox(0, _T("Couldn't load the image"), _T("Error"), MB_OK);
	}
}

void CChatOnlyPerson::OnBnClickedButton7()
{
	CString Filter;
	Filter = "all files (*.bmp, *.jpg, *.gif, *tiff) |*.bmp; *.jpg; *.gif; BMP |*.bmp| (*.bmp) JPG |*.jpg| (*.jpg) GIF *.tiff| (*.gif) |*.gif| () TIFF |*.tiff|| (*.tiff)";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, Filter, NULL);

	//Press the OK button(dlg.DoModal) / / function to display the dialog box
		if(dlg.DoModal() == IDOK)
	{
			// open dialog box to obtain image information
			CString path = dlg.GetPathName(); // get the file path name such as D:\pic\abc.bmp
			CString EntName = dlg.GetFileExt(); // get the file extension
			CString filn = dlg.GetFileName();
			CImage img1;
			int dimx = 213, dimy = 284;
			img1.Load((LPCTSTR)path);
			CDC *screenDC = GetDC();
			CDC mDC;
			mDC.CreateCompatibleDC(screenDC);
			CBitmap b;
			b.CreateCompatibleBitmap(screenDC, dimx, dimy);

			CBitmap *pob = mDC.SelectObject(&b);
			mDC.SetStretchBltMode(HALFTONE);
			img1.StretchBlt(mDC.m_hDC, 0, 0, dimx, dimy, 0, 0, img1.GetWidth(), img1.GetHeight(), SRCCOPY);
			mDC.SelectObject(pob);

			m_Anh.SetBitmap((HBITMAP)b.Detach());
			::MessageBox(0, path, _T("Error"), MB_OK);
			//HBITMAP hBmp = NULL;
			////(EntName.MakeLower); // the file extension is converted to a lowercase character
			//hBmp = (HBITMAP)::LoadImageW(NULL, path, IMAGE_BITMAP, 218*2, 123*2, LR_LOADFROMFILE);
			////Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(path, false);
			////bitmap->GetHBITMAP(NULL, &hBmp);
			////delete bitmap;
			//if (hBmp != NULL)
			//{
			//	//bmTemp.DeleteObject();
			//	m_Anh.SetBitmap(hBmp);
			//	UpdateData(FALSE);
			//	//m_Anh là biến đại diện của control Picture Control
			//}
			//else {
			//	::MessageBox(0, (LPCWSTR)GetLastError(), _T("Error"), MB_OK);
			//}
		//}
	}
	// TODO: Add your control notification handler code here
}
