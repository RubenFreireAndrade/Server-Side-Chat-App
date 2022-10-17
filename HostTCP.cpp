#include "HostTCP.h"

HostTCP::HostTCP()
{
}

HostTCP::~HostTCP()
{
}

void HostTCP::SDLInitialize()
{
	std::cout << "This is Server" << std::endl;
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL2 is not initialize properly" << std::endl;
		//return 0;
	}
	else if (SDLNet_Init() == -1)
	{
		std::cout << "SDL_net is not initialize properly" << std::endl;
		//return 0;
	}
}

int HostTCP::OpenSocket()
{
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
}

void HostTCP::AcceptConnection()
{
	while (!clientSocket)
	{
		std::cout << ":" << std::endl;
		clientSocket = SDLNet_TCP_Accept(listenSocket);
		socketContainer.push_back(clientSocket);
		SDL_Delay(1000);
	}

	if (clientSocket)
	{
		std::cout << "Client connected!" << std::endl;
		SendMessage();
		ReceiveMessage();
	}
	//SDLNet_TCP_Close(listenSocket);

	//clientSocket = nullptr;
	//return 0;
}

void HostTCP::SendMessage()
{
	int length = welcomeMessage.length() + 1;
	if (SDLNet_TCP_Send(clientSocket, welcomeMessage.c_str(), length) < length)
	{
		std::cout << "Could not send message" << std::endl;
	}
	else
	{
		std::cout << "Welcome message sent successfully!" << std::endl;
	}
}

void HostTCP::ReceiveMessage()
{
	char message[100];
	//std::string message[100];
	if (SDLNet_TCP_Recv(clientSocket, message, 100) <= 0)
	{
		std::cout << "Could not receive message" << std::endl;
	}
	else
	{
		std::cout << "Message received: " << message << std::endl;
	}
}

void HostTCP::ShutDown()
{
	SDLNet_Quit();
	SDL_Quit();
}
