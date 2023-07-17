#pragma once
#include <iostream>// вывод в консоль 

using namespace std;

class RoomManager
{
public:
	//RoomManager(); //~RoomManager();
	static void SetBrigade(short _myId, short& _players);
	bool GetWaitRoom();// ждать игроков
	void GetBrigade(short _brigade[]);

private:
	static short const maxPlayers;
	static const short players;
	static short countPlayers;
	static short brigade[];// ID

	static bool wait;
};
