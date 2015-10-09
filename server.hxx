#include <netdb.h>
#include <x86_64-linux-gnu/sys/types.h>
#include <x86_64-linux-gnu/sys/socket.h>


typedef void (*A_WORK_FUNC)(char *, char *,int);

class server{
public:
  server(A_WORK_FUNC a_work_func,int port);
  ~server();
private:
  A_WORK_FUNC work_func;
  int sock_descriptor;
  int m_port;
  struct sockaddr_in sin;
  struct sockaddr_in pin;

  int temp_sock_descriptor;
  char * temp_buf;
};
