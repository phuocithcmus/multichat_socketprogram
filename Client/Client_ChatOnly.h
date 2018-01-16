#pragma once
#include <iostream>
#include "string.h"
#include "string"
#include <afxSock.h>
using namespace std;
class CChatOnlyPerson;

class Client_ChatOnly
{
public:
	Client_ChatOnly(CChatOnlyPerson *dlg);
	~Client_ChatOnly(void);
	void StartConnect(string sUser_Name, string sAddress, int iPort);
	void SendData(string sMessage);
	void SendDataFilename();
	void RequestSendingFile();
	WSADATA wsa;
	SOCKET s;
	CChatOnlyPerson *m_pClient;
	string m_pUser;
	string fileNameToSend;
};