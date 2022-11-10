#include "HostTCP.h"

HostTCP::HostTCP()
{
}

HostTCP::~HostTCP()
{
}

bool HostTCP::SDLInitialize()
{
	std::cout << "This is Server" << std::endl;
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL2 is not initialize properly" << std::endl;
		return false;
	}
	else if (SDLNet_Init() == -1)
	{
		std::cout << "SDL_net is not initialize properly" << std::endl;
		return false;
	}
}

bool HostTCP::OpenSocket()
{
	if (SDLNet_ResolveHost(&ip, nullptr, port) == -1)
	{
		std::cout << "Could not create server" << std::endl;
		return false;
	}

	listenSocket = SDLNet_TCP_Open(&ip);
	if (!listenSocket)
	{
		std::cout << "Could not open socket" << std::endl;
		return false;
	}
}

bool HostTCP::ListenSocket()
{
	while (totalClients < maxClients)
	{
		TCPsocket tempSocket = nullptr;
		tempSocket = SDLNet_TCP_Accept(listenSocket);
		if (!tempSocket)
		{
			std::cout << "Listening for Clients. . ." << std::endl;
			SDL_Delay(1000);
			return false;
		}
		else
		{
			clientSockets[totalClients] = tempSocket;
			std::cout << "Client connected!" << std::endl;
			//std::thread welcomeMsg((SendWelcomeMessage, clientSockets[totalClients], welcomeMessage));
			SendWelcomeMessage(clientSockets[totalClients], welcomeMessage);
			ReceiveMessage(clientSockets[totalClients]);
			totalClients++;
			std::cout << "number of clients: " << totalClients << std::endl;
			return true;
		}
	}
}

bool HostTCP::SendWelcomeMessage(TCPsocket sock, std::string message)
{
	int length = message.length() + 1;
	if (SDLNet_TCP_Send(sock, message.c_str(), length) < length)
	{
		std::cout << "Welcome message sent successfully!" << std::endl;
		return true;
	}
	std::cout << "Could not send message" << std::endl;
	return false;
}

bool HostTCP::ReceiveMessage(TCPsocket sock)
{
	char message[100];
	if (SDLNet_TCP_Recv(sock, message, 100) <= 0)
	{
		std::cout << "Message received: " << message << std::endl;
		return true;
	}
	std::cout << "Could not receive message" << std::endl;
	return false;
}

void HostTCP::ShutDown()
{
	SDLNet_Quit();
	SDL_Quit();
}
