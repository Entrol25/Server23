#pragma once
#include "Room.h"

#include <iostream>// вывод в консоль 

using namespace std;

class RoomManager
{
public:
	RoomManager(); //~RoomManager();
	void SetBrigade(short _myId, short& _players, short& _numRoom);// в очередь в комнату
	void GetWaitRoom(bool& _wait, short& _numRoom);// свободная комната. ожидание игроков.
	void GetBrigade(short _brigade[], short& _numRoom);// получить ID игроков комнаты

private:
	static short const rooms;
	static Room room[];
};
