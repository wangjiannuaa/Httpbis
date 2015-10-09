#include "client.hxx"

//#include <linux/types.h>//kernel
//#include <linux/socket.h>

#include <x86_64-linux-gnu/sys/types.h>//user
#include <x86_64-linux-gnu/sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

//#include <boost/>


#include <iostream>
using namespace std;

client::client(const char* my_host_name,int my_port){
  port = my_port;
  host_name = const_cast<char*> (my_host_name);
  if((server_host_name = gethostbyname(host_name)) == 0){
    perror("Error resolving local host\n");
    exit(1);
  }

  bzero(&pin,sizeof(pin));
  pin.sin_family = AF_INET;
  pin.sin_addr.s_addr = htonl(INADDR_ANY);
  pin.sin_addr.s_addr = 
    ((struct in_addr *) (server_host_name->h_addr))->s_addr;
  pin.sin_port = htons(port);
}

char* client::getResponseFromServer(char* str){
  if((socket_descriptor = socket(AF_INET, SOCK_STREAM,0)) == -1){
    perror("Error opening socket\n");
    exit(1);
  }

  if(connect(socket_descriptor,
	     (const sockaddr *)&pin,sizeof(pin)) ==-1){
    perror("Error connecting to socket\n");
    exit(1);
  }

  cout<<"Sending message'"<<str<<"' to server ;;;\n";
  if(send(socket_descriptor,str,strlen(str),0)==-1){
    perror("Error in send\n");
    exit(1);
  }

  cout<<"..send message..wait for response...\n";

  if(recv(socket_descriptor,buf,8192,0)==-1){
    perror("Error in receiving response from server\n");
    exit(1);
  }

  close(socket_descriptor);
  cout<<"\n Response from server:\n"<<buf<<"\n";
  return buf;
}
