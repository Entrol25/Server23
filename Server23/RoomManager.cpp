#include "RoomManager.h"

//const short RoomManager::players = 2;// init 
//const short RoomManager::maxPlayers = 2;// init 
//short RoomManager::countPlayers = 0;// init
//short RoomManager::brigade[maxPlayers] = { -1,-1 };// ID init
//bool RoomManager::wait = true;// init
//------------------------------------------------
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
//-----------------------------------------------------

//void RoomManager::SetBrigade(short _myId, short& _players)// в очередь в комнату
//{
//	for (short i = 0; i < players; i++)
//	{
//		if (brigade[i] == -1)
//		{
//			//cout << "\t1.0 brigade[i] = " << brigade[i] << endl;
//			brigade[i] = _myId;
//			//cout << "\t1.1 brigade[i] = " << brigade[i] << endl;
//			//cout << "\t0) id = " << brigade[i] << endl;
//			countPlayers++;
//			break;// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//		}
//	}
//	if (countPlayers == maxPlayers)
//	{
//		//cout << "\t1) countPlayers = " << countPlayers << endl;
//		wait = false;
//	}
//	_players = players;// return
//}
//bool RoomManager::GetWaitRoom()// ждать игроков
//{
//	for (short i = 0; i < players; i++)
//	{
//		cout << "\twait brigade[" <<  i  <<"] = " << brigade[i] << endl;
//	}
//	//cout << "\t2) wait = " << wait << endl;
//	return wait;// wait = true;// по умолчанию
//}
//void RoomManager::GetBrigade(short _brigade[])// ???????????????
//{
//	for (short i = 0; i < players; i++)
//	{
//		_brigade[i] = brigade[i];
//		//cout << "\t3) _brigade[i] = " << _brigade[i] << endl;
//	}
//}

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
