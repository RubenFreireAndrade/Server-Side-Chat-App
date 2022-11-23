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
	return true;
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
	return true;
}

bool HostTCP::ListenSocket()
{
	while (totalClients < maxClients)
	{
		TCPsocket tempSock = nullptr;
		tempSock = SDLNet_TCP_Accept(listenSocket);
		if (!tempSock)
		{
			std::cout << "Listening for Clients. . ." << std::endl;
			SDL_Delay(1000);
		}
		else
		{
			clientIp = SDLNet_TCP_GetPeerAddress(tempSock);
			clientSockets[totalClients] = tempSock;
			std::cout << "Client connected: " << SDLNet_Read32(&clientIp->port) << std::endl;
			return true;
		}
	}
}

bool HostTCP::SendWelcomeMessage(TCPsocket sock, std::string message)
{
	int length = message.length() + 1;
	if (SDLNet_TCP_Send(sock, message.c_str(), length))
	{
		std::cout << "Welcome message sent successfully!" << std::endl;
		hasMsgSent = true;
		return true;
	}
	std::cout << "Could not send message" << std::endl;
	return false;
}

bool HostTCP::ReceiveMessage()
{
	char message[100];
	while (SDLNet_TCP_Recv(clientSockets[totalClients], message, 100))
	{
		std::cout << SDLNet_Read32(&clientIp->port) << " Sent: " << message << std::endl;
		// Do something here to check if server lost connection with Client and return "is lost connection".
		//return true;
	}
	std::cout << "Could not receive message" << std::endl;
	return false;
}

bool HostTCP::GetMsgSentFlag()
{
	return hasMsgSent;
}

TCPsocket HostTCP::GetClientSock()
{
	return clientSockets[totalClients];
}

std::string HostTCP::GetWelcomeMessage()
{
	return welcomeMessage;
}

void HostTCP::ShutDown()
{
	SDLNet_Quit();
	SDL_Quit();
}
