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
	void SDLInitialize();
	int OpenSocket();
	void AcceptConnection();
	void SendMessage();
	void ReceiveMessage();
	void ShutDown();

	const int port = 1234;
	const char* client = "10.18.27.96";
	std::string welcomeMessage = "Hello! Welcome to the chat.";
	IPaddress ip;
	TCPsocket listenSocket = nullptr;
	TCPsocket clientSocket = nullptr;

	std::vector<TCPsocket> socketContainer;

private:

};

