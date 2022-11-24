#pragma once
#include<string>
#include<vector>
#include<thread>
#include<chrono>
#include<mutex>
#include<Windows.h>
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
	TCPsocket ListenSocket();
	bool SendWelcomeMessage(/*TCPsocket sock, */std::string message);
	bool ReceiveMessage(/*TCPsocket sock*/);
	bool GetMsgSentFlag();
	TCPsocket GetClientSock();
	std::string GetWelcomeMessage();
	void SetConsoleTextColor(WORD c);
	void ShutDown();

	int totalClients = 0;
private:
	int defaultColor = 7;
	int maxClients = 5;
	const int port = 1234;
	bool hasMsgSent = false;
	const std::string welcomeMessage = "Hello! Welcome to the chat.";

	IPaddress ip;
	IPaddress* clientIp;

	TCPsocket clientSockets[5];
	TCPsocket listenSocket = nullptr;
	TCPsocket clientSocket = nullptr;
};