#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <string>

#include <iostream>

class Socket
{
public:
  /**
   * Crea un Socket TCP
   * @param port  Puerto de escucha del Socket TCP
   * @return      Socket tipo SOCK_STREAM
   */
  static Socket CreateTCPSocket(int port);
  
  /**
   * Crea un Socket UDP
   * @param port  Puerto de escucha del Socket
   * @return      Socket tipo SOCK_DGRAM
   */
  static Socket CreateUDPSocket(int port);
  
  /**
   * Constructor por copia.
   * @param socket  Socket base.
   */
  Socket(const Socket&);
  
  /**
   * Constructor Socket
   * @param doamin  Dominio del Socket [AF_INET, AF_UNIX]
   * @param type    Tipo del Socket [SOCK_STREAM, SOCK_DGRAM]
   * @param port    Puerto de escucha del Socket
   */
  Socket(int domain, int type, unsigned int port);
  
  /**
   * Pone a escuchar al Socket
   */
  void listen();
  
  /**
   * Cierra el Socket
   */
  void close();
  
  /**
   * Envia una cadena tipo String
   * @param data  Cadena que será enviada
   * @return      Retorna -1 si hubo algún error al enviar
   */
  int SendLine(std::string data);
  
  /**
   * 
   */
  int SendBytes(const std::string& data);
  
  /**
   * Reciba una cadena de caracteres hasta encontrar un salto de línea [\n]
   * @return    String
   */
  std::string RecvLine();
  
  /**
   * Recibe tantos caracteres especificados por bufferSize
   * @param bufferSize  Tamaño de buffer
   */
  std::string RecvData(int bufferSize);
  
  /**
   * Obtiene el puerto de escucha del Socket
   * @return  Puerto asociado al socket
   */
  int getPort() const;
  
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
  
protected:
  friend class SocketServer;
  friend class SocketSelect;

  /**
   * Constructor de Socket a partir un descriptor y una estructura sockaddr
   * @param desc      Descriptor del Socket
   * @param socket_s  Estructura sockaddr
   */
  Socket(int desc, struct sockaddr& socket_s);
  
  /*
   * Identificador del Socket
   */
  int socketDesc;

private:
  /**
   * Inicializa el Socket
   */
  void init();
  
  /**
   * Avisa al SO que se ha abierto un socket y se asocie dicho socket.
   * @return    Retorna -1 si hubo algún error.
   */
  int bindSocket();

  /// Puerto de escucha del Socket.
  unsigned int port;
  /// Dominio del Socket [AF_INET, AF_UNIX]
  unsigned int domain;
  /// Tipo de Socket [SOCK_STREAM, SOCK_DGRAM]
  unsigned int type;
};

#endif /* SOCKET_H */
