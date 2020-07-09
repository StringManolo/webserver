#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <map>
#include <array>

/* console.log defined here */
#include "console.h"
CONSOLE console;

/* split defined here */
#include "utils.h"
UTILS utils;

/* Make cli params readable */
#define HOST_PORT atoi(argv[2])
#define HOST_IP inet_aton(argv[1], &ip)
#define ERROR -1

/* Make conditionals readable. */
#define GET (tmpString[0] == 'G')
#define POST (tmpString[0] == 'P' && tmpString[1] == 'O')
#define HEAD (tmpString[0] == 'H')
#define OPTIONS (tmpString[0] == 'O')
#define PUT (tmpString[0] == 'P' && tmpString[1] == 'U')
#define TRACE (tmpString[0] == 'T')
#define PATCH (tmpString[0] == 'P' && tmpString[1] == 'A')
#define DELETE (tmpString[0] == 'D')


int main(int argc, char **argv) {

  struct in_addr ip;

  if (!argv[1]) {
    console.log(true, "YOU FORGOT PARAMETERS:\nAdd ip and port.\nExample: ./server 127.0.0.1 9090", CRITICAL);

    return 0;
  } else if (!argv[2]) {
    console.log(true, "YOU FORGOT PARAMETERS:\nAdd ip and port.\nExample: ./server 127.0.0.1 9090", CRITICAL);

    return 0;
  }

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




    /* HTTP PARSER TMP PLACED HERE */
    /* This source is change */
    struct HTTP {
      std::string method = "";
      std::string path = "";
      std::string version = ""; 
    };
    
    HTTP http;

    std::vector<std::string> tmpVec, strings;
    std::string tmpString;
    for(int i = 0, j = 0; i < buffer.size()-1; ++i) {
        if(buffer[i] == '\n') {
          /* Debug/raw */ tmpVec.push_back(tmpString);
	  switch(j) {
	    case 0: /* Primera linea */

              if GET {
		console.log(true, "GET", DEBUG);
        
		utils.split(tmpString, ' ', strings);
                http.method = strings[0];
		http.path = strings[1];
		http.version = strings[2];



		std::cout << "method: " << http.method << std::endl;
		std::cout << "path: " << http.path << std::endl << std::endl;
                std::cout << "version: " << http.version << std::endl;

	      } else if POST {
	        console.log(true, "POST", DEBUG);
	      } else if HEAD {
                console.log(true, "HEAD", DEBUG);
	      } else if OPTIONS {
                console.log(true, "OPTIONS", DEBUG);
	      } else if PUT {
                console.log(true, "PUT", DEBUG);
	      } else if TRACE {
                console.log(true, "TRACE", DEBUG);
	      } else if PATCH {
                console.log(true, "PATCH", DEBUG);
	      } else if DELETE {
                console.log(true, "DELETE", DEBUG);
	      } else {
	        console.log(true, "Not valid http method found.", DEBUG);
	      }
            break;


	  }
	  ++j;
      }
        tmpString += buffer[i];
    }

    std::cout << "Test: " << tmpVec[0] << std::endl;

    console.log(true, "Connection closed.", DEBUG);
    close(connection); 
  }


  return 0;
}


