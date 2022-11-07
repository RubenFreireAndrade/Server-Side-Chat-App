#include<string>
#include<thread>
#include<iostream>
#include<SDL.h>
#include<SDL_net.h>

#include"HostTCP.h"

int main(int argc, char* argv[])
{
	HostTCP hostTcp;
	bool isAppRunning = true;

	std::thread openSockThread;

	hostTcp.SDLInitialize();
	//openSockThread = std::thread();
	hostTcp.OpenSocket();
	while (isAppRunning)
	{
		hostTcp.AcceptConnection();
	}
	hostTcp.ShutDown();
	return 0;
}