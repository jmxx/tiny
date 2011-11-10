#ifndef TINY_H
#define TINY_H

#include <iostream>

#include "HttpRequest.h"
#include "HttpResponse.h"
#include "EpollHandler.h"
#include "SocketServer.h"

#define DEFAULT_PORT  8005

class EpollHandler;
class SocketServer;

class Tiny
{
  friend class EpollHandler;
public:
  /*
   * Definimos TinyFn, un puntero a una funcion que recibe como parametros
   * un objeto HttpRequest y un objeto HttpResponse. Retorna void.
   */
  typedef void (*TinyFunction) (HttpRequest req, HttpResponse res);
  
  /*
   * Crea una aplicación.
   * Método estático que retorna un objecto Tiny.
   */
  static Tiny createApp(TinyFunction tinyFn);
  
  /*
   *Constructor de Tiny.
   * @tinyFn Funcion que se ejecutara en cada peticion.
   * @port Puerto de escucha.
   */
  Tiny(TinyFunction tinyFn, unsigned int port);
  Tiny();
  Tiny(TinyFunction tinyFn);
  
  void listen();
  void listen(int port);
  
  SocketServer* Server();
  int respond();

private:
  //static TinyFunction   tinyFn;
  TinyFunction   tinyFn;

  /**
   * Inicializa Tiny
   */
  void init();
  
  /**
   * Una vez configurado, ejecuta Tiny
   */
  void run();
  
  
  port_t        port;
  
  HttpRequest   request;
  HttpResponse  response;
  
  SocketServer  *socketServer;
  EpollHandler  *epoll;
  
  std::string   serverName;
  std::string   version;
};


#endif /* TINY_H */
