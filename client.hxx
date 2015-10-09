//#include <iostream>
#include <netdb.h>
#include <x86_64-linux-gnu/sys/socket.h>
#include <x86_64-linux-gnu/sys/types.h>

class client{

public:
  client(const char * host = "127.0.0.1",int port = 9090);
  char* getResponseFromServer(char* command);
private:
  int port;
  char * host_name;
  char buf[8192];
  char message[256];
  int socket_descriptor;
  struct sockaddr_in pin;
  struct hostent *server_host_name;
};


