#include "stdafx.h"
#include "Client_ChatOnly.h"
#include<stdio.h>

#include <string.h>
#include "ChatOnlyPerson.h"
#include <fstream>
#include <stdlib.h>
#include <errno.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <Synchapi.h>
#include <filesystem>
#include <gdiplus.h>

static  string a[2]; // luu ten file gui
//static string b[1]; //luu ten chat 

Client_ChatOnly::Client_ChatOnly(CChatOnlyPerson *dlg) {
	m_pClient = dlg;
}


Client_ChatOnly::~Client_ChatOnly(void) {

	closesocket(s);
	WSACleanup();
}


void Client_ChatOnly::StartConnect(string sUser_Name, string sAddress = "127.0.0.1", int iPort = 1234) {
	struct sockaddr_in server;
	char *message, server_reply[2048];
	//memset(server_reply, '0', sizeof(server_reply));
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
	long double sz = 1;
	a[0] = "";
	a[1] = "";
	while ((recv_size = recv(s, server_reply, 2048, 0)) != SOCKET_ERROR)
	{
		puts("Reply received\n");

		//Add a NULL terminating character to make it a proper string before printing
		puts(server_reply);
		if (a[0] == "") {
			if (server_reply[0] == '0') {
				server_reply[recv_size] = '\0';
				string sTempMsg = string(server_reply).erase(0, 1);
				string code_chat = sTempMsg;
				code_chat.erase(code_chat.find(" "));
				sTempMsg.erase(0, sTempMsg.find(" ") + 1);
				if (code_chat == m_pClient->codeChat)
					m_pClient->ShowServerInfo(sTempMsg);
			}
			else  if (server_reply[0] == '1') {}
			else  if (server_reply[0] == '2') {}
			else  if (server_reply[0] == '3') {}
			else  if (server_reply[0] == '4') {}
			else  if (server_reply[0] == '5') {}
			else  if (server_reply[0] == '6') {}
			else  if (server_reply[0] == '7') {
				server_reply[recv_size] = '\0';
				string dataRecvFileName = string(server_reply);
				dataRecvFileName.erase(0, 1);
				//dataRecv.erase(dataRecv.find('\0'));
				string(fileName) = dataRecvFileName;
				a[0] = string(fileName);
				a[1] = a[0];
				a[1].erase(a[1].find('.'));
				a[1].append(".bmp");
				m_pClient->bmpFile = a[1];
				memset(server_reply, 0, 2048);
			}
		}
		else if (a[0] != "") {
			sz++;
			FILE* fp;//, *fpbmp
			fp = fopen(a[0].c_str(), "ab");
			//fpbmp = fopen(a[1].c_str(), "ab");
			int szfwrite = fwrite(server_reply, 1, recv_size, fp);
			//int szfwritebmp = fwrite(server_reply, 1, recv_size, fpbmp);
			auto str = to_string(sz * 2 / 1024);
			CString strr(str.c_str());
			//m_pClient->ShowFileInfo("Recveied: ");
			//m_pClient->ShowFileInfo(str);
			//m_pClient->ShowFileInfo("Mb\n");
			//m_pClient->textBox_InforSendFile.SetWindowTextW(_T(""));
			fseek(fp, 0, SEEK_END);
			//fseek(fpbmp, 0, SEEK_END);
			if (szfwrite < 2048) {
				printf("Error");
				fclose(fp);
				//fclose(fpbmp);
				//send(s, a[0].c_str(), a[0].size(), 0);
				//m_pClient->LoadBitmapFile();
				//m_pClient->m_Anh.SetBitmap(hBmp);
				//m_pClient->UpdateData(FALSE);
				a[0] = "";
				m_pClient->textBox_InforSendFile.SetWindowTextW(_T("Recveied: ") + strr + _T("Mb"));
				memset(server_reply, 0, 2048);
			}
		}
		//else if(server_reply[0] == '7') {
		//	string FilePathName = string(server_reply);
		//	FilePathName.erase(0, 1);

		//	fileName = FilePathName.c_str();
		//}
	}
}


