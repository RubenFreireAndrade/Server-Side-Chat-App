#include "App.h"

App::App()
{
	hostTcp = new HostTCP();
}

bool App::RunApp()
{
	bool isAppRunning = true;

	hostTcp->SDLInitialize();
	hostTcp->OpenSocket();
	/*std::thread listenSockThread(&HostTCP::ListenSocket, hostTcp);
	listenSockThread.join();*/

	while (isAppRunning)
	{
		if (hostTcp->ListenSocket())
		{
			std::thread welcomeMsgThread(&HostTCP::SendWelcomeMessage, hostTcp, hostTcp->clientSockets[hostTcp->totalClients], hostTcp->welcomeMessage);
			hostTcp->totalClients++;
			std::cout << hostTcp->totalClients << std::endl;
			welcomeMsgThread.detach();
		}
	}
	return false;
}

void App::ShutDown()
{
	hostTcp->ShutDown();
}
