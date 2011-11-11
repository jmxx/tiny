#include "Tiny.h"

//Tiny::TinyFunction Tiny::tinyFn = 0;

/*
 * Metodo estático para crear una App.
 */
Tiny Tiny::createApp(TinyFunction tinyFn)
{
  return Tiny(tinyFn);
}

Tiny::Tiny()
{
  INFO("Constructor de Tiny.");
  init();
}

Tiny::Tiny(TinyFunction _tinyFn) : tinyFn(_tinyFn)
{
  init();
}

void Tiny::init()
{
  epoll = 0;
  serverName = "Tiny Server";
  version = "0.0.1";
  INFO("Iniciando Tiny");
}

SocketServer *Tiny::Server()
{
  return socketServer;
}

void Tiny::listen()
{
  this->listen(DEFAULT_PORT);
}

void Tiny::listen(int port)
{
  this->port = port;
  this->socketServer = new SocketServer(this->port); //Escucha
  epoll = new EpollHandler(this);
  //this->request = new HttpRequest();
  this->run();
}

void Tiny::run()
{
  std::string line;
  /*
  INFO("Listen Tiny at " << this->port);
  this->request = HttpRequest(socketServer->Accept());
  /*if (this->client == NULL) {
    std::cout << "No se puede abrir socket de cliente\n";
    //exit(-1);
  }
  this->request.processRequest();
  std::cout<< "Path: " << this->request.path << std::endl;
  std::cout<< "Method: " << this->request.method << std::endl;
  std::cout<< "Accept Charset: " << this->request.charset << std::endl;
  std::cout<< "User Agent: " << this->request.userAgent << std::endl;
  
  /**
   * Ejecuta la función
   
  tinyFn(this->request, this->response);
  */
  epoll->loop();
  std::cout << "Enviado: " << std::endl;
  this->socketServer->close();
}

int Tiny::respond()
{
  this->request.processRequest();
  std::cout<< "Path: " << this->request.path << std::endl;
  //std::cout<< "Method: " << this->request.method << std::endl;
  //std::cout<< "Accept Charset: " << this->request.charset << std::endl;
  //std::cout<< "User Agent: " << this->request.userAgent << std::endl;
  tinyFn(this->request, this->response);
  //INFO("ENVIANDO:");
  return 1;
}
