#ifndef SOCKET_H
#define SOCKET_H

#include <unistd.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h> 

#include "SocketInclude.h"

class Socket
{
public:
  /**
   * Constructor Socket
   * @param doamin  Dominio del Socket [AF_INET, AF_UNIX]
   * @param type    Tipo del Socket [SOCK_STREAM, SOCK_DGRAM]
   * @param port    Puerto de escucha del Socket
   */
  Socket(int domain, int type, port_t port);
  
  /**
   * Destructor de Socket
   */
  virtual ~Socket() {;}
  
  /**
   * Pone a escuchar al Socket
   */
  void listen();
  
  /**
   * Cierra el Socket
   */
  void close();
  
  
  /**
   * Hace al Socket no-bloqueante
   */
  int setNonBlocking();
  
  /**
   * Envia una cadena tipo String
   * @param data  Cadena que será enviada
   * @return      Retorna -1 si hubo algún error al enviar
   */
  int sendLine(std::string data);
  
  /**
   * 
   */
  int sendBytes(const std::string& data);
  
  /**
   * Reciba una cadena de caracteres hasta encontrar un salto de línea [\n]
   * @return    String
   */
  std::string recvLine();
  
  /**
   * Recibe tantos caracteres especificados por bufferSize
   * @param bufferSize  Tamaño de buffer
   */
  std::string recvData(int bufferSize);
  
  /**
   * Obtiene el descriptor del Socket
   */
  SOCKET_t getDescriptor() const;
  
  /**
   * Obtiene el puerto de escucha del Socket
   * @return  Puerto asociado al socket
   */
  port_t getPort() const;
  
  /**
   * Obtiene el dominio del Socket
   * @return  Dominio del socket
   */
  int getDomain() const;
  
  /**
   * Obtiene el tipo del Socket
   * @return  Tipo del socket
   */
  int getType() const;
  
  /**
   *
   */
  SOCKET_t createSocket(int domain, int type);
protected:
  friend class SocketServer;
  friend class SocketSelect;
  
  Socket() {}
  /**
   * Constructor por copia.
   * @param socket  Socket base.
   */
  Socket(const Socket&);
  
  /**
   * Constructor de Socket a partir un descriptor y una estructura sockaddr
   * @param desc      Descriptor del Socket
   * @param socket_s  Estructura sockaddr
   */
  Socket(int desc, struct sockaddr& socket_s);
  
  /*
   * Descriptor del Socket
   */
  SOCKET_t socketDesc;

private:
  /**
   * Inicializa el Socket
   */
  void create();
  
  /**
   * Avisa al SO que se ha abierto un socket y se asocie dicho socket.
   * @return    Retorna -1 si hubo algún error.
   */
  int bindSocket();

  /// Puerto de escucha del Socket.
  port_t port;
  /// Dominio del Socket [AF_INET, AF_UNIX]
  unsigned int domain;
  /// Tipo de Socket [SOCK_STREAM, SOCK_DGRAM]
  unsigned int type;
};

#endif /* SOCKET_H */
