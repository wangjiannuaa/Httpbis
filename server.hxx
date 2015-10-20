#include <netdb.h>
#include <x86_64-linux-gnu/sys/types.h>
#include <x86_64-linux-gnu/sys/socket.h>

class server{
public:
  static void work_func(char *, char *,int);
  server(int port);
  ~server();
private:
  
  int sock_descriptor;
  int m_port;
  struct sockaddr_in sin;
  struct sockaddr_in pin;
  
  int counter;
  int timer;
};

//simulate timer procedure
//make -Dkernel enable <linux/> defination,disable<sys/>system call defination
