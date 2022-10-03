#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_net.h>

int main(int argc, char* argv[])
{
	IPaddress ip;
	const int port = 1234;
	TCPsocket listenSocket = nullptr;
	TCPsocket clientSocket = nullptr;

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL2 is not initialize properly" << std::endl;
		return 0;
	}
	else if (SDLNet_Init() == -1)
	{
		std::cout << "SDL_net is not initialize properly" << std::endl;
		return 0;
	}

	///////////////////////////////////////////////////////////////
	if (SDLNet_ResolveHost(&ip, nullptr, port) == -1)
	{
		std::cout << "COuld not create server" << std::endl;
		return 0;
	}

	listenSocket = SDLNet_TCP_Open(&ip);
	if (!listenSocket)
	{
		std::cout << "Could not open socket" << std::endl;
		return 0;
	}

	while (!clientSocket)
	{
		clientSocket = SDLNet_TCP_Accept(listenSocket);
		std::cout << ":" << std::endl;
		SDL_Delay(1000);
	}
	SDLNet_TCP_Close(listenSocket);
	std::cout << "Client connected!" << std::endl;



	std::cout << "This is Server" << std::endl;

	SDLNet_Quit();
	SDL_Quit();
	return 0;
}