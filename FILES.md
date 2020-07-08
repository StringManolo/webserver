# FILES

├── [README.md](https://github.com/StringManolo/webserver/blob/master/FILES.md#readmemd)    
├── [console.h](https://github.com/StringManolo/webserver/blob/master/FILES.md#consoleh)  
├── [page.conf](https://github.com/StringManolo/webserver/blob/master/FILES.md#pageconf)  
├── [read_config.c](https://github.com/StringManolo/webserver/blob/master/FILES.md#read_configc)  
└── [serv.cpp](https://github.com/StringManolo/webserver/blob/master/FILES.md#servcpp)  
  
0 directories, 5 files  
  
&nbsp;  
  
## **[README.md](https://github.com/StringManolo/webserver/blob/master/README.md)**  
+ Project presentation.  
  
&nbsp;  
  
## **[console.h](https://github.com/StringManolo/webserver/blob/master/console.h)**  
###### Exposed:  
  
   _console.log(bool, string, type)_  
  
###### Intended for:  
  
   cout wrapper intended to split out messages in categories.  
###### Description:
  
   Outputs a message in diferent colors and formats.  
  
   1st parameter manages output. (_DEBUG_ and _VERBOSE_ only)  
  
   2st parameter is the _std::string_ to log.  
  
   3rd parameter is the type. (_CRITICAL_, _WARNING_, _VERBOSE_, _DEBUG_)  
###### Example:
```
#include "console.h"

int main() {
  CONSOLE console;
  bool debug = true;
  bool verbose = false;
  console.log(debug, "Text to output", DEBUG);
  console.log(verbose, "Verbose = true; to display", VERBOSE);

  return 0;
}
```
  
&nbsp;  
  
## **[page.conf](https://github.com/StringManolo/webserver/blob/master/page.conf)**  
  
&nbsp;  
  
## **[read_config.c](https://github.com/StringManolo/webserver/blob/master/read_config.c)**  
  
&nbsp;  
  
## **[serv.cpp](https://github.com/StringManolo/webserver/blob/master/serv.cpp)**  
  
  
