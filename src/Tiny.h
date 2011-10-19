#ifndef TINY_H
#define TINY_H

#include <iostream>

#include "HttpRequest.h"
#include "HttpResponse.h"

#define DEFAULT_PORT  8005



class Tiny
{
public:
  /*
   * Definimos RequestFn, un puntero a una funcion que recibe como parametro
   * un puntero a un objeto HttpRequest y retorna void.
   */
  typedef void (*ReqFunction) (HttpRequest* req, HttpResponse* res);
  
  /*
   * Método estático que retorna un objecto Tiny.
   */
  static Tiny* createApp(ReqFunction reqFn);
  
  /*
   *Constructor de Tiny.
   * @reqFn Funcion que se ejecutara en cada peticion.
   * @port Puerto de escucha.
   */
  //Tiny(ReqFunction reqFn, unsigned int port);
  Tiny();
  Tiny(ReqFunction reqFn);
  void listen();
  void listen(int port);

private:
  static ReqFunction   reqFunction;

  bool isValidPort();
  void run();
  void init();
  
  unsigned int port;
  
  HttpRequest   *request;
  HttpResponse  *response;
  
  SocketServer *serverSocket;
  std::string ServerName;
};


#endif /* TINY_H */
