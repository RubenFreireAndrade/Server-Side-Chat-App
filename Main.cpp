#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_net.h>

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	std::cout << "This is Server" << std::endl;
	return 0;
}