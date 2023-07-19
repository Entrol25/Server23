#pragma once

#include <iostream>// вывод в консоль 

using namespace std;

class Room
{
public:
	Room();//~Room();
	void SetClassID(short _classID);// SetClassID
	void SetBrigade(short _myId, short& _players);// в очередь в комнату
	void GetWaitRoom(bool& _wait);// свободная комната. ожидание игроков.
	void GetBrigade(short _brigade[]);// получить ID игроков комнаты
	short GetClassID();// Debug

private:
	short classID = -1;
	bool wait = true;// ожидание игроков.
	short countPlayers = 0;
	const short players = 2;
	short brigade[2];// [players] / ID
};
