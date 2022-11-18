#include "App.h"

App::App()
{
	hostTcp = new HostTCP();
}

bool App::RunApp()
{
	bool isListening = true;

	hostTcp->SDLInitialize();
	hostTcp->OpenSocket();
	/*std::thread listenSockThread(&HostTCP::ListenSocket, hostTcp);
	listenSockThread.join();*/

	while (isListening)
	{
		if (hostTcp->ListenSocket())
		{
			sendMsgThr = std::thread(&HostTCP::SendWelcomeMessage, hostTcp, hostTcp->clientSocket, hostTcp->welcomeMessage);
			hostTcp->totalClients++;
			std::cout << hostTcp->totalClients << std::endl;

			sendMsgThr.join();
		}
		/*std::thread receiveMsgThread(&HostTCP::ReceiveMessage, hostTcp, hostTcp->listenSocket);
		receiveMsgThread.detach();*/
	}
	return false;
}

void App::ShutDown()
{
	hostTcp->ShutDown();
}
