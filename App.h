#pragma once
#include<string>
#include<iostream>
#include<thread>
#include<mutex>

#include"HostTCP.h"

class App
{
public:
	App();
	bool InitApp();
	bool RunApp();
	void ShutDown();

	int maxClients = 5;
private:
	HostTCP* tcp;
};

