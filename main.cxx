#include <iostream>
#include "client.hxx"
#include <stdio.h>

using namespace std;
int main(int argc,char* argv[]){
  client * cli=new client();
  char *s;
  char buf[100];
  sprintf(buf,"this is a test");

  s=cli->getResponseFromServer(buf);
  cout<<"Server response:"<<s<<"\n";
  sprintf(buf,"this is an another test");
  s=cli->getResponseFromServer(buf);
  cout<<"server response:"<<s<<"\n";
  delete cli;//closes the socket connection

}
