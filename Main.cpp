#include<string>
#include<thread>
#include<iostream>

#include"App.h"

int main(int argc, char* argv[])
{	
	App app;
	if (app.InitApp())
	{
		app.RunApp();
	}
	app.ShutDown();
	return 0;
}