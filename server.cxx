#include "server.hxx"
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <pthread.h>
#include <malloc.h>

struct thread_info{
  pthread_t thread_id;//kernel id returned by pthread_create
  int thread_num;//application defined id
  char* argv_string;
};


void* threadfunction(void* arg){
  
  
}

server::server(A_WORK_FUNC a_work_func,int port){

  work_func = a_work_func;
  m_port = port;

  unsigned int address_size;
  int i,len;
  
  char buf[4000]; //for receiving data from clients
  
  temp_buf = new char[16384];//space for return data

  sock_descriptor = socket(AF_INET,SOCK_STREAM,0);

  if(sock_descriptor == -1){
    perror("call to socket");
    exit(1);
  }

  bzero(&sin,sizeof(sin));
  sin.sin_family=AF_INET;
  sin.sin_addr.s_addr=INADDR_ANY;
  sin.sin_port= htons(port);

  if(bind(sock_descriptor,(struct sockaddr*)&sin, sizeof(sin)) == -1){
    
    perror("call to bind");
    exit(1);
  }
  
  if(listen(sock_descriptor,20) == -1){
    perror("call to listen");
    exit(1);
  }

  while(1){

    temp_sock_descriptor =
      accept(sock_descriptor,(struct sockaddr *) &pin,
	     &address_size);//blocking

    if(temp_sock_descriptor == -1)
    {
      perror("call to accept");
      exit(1);
    }

    struct thread_info* tinfo=(struct thread_info*)malloc(sizeof(struct thread_info));
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    int  succuss=pthread_create(&tinfo->thread_id,&attr,threadfunction,tinfo);
    

    if(recv(temp_sock_descriptor,buf,4000,0) == -1)
    {
      perror("call to recv");
      exit(1);
    }

    work_func(buf,temp_buf,16384);
    len=strlen(temp_buf);
    if(send(temp_sock_descriptor,
	    temp_buf,len,0) == -1){
    
      perror("call to send");
      exit(1);
    }
    
    close(temp_sock_descriptor);
  }
}

server::~server(){
}
