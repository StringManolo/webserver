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
#define REQUEST j == 0

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

      std::vector<std::string> headers;
      std::string body = "";
      int headersEnd = 0;
    };
    
    HTTP http;

    std::vector<std::string> tmpVec, strings;
    std::string tmpString;
    for(int i = 0, j = 0; i < buffer.size(); ++i) {
      if(buffer[i] == '\n' || (buffer[i] == '\0' && buffer[i+1] != '\0')) {
        /* Debug/raw */ 
	tmpVec.push_back(tmpString);
	/* console.log(true, tmpString, VERBOSE); */

	tmpString = "";
	++j;
      }
      tmpString += buffer[i];
    } 


    for(int k = 0; k < tmpVec.size(); ++k) {
      for(int l = 0; l < tmpVec[k].size(); ++l) {
        if(static_cast<char>(tmpVec[k][l]) == '\r') {
      /*  console.log(true, "Encontrado r", WARNING); */
          tmpVec[k][l] = '\0';
	} if (static_cast<char>(tmpVec[k][l]) == '\n') {
      /* console.log(true, "Encontrado n", WARNING); */
          tmpVec[k][l] = '\0';
	}
      }

      if (k == 0) {

	utils.split(tmpVec[k], ' ', strings);
	http.method = strings[0];
	http.path = strings[1];
	http.version = strings[2];

      }

      if (k > 0) {
	
        /* End of headers */
        if (tmpVec[k].size() == 2) {

	  /* Set only once */
	  if (http.headersEnd == 0) {
            http.headersEnd = k;
	  }
	}

	if (http.headersEnd == 0) {
          http.headers.push_back(tmpVec[k]);
	} else {
          http.body += tmpVec[k];
	}
	
      }

     /* std::cout << "HEADER:" << tmpVec[k] << std::endl << std::endl; */
    }


    std::cout << "Method: " << http.method << std::endl;
    std::cout << "Path: " << http.path << std::endl;
    std::cout << "Version: " << http.version << std::endl;

    for (int i = 0; i < http.headers.size(); ++i) {
      std::cout << "Header" << i+1 << ":"
        << http.headers[i] << std::endl;
    }

    std::cout << "Body: " << http.body << std::endl;

    console.log(true, "Connection closed.", DEBUG);
    close(connection); 
  }


  return 0;
}


