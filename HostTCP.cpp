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

int HostTCP::ListenSocket()
{
	while (isListening)
	{
		TCPsocket tempSock = SDLNet_TCP_Accept(listenSocket);
		if (!tempSock)
		{
			this->SetConsoleTextColor(2);
			std::cout << "Listening for Clients. . ." << std::endl;
			this->SetConsoleTextColor(7);
			SDL_Delay(1000);
		}
		else
		{
			std::cout << "Client connected: ";
			this->SetConsoleTextColor(3);
			std::cout << this->GetIp(tempSock) << std::endl;
			this->SetConsoleTextColor(7);

			clients.push_back(tempSock);
			std::cout << "Number of Clients: " << clients.size() << std::endl;

			int clientId = clients.size() - 1;
			if (SendMessage(clientId, this->welcomeMessage))
			{
				this->SetConsoleTextColor(6);
				std::cout << "Welcome message sent successfully!" << std::endl;
				this->SetConsoleTextColor(7);
			}
			return clientId;
		}
	}
}

bool HostTCP::SendMessage(int clientId, std::string message)
{
	if (SDLNet_TCP_Send(clients[clientId], message.c_str(), message.length() + 1))
	{
		return true;
	}
	std::cout << "Could not send message" << std::endl;
	return false;
}

bool HostTCP::ReceiveMessage(int clientId)
{
	TCPsocket sock = clients[clientId];
	char message[100];
	while (SDLNet_TCP_Recv(sock, message, 100))
	{
		SDL_Delay(100);
		std::cout << "/ / / / / / / / / / / 'Funny Looking Chat Box' / / / / / / / / / / /" << std::endl;
		this->SetConsoleTextColor(3);
		std::cout << this->GetIp(sock) << ":" << clientId << " Sent: " << message << "			|" << std::endl;
		this->SetConsoleTextColor(7);
		std::cout << "/ / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /" << std::endl;
		for (int cId = 0; cId < clients.size(); cId++)
		{
			if (cId == clientId) continue;
			SendMessage(cId, message);
		}
		SDL_Delay(100);
	}
	std::cout << "Could not receive message" << std::endl;
	return false;
}

void HostTCP::SetConsoleTextColor(WORD c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

Uint32 HostTCP::GetIp(TCPsocket sock)
{
	IPaddress* clientIp = SDLNet_TCP_GetPeerAddress(sock);
	return SDLNet_Read32(&clientIp->host);
}

void HostTCP::ShutDown()
{
	SDLNet_Quit();
	SDL_Quit();
}
