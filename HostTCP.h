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
	int OpenSocket();
	void AcceptConnection();

	const int port = 1234;
	const char* client = "10.18.27.96";
	std::string message = "Hello! Welcome to the chat";
	IPaddress ip;
	TCPsocket listenSocket = nullptr;
	TCPsocket clientSocket = nullptr;

	std::vector<TCPsocket> socketContainer;

private:

};

