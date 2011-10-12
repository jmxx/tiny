#include "Mesero.h"

Mesero::Mesero()
{
  std::cout << "Constructor Mesero" << std::endl;
  this->port = 8005;
  this->server = new SocketServer(this->port);
}

/*Mesero::Mesero(RequestFunction reqFn, unsigned int port)
{

}*/

int Mesero::listen()
{
  std::cout << "Listen Mesero at " << this->port << std::endl;
  this->client = this->server->Accept();
  if (this->client == NULL) {
    std::cout << "No se puede abrir socket de cliente\n";
    //exit(-1);
  }
  std::cout<< "Recibiendo: " << this->client->RecvLine() << std::endl;
}
