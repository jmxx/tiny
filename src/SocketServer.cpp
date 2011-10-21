#include "SocketServer.h"

SocketServer::SocketServer(int port) : 
  Socket(AF_INET, SOCK_STREAM, port)
{
  this->listen();
}

Socket* SocketServer::Accept()
{
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
    return NULL;
  }
  
  std::cout << "---Ha ocurrido un error asociando el Socket." << clientDesc << std::endl;
  /*
  * Se devuelve el socketDesc en el que esta "enchufado" el client.
  */
  return new Socket(clientDesc, client);
}

std::string SocketServer::RecvHeaders()
{
  std::string line;
  std::string headers;
  do {
    line = this->RecvLine();
    headers += line;
  } while (line != "\r\n");
  return headers;
}
