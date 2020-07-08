#include <cstring>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <map>
#include "serv.h"

#include "serv.h"

using namespace std;



int main()	{
	read_config();
	std::cout<<_CONFIG["IP"];
}