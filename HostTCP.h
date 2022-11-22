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
	void ShutDown();

	int maxClients = 5;
	int totalClients = 0;
	bool hasMsgSent = false;
	const int port = 1234;
	const char* client = "10.18.27.96";
	const std::string welcomeMessage = "Hello! Welcome to the chat.";
	IPaddress ip;
	TCPsocket listenSocket = nullptr;
	TCPsocket clientSocket = nullptr;
	TCPsocket clientSockets[5];
	SDLNet_SocketSet socketSet;

private:

};