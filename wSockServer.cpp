// wSockServer.cpp : Defines the entry point for the console application.
//
#include <signal.h> 
#include "stdafx.h"
#include "Server.h"

int _tmain(int argc, _TCHAR* argv[])
{
	signal(SIGINT, signalHandler);
	server();
}
