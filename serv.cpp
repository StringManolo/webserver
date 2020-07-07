#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

#define HOST_PORT atoi(argv[2])
struct in_addr ip;
#define HOST_IP inet_aton(argv[1], &ip)
#define ERROR -1

int main(int argc, char **argv) {

  if (!argv[1]) {
    std::cout << std::endl <<  "YOU FORGOT PARAMETERS:"  << 
      std::endl << "Add ip and port." << std::endl <<
      "Example: ./server 127.0.0.1 9090" << std::endl;
    return 0;
  } else if (!argv[2]) {
    std::cout << std::endl <<  "YOU FORGOT PARAMETERS:"  << 
      std::endl << "Add ip and port." << std::endl <<
      "Example: ./server 127.0.0.1 9090" << std::endl;
    return 0;
  }

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == ERROR) {
    std::cout << "Failed to create socket. Errno: " << errno << std::endl;
    return 1;
  }

  sockaddr_in sockaddr;
  sockaddr.sin_family = AF_INET;
  HOST_IP;
  sockaddr.sin_addr.s_addr = ip.s_addr;
  sockaddr.sin_port = htons(HOST_PORT);

  int sockbind = bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
  if (sockbind == ERROR) {
    std::cout << "Failed to bind to port " << HOST_PORT
        << ". Errno: " << errno << std::endl;
    return 2;
  }

  int socklist = listen(sockfd, 10);
  if (socklist == ERROR) {
    std::cout << "Failed to listen on socket. Errno: " << errno << std::endl;
    return 3;
  }

  for(;;) {
    auto addrlen = sizeof(sockaddr);
    int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);

    if (connection == ERROR) {
      std::cout << "Failed to grab connection. Errno: " << errno << std::endl;
      /* nada */
    }

    char buffer[8192];
    auto bytesRead = read(connection, buffer, 8192);
    std::cout << "Recived: " << buffer << std::endl;

    
    std::cout << "Connection closed." << std::endl;
    close(connection); 
  }


  return 0;
}
