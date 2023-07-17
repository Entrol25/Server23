#include "DataClient.h"

void DataClient::SetLogin(char buffer[])
{
	if (entrance == false)
	{
		for (short i = 0; i < 1024; i++)
		{
			startClientData[i] = buffer[i];
			if (buffer[i] == '`')
			{
				break;
			}
		}
		if (true)
		{
			entrance = true; // вход
		}
	}
}
