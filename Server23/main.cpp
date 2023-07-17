﻿#pragma comment(lib,"Ws2_32.lib")// библиотека сокетов 
// & s 85 
#include <WinSock2.h>// подкл сокеты 
#include <iostream>// вывод в консоль 
// & s 85 преобразование адресов 
#include <WS2tcpip.h>// для работы с сервером 
//---------------------------
//#include<thread>// потоки
//#include<chrono>// время 
//#include<string>// string
//#include<fstream>

//using namespace std;// мотает строки в консоли

// ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤

SOCKET Connect;// создание сокета. приём подключаемых пользователей и передавать в большую коллекцию сокетов.
SOCKET* Connections;// коллекция сокетов. все пользователи подкл. к серверу.
SOCKET Listen;// сокет для подключкния

int ClientCount = 0;// подключённые клиенты

void SendMessageToClient(int ID)// ф. рассылает всем сообщения
{
	char* buffer = new char[1024];// создать временный буфер для сообщения
	for (;; Sleep(75))// for (;; Sleep(75))
	{
		memset(buffer, 0, sizeof(buffer));// чистим буфер
		if (recv(Connections[ID], buffer, 1024, NULL))// получить сообщение от сервера
		{
			printf(buffer);// вывод сообщения
			printf("\n");//
			for (int i = 0; i <= ClientCount; i++)// переслать сообщение всем клиентам
			{
				send(Connections[i], buffer, strlen(buffer), NULL);// отправить сообщение
			}
		}
	}
	delete buffer;// удалить временный буфер
}

int main()//-----------------------------------------------------------------//
{
	setlocale(LC_ALL, "Rus");//

	WSAData data;// переменная
	WORD version = MAKEWORD(2, 2);// верси сокетов 
	int res = WSAStartup(version, &data);// инициализация сокетов 
	if (res != 0)// если не иниц. сокет 
	{
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

	printf("Start server...\n");// сообщение на сервер
	char m_connect[] = "Connect...;;;5";// переменная -> отправить клиенту о удачном подкл. к серверу

	for (;; Sleep(75))// for (;; Sleep(75))
	{
		if (Connect = accept(Listen, NULL, NULL))// ждёт подкл. от клиента
		{
			printf("Client connect...\n");// подключён
			Connections[ClientCount] = Connect;// сохранить сокет клиента
			send(Connections[ClientCount], m_connect, strlen(m_connect), NULL);// отправить клиенту сообщение
			ClientCount++;// + 1 клиент 
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SendMessageToClient, (LPVOID)(ClientCount - 1), NULL, NULL);// создать поток

		}
	}
	//---------
	return 1;//
	//system("pause"); // задержка консоли до нажатия любой клавиши
}