#include "stdafx.h"
#include <winsock2.h>
#include <iostream>

	
void signalHandler(int);
DWORD WINAPI connection(void*);
UINT server(void);

	