#include "stdafx.h"
#include "Client_Imple.h"
#include<stdio.h>

#include <string.h>
#include "ClientDlg.h"

Client_Imple::Client_Imple(CClientDlg *dlg) {
	m_pClient = dlg;
}


Client_Imple::~Client_Imple(void) {

	closesocket(s);
	WSACleanup();
}

void Client_Imple::StartConnectToRequestGroupChat(string Group_Name, string sAddress, int iPort) {
	struct sockaddr_in server;
	char *message, server_reply[2000];
	int recv_size;

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
	if (m_pClient != NULL)
		SendGroupName(Group_Name);
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
		if (string(server_reply) == "Accept") {
			m_pClient->MessageBox(NULL, _T("Tạo nhóm thành công."));
		}
		else if (string(server_reply) == "No Accept") {
			m_pClient->MessageBox(NULL, _T("Tạo nhóm không thành công"));
		}
		else if (server_reply[0] == '3') {
			bool check = true;
			string send_client = string(server_reply);
			send_client.erase(0, 1);
			string recv_client = send_client;
			send_client.erase(send_client.find(' '));
			recv_client.erase(0, recv_client.find(' ') + 1);
			if (recv_client == m_pUser) {
				string replys = "4Y" + send_client;
				m_pClient->OnBnClickedButton5();
				send(s, replys.c_str(), replys.size(), 0);
			}
			else {
				string replys = "4N" + send_client;
				send(s, replys.c_str(), replys.size(), 0);
			}
		}
		else if (server_reply[0] == '4') {
			string send_client = string(server_reply);
			send_client.erase(0, 1);
			if (send_client == m_pUser) {
				if (send_client[0] == 'N')
					m_pClient->MessageBox(NULL, _T("Tài khoản đang offline"));
				else if (send_client[0] == 'Y') {
					m_pClient->MessageBox(NULL, _T("Đã thêm vào nhóm."));
				}
			}
		}
		else {
			string sTempMsg = string(server_reply) + "\n";
			m_pClient->ShowServerInfo(sTempMsg);
		}
	}
}

void Client_Imple::StartConnectToRegister(string messageRegister, string sAddress, int iPort) {
	struct sockaddr_in server;
	char *message, server_reply[2000];
	int recv_size;

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
	if (m_pClient != NULL)
		SendRegister(messageRegister, "123");
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
		if (string(server_reply) == "Tạo tài khoản thành công.") {
			m_pClient->MessageBox(NULL, _T("Tạo tài khoản thành công."));
			break;
		}
		else if (string(server_reply) == "Tài khoản đã tồn tại."){
			m_pClient->MessageBox(NULL, _T("Tài khoản đã tồn tại."));
			break;
		}
		else if (server_reply[0] == '3') {
			string send_client = string(server_reply);
			send_client.erase(0, 1);
			string recv_client = send_client;
			send_client.erase(send_client.find(' '));
			recv_client.erase(0, recv_client.find(' '));
			if (recv_client == m_pUser) {
				string replys = "4Y" + send_client;
				m_pClient->OnBnClickedButton5();
				send(s, replys.c_str(), replys.size(), 0);
			}
			else {
				string replys = "4N" + send_client;
				send(s, replys.c_str(), replys.size(), 0);
			}
		}
		else if (server_reply[0] == '4') {
			string send_client = string(server_reply);
			send_client.erase(0, 1);
			if (send_client == m_pUser) {
				if (send_client[0] == 'N')
					m_pClient->MessageBox(NULL, _T("Tài khoản đang offline"));
				else if (send_client[0] == 'Y') {
					m_pClient->MessageBox(NULL, _T("Đã thêm vào nhóm."));
				}
			}
		}
	}
	m_pClient->m_pClient = NULL;
}


