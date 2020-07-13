#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <map>
#include <array>
#include <errno.h>

/* console.log defined here */
#include "console.h"
CONSOLE console;

/* split defined here */
#include "utils.h"
UTILS utils;

/* parser defined here */
#include "http.h"
HTTP http;
HTTP_PARSER http_p;

/* pwd && getFileList defined here */
#include "directories.h"
DIRECTORIES dir;

/* read config */
#include "conf.h"


/* error pages defined here */
#include "pages.h"
PAGES page;

#include "mime_type_sniff.h"
MIME mime;



/* Make cli params readable */
#define HOST_PORT atoi(argv[2])
#define HOST_IP inet_aton(argv[1], &ip)
#define ERROR -1

/* Make conditionals readable. */
#define REQUEST j == 0

int main(int argc, char **argv) {

  std::string hexfile = "serv.cpp";
  std::cout << "Requested file = " << hexfile << 
    std::endl << "File Headers Seems like a " << mime.sniff(hexfile) << " file type." <<  std::endl;

  /*std::cout << mime.header.size() << std::endl << mime.type.size()  << std::endl;*/

  /*for(int i = 0; i < mime.type.size(); ++i) {
    std::cout << i << " . " << mime.type[i] << std::endl << mime.header[i] << std::endl << std::endl;
  }*/

  struct in_addr ip;

  if (!argv[1]) {
    console.log(true, "YOU FORGOT PARAMETERS:\nAdd ip and port.\nExample: ./server 127.0.0.1 9090", CRITICAL);

    return 0;
  } else if (!argv[2]) {
    console.log(true, "YOU FORGOT PARAMETERS:\nAdd ip and port.\nExample: ./server 127.0.0.1 9090", CRITICAL);

    return 0;
  }

  read_config(); 
  console.log(true,"IP in serv.conf " + _CONFIG["IP"],DEBUG);
  
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == ERROR) {
    console.log(true, "Failed to create socket.", CRITICAL);
    return 1;
  }

  sockaddr_in sockaddr;
  sockaddr.sin_family = AF_INET;
  HOST_IP;
  sockaddr.sin_addr.s_addr = ip.s_addr;
  sockaddr.sin_port = htons(HOST_PORT);

  int sockbind = bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
  if (sockbind == ERROR) {
    console.log(true, "Failed to bind to port", CRITICAL);
    return 2;
  }

  int socklist = listen(sockfd, 10);
  if (socklist == ERROR) {
    console.log(true, "Failed to listen on socket.", CRITICAL);
    return 3;
  }

  console.log(true, "Server is listening", VERBOSE);

  console.log(true,"PATH in serv.conf " + _CONFIG["PATH"],DEBUG);


  /* Change dir */
  //std::string publicDir = realpath(_CONFIG["PATH"].c_str(),NULL);

  for(;;) {
    auto addrlen = sizeof(sockaddr);
    int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);

    if (connection == ERROR) {
      console.log(true, "Failed to grab connection.", DEBUG);
      /* nada */
    }

    std::vector<char> buffer(2048); 
    auto bytesRead = read(connection, &buffer[0], buffer.size()); 
    std::string bufferOut (buffer.begin(), buffer.end());

    console.log(true, "Connection recived", DEBUG);
    console.log(true, bufferOut, DEBUG);

    /* http parser call */
    http_p.parser(buffer, http);
    /* console.log(true, http.method, DEBUG);
    console.log(true, http.body, DEBUG); */


    /* Working Dir */
    /* std::cout << dir.pwd << std::endl; */

    /* Default Error Pages */
    /* std::cout << page.error.fourZeroZero << std::endl << std::endl;
    std::cout << page.error.fourZeroOne << std::endl << std::endl;
    std::cout << page.error.fourZeroThree << std::endl << std::endl;
    std::cout << page.error.fourZeroFour << std::endl << std::endl;
    std::cout << page.error.fiveZeroZero << std::endl << std::endl;
    std::cout << page.error.fiveZeroThree << std::endl << std::endl; */


    /* List files and folders */
    /* std::vector<std::string> files;
    const char * pwd  = dir.pwd.c_str();
    files = dir.getFileList(pwd);

    for(int i = 0; i < files.size(); ++i) {
      std::cout << files[i] << std::endl;
    } */

    /* Server Response */
    std::string rH = "";
	
	if(strcmp(http.path.c_str(),"/") == 0)	{
		http.path = "/index.html";
	}

    if (http.method == "GET" || http.method == "HEAD") {
      /* Find Path */
      std::string fullPath = _CONFIG["PATH"] + http.path;
      const char * reqFile = fullPath.c_str();

      std::cout << "MECAGOENMISMUERTOS: " << reqFile << std::endl;

      if (dir.isDirectory(reqFile)) {
        std::cout << reqFile << " is a directory." << std::endl;
          if (_CONFIG["DIRLIST"] == "ON") {
            /* Show dirs and links when GET /folder/ */
		  }
		  else {
			rH = "";
			rH += "HTTP/1.1 403 Forbidden";
			rH += "\r\n\r\n";
			rH += page.error.fourZeroThree;
			rH += "\r\n\r\n";
          }
	  } else if (dir.is_regular_file(reqFile)) {
        std::cout << reqFile << " is a file." << std::endl;
        rH = "";
		rH += "HTTP/1.1 200 OK";
		rH += "\r\n\r\n";
		rH += page.error.twoZeroZero;
		rH += "\r\n\r\n";
        
      } else {
        rH = "";
        rH += "HTTP/1.1 404 Not Found ";
	rH += "\r\n\r\n";
	rH += page.error.fourZeroFour;
	rH += "\r\n\r\n";
      }
      
      send(connection, rH.c_str(), rH.length(), 0);
/*     } else {
       rH = "";
       rH += "HTTP/1.1 403 Forbidden";
       rH += "\r\n\r\n";
       rH += page.error.fourZeroThree;
       rH += "\r\n\r\n"; 
       }
*/


    }
    std::cout <<  "conf : " <<  _CONFIG["DIRLIST"] << std::endl;
    close(connection); 
  }


  return 0;
}


