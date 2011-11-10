#include "SocketServer.h"

SocketServer::SocketServer(int port) : 
  Socket(AF_INET, SOCK_STREAM, (port_t)port)
{
  this->listen();
}

Socket* SocketServer::Accept()
{
  //this->listen();
  socklen_t clientLength;
  struct sockaddr client;
  int clientDesc;
  /*
  * La llamada a la funcion accept requiere que el parametro 
  * clientLength contenga inicialmente el tamaño de la
  * estructura client que se le pase. A la vuelta de la
  * funcion, esta variable contiene la longitud de la informacion
  * util devuelta en client
  */
  clientLength = sizeof(client);
  clientDesc = ::accept(this->socketDesc, &client, &clientLength);
  if (clientDesc == -1) {
    std::cout << "---Ha ocurrido un error asociando el Socket." << clientDesc << std::endl;
    return NULL;
  }
  
  
  /*
  * Se devuelve el socket_desc en el que esta "enchufado" el client.
  */
  return new Socket(clientDesc, client);
}

std::string SocketServer::RecvHeaders()
{
  std::string line;
  std::string headers;
  do {
    line = this->recvLine();
    headers += line;
  } while (line != "\r\n");
  return headers;
}
