#include <WinSock2.h>
#include <thread>
#include <iostream>
#include <sstream>
#include "C:\Users\Admin\Documents\MyDocs\UNI\Course II\OOP\Chat\SockUtils.h"
#include "C:\Users\Admin\Desktop\Chat\RSA.h"

using namespace std;

unsigned int DefaultPort_ = 10001;
const char *DefaultServerAddress_ = "127.0.0.1";
SOCKET s;
bool onServer = false;

//string encrypt_string(string msg);
//string decrypt_string(string msg);

void TestSendToServer0()
{
	string dataToSend;

	cin >> dataToSend;

	string enc_msg = encrypt_string(dataToSend);//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//while (send(s, dataToSend.c_str(), dataToSend.length(), 0) != SOCKET_ERROR)
	while (send(s, enc_msg.c_str(), enc_msg.length(), 0) != SOCKET_ERROR)
	{
		getline(cin, dataToSend);
		enc_msg = encrypt_string(dataToSend); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	}

	closesocket(s);
}

void RecieveFromServer0()
{
	onServer = true;
	int bufSize = 101;
	char* buf = new char[bufSize];
	memset(buf, 0, bufSize);
	ostringstream dec_msg; 
	string msg;
	while (onServer && recv(s, buf, bufSize - 1, 0))
	{
		dec_msg.clear();
		dec_msg << buf;
		msg = decrypt_string(dec_msg.str());
		cout << msg << endl;
		memset(buf, 0, bufSize);
	}
}

void main()
{
	InitSocketsLib();

	s = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in dest_addr;
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(DefaultPort_);
	dest_addr.sin_addr.s_addr = inet_addr(DefaultServerAddress_);



	if (connect(s, (sockaddr *)&dest_addr, sizeof(dest_addr)) != 0)
	{
		cout << "Error connecting to server!";
		return;
	}

	//thread send(TestSendToServer0);
	
	thread recieve(RecieveFromServer0);

	/*
	onServer = true;
	int bufSize = 100;
	char* buf = new char[bufSize];
	memset(buf, 0, bufSize);
	while (onServer && recv(s, buf, bufSize - 1, 0))
	{
		cout << buf << endl;
		memset(buf, 0, bufSize);
	}
	*/
	
	// Next code is equivalent to SendToServer
	string dataToSend;
	cin >> dataToSend;
	string enc_msg = encrypt_string(dataToSend);//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//while (send(s, dataToSend.c_str(), dataToSend.length(), 0) != SOCKET_ERROR)
	while (send(s, enc_msg.c_str(), enc_msg.length(), 0) != SOCKET_ERROR)
	{
		getline(cin, dataToSend);
		enc_msg = encrypt_string(dataToSend); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	}
	//closesocket(s);
	
	//send.join();
	recieve.join();
	
	closesocket(s);

	//TestSendToServer();
	//TestSockets();

	ReleaseSocketsLib();
}