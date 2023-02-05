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
	int ListenSocket();
	bool SDLInitialize();
	bool OpenSocket();
	bool SendMessage(int clientId, std::string message);
	bool ReceiveMessage(int clientId);
	void SetConsoleTextColor(WORD c);
	void ShutDown();

private:
	int defaultColor = 7;
	const int port = 1234;
	bool isListening = true;
	const std::string welcomeMessage = "Hello! Welcome To Server!";

	IPaddress ip;
	std::vector<TCPsocket> clients;
	TCPsocket listenSocket = nullptr;
	
	Uint32 GetIp(TCPsocket sock);
};