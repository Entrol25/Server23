#pragma once
#include <iostream>// вывод в консоль 
using namespace std;

class ServerManager
{
public:
	short WorkVector3(char _buffer[]);
	void WorkVector3(short _sizeBuffer, char bufferRoom[], char buffer[]);
	string Status(char buffer[]);
	void SetStatus(string _st, char res[]);
	void Response(char res[]);

private:
	string _status = "-:-";// 0 connect, 1 connect, 2 room onliyne game
};
