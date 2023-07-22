#include "RoomManager.h"

const short RoomManager::rooms = 2;
Room RoomManager::room[rooms] = {};

RoomManager::RoomManager()// конструктор 
{
	short _classID;

	for (short i = 0; i < rooms; i++)// SetClassID
	{
		room[i].SetClassID(i);

		_classID = room[i].GetClassID();// Debug
		cout << "\t0) _classID = " << _classID << endl;
	}
}
//-------------------------------------------------------
void RoomManager::SetBrigade(short _myId, short& _players, short& _numRoom)// в очередь в комнату
{
	bool _wait = false;

	for (short i = 0; i < rooms; i++)// SetClassID
	{
		room[i].GetWaitRoom(_wait);// свободная комната. ожидание игроков. 

		if (_wait == true)// свободная комната. ожидание игроков. 
		{
			_numRoom = i;// return >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			room[i].SetBrigade(_myId, _players);// players/ return >>>>>>>>>>>>
			break;// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}
	}
}
void RoomManager::GetWaitRoom(bool& _wait, short& _numRoom)// свободная комната. ожидание игроков.
{
	room[_numRoom].GetWaitRoom(_wait);// wait / return >>>>>
}
void RoomManager::GetBrigade(short _brigade[], short& _numRoom)// получить ID игроков комнаты
{
	room[_numRoom].GetBrigade(_brigade);
}
