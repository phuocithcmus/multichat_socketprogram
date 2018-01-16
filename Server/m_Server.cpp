#include "stdafx.h"
#include "m_Server.h"
#include "Server.h"
#include "ServerDlg.h"
#include <Windows.h>
#include<afxSock.h>
#include<WS2tcpip.h>
#include <fstream>


static SOCKET sArray[100];
static int iCount;
static char status[100];
static string a[1];
static char fileName[100];

//void CServerDlg::SaveFileFunc();

m_Server::m_Server(CServerDlg* dialog) {
	m_pDialog = dialog;
	//m_pDialog->SaveFileFunc();
}


m_Server::~m_Server(void) {
	closesocket(s);
	WSACleanup();
}


void m_Server::ClearServer() {
	closesocket(s);
	WSACleanup();
}


void m_Server::StartListening(int iPort = 1234) {
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

UINT __cdecl m_Server::DataThreadFunc(LPVOID pParam)
{

	SOCKET pYourSocket = reinterpret_cast<SOCKET>(pParam);
	//UINT retCode = pYourClass->ThreadFunc();
	//SendReceiveData(pYourClass);
	

	char *message;
	//message = "6";
	//send(pYourSocket, message, strlen(message), 0);
	char server_reply[2048];
	//memset(server_reply, 0, 2049);
	memset(server_reply, '0', sizeof(server_reply));
	int recv_size;
	a[0] = "";
	while ((recv_size = recv(pYourSocket, server_reply, 2048, 0)) != SOCKET_ERROR)
	{
		if (a[0] == "") {
			if (server_reply[0] == '1') {
				server_reply[recv_size] = '\0';
				//send(new_socket, server_reply, strlen(server_reply), 0);
				string username, password;
				username = server_reply;
				username.erase(username.begin(), username.begin() + 1);
				username.erase(username.begin() + username.find('|'), username.end());
				char* rep;
				fstream fin;
				fin.open("data.txt", ios::in);
				bool infor = true;
				int userNumber = 0;
				if (fin.is_open()) {
					string line;
					while (!fin.eof()) {
						getline(fin, line);
						userNumber++;
						if (line == username) {
							//::MessageBox(NULL, _T("Tài khoản đã tồn tại."), _T("Thông báo"), MB_OK | MB_ICONINFORMATION);
							rep = "Tài khoản đã tồn tại.";
							send(pYourSocket, rep, strlen(rep), 0);
							infor = false;
							break;
						}
					}
					if (userNumber == 100) {
						//::MessageBox(NULL, _T("Số lượng quá tải. Quay lại sau."), _T("Thông báo"), MB_OK | MB_ICONINFORMATION);
						//m_box2.SetWindowTextW(_T("Số lượng quá tải. Quay lại sau."));
						rep = "Số lượng quá tải. Quay lại sau.";
						send(pYourSocket, rep, strlen(rep), 0);
					}
					fin.close();
					fstream fout;
					fout.open("data.txt", ios::out | ios::app);
					if (infor == true) {
						fout << username << endl;
						//::MessageBox(NULL, _T("Tạo tài khoản thành công."), _T("Thông báo"), MB_OK | MB_ICONINFORMATION);
						//m_box2.SetWindowTextW(_T("Tạo tài khoản thành công."));
						rep = "Tạo tài khoản thành công.";
						send(pYourSocket, rep, strlen(rep), 0);
					}
					fout.close();
				}

			}
			else if (server_reply[0] == '2') {
				char* rep = "Accept";
				send(pYourSocket, rep, strlen(rep), 0);
			}
			else if (server_reply[0] == '0')
			{
				server_reply[recv_size] = '\0';
				//m_pDialog->ShowServerInfo("Message Received: "+ string(server_reply));
				for (int i = 1;i <= iCount; i++)
				{
					if (send(sArray[i], server_reply, recv_size, 0) < 0)
					{
						puts("Send failed");
						//return -1;
					}
				}
			}
			else if (server_reply[0] == '3')
			{
				//server_reply[recv_size] = '\0';
				////m_pDialog->ShowServerInfo("Message Received: "+ string(server_reply));
				//for (int i = 1;i <= iCount; i++)
				//{
				//	if (pYourSocket != sArray[i]) {
				//		if (send(sArray[i], server_reply, recv_size, 0) < 0)
				//		{
				//			puts("Send failed");
				//			//return -1;
				//		}
				//	}
				//}
				server_reply[recv_size] = '\0';
				//m_pDialog->ShowServerInfo("Message Received: "+ string(server_reply));
				string username = string(server_reply);
				username.erase(0, username.find(' ') + 1);

				fstream fin;
				fin.open("data.txt", ios::in);
				bool infor = true;
				int userNumber = 0;
				if (fin.is_open()) {
					string line;
					while (!fin.eof()) {
						getline(fin, line);
						userNumber++;
						if (line == username) {
							//::MessageBox(NULL, _T("Tài khoản đã tồn tại."), _T("Thông báo"), MB_OK | MB_ICONINFORMATION);
							if (status[userNumber - 1] == '1') {
								for (int i = 1;i <= iCount; i++)
								{
									if (pYourSocket != sArray[i]) {
										if (send(sArray[i], server_reply, recv_size, 0) < 0)
										{
											puts("Send failed");
											//return -1;
										}
									}
								}
								infor = false;
							}
							fin.close();
							break;
						}
					}
					if (infor == true) {
						char* rep = "Tài khoản hiện không online";
						send(pYourSocket, rep, strlen(rep), 0);
					}

				}
			}
			else if (server_reply[0] == '4')
			{
				server_reply[recv_size] = '\0';
				//m_pDialog->ShowServerInfo("Message Received: "+ string(server_reply));

				for (int i = 1;i <= iCount; i++)
				{
					if (pYourSocket != sArray[i]) {
						if (send(sArray[i], server_reply, recv_size, 0) < 0)
						{
							puts("Send failed");
							//return -1;
						}
					}
				}
			}
			else if (server_reply[0] == '5')
			{
				server_reply[recv_size] = '\0';
				//m_pDialog->ShowServerInfo("Message Received: "+ string(server_reply));
				string username = string(server_reply);
				username.erase(0, username.find(' ') + 1);

				fstream fin;
				fin.open("data.txt", ios::in);
				bool infor = true;
				int userNumber = 0;
				if (fin.is_open()) {
					string line;
					while (!fin.eof()) {
						getline(fin, line);
						userNumber++;
						if (line == username) {
							//::MessageBox(NULL, _T("Tài khoản đã tồn tại."), _T("Thông báo"), MB_OK | MB_ICONINFORMATION);
							if (status[userNumber - 1] == '1') {
								for (int i = 1;i <= iCount; i++)
								{
									if (pYourSocket != sArray[i]) {
										if (send(sArray[i], server_reply, recv_size, 0) < 0)
										{
											puts("Send failed");
											//return -1;
										}
									}
								}
								infor = false;
							}
							fin.close();
							break;
						}
					}
					if (infor == true) {
						char* rep = "Tài khoản hiện không online";
						send(pYourSocket, rep, strlen(rep), 0);
					}

				}

			}
			else if (server_reply[0] == '6')
			{
				server_reply[recv_size] = '\0';
				//m_pDialog->ShowServerInfo("Message Received: "+ string(server_reply));
				string username = string(server_reply);
				username.erase(0, 1);
				fstream fin;
				fin.open("data.txt", ios::in);
				bool infor = true;
				int userNumber = 0;
				if (fin.is_open()) {
					string line;
					while (!fin.eof()) {
						getline(fin, line);
						userNumber++;
						if (line == username) {
							//::MessageBox(NULL, _T("Tài khoản đã tồn tại."), _T("Thông báo"), MB_OK | MB_ICONINFORMATION);
							status[userNumber - 1] = '1';
							char* rep = "Đăng nhập thành công";
							send(pYourSocket, rep, strlen(rep), 0);
							infor = false;
							break;
						}
					}
					if (infor == true) {
						char* rep = "Đăng nhập thất bại. Xin đăng kí.";
						send(pYourSocket, rep, strlen(rep), 0);
					}
					fin.close();
				}
			}
			else if (server_reply[0] == '9')
			{
				int OpClient; // client can gui toi
				server_reply[recv_size] = '\0';
				string sfileName = string(server_reply);
				sfileName.resize(recv_size);
				sfileName.erase(0, 1);
				sfileName = "7" + sfileName;
				for (int i = 1;i <= iCount; i++)
				{
					if (pYourSocket != sArray[i]) {
						if (send(sArray[i], sfileName.c_str(), sfileName.size(), 0) < 0)
						{
							puts("Send failed");
							//return -1;
						}

					}
				}
				sfileName.erase(0, 1);
				FILE *fp = fopen(sfileName.c_str(), "rb");
				if (fp == NULL)
				{
					printf("File open error");
				}
				long double sz = 1;
				while (1)
				{
					/* First read file in chunks of 256 bytes */
					//unsigned char buff[1024] = { 0 };
					char buff[2048] = { 0 };
					//memset(buff, 0, 2000);
					int nread = fread(buff, 1, 2048, fp);
					fseek(fp, 0, SEEK_CUR);   /* di chuyne con tro*/
											  /*int indexFileName = 0;
											  int i;
											  for (i = nread;i < nread + sFileName.size();i++) {
											  buff[i] = sFileName[indexFileName];
											  indexFileName++;
											  }


											  buff[nread] = '8';
											  //printf("Bytes read %d \n", nread);
											  //buff[1024] = '8';

											  /* If read was success, send data. */
					sz++;
					//string sendFile = "8" + string(buff);
					//sendFile.resize(1 + nread);
					if (nread > 0)
					{
						//printf("Sending \n");
						for (int i = iCount;i >= 1; i--)
						{
							if (pYourSocket != sArray[i]) {
								if (send(sArray[i], buff, nread, 0) < 0)
								{
									puts("Send failed");
									//return -1;
								}
								else {
									break;
								}
							}
						}
						//send(s, buff, nread, 0);
					}
					if (nread < 2048)
					{
						if (feof(fp))
						{
							//::MessageBox(NULL, _T("Đã gửi xong tệp."), _T("Thông báo"), MB_OK | MB_ICONINFORMATION);
							printf("End of file\n");
						}
						if (ferror(fp)) {
							printf("Error reading\n");
						}
						break;
					}
					Sleep(20);
				}
				fclose(fp);
				//}
			}
			else if (server_reply[0] == '7') {
				server_reply[recv_size] = '\0';
				string dataRecvFileName = string(server_reply);
				dataRecvFileName.erase(0, 1);
				//dataRecv.erase(dataRecv.find('\0'));
				string(fileName) = dataRecvFileName;
				a[0] = string(fileName);
				memset(server_reply, 0, 2048);
			}
		}
		else if (a[0] != ""){
				//string dataRecv = string(server_reply);
				//dataRecv.resize(recv_size);
				//dataRecv.erase(0, 1);
				//dataRecv.erase(dataRecv.find('\0'));
				FILE* fp;
				fp = fopen(a[0].c_str(), "ab");
				int szfwrite = fwrite(server_reply, 1, recv_size, fp);
				fseek(fp, 0, SEEK_END);
				if (szfwrite < 2048) {
					printf("Error");
					fclose(fp);
					a[0] = "";
					memset(server_reply, 0, 2048);
					//continue;
				}
		}
	}
	return 0;
}


UINT m_Server::SendReceiveData(SOCKET cSocket)
{

	return 0;
}


void m_Server::SetStaticVariable(int iC, SOCKET cS)
{
	iCount = iC;
	//sArray[iCount] = cS;
}