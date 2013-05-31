#pragma once
#include "stdafx.h"
#include <string>
#include "Fetch.h"
#include <vector>
class requestHandler{
private:
	wstring end;
	vector<wstring> sendBuffer;
	wstring errorType;
	int id,result;
	std::string temp;
	void requestHandler::vecToVec();
	void call_DB(int choice,int id);  //choice: 1Deals, 2Store
	Fetch session;
public:
	requestHandler();
	vector<wstring> messageAnalyze(char*);
	void reset();
};
