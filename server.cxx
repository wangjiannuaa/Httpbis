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
#include <signal.h>
#include <x86_64-linux-gnu/sys/time.h>

#include <iostream>
struct thread_info{
  pthread_t thread_id;//kernel id returned by pthread_create
  int thread_num;//application defined id
  int sock;
  char* argv_string;
};


void server::work_func(char* command,char* return_buffer ,int return_buffer_size){//static membership statement and definition
  std::cout<<"entering my_work_func("<<command<<",...)\n";
  sprintf(return_buffer,"overriden my_work_func. %s",command);

}

 void timerhandler(int num)
 {
    //do something   
}



void* threadfunction(void* arg){
  struct thread_info* tinfo=(struct thread_info*) arg;
  int sock=tinfo->sock;  

  char buf[4000]; //for receiving data from clients
  
  char temp_buf[16384];//space for sending data
   
    if(recv(sock,buf,4000,0) == -1)
    {
      perror("call to recv");
      exit(1);
    }

    server:: work_func(buf,temp_buf,16384);

    int len=strlen(temp_buf);

    if(send(sock,
	    temp_buf,len,0) == -1){
    
      perror("call to send");
      exit(1);
    }

    close(sock);
}

server::server(int port){

  m_port = port;

  unsigned int address_size;
  

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

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

    
    signal(SIGALRM,timerhandler);
    struct itimerval tick;
    tick.it_value.tv_sec = 0;//now 
    tick.it_value.tv_usec=0;
    tick.it_interval.tv_sec =1;//1 s handler
    tick.it_interval.tv_usec=0;


    int ret = setitimer(ITIMER_REAL,&tick,NULL);
    

  while(1){

   int  temp_sock_descriptor =
      accept(sock_descriptor,(struct sockaddr *) &pin,
	     &address_size);//blocking

    if(temp_sock_descriptor == -1)
    {
      perror("call to accept");
      exit(1);
    }

      
    struct thread_info* tinfo=(struct thread_info*)malloc(sizeof(struct thread_info));
    tinfo->sock=temp_sock_descriptor;
   
    int  success=pthread_create(&tinfo->thread_id,&attr,threadfunction,tinfo);
   
    if(success) perror("thread is created");
  }
    
    pthread_attr_destroy(&attr);
}

server::~server(){
  printf("Server is being destroyed");
}
