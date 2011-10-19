#include "Tiny.h"

Tiny::ReqFunction Tiny::reqFunction = 0;

/*
 * Metodo estático para crear una App.
 */
Tiny* Tiny::createApp(ReqFunction reqFn)
{
  return new Tiny(reqFn);
}

Tiny::Tiny()
{
  std::cout << "Constructor Tiny" << std::endl;
  this->init();
}

Tiny::Tiny(ReqFunction reqFn)
{
  reqFunction = reqFn;
}

void Tiny::init()
{
  this->ServerName = "Tiny";
}

void Tiny::listen()
{
  this->listen(DEFAULT_PORT);
}

void Tiny::listen(int port)
{
  this->port = port;
  this->serverSocket = new SocketServer(this->port);
  //this->request = new HttpRequest();
  this->run();
}

void Tiny::run()
{
  std::string line;
  
  std::cout << "Listen Tiny at " << this->port << std::endl;
  this->request = new HttpRequest(this->serverSocket->Accept());
  /*if (this->client == NULL) {
    std::cout << "No se puede abrir socket de cliente\n";
    //exit(-1);
  }*/
  this->request->processRequest();
  std::cout<< "Path: " << this->request->path << std::endl;
  std::cout<< "Method: " << this->request->method << std::endl;
  std::cout<< "Accept Charset: " << this->request->charset << std::endl;
  std::cout<< "User Agent: " << this->request->userAgent << std::endl;
  reqFunction(this->request, this->response);
  std::cout << "Enviado: " << std::endl;
}

bool Tiny::isValidPort()
{

}
