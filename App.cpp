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
	/*std::thread listenSockThread(&HostTCP::ListenSocket, hostTcp);
	listenSockThread.join();*/

	while (tcp->ListenSocket())
	{
		sendMsgThr = std::thread(&HostTCP::SendWelcomeMessage, tcp, tcp->clientSockets[tcp->totalClients], tcp->welcomeMessage);
		//tcp->totalClients++;
		//std::cout << tcp->totalClients << std::endl;
		sendMsgThr.detach();

		recieveMsgThr = std::thread(&HostTCP::ReceiveMessage, tcp /*tcp->clientSockets[tcp->totalClients]*/);
		recieveMsgThr.detach();
	}
	return false;

}

void App::ShutDown()
{
	tcp->ShutDown();
}
