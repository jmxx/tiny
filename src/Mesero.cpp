#include "Mesero.h"

Mesero::ReqFunction Mesero::reqFunction = 0;

/*
 * Metodo estático para crear una App.
 */
Mesero* Mesero::createApp(ReqFunction reqFn)
{
  return new Mesero(reqFn);
}

Mesero::Mesero()
{
  std::cout << "Constructor Mesero" << std::endl;
  this->init();
}

Mesero::Mesero(ReqFunction reqFn)
{
  reqFunction = reqFn;
}

void Mesero::init()
{
  this->ServerName = "Mesero";
}

void Mesero::listen()
{
  this->listen(DEFAULT_PORT);
}

void Mesero::listen(int port)
{
  this->port = port;
  this->serverSocket = new SocketServer(this->port);
  //this->request = new HttpRequest();
  this->run();
}

void Mesero::run()
{
  std::string line;
  
  std::cout << "Listen Mesero at " << this->port << std::endl;
  this->request = new HttpRequest(this->serverSocket->Accept());
  /*if (this->client == NULL) {
    std::cout << "No se puede abrir socket de cliente\n";
    //exit(-1);
  }*/
  line = this->request->data();
  std::cout<< "Recibiendo: \n" << line << std::endl;
  reqFunction(this->request);
  std::cout << "Enviado: " << std::endl;
}

bool Mesero::isValidPort()
{

}