void Client_ChatOnly::SendData(string sMessage) {
	string sTemp = "0"+ m_pClient->codeChat + " " + m_pUser + ": " + sMessage + "\n";

	if (send(s, sTemp.c_str(), sTemp.size(), 0) < 0)
	{
		puts("Send failed");
		return;
	}
}

void Client_ChatOnly::SendDataFilename() {
	CFileDialog ChooseFile(true);
	if (ChooseFile.DoModal()) {
		::MessageBox(NULL, ChooseFile.GetPathName(), _T("Thông báo"), MB_OK);
	}
	CT2A FilePathName(ChooseFile.GetPathName());
 	string sFilePathName(FilePathName);

	//take file name
	CT2A FileName(ChooseFile.GetFileName());
	string sFileName(FileName);
	this->fileNameToSend = sFileName;
	sFileName = "7" + sFileName;
	send(s, sFileName.c_str(), sFileName.size(), 0);
	////begin take content file want to send to orthers client

	//send(s, sendAccount.c_str(), sendAccount.size(), 0);
	FILE *fp = fopen(sFilePathName.c_str(), "rb");
	if (fp == NULL)
	{
		printf("File open error");
		return;
	}
	long double sz = 1;
	/* Read data from file and send it */
	while (1)
	{
		/* First read file in chunks of 256 bytes */
		//unsigned char buff[1024] = { 0 };
		char buff[2048] = {0};
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
			auto str = to_string(sz*2/1024);
			CString strr(str.c_str());
			//CString strString(_T("Sending: ") + strr + _T("Mb\n"));
			m_pClient->ShowFileInfo("Sending: ");
			m_pClient->ShowFileInfo(str);
			m_pClient->ShowFileInfo("Mb\n");
			m_pClient->textBox_InforSendFile.SetWindowTextW(_T(""));
			
			//m_pClient->textBox_Chat.ReplaceSel();
			//m_pClient->SetWindowTextW(_T(""));

			
			/*int i, nLineCount = m_pClient->textBox_Chat.GetLineCount();
			CString strText, strLine;*/
			// Dump every line of text of the edit control. 
			//m_pClient->textBox_InforSendFile.SetWindowTextW(strString);
			/*m_pClient->ShowServerInfo("Sent: ");
			m_pClient->ShowServerInfo(str);
			m_pClient->ShowServerInfo("Mb\n"); */
			//else {
			//		// length of line i: 
			//		int len = m_pClient->textBox_Chat.LineLength(m_pClient->textBox_Chat.LineIndex(nLineCount - 1));
			//		m_pClient->textBox_Chat.GetLine(i, strText.GetBuffer(len), len);
			//		strText.ReleaseBuffer(len);
			//		strString.Format(_T("line %d: '%s'\n"), i, strText);
			//		AFXDUMP(strString);
			//}
			send(s, buff, nread, 0);
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
			/*auto strrr = to_string(m_pClient->textBox_Chat.GetLineCount());
			CString strrrr(strrr.c_str());
			m_pClient->textBox_Chat.SetWindowTextW(strrrr);*/
			auto str = to_string(sz * 2 / 1024);
			CString strr(str.c_str());
			CString strString(_T("Sending: ") + strr + _T("Mb\n") + _T('\n'));
			//m_pClient->textBox_InforSendFile.SetWindowTextW(strString + _T("Chọn gửi để hoàn tất.\n"));
			m_pClient->ShowFileInfo("Chon gui de hoan tat.");
			break;
		}
		Sleep(20);
	}
	fclose(fp);
}

void Client_ChatOnly::RequestSendingFile() {
	string sTemp = "9" + this->fileNameToSend;
	if (send(s, sTemp.c_str(), sTemp.size(), 0) < 0)
	{
		puts("Send failed");
		return;
	}
	::MessageBox(NULL, _T("Đã gửi xong tệp."), _T("Thông báo"), MB_OK | MB_ICONINFORMATION);
}

