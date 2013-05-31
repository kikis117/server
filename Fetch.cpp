#include "stdafx.h"
#include "Fetch.h"
#include <iostream>
Fetch::Fetch(void)
{
		
	hr = CoInitialize(NULL);//Initialize HRESULT

	//Obtain the CLSID of SQL
	hr=CLSIDFromProgID(L"SQLOLEDB",&clsid); 
	if(hr == S_OK)
		tstamp("SQL CLSID Obtained");

	
	
	//Specify the server,database and authentication method(Windows Integrated)
	      CDBPropSet propset(DBPROPSET_DBINIT);
      propset.AddProperty(DBPROP_INIT_DATASOURCE, L"G30-PC\\SQLEXPRESS");
      propset.AddProperty(DBPROP_INIT_CATALOG, L"DealBase");
      propset.AddProperty(DBPROP_AUTH_INTEGRATED, L"");


	  hr = CoInitialize(NULL);

	//Attempt to establish connection	
	hr=connection.Open(clsid,&propset);
		if(hr == S_OK)
		tstamp("Connection Established");

	hr = CoInitialize(NULL);
	//Start session
	hr=session.Open(connection);
	if(hr == S_OK)
		tstamp("Session Started");
}


Fetch::~Fetch(void)
{
		//Close the connection and end the session
		session.Close();
		connection.Close();	
}

vector<std::wstring> Fetch::Store(int Id)
{


	vector<std::wstring> ret;


	tstamp("Request For Store, Id= ",Id);
	
	//Select from store the record with Store.Id= input parameter Id 
	store.m_Id= Id;
	store.Open(session,"SELECT * FROM STORE WHERE Id = ?");
	  while(store.MoveNext() == S_OK)
      {

		 ret.push_back(to_wstring(store.m_Id));
		 ret.push_back((wstring) store.m_Name);
		 ret.push_back( (wstring)store.m_Address);
		 ret.push_back((wstring) store.m_Phone);
		 ret.push_back((wstring) store.m_Description);


         
      }

	  store.Close();
	  return ret;
}
	vector <vector<std::wstring> >   Fetch::Deals(type t)
{


		vector <vector<std::wstring> > ret;


	
	tstamp("Request For Deals, Type= ",t);
	deals.m_Type= t;
	deals.Open(session,"SELECT * FROM Deals Where Deals.Type = ? ");

	  while(deals.MoveNext() == S_OK)
      {
		 
		  std::vector<std::wstring> row;
		  //Type is not returned, as it is already known
		  row.push_back(to_wstring(deals.m_Id));

		  row.push_back((wstring) deals.m_Name);

		  row.push_back(to_wstring(deals.m_Time.hour));

		  row.push_back(to_wstring(deals.m_Time.minute));

		  row.push_back(to_wstring(deals.m_Price.int64/10000));

		  row.push_back((wstring) deals.m_Place);

		 row.push_back(to_wstring(deals.m_Id_S));

		 ret.push_back(row);
      }

	
	  deals.Close();
	  return ret;

}
//print a string with timestamp
void Fetch::tstamp(string print)
{

time_t now;
struct tm current;
now = time(0);

localtime_s(&current,&now);

	cout<<current.tm_mday<<"-";
	cout<<current.tm_mon<<"-";	
	cout<<(current.tm_year+1900)<<" ";	
	cout<<current.tm_hour<<":";
	cout<<current.tm_min<<" ";
	cout << print<< endl;
	cout << string(40, '-')<<"\n";
}

//print a string and an int with timestamp
void Fetch::tstamp(string print,int a)
{

time_t now;
struct tm current;
now = time(0);

localtime_s(&current,&now);

	cout<<current.tm_mday<<"-";
	cout<<current.tm_mon<<"-";	
	cout<<(current.tm_year+1900)<<" ";	
	cout<<current.tm_hour<<":";
	cout<<current.tm_min<<" ";
	cout << print<<a<< endl;
	cout << string(40, '-')<<"\n";
}