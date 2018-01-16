
#include "stdafx.h"
#include "Client_GroupChat.h"
#include<stdio.h>

#include <string.h>
#include "GroupChatDialog.h"

Client_GroupChat::Client_GroupChat(CGroupChatDialog *dlg) {
	m_pClient = dlg;
}


Client_GroupChat::~Client_GroupChat(void) {

	closesocket(s);
	WSACleanup();
}


void Client_GroupChat::StartConnect(string sUser_Name,string sAddress = "127.0.0.1", int iPort = 1234) {
	struct sockaddr_in server;
	char *message, server_reply[2000];
	int recv_size;
	m_pUser = sUser_Name;
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return;
	}

	printf("Initialised.\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	printf("Socket created.\n");


	server.sin_addr.s_addr = inet_addr(sAddress.c_str());
	server.sin_family = AF_INET;
	server.sin_port = htons(iPort);

	//Connect to remote server
	if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("connect error");
		return;
	}

	puts("Connected");

	//Send some data
	//message = "GET / HTTP/1.1\r\n\r\n";
	/*

	puts("Data Send\n");
	*/
	//Receive a reply from the server
	while ((recv_size = recv(s, server_reply, 2000, 0)) != SOCKET_ERROR)
	{
		puts("Reply received\n");

		//Add a NULL terminating character to make it a proper string before printing
		server_reply[recv_size] = '\0';
		puts(server_reply);
		if (server_reply[0] == '0') {
			/*string sTempMsg = string(server_reply).erase(0, 1) + "\n";
			m_pClient->ShowServerInfo(sTempMsg);*/

			server_reply[recv_size] = '\0';
			string sTempMsg = string(server_reply).erase(0, 1);
			string code_group = sTempMsg;
			code_group.erase(code_group.find(" "));
			sTempMsg.erase(0, sTempMsg.find(" ") + 1);
			if (code_group == m_pClient->codegroup)
				m_pClient->ShowServerInfo(sTempMsg);
		}
		else if (string(server_reply) == "Tài khoản hiện không online") {
			::MessageBox(NULL, _T("Tài khoản hiện không online."), _T("Thông báo"), MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
		}
		//else if (server_reply[0] == '3') {
		//	string send_client = string(server_reply);
		//	send_client.erase(0, 1);
		//	string recv_client = send_client;
		//	send_client.erase(send_client.find('.'));

		//	//m_pClient->ShowServerInfo(m_pUser);
		//	recv_client.erase(0, recv_client.find('.') + 1);
		//	string group_name = recv_client;
		//	group_name.erase(group_name.find(' '));

		//	recv_client.erase(0, recv_client.find(' ') + 1);
		//	//m_pClient->ShowServerInfo(recv_client);
		//	if (recv_client == m_pUser) {
		//		string replys = "4Y" + send_client;
		//		m_pClient->CreateGroupChat(recv_client,group_name);
		//		send(s, replys.c_str(), replys.size(), 0);
		//	}
		//	else {
		//		string replys = "4N" + send_client;
		//		send(s, replys.c_str(), replys.size(), 0);
		//	}
		//}
		/*else if (server_reply[0] == '4') {
			string send_client = string(server_reply);
			char first_char = send_client[1];
			send_client.erase(0, 2);
			if (send_client == m_pUser) {
				if (first_char == 'N') {
					m_pClient->MessageBox(NULL, _T("Tài khoản đang offline"));
				}
				else if (first_char == 'Y') {
					m_pClient->MessageBox(NULL, _T("Đã thêm vào nhóm."));
				}
			}
		}*/
	}

}

void Client_GroupChat::SendData(string sMessage) {
	//string sTemp = "0" + m_pUser + ": " + sMessage + "\n";
	string sTemp = "0" + m_pClient->codegroup + " " + m_pUser + ": " + sMessage + "\n";
	if (send(s, sTemp.c_str(), sTemp.size(), 0) < 0)
	{
		puts("Send failed");
		return;
	}
}

void Client_GroupChat::SendDataMemName(string sName, string sGroupName) {
	string sendAccount = "3" + m_pUser + "." + sGroupName + " " + sName;

	if (send(s, sendAccount.c_str(), sendAccount.size(), 0) < 0)
	{
		puts("Send failed");
		return;
	}
}