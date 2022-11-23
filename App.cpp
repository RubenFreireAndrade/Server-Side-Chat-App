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
	while (tcp->ListenSocket())
	{
		std::thread sendMsgThr(&HostTCP::SendWelcomeMessage, tcp, tcp->GetClientSock(), tcp->GetWelcomeMessage());
		if (sendMsgThr.joinable())
		{
			sendMsgThr.join();
		}
		std::thread receiveMsgThr(&HostTCP::ReceiveMessage, tcp);
		if (tcp->GetMsgSentFlag())
		{
			receiveMsgThr.detach();
		}
		
	}
	return true;
}

void App::ShutDown()
{
	tcp->ShutDown();
}
