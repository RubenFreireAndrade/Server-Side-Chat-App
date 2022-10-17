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

	hostTcp.SDLInitialize();
	while (isAppRunning)
	{
		hostTcp.OpenSocket();
		hostTcp.AcceptConnection();
	}
	hostTcp.ShutDown();
	return 0;
}