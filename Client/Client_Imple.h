#pragma once
#include <iostream>
#include "string.h"
#include "string"
#include <afxSock.h>
using namespace std;
class CClientDlg;

class Client_Imple
{
public:
	Client_Imple(CClientDlg *dlg);
	~Client_Imple(void);
	void StartConnect(string user, string sAddress, int iPort);
	void StartConnectToRegister(string messageRegister, string sAddress, int iPort); 
	void StartConnectToRequestGroupChat(string Group_Name, string sAddress, int iPort); // làm bị dư
	void SendData(string sMessage);
	void SendDataMemName(string sName);
	void SendOffline(string sName);// làm bị dư
	void SendUsernameChatWith(string sName, string sGroupName);
	void SendStatus(string status);
	void SendGroupName(string name);
	void SendRegister(string user, string password);
	WSADATA wsa;
	SOCKET s;
	CClientDlg *m_pClient;
	string m_pUser;

};