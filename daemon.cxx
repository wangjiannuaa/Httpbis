#include <iostream>
#include "server.hxx"
#include <stdio.h>
using namespace std;
void my_work_func(char * command, char * return_buffer,
		  int return_buffer_size){

  cout<<"entering my_work_func("<<command<<",...)\n";
  sprintf(return_buffer,"overriden my_work_func. %s",command);
}

int main(int argc, char* argv[]){

  A_WORK_FUNC a= my_work_func;

  server* ser=new server(a,9090);//default to prot=9090;
}
