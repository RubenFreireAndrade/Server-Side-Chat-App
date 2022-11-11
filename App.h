#pragma once
#include<string>
#include<iostream>
#include<thread>

#include"HostTCP.h"

class App
{
public:
	App();
	bool RunApp();
	void ShutDown();
private:
	HostTCP* hostTcp;
};

