// Server: Defines the entry point for the console application.
//
#include "stdafx.h"
#define portNo 20000
#include "Server.h"
#include "Strsafe.h"
#include "requestHandler.h"

struct clientInfo{
	SOCKET sock;
	requestHandler req;
};


UINT server(){
	struct sockaddr_in ServAddr; /* Local address */
	struct sockaddr_in ClntAddr; /* Client address */
	WSADATA wsaData;
	SOCKET sock;
	//requestHandler req;
	SOCKET client;
	struct clientInfo passInfo;
	sockaddr_in from;
	int fromlen,countClients=0;

	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) 
	{
		cout<<"WSAStartup() failed"<<endl;
		exit(1);
	}
	
	memset(& ServAddr, 0, sizeof(ServAddr)); // Zero out structure
	ServAddr.sin_family = AF_INET; // Internet address family 
	ServAddr.sin_addr.s_addr = htonl(INADDR_ANY); //Any incoming interface
	ServAddr.sin_port = htons(portNo); // Local port 
	
	if ((sock = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP)) < 0)
		cout<<"socket() failed"<<endl;
	
	
	if(bind(sock,(sockaddr*)&ServAddr,sizeof(ServAddr))!=0)
	{
		return 0;
	}

	if(listen(sock,30)!=0)
	{
		cout<<"error setting listening mode"<<endl;
		return 0;
	}

	fromlen=sizeof(from);
	cout<<"Server running.. \n Waiting for incoming connections\n"<<endl;
	//////////Loop για δημιουργία νέων συνδέσεων-threads
	while(true)
	{
		
		client=accept(sock,(struct sockaddr*)&from,&fromlen);

		if (client != INVALID_SOCKET) {
			countClients++;
            cout << "Accepted connection from " <<inet_ntoa(from.sin_addr) << ":" <<ntohs(from.sin_port) << "." <<endl;
			///////////Accept connection και δημιουργία thread
			DWORD nThreadID;
            CreateThread(0, 0, connection, (void*)client, 0, &nThreadID);
			cout<<"Client:"<<countClients<<"added"<<endl;
		}else{
			cout<<"accept failed"<<endl;
		}	


}
		return 0;
}


DWORD WINAPI connection(void* pParam){
	
	SOCKET clientSock=(SOCKET) pParam;
	char buff[1024];
	vector<wstring> sendBuffer;
	requestHandler req;
	int result,sendLen;
	string temp;

	string tempEnd="endOfResponse\n",test="alskjdfalksjfjuhsagdkjlalskg\n";
			wstring end;
	while(true)
	{
			int ret = recv(clientSock, buff, 1024, 0);
			if (ret == 0)
				break;
			else if(ret==ENOTCONN){
				cout<<"client disconnected\n"<<endl;
			}
			else if (ret == SOCKET_ERROR)
			{
				printf("Receive data failed");
				break;
			}

			sendBuffer=req.messageAnalyze(buff);
			
			memset(&buff,'\0',sizeof(buff));
			/*///////test sendBuffer
			end.assign(test.begin(),test.end());
			for (int i = 0; i < 500; i++)
			{
				sendBuffer.push_back(end); 
			}
			end.assign(tempEnd.begin(),tempEnd.end());
			sendBuffer.push_back(end);
			//////end test*/
			
			
			if (!sendBuffer.empty())
			{
				for (u_int i = 0; i < sendBuffer.size(); i++)
				{
					cout<<"for loop"<<i<<endl;
					memset(&buff,'\0',1023);
					
					///////μετατροπή του sendBuffer για αποστολή
					temp.assign(sendBuffer[i].begin(),sendBuffer[i].end());
					std::strcpy(buff,temp.c_str());
					result=strlen(buff);
					//////send
					if (result>0)
					{
						sendLen=send(clientSock,buff,result,0);
					}
					printf("asked for:%d sent:%d",result,sendLen);
				}
			}
   
	}
	return 0;
}


void signalHandler(int sign){
	cout << "Interrupt signal (" << sign << ") received.\n";

	WSACleanup();
	exit(0);
}