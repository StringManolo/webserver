#include <cstring>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <map>
#include "serv.h"

#include "serv.h"

using namespace std;

map<string,string> _CONFIG;

int main()	{
	read_config();
	std::cout<<_CONFIG["IP"];
}