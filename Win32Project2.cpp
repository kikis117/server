// Win32Project2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Fetch.h"





		




int _tmain(int argc, _TCHAR* argv[])
{

	 Fetch d;
	CStore a;
	CDeals* f;
	int s;

	//request the store with id=2
	a=d.Store(2);
 
	//request all the deals about coffee
    f=d.Deals(Coffee,s);
 
	   system("Pause");
	   return 0;
}




