#pragma once
#include <iostream>// вывод в консоль 
using namespace std;

class ServerManager
{
public:
	int WorkVector3(char _buffer[]);
	void WorkVector3(int _sizeBuffer, char bufferRoom[], char buffer[]);
	string Status(char buffer[]);
	void SetStatus(string _st, char res[]);
	void Response(char res[]);
	//void Response_2(char res[]);

private:
	//char buffer[5] = {};// создать временный буфер для сообщения
	string _status = "-:-";// 0 connect, 1 connect, 2 room onliyne game
	//char response[5] = {};// ответ
	//char* response = new char[1024];// ответ
};
