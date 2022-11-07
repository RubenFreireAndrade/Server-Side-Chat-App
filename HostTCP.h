#pragma once
#include<SDL.h>
#include<string>
#include<vector>
#include<iostream>
#include<SDL_net.h>

class HostTCP
{
public:
	HostTCP();
	~HostTCP();
	bool SDLInitialize();
	bool OpenSocket();
	bool AcceptConnection();
	bool SendWelcomeMessage(TCPsocket sock, std::string message);
	bool ReceiveMessage(TCPsocket sock);
	void ShutDown();

	int maxClients = 5;
	int totalClients = 0;
	const int port = 1234;
	const char* client = "10.18.27.96";
	const std::string welcomeMessage = "Hello! Welcome to the chat.";
	IPaddress ip;
	TCPsocket listenSocket = nullptr;
	TCPsocket clientSocket = nullptr;

	std::vector<TCPsocket> socketContainer;
	TCPsocket clientSockets[];

private:

};

