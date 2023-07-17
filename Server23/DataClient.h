#pragma once

class DataClient
{
public:
	/*DataClient();
	~DataClient();*/
	void SetLogin(char buffer[]);

private:
	bool entrance = false;// вход
	char startClientData[1024] = {};//
};