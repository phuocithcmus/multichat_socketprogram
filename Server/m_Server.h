#pragma once
#include<afxSock.h>
#include <string>
#include <iostream>
#include <string.h>
class CServerDlg;

class m_Server
{
public:
	m_Server(CServerDlg* dialog);
	~m_Server(void);

	void StartListening(int iPort);

	static UINT __cdecl DataThreadFunc(LPVOID pParam);
	UINT SendReceiveData(SOCKET cSocket);
	void ClearServer();
	WSADATA wsa;
	SOCKET s, new_socket;
	struct sockaddr_in server, client;
	//static SOCKET sArray[100];
	int c;
	//static int iCount;
	int iTempCount;
	CServerDlg* m_pDialog;
	HANDLE m_Thread_handle[100];
	CWinThread *cpTh[100];
	static void SetStaticVariable(int iC, SOCKET cS);
};