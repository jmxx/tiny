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
  /*
   * Constructor por copia.
   */
  Socket(const Socket&);
  Socket(int domain, int type, unsigned int port);
  Socket(int port);
  void Listen();
  void Close();
  
  //int sendLine(std::string);
  //int sendBytes(const std::string&);
  
  //int SendData(std::string data);
  //int SendLine(std::string data);
  
  //std::string RecvData();
  std::string RecvLine();
  
  // Puerto de escucha del Socket.
  unsigned int port;
  // Dominio del Socket: INET o UNIX
  unsigned int domain;
  // Tipo de Socket: TCP o UDP
  unsigned int type;
protected:
  friend class SocketServer;
  friend class SocketSelect;

  Socket(int desc, struct sockaddr& socket_s);
  
  /*
   * Identificador del Socket
   */
  int socketDesc;

private:
  /*
   * Crea Socket tipo INET
   */
  int createInetSocket();
  //int createInetSocketUDP();
  
  /*
   * Crea Socket tipo UNIX
   */
  int createUnixSocket();
  //int createUnixSocketUDP();
  int bindSocket();
};

#endif /* SOCKET_H */
