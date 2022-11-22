#include "App.h"

App::App()
{
	tcp = new HostTCP();
}

bool App::RunApp()
{
	bool isOpen = true;

	tcp->SDLInitialize();
	tcp->OpenSocket();
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
