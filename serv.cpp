#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
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

HTTP_PARSER http_p;

/* pwd && getFileList defined here */
#include "directories.h"
DIRECTORIES dir;

/* read config */
#include "conf.h"

/* error pages defined here */
#include "pages.h"
PAGES page;

/* mimetypes defined here*/
#include "mime_type_sniff.h"
MIME mime;


#define THREAD_MAX 16
/*
   Function prototypes
*/
void *thread_process(void *vargp);


/* Make cli params readable */
#define ERROR -1

/* Make conditionals readable. */
//#define REQUEST j == 0

int main(int argc, char **argv) {
  /*
  threads variables
  */
  pthread_attr_t attr;
	pthread_t tid;
	int pth_r;
	int *tothread = NULL;

  int sockbind = 0;
  int sockfd = 0;
  int socklist = 0;
  struct in_addr ip;
  sockaddr_in sockaddr;
  read_config();
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == ERROR) {
    console.log(true, "Failed to create socket.", CRITICAL);
    return 1;
  }

  sockaddr.sin_family = AF_INET;
  inet_aton(_CONFIG["IP"].c_str(), &ip);
  sockaddr.sin_addr.s_addr = ip.s_addr;
  sockaddr.sin_port = htons(atoi(_CONFIG["PORT"].c_str()));
  sockbind = bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
  if (sockbind == ERROR) {
	  std::string error = strerror(errno);
    console.log(true, "Failed to bind to port " + _CONFIG["PORT"] + " : " +error, CRITICAL);
    return 2;
  }
  socklist = listen(sockfd, 10);
  if (socklist == ERROR) {
    console.log(true, "Failed to listen on socket.", CRITICAL);
    return 3;
  }

  console.log(true, "Server is listening @ http://" +_CONFIG["IP"] + ":"+_CONFIG["PORT"], VERBOSE);
  //console.log(true,"PATH in serv.conf " + _CONFIG["PATH"],DEBUG);

  for(;;) {
    auto addrlen = sizeof(sockaddr);
    int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);

    if (connection == ERROR) {
      console.log(true, "Failed to grab connection.", DEBUG);
      /* nada */
    }
    /*
			init the pthread_attr_t variable
		*/
		pth_r = pthread_attr_init(&attr);
		if (pth_r != 0)	{
			perror("pthread_attr_init");
			exit(6);
		}
		/*
			set stack size of the pthread to min
		*/
		pth_r = pthread_attr_setstacksize(&attr,PTHREAD_STACK_MIN);
		if(pth_r != 0)	{
			perror("pthread_attr_setstacksize");
			exit(7);
		}
		/*
			Set deteched of the pthread
		*/
		pth_r = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
		if(pth_r != 0)	{
			perror("pthread_attr_setstacksize");
			exit(8);
		}
		/*
			Values to pass to the pthread
		*/
		tothread = new int[2];
		tothread[0] = connection;			/*	Client file descriptor */

		pth_r = pthread_create(&tid,&attr,thread_process,(void *)tothread);
		if(pth_r != 0)	{
			perror("pthread_create");
			exit(9);
		}
		pthread_attr_destroy(&attr);
  }
  return 0;
}

void *thread_process(void *vargp)	{
  HTTP http;
  int *thread_arg;
  int connection;
  thread_arg = (int*)vargp;
  connection = thread_arg[0];
  delete thread_arg;

  std::vector<char> buffer(2048);
  auto bytesRead = read(connection, &buffer[0], buffer.size());
  std::string bufferOut (buffer.begin(), buffer.end());

  console.log(true, "Connection recived", DEBUG);
  console.log(true, bufferOut, DEBUG);
  /* http parser call */
  http_p.parser(buffer, http);
  /* console.log(true, http.method, DEBUG); */

  /* Server Response */
  std::string rH = "";

  if(strcmp(http.path.c_str(),"/") == 0)  {
	http.path = "/index.html";
  }

  if (http.method == "GET" || http.method == "HEAD") {
    /* Find Path */
    std::string fullPath = _CONFIG["PATH"] + http.path;
    const char * reqFile = fullPath.c_str();
  int leido = 0;

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
      if(strncmp(_CONFIG["PATH"].c_str(),reqFile,_CONFIG["PATH"].length()) == 0)  {  // reqFile is inside of _CONFIG["PATH"]
      std::cout << reqFile << " is a file." << std::endl;
        rH = "";
        rH += "HTTP/1.1 200 OK\r\n";
	  rH += "Content-Type: " + mime.sniff(reqFile) + "\r\n";
	  rH += "Content-Length: " + std::to_string(dir.fsize(reqFile)) + "\r\n";
        rH += "\r\n";
        char *buffer = dir.file_get_contents(reqFile,&leido);
        rH += std::string(buffer,leido);
      }
      else  {    //reqFile is outside of _CONFIG["PATH"], maybe ../../../ or something like that
        rH = "";
        rH += "HTTP/1.1 403 Forbidden";
        rH += "\r\n\r\n";
        rH += page.error.fourZeroThree;
        rH += "\r\n\r\n";
      }

    } else {
      rH = "";
      rH += "HTTP/1.1 404 Not Found ";
      rH += "\r\n\r\n";
      rH += page.error.fourZeroFour;
      rH += "\r\n\r\n";
    }
    send(connection, rH.c_str(), rH.length(), 0);
  }
  std::cout <<  "conf : " <<  _CONFIG["DIRLIST"] << std::endl;
  close(connection);
	pthread_exit(NULL);
}
