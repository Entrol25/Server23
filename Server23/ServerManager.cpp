#include "ServerManager.h"

short ServerManager::WorkVector3(char buffer[])// получить длинну для временного буфера bufferRoom[]
{
	//cout << "room = " << buffer << endl;// room = *2:2:2,27:0,01`
	for (short i = 0; i < 1024; i++)// for (int i = 0; i < sizeof(buffer); i++)
	{
		if (buffer[i] != '`')
		{
			//cout << "i = " << i << "\t buffer[i] = " << buffer[i] << endl;
		}
		else if (buffer[i] == '`')// конец сообщения
		{
			//cout << "i = " << i << "\t buffer[i] = " << buffer[i] << endl;
			i++;// невилировать [0] элемент массива
			if (buffer[4] == '`')
			{
				i = i + 2;// добавить '/' и 'r'. разделитель и room 
			}
			//cout << "sizeBuffer = " << i << endl;
			return i;
		}
	}
	return 0;
}
// заполняем временный буфер для сообщения
void ServerManager::WorkVector3(short _sizeBuffer, char bufferRoom[], char buffer[])
{
	for (short i = 0; i < _sizeBuffer; i++)
	{
		if (buffer[i] != '`')// 
		{
			bufferRoom[i] = buffer[i];
			//cout << "i = " << i << "\t bufferRoom[i] = " << bufferRoom[i] << endl;
		}
		else if (buffer[i] == '`')// конец сообщения 
		{
			if (buffer[4] == '`')
			{
				bufferRoom[i] = '/';// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				//cout << "i = " << i << "\t bufferRoom[i] = " << bufferRoom[i] << endl;

				bufferRoom[i + 1] = 'r';// room !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				//cout << "i = " << i + 1 << "\t bufferRoom[i] = " << bufferRoom[i + 1] << endl;

				bufferRoom[i + 2] = '`';// конец сообщения
				//cout << "i = " << i + 2 << "\t bufferRoom[i] = " << bufferRoom[i + 2] << endl;
			}
			else
			{
				bufferRoom[i] = buffer[i];
				//cout << "i = " << i << "\t bufferRoom[i] = " << bufferRoom[i] << endl;
			}
			break;
		}
	}
}
string ServerManager::Status(char buffer[])// получить статус 
{
	//                                !=
	if (buffer[0] == '*' && buffer[4] != '`')// начало конец сообщения
	{
		//cout << "buffer 2 = " << buffer << endl;
		if (buffer[1] == '0' && buffer[3] == '1')// подключился к SendMessageToClient()
		{
			_status = "1:1";
			return _status;
		}
		else if (buffer[1] == '2' && buffer[3] == '2')// подтверждение в Room Online Game
		{
			_status = "room";
			return _status;
		}// понижение ********************************
		else if (buffer[3] == '0')// выход. Unity
		{
			_status = "0:0";
			return _status;
		}
		else
		{
			_status = "1:1"; return _status;
		}
	}//                                    ==
	else if (buffer[0] == '*' && buffer[4] == '`')// начало конец сообщения
	{
		if (buffer[1] == '1' && buffer[3] == '2')// войти в room onliyne game
		{
			_status = "2:2";
			return _status;
		}
		else if (buffer[1] == '2' && buffer[3] == '2')// подтверждение в Room Online Game
		{
			_status = "room";
			return _status;
		}// понижение ********************************
		else if (buffer[1] == '2' && buffer[3] == '1')// выйти из Room Online Game
		{
			_status = "1:1";
			return _status;
		}
		// Выкидывать из комнаты будет комната 0:1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	return "e";
}
void ServerManager::SetStatus(string _st, char res[])
{
	_status = _st;

	if (_status == "1:1")
	{
		res[0] = '*';
		res[1] = '1';
		res[2] = ':';
		res[3] = '1';
		res[4] = '`';
	}
}
void ServerManager::Response(char res[])// подключился к SendMessageToClient()
{
	if (_status == "1:1")// Accaunt
	{
		res[0] = '*';
		res[1] = '1';
		res[2] = ':';
		res[3] = '1';
		res[4] = '`';
	}
	else if (_status == "2:2")// Room Online Game
	{
		res[0] = '*';
		res[1] = '2';
		res[2] = ':';
		res[3] = '2';
		res[4] = '`';
	}
	else if (_status == "0:0")// выход. Unity
	{
		res[0] = '*';
		res[1] = '0';
		res[2] = ':';
		res[3] = '0';
		res[4] = 'x';
		res[5] = '`';
	}
}
