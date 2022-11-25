#pragma once
#include<string>
#include<iostream>
#include<thread>

#include"HostTCP.h"

class App
{
public:
	App();
	bool InitApp();
	bool RunApp();
	void ShutDown();

private:
	int maxClients = 5;
	HostTCP* tcp;
};

