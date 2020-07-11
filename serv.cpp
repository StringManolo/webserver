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
  read_config();
  
  console.log(true,"IP in serv.conf" + _CONFIG["IP"],DEBUG);
  
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

    /* http parser call */
    http_p.parser(buffer, http);
    console.log(true, http.method, DEBUG);
    console.log(true, http.body, DEBUG);


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
    if (http.method == "GET" || http.method == "HEAD") {
      /* Find Path */
      const char * reqPath = http.path.c_str();
      const char * reqFile = http.path.substr(1, http.path.size()).c_str();
      if (dir.isDirectory(reqPath)) {
        std::cout << reqPath << " is a directory." << std::endl;
        /* Check in config if is allowed directory listing.
	 * else throw 403 */
	rH = "";
	rH += "HTTP/1.1 403 Forbidden";
	rH += "\r\n\r\n";
	rH += page.error.fourZeroThree;
	rH += "\r\n\r\n";

      } else if (dir.is_regular_file(reqFile)) {
        std::cout << reqPath << " is a file." << std::endl;
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
    }

    close(connection); 
  }


  return 0;
}


