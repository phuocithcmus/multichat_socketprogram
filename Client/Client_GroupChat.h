#pragma once
#include <iostream>
#include "string.h"
#include "string"
#include <afxSock.h>
using namespace std;
class CGroupChatDialog;

class Client_GroupChat
{
public:
	Client_GroupChat(CGroupChatDialog *dlg);
	~Client_GroupChat(void);
	void StartConnect(string sUser_Name, string sAddress, int iPort);
	void SendData(string sMessage);
	void SendDataMemName(string sName, string GroupName);
	WSADATA wsa;
	SOCKET s;
	CGroupChatDialog *m_pClient;
	string m_pUser;
};