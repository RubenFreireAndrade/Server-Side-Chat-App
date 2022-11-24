#include "App.h"

std::mutex mutex;

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
		std::thread sendMsgThr(&HostTCP::SendWelcomeMessage, tcp, /*tcp->GetClientSock(),*/ tcp->GetWelcomeMessage());
		sendMsgThr.join();
		if (tcp->GetMsgSentFlag())
		{
			std::thread receiveMsgThr(&HostTCP::ReceiveMessage, tcp);
			if (receiveMsgThr.joinable())
			{
				receiveMsgThr.detach();
			}
		}
	}
	return true;
}

void App::ShutDown()
{
	tcp->ShutDown();
}
