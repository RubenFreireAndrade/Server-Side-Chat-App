#pragma once
#include<string>
#include<vector>
#include<thread>
#include<iostream>

#include<SDL.h>
#include<SDL_net.h>

class HostTCP
{
public:
	HostTCP();
	~HostTCP();
	bool SDLInitialize();
	bool OpenSocket();
	bool ListenSocket();
	bool SendWelcomeMessage(TCPsocket sock, std::string message);
	bool ReceiveMessage(/*TCPsocket sock*/);
	bool GetMsgSentFlag();
	TCPsocket GetClientSock();
	std::string GetWelcomeMessage();
	void ShutDown();

private:
	int maxClients = 5;
	int totalClients = 0;
	const int port = 1234;
	bool hasMsgSent = false;
	const std::string welcomeMessage = "Hello! Welcome to the chat.";

	IPaddress ip;
	IPaddress* clientIp;

	TCPsocket clientSockets[5];
	TCPsocket listenSocket = nullptr;
	TCPsocket clientSocket = nullptr;
};