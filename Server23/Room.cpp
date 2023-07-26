#include "Room.h"


Room::Room()// конструктор 
{
	cout << "\t \t 6) classID = " << classID << endl;

	for (short i = 0; i < players; i++)
	{
		brigade[i] = -1;// NULL
		cout << "\t \t 6.1) brigade[" << i << "] = " << brigade[i] << endl;
	}
}
//------------------------------------------------
void Room::SetClassID(short _classID)// SetClassID
{
	classID = _classID;
}
void Room::SetBrigade(short _myId, short& _players)// в очередь в комнату
{
	for (short i = 0; i < players; i++)
	{
		if (brigade[i] == -1)
		{
			cout << "\t1.0 brigade[" << i << "] = " << brigade[i] << endl;
			brigade[i] = _myId;
			cout << "\t1.1 brigade[" << i << "] = " << brigade[i] << endl;
			cout << "\t1.2) id = " << brigade[i] << endl;
			countPlayers++;
			cout << "\tcountPlayers = " << countPlayers << endl;
			break;// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}
	}
	if (countPlayers == players)
	{
		cout << "\t \t 2) countPlayers = " << countPlayers << endl;
		wait = false;
	}
	_players = players;// return >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}
void Room::GetWaitRoom(bool& _wait)// свободная комната. ожидание игроков.
{
	_wait =  wait;// return >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//cout << "\t \t 3) _wait = " << _wait << endl;
}
void Room::GetBrigade(short _brigade[])// получить ID игроков комнаты
{
	for (short i = 0; i < players; i++)
	{
		_brigade[i] = brigade[i];
		cout << "\t4) _brigade[" << i << "] = " << _brigade[i] << endl;
	}
}
short Room::GetClassID()// Debug
{
	return classID;
}
