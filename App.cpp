#include "App.h"

App::App()
{
	tcp = new HostTCP();
}

bool App::InitApp()
{
	if (!tcp->SDLInitialize())
	{
		return false;
	}

	if (!tcp->OpenSocket())
	{
		return false;
	}
	return true;
}

bool App::RunApp()
{
	int totalClients = 0;
	while (totalClients < maxClients)
	{
		int clientId = tcp->ListenSocket();

		std::thread receiveMsgThr(&HostTCP::ReceiveMessage, tcp, clientId);
		receiveMsgThr.detach();
		totalClients++;
	}
	return true;
}

void App::ShutDown()
{
	tcp->ShutDown();
}
