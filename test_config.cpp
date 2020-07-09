#include <cstring>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <map>
#include "serv.h"

int main()	{
	read_config();
	std::cout<<_CONFIG["IP"];
}