void Client_Imple::StartConnect(string user, string sAddress = "192.168.100.0", int iPort = 1234) {
	struct sockaddr_in server;
	char *message, server_reply[2048];
	int recv_size;
	m_pUser = user;

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
	m_pClient->CheckLogin("6" + m_pUser);
	//Send some data
	//message = "GET / HTTP/1.1\r\n\r\n";
	/*

	puts("Data Send\n");
	*/
	//Receive a reply from the server
	while ((recv_size = recv(s, server_reply, 2048, 0)) != SOCKET_ERROR)
	{
		puts("Reply received\n");

		//Add a NULL terminating character to make it a proper string before printing
		server_reply[recv_size] = '\0';
		puts(server_reply);
		if (string(server_reply) == "Tạo tài khoản thành công.") {
			m_pClient->MessageBox(NULL, _T("Tạo tài khoản thành công."));
		}
		else if (string(server_reply) == "Tài khoản đã tồn tại."){
			m_pClient->MessageBox(NULL, _T("Tài khoản đã tồn tại."));
		}
		else if (server_reply[0] == '3') {
			string send_client = string(server_reply);
			send_client.erase(0, 1);
			string recv_client = send_client;
			send_client.erase(send_client.find('.'));

			//m_pClient->ShowServerInfo(m_pUser);
			recv_client.erase(0, recv_client.find('.') + 1);
			string group_name = recv_client;
			group_name.erase(group_name.find(' '));

			recv_client.erase(0, recv_client.find(' ') + 1);
			//m_pClient->ShowServerInfo(recv_client);
			if (recv_client == m_pUser) {
				string replys = "4Y" + send_client;
				m_pClient->CreateGroupChat(recv_client, group_name, replys);
			}
			/*else {
				string replys = "4N" + send_client;
				send(s, replys.c_str(), replys.size(), 0);
			}*/
		}
		else if (server_reply[0] == '4') {
			string send_client = string(server_reply);
			char first_char = send_client[1];
			send_client.erase(0, 2);
			if (send_client == m_pUser) {
				if (first_char == 'N')
					::MessageBox(NULL, _T("Tài khoản đang offline"), L"OK", MB_OK | MB_TOPMOST);
				/*else if (first_char == 'Y') {
					::MessageBox(NULL, _T("Đã thêm vào nhóm"), L"OK", MB_OK);
				}*/
			}
		}
		else if (string(server_reply) == "Accept") {
			::MessageBox(NULL, _T("Tạo nhóm thành công."), L"OK", MB_OK | MB_TOPMOST);
		}
		else if (string(server_reply) == "No Accept") {
			m_pClient->MessageBox(NULL, _T("Tạo nhóm không thành công"));
		}
		else if (string(server_reply) == "Đăng nhập thành công") {
			m_pClient->MessageBox(NULL, _T("Đăng nhập thành công"));
		}
		else if (string(server_reply) == "Đăng nhập thất bại. Xin đăng kí.") {
			m_pClient->MessageBox(NULL, _T("Đăng nhập thất bại. Xin đăng kí."));
		}
		/*else if (server_reply[0] =='6') {
			m_pClient->CheckLogin("6" + m_pUser);
		}*/
		else if (server_reply[0] == '5') {
			string send_client = string(server_reply);
			send_client.erase(0, 1);
			string recv_client = send_client;
			send_client.erase(send_client.find('.'));

			//m_pClient->ShowServerInfo(m_pUser);
			recv_client.erase(0, recv_client.find('.') + 1);
			string group_name = recv_client;
			group_name.erase(group_name.find(' '));
			recv_client.erase(0, recv_client.find(' ') + 1);
			//m_pClient->ShowServerInfo(recv_client);
			if (recv_client == m_pUser) {
				string replys = "4Y" + send_client;
				m_pClient->CreateChatOnly(recv_client, group_name, replys);
				//m_pClient->CreateChatOnlyMain(send_client, group_name, replys);
			}
			//else {
			//	string replys = "4N" + send_client;
			//	//send(s, replys.c_str(), replys.size(), 0);
			//	m_pClient->Offline(replys);
			//}
		}
		else if (string(server_reply) == "Tài khoản hiện không online") {
			::MessageBox(NULL, _T("Tài khoản hiện không online. Rời chat."), _T("Thông báo"), MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
		}
	}

}

void Client_Imple::SendGroupName(string name) {
	string sTemp = "2" + name ;

	if (send(s, sTemp.c_str(), sTemp.size(), 0) < 0)
	{
		puts("Send failed");
		return;
	}
}


void Client_Imple::SendData(string sMessage) {
	string sTemp = "0" + m_pUser + ">>" + sMessage + "\n";

	if (send(s, sTemp.c_str(), sTemp.size(), 0) < 0)
	{
		puts("Send failed");
		return;
	}
}


void Client_Imple::SendRegister(string user, string password = "123") {
	string sendAccount = "1" + user + "|" + password;

	if (send(s, sendAccount.c_str(), sendAccount.size(), 0) < 0)
	{
		puts("Send failed");
		return;
	}
}

void Client_Imple::SendDataMemName(string sName) {
	string sendAccount =sName;

	if (send(s, sendAccount.c_str(), sendAccount.size(), 0) < 0)
	{
		puts("Send failed");
		return;
	}
}

void Client_Imple::SendUsernameChatWith(string sName, string sGroupName) {
	string sendAccount = "5" + m_pUser + "." + sGroupName + " " + sName;

	if (send(s, sendAccount.c_str(), sendAccount.size(), 0) < 0)
	{
		puts("Send failed");
		return;
	}
}

void Client_Imple::SendOffline(string sName) {
	string sendAccount = sName;

	if (send(s, sendAccount.c_str(), sendAccount.size(), 0) < 0)
	{
		puts("Send failed");
		return;
	}
}

void Client_Imple::SendStatus(string status) {
	string sTemp = status;

	if (send(s, sTemp.c_str(), sTemp.size(), 0) < 0)
	{
		puts("Send failed");
		return;
	}
}
