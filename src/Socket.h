#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <string>

class Socket
{
public:
  Socket(const Socket&);
  Socket(int domain, int type, unsigned int port);
  void listen();
  void close();
  
  int sendLine(std::string);
  int sendBytes(const std::string&);
  
  unsigned int port;
  unsigned int domain;
  unsigned int type;

private:
  int createInetSocket();
  int createUnixSocket();
  int bindSocket();
  
  int descriptor;
}

#endif /* SOCKET_H */
