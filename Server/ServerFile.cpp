
#pragma once
#include "stdafx.h"
#include "m_Server.h"
#include "Server.h"
#include "ServerDlg.h"
#include <Windows.h>
#include<afxSock.h>
#include<WS2tcpip.h>
#include <fstream>
#include "SaveFile.h"
#include "ServerFile.h"


static SOCKET sArray[100];
static int iCount;


ServerFile::ServerFile(CSaveFile* dialog) {
	m_pDialog = dialog;
}


ServerFile::~ServerFile(void) {
	closesocket(s);
	WSACleanup();
}


void ServerFile::ClearServer() {
	closesocket(s);
	WSACleanup();
}


void ServerFile::StartListening(int iPort = 1234) {
	iCount = 0;
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
		m_pDialog->ShowServerInfo("Could not create socket");
	}

	printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(iPort);

	//Bind
	if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		m_pDialog->ShowServerInfo("Bind failed with error code");
		exit(EXIT_FAILURE);
	}

	puts("Bind done");

	//Listen to incoming connections
	listen(s, 100);
	char *message;
	puts("Waiting for incoming connections...");
	m_pDialog->ShowServerInfo("Waiting for incoming connections...\n");
	c = sizeof(struct sockaddr_in);

	while ((new_socket = accept(s, (struct sockaddr *)&client, &c)) != INVALID_SOCKET)
	{

		puts("Connection accepted");
		// m_pDialog->ShowServerInfo("Connection accepted\n");
		//Reply to the client
		socklen_t len;
		struct sockaddr_storage addr;
		char ipstr[INET6_ADDRSTRLEN];
		int port;

		len = sizeof addr;
		getpeername(new_socket, (struct sockaddr*)&addr, &len);

		// deal with IPv4:
		if (addr.ss_family == AF_INET) {
			struct sockaddr_in *s = (struct sockaddr_in *)&addr;
			port = ntohs(s->sin_port);
			inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
		}

		printf("Peer IP address: %s\n", ipstr);
		m_pDialog->ShowServerInfo("Connected Peer IP address: " + string(ipstr) + "\n");


		CWinThread *cTh = AfxBeginThread(
			DataThreadFunc,
			(LPVOID)new_socket);
		++iCount;
		//m_Thread_handle[++iCount] = cTh->m_hThread;
		//cpTh[iCount] = cTh;
		sArray[iCount] = new_socket;
		//message = "Hello Client , I have received your connection.\n";
		//send(new_socket , message , strlen(message) , 0);

		//SetStaticVariable(iTempCount, new_socket);



	}
	if (new_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d", WSAGetLastError());
		return;
	}



}

UINT __cdecl ServerFile::DataThreadFunc(LPVOID pParam)
{

	SOCKET pYourSocket = reinterpret_cast<SOCKET>(pParam);
	//UINT retCode = pYourClass->ThreadFunc();
	//SendReceiveData(pYourClass);


	char *message;
	//message = "6";
	//send(pYourSocket, message, strlen(message), 0);
	char server_reply[2048];
	int recv_size;

	while ((recv_size = recv(pYourSocket, server_reply, 2048, 0)) != SOCKET_ERROR)
	{
	}
	return 0;
}


UINT ServerFile::SendReceiveData(SOCKET cSocket)
{

	return 0;
}


void ServerFile::SetStaticVariable(int iC, SOCKET cS)
{
	iCount = iC;
	//sArray[iCount] = cS;
}