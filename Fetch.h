#pragma once
#include "stdafx.h"
#include <ctime>
#include <string>
#include "Deals.h"
#include "Store.h"
#include <vector>

class Fetch
{
public:

	Fetch(void);
	~Fetch(void);
	//returns a string vector:{[0]Id,[1]Name,[2]Phone,[3]Address,[4]Description}
	vector<std::wstring> Store(int Id);

	//returns a (string vector) vector:{{[0]Id,[1]Name,[2]Hour of Expiration,[3]Minute of Expiration,[4]Price,[5]Place,[6]Store's Id},{},{}......}
	vector <vector<std::wstring> > Deals(type t);


private :

	void tstamp(string print);
	void tstamp(string print,int n);


	CDataSource connection;
	CSession session;
	CCommand<CAccessor<CStore> > store;
	CCommand<CAccessor<CDeals> > deals;
	CLSID clsid;
	HRESULT hr;
	CDeals* RDeals;
};
