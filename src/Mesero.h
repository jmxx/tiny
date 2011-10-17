#ifndef MESERO_H
#define MESERO_H

#include <iostream>
#include <sstream>

#include "SocketServer.h"

class Mesero
{
public:
  static Mesero* createApp(void);
  
  /*
   * Definimos RequestFn, un puntero a una funcion que recibe como parametro
   * un puntero a un objeto HttpRequest y retorna void.
   */
  //typedef void (*RequestFunction) (/*HttpRequest**/);
  
  /*
   *Constructor de Mesero.
   * @reqFn Funcion que se ejecutara en cada peticion.
   * @port Puerto de escucha.
   */
  //Mesero(RequestFunction reqFn, unsigned int port);
  Mesero();
  int listen();

private:
  //bool isValidPort();
  
  unsigned int port;
  Socket *client;
  
  SocketServer *server;
  std::string ServerName;
};


#endif /* MESERO_H */
