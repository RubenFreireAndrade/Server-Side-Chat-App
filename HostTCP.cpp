#include "HostTCP.h"

std::mutex m;

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

TCPsocket HostTCP::ListenSocket()
{
	while (true)
	{
		TCPsocket tempSock = nullptr;
		tempSock = SDLNet_TCP_Accept(listenSocket);
		if (!tempSock)
		{
			SetConsoleTextColor(2);
			std::cout << "Listening for Clients. . ." << std::endl;
			SetConsoleTextColor(7);
			SDL_Delay(1000);
		}
		else
		{
			clientIp = SDLNet_TCP_GetPeerAddress(tempSock);
			clientSockets[totalClients] = tempSock;
			std::cout << "Client connected: ";

			SetConsoleTextColor(3);
			std::cout << SDLNet_Read32(&clientIp->host) << std::endl;
			SetConsoleTextColor(7);

			totalClients++;
			std::cout << "Number of Clients: " << totalClients << std::endl;
			return tempSock;
		}
	}
}

bool HostTCP::SendWelcomeMessage(/*TCPsocket sock, */std::string message)
{
	int length = message.length() + 1;
	if (SDLNet_TCP_Send(clientSockets[totalClients], message.c_str(), length))
	{
		SetConsoleTextColor(6);
		std::cout << "Welcome message sent successfully!" << std::endl;
		SetConsoleTextColor(7);
		std::this_thread::sleep_for(std::chrono::seconds(1));
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
		SetConsoleTextColor(3);
		std::cout << SDLNet_Read32(&clientIp->host) << " Sent: " << message << std::endl;
		SetConsoleTextColor(7);
		SDL_Delay(500);
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

void HostTCP::SetConsoleTextColor(WORD c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void HostTCP::ShutDown()
{
	SDLNet_Quit();
	SDL_Quit();
}
