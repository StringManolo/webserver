# FILES

├── [README.md](https://github.com/StringManolo/webserver/blob/master/FILES.md#readmemd)    
├── [console.h](https://github.com/StringManolo/webserver/blob/master/FILES.md#consoleh)  
├── [makefile](https://github.com/StringManolo/webserver/blob/master/FILES.md#makefile)  
├── [read_config.cpp](https://github.com/StringManolo/webserver/blob/master/FILES.md#read_configcpp)  
├── [serv.conf](https://github.com/StringManolo/webserver/blob/master/FILES.md#servconf)  
├── [serv.cpp](https://github.com/StringManolo/webserver/blob/master/FILES.md#servcpp)  
├── [serv.h](https://github.com/StringManolo/webserver/blob/master/FILES.md#servh)  
├── [test](https://github.com/StringManolo/webserver/blob/master/FILES.md#test)  
│   ├── [read_config.c](https://github.com/StringManolo/webserver/blob/master/FILES.md#read_configc)  
│   └── [serv.conf](https://github.com/StringManolo/webserver/blob/master/FILES.md#readconf)  
├── [test_config.cpp](https://github.com/StringManolo/webserver/blob/master/FILES.md#testconfigcpp)  
└── [utils.h](https://github.com/StringManolo/webserver/blob/master/FILES.md#utilsh)
  
1 directory, 11 files  
  
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
  
###### Extra:  
DEBUG also outputs current time and logs messages to logs.txt
  
&nbsp;  
  
## **[makefile](https://github.com/StringManolo/webserver/blob/master/makefile)**  
  
&nbsp;

## **[read_config.cpp](https://github.com/StringManolo/webserver/blob/master/read_configcpp)**  
  
&nbsp;
  
## **[serv.conf](https://github.com/StringManolo/webserver/blob/master/servconf)**  
  
&nbsp;
  
## **[serv.cpp](https://github.com/StringManolo/webserver/blob/master/servcpp)**  
  
&nbsp;
  
## **[serv.h](https://github.com/StringManolo/webserver/blob/master/servh)**  
  
&nbsp;
  
## **[test](https://github.com/StringManolo/webserver/blob/master/test)**  
  
&nbsp;
  
+  ### **[read_config.c](https://github.com/StringManolo/webserver/blob/master/test/read_configc)**  
  
&nbsp;
  
+  ### **[serv.conf](https://github.com/StringManolo/webserver/blob/master/test/readconf)**  
  
&nbsp;
  
## **[test_config.cpp](https://github.com/StringManolo/webserver/blob/master/testconfigcpp)**  
  
&nbsp;
  
## **[utils.h](https://github.com/StringManolo/webserver/blob/master/utilsh)**  
  

