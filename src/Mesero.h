#ifndef MESERO_H
#define MESERO_H

#include <iostream>

#include "HttpRequest.h"

#define DEFAULT_PORT  8005



class Mesero
{
public:
  /*
   * Definimos RequestFn, un puntero a una funcion que recibe como parametro
   * un puntero a un objeto HttpRequest y retorna void.
   */
  typedef void (*ReqFunction) (HttpRequest* req);
  
  /*
   * Método estático que retorna un objecto Mesero.
   */
  static Mesero* createApp(ReqFunction reqFn);
  
  /*
   *Constructor de Mesero.
   * @reqFn Funcion que se ejecutara en cada peticion.
   * @port Puerto de escucha.
   */
  //Mesero(ReqFunction reqFn, unsigned int port);
  Mesero();
  Mesero(ReqFunction reqFn);
  void listen();
  void listen(int port);

private:
  static ReqFunction   reqFunction;

  bool isValidPort();
  void run();
  void init();
  
  unsigned int port;
  
  HttpRequest   *request;
  
  SocketServer *serverSocket;
  std::string ServerName;
};


#endif /* MESERO_H */
