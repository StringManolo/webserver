## **DOCUMENTATION**

├── [README.md](https://github.com/StringManolo/webserver/blob/master/FILES.md#readmemd)    
├── [console.h](https://github.com/StringManolo/webserver/blob/master/FILES.md#consoleh)  
├── [http.h](https://github.com/StringManolo/webserver/blob/master/FILES.md#httph)  
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
  
## **[http.h](https://github.com/StringManolo/webserver/blob/master/http.h)**  
###### Exposed:  
  
   _http_p.parser(vector<char>, struct HTTP &http)_  
   _http.method_  
   _http.path_
   _http.version_  
   _http.headers[i]_  
   _http.body_  
   
###### Intended for:  
  
   Intended to parse and recive http headers.
###### Description:
  
   Read a vector of chars(acts as buffer) to iterate over and extract the http headers and body.
  
   1st parameter is the vector of chars of any size holding the http request recived by the server.  
  
   2st parameter is a reference of a HTTP custom type what is going to be filled by the http_p.parser() method.
  
###### Example:
```
#include "http.h"

int main() {
  HTTP http;
  HTTP_PARSER http_p;
  
  http_p.parser(buffer, http);
  cout << http.method;

  return 0;
}
```
  
&nbsp;
  

## **[makefile](https://github.com/StringManolo/webserver/blob/master/makefile)**  
  
&nbsp;

## **[read_config.cpp](https://github.com/StringManolo/webserver/blob/master/read_config.cpp)**  
  
&nbsp;
  
## **[serv.conf](https://github.com/StringManolo/webserver/blob/master/serv.conf)**  
  
&nbsp;
  
## **[serv.cpp](https://github.com/StringManolo/webserver/blob/master/serv.cpp)**  
  
&nbsp;
  
## **[serv.h](https://github.com/StringManolo/webserver/blob/master/serv.h)**  
  
&nbsp;
  
## **[test](https://github.com/StringManolo/webserver/blob/master/test)**  
  
&nbsp;
  
+  ### **[read_config.c](https://github.com/StringManolo/webserver/blob/master/test/read_config.c)**  
  
&nbsp;
  
+  ### **[serv.conf](https://github.com/StringManolo/webserver/blob/master/test/serv.conf)**  
  
&nbsp;
  
## **[test_config.cpp](https://github.com/StringManolo/webserver/blob/master/test_config.cpp)**  
  
&nbsp;
  
## **[utils.h](https://github.com/StringManolo/webserver/blob/master/utils.h)**  
###### Exposed:  
  
   _utils.split(string, char, &vector<string>)_  
  
###### Intended for:  
  
   Parse http requests to get method, path, version, headers...
###### Description:
  
   Split a string content into a vector of strings using a char as delimitator.  

   1st parameter is a string holding the text to split.  
  
   2st parameter is the delimitator used as split point.  
  
   3rd parameter vector to hold the splited strings.  
###### Example:
```
#include <vector>
#include <string>
#include "utils.h"


int main() {
  UTILS utils;
  std::string content = "Hello World";
  std::vector<std::string> strings;

  utils.split(content, ' ', strings);
  cout << strings[0] << " this is my " << strings[1];

  return 0;
}
```
  
