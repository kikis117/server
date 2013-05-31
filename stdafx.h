#pragma once
#include "targetver.h"
#include <string>
#include <vector>
#include "Store.h"
#include "Deals.h"
#include <tchar.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit
#define _UNICODE



enum type{
		Coffee,
		Drink,
		Food
	};
#include <atlbase.h>
#include <atlstr.h>
#include <atldbcli.h>
#include <signal.h>
using namespace std;