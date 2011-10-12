#include "SocketServer.h"

SocketServer::SocketServer(int port) : Socket(port)  {
  std::cout << "Socket Server" << std::endl;
  this->Listen();
}

Socket* SocketServer::Accept()
{
  socklen_t clientLength;
  struct sockaddr client;
  int clientDesc;
  std::cout << "1. Aceptando peticiones" << std::endl;
  /*
  * La llamada a la funcion accept requiere que el parametro 
  * clientLength contenga inicialmente el tamaño de la
  * estructura client que se le pase. A la vuelta de la
  * funcion, esta variable contiene la longitud de la informacion
  * util devuelta en client
  */
  clientLength = sizeof(client);
  clientDesc = ::accept(this->socketDesc, &client, &clientLength);
  std::cout << "2. Aceptando peticiones" << std::endl;
  if (clientDesc == -1)
    return NULL;
  
  std::cout << "3. Aceptando peticiones" << std::endl;
  /*
  * Se devuelve el socketDesc en el que esta "enchufado" el client.
  */
  return new Socket(clientDesc, client);
}
