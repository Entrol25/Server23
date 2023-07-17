#pragma once// от повторного включения
#pragma comment(lib,"Ws2_32.lib")// библиотека сокетов 
// & s 85 
#include <WinSock2.h>// подкл сокеты 
// & s 85 преобразование адресов 
#include <WS2tcpip.h>// для работы с сервером 
//
#include <iostream>// вывод в консоль 
//#include "MyConvert.h"
#include "ServerManager.h"
#include "DataClient.h"
#include "RoomManager.h"

using namespace std;
/*
* char от 0 до 255. 1 байт (8 бит).
short от –32768 до 32767. 2 байта (16 бит).
unsigned short от 0 до 65535. 2 байта (16 бит).
int от −2 147 483 648 до 2 147 483 647. 4 байта (32 бит).
float 4 байта (32 бита). 3,4E +/- 38 (7 знаков)
double 8 байт (64 бит). 1,7E +/- 308 (15 знаков)
*/
SOCKET Connect;// создание сокета. приём подключаемых пользователей и передавать в большую коллекцию сокетов.
SOCKET* Connections;// коллекция сокетов. все пользователи подкл. к серверу.
SOCKET Listen;// сокет для подключкния
int ClientCount = -1;// подключённые клиенты

void SendMessageToClient(int ID)// ф. рассылает всем сообщения
{
#pragma region Region2 //---------------------------------

	bool wait = true;
	bool setBrigade = false;
	//
	short players = 0;
	int const maxPlayers = 2;
	short brigade[2] = {};// ID
	//
	int sizeBuffer = 0;
	string status = "-:-";// 0 connect, 1 connect, 2 room onliyne game
	char buffer[1024] = {};// создать временный буфер для сообщения
	char response[5] = {};// ответ

	ServerManager serverManager;//
	DataClient dataClient;// 
	RoomManager roomManager;// !!!!!!!!!!!!!!!

#pragma endregion

	for (int i = 0; i < 1024; i++) { buffer[i] = '\0'; }// чистим буфер

	for (;;)// for (;; Sleep(75))
	{
		if (recv(Connections[ID], buffer, 1024, NULL))// получить сообщение от игрока[ID]
		{
			cout << "..................................................................................." << endl;
			cout << "id = " << ID << " buffer = " << buffer << endl;// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			status = serverManager.Status(buffer);// получить статус 
			if (status == "room")// 
			{
				cout << "id = " << ID << " status = " << status << endl;
				sizeBuffer = serverManager.WorkVector3(buffer);// получить длинну для временного буфера bufferRoom[]

				char* bufferRoom = new char[sizeBuffer];// создать временный буфер для сообщения
				for (int i = 0; i < sizeBuffer; i++) { bufferRoom[i] = '`'; }// чистим буфер для сообщения

				serverManager.WorkVector3(sizeBuffer, bufferRoom, buffer);// заполняем временный буфер для сообщения

				send(Connections[ID], bufferRoom, strlen(bufferRoom), NULL);// отправить сообщение игроку[i]
				delete[] bufferRoom;

			}
			else if (status == "1:1")// подключился к SendMessageToClient()
			{
				cout << "id = " << ID << " status = " << status << endl;
				dataClient.SetLogin(buffer);// Login <<<<<<<<<<<<<<

				serverManager.Response(response);
				send(Connections[ID], response, strlen(response), NULL);// отправить сообщение игроку[i]
			}
			else if (status == "2:2")// войти в room onliyne game
			{
				cout << "id = " << ID << " status = " << status << endl;
				//cout << "setBrigade = " << setBrigade << endl;
				/*
				if (setBrigade == false)// первый запрос в комнату. по умолчанию
				{
					setBrigade = true;
					//cout << "id = " << ID << " setBrigade = true; = " << setBrigade << endl;
				}
				serverManager.Response_2(response);
				send(Connections[ID], response, strlen(response), NULL);// отправить сообщение игроку[i]
				*/
				if (setBrigade == false)// первый запрос в комнату. по умолчанию
				{
					setBrigade = true;
					RoomManager::SetBrigade(ID, players);// players;// return >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
				}
				if (wait == true)// по умолчанию
				{
					wait = roomManager.GetWaitRoom();// ждать игроков
				}
				if (wait == false)// дождались всех игроков
				{
					for (short i = 0; i < players; i++) { brigade[i] = -2; }// чистим
					roomManager.GetBrigade(brigade);
					for (short i = 0; i < players; i++)
					{
						cout << "id = " << ID << " brigade[" << i << "] = " << brigade[i] << endl;
					}
					serverManager.Response(response);
					send(Connections[ID], response, strlen(response), NULL);// отправить сообщение игроку[i]
				}
				if (wait == true)// по умолчанию. неудачная попытка
				{
					status == "1:1";
					cout << "id = " << ID << " status = " << status << endl;
					serverManager.SetStatus(status, response);
					send(Connections[ID], response, strlen(response), NULL);// отправить сообщение игроку[i]
				}
				cout << "id = " << ID << " wait = " << wait << endl;
			}
		}
		for (int i = 0; i < 1024; i++) { buffer[i] = '\0'; }// чистим буфер
	}
}
int StartServer()
{
#pragma region Region1 //--------------------------------

	WSAData data;// переменная
	WORD version = MAKEWORD(2, 2);// верси сокетов 
	int res = WSAStartup(version, &data);// инициализация сокетов 
	if (res != 0)// если не иниц. сокет 
	{
		printf("res != 0");
		return 0;// возврат 
	}

	struct addrinfo hints;// 
	struct addrinfo* result;// для работы сокетов 



	Connections = (SOCKET*)calloc(64, sizeof(SOCKET));// иниц. массива - коллекции

	ZeroMemory(&hints, sizeof(hints));// чистка структуры

	hints.ai_family = AF_INET;// задать тип сокета 
	hints.ai_flags = AI_PASSIVE;// задать флаг
	hints.ai_socktype = SOCK_STREAM;// задать тип сокета 
	hints.ai_protocol = IPPROTO_TCP;// задать тип протокола

	getaddrinfo(NULL, "7890", &hints, &result);// получить инфу о хосте

	Listen = socket(result->ai_family, result->ai_socktype, result->ai_protocol);// настроить сокет Listen

	bind(Listen, result->ai_addr, result->ai_addrlen);// объявить сервер

	listen(Listen, SOMAXCONN);// дать сокет который ждёт подключение listen(Listen, максимум подключившихся);
	freeaddrinfo(result);// удалить инфу т.к. сокеты уже настроены
	//char m_connect[] = "Connect...;;;5";// переменная -> отправить клиенту о удачном подкл. к серверу
#pragma endregion

	char m_connect[] = { '*','0',':','0','`','\0' };// переменная -> отправить клиенту о удачном подкл. к серверу
	printf("Start server...\n");// сообщение на сервер

	for (;;)// for (;; Sleep(75))
	{
		if (Connect = accept(Listen, NULL, NULL))// ждёт подкл. от клиента
		{
			//~~~~~~~~~~~~~~~ s 107 ~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*u_long _nB = (u_long)1;
			int _notBlock = ioctlsocket(Connect, FIONBIO, &_nB);*/
			/*if (_notBlock == SOCKET_ERROR)
			{ printf("SOCKET_ERROR\n"); }
			else { printf("SOCKET NotBlock\n"); }*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ClientCount++;// + 1 клиент 
			Connections[ClientCount] = Connect;// сохранить сокет клиента
			send(Connections[ClientCount], m_connect, strlen(m_connect), NULL);// отправить клиенту сообщение
			CreateThread(// создать поток
				NULL,
				NULL,
				(LPTHREAD_START_ROUTINE)SendMessageToClient,
				(LPVOID)(ClientCount),
				NULL,
				NULL);
		}
	}
}
int main()//-----------------------------------------------------------------//
{
	StartServer();
	return 1;//
	//system("pause"); // задержка консоли до нажатия любой клавиши
}