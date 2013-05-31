
#include "stdafx.h"
#include "requestHandler.h"
requestHandler::requestHandler()
{
	errorType.assign('-1',sizeof(int));
	string tempEnd="endOfResponse\n";
	end.assign(tempEnd.begin(),tempEnd.end());
	Fetch session();
}

vector<wstring> requestHandler::messageAnalyze(char buff[]){
	
	std::string temp = "";
	std::string tempID = "";
	reset();
	int id,i=0;
	while(buff[i]!= '\n'){
		if(buff[i]!=',')
			if(i<5)
				temp+=buff[i];
			else
				tempID+=buff[i];
		i++;
	}
	id=atoi(tempID.c_str());
	result=temp.compare("Deals");
	if(result==0){
		call_DB(1,0);
	}else if((result= temp.compare("Store"))==0)
	{
		call_DB(2,id);
	}else
	{
		sendBuffer.push_back(errorType);
	}

	sendBuffer.push_back(end);
	return sendBuffer;
}

void requestHandler::call_DB(int choice, int id){
	
	if(id==0){
		
		vecToVec();
	}
	else{
		sendBuffer.insert(sendBuffer.begin(),session.Store(id).begin(),session.Store(id).end());
	}

}
void requestHandler::reset(){
	sendBuffer.clear();
}

void requestHandler::vecToVec(){
	string t="\n";
	wstring addt;
	addt.assign(t.begin(),t.end());
	for (int y=0; y < 3; y++)
	{
		for(u_int i=0; i< session.Deals((type)y).size();i++){
			for(u_int j=0; j<session.Deals((type)y).at(i).size();j++){
				session.Deals((type)y).at(i).at(j).append(addt);
				sendBuffer.push_back(session.Deals((type)y).at(i)[j]);
			//sendBuffer.insert(sendBuffer.begin(),session.Deals((type)y)[i].begin(),session.Deals((type)y)[i].end());
			}
		}
	}

}