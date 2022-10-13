#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_net.h>

#include"HostTCP.h"

int main(int argc, char* argv[])
{
	bool isAppRunning = true;
	HostTCP hostTcp;

	hostTcp.OpenSocket();
	hostTcp.AcceptConnection();
	/*while (isAppRunning)
	{
	}*/

	SDLNet_Quit();
	SDL_Quit();
	return 0;
}