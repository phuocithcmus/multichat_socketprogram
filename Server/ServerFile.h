#pragma once
#include<afxSock.h>
#include <string>
#include <iostream>
#include <string.h>
class CSaveFile;

class ServerFile
{
public:
	ServerFile(CSaveFile* dialog);
	~ServerFile(void);

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
	CSaveFile* m_pDialog;
	HANDLE m_Thread_handle[100];
	CWinThread *cpTh[100];
	static void SetStaticVariable(int iC, SOCKET cS);
};
