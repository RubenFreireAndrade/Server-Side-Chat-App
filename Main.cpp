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
	hostTcp.OpenSocket();
	while (isAppRunning)
	{
		std::thread acceptSockThread(&HostTCP::ListenSocket, &hostTcp);
		acceptSockThread.join();

		//std::thread sendMessageThread(&HostTCP::SendWelcomeMessage, &hostTcp);
		//sendMessageThread.detach();
		
		//std::thread receiveMessageThread(&HostTCP::ReceiveMessage, &hostTcp);
		//receiveMessageThread.join();
		//hostTcp.AcceptConnection();
	}
	hostTcp.ShutDown();
	return 0;
}