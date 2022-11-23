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
	HostTCP* tcp;
	//std::thread sendMsgThr;
	//std::thread recieveMsgThr;
};

