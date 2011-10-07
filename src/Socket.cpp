#include "Socket.h"

Socket::Socket(int domain, int type, unsigned int port)
{
  this->domain = domain;
  this->type = type;
  this->port = port;
}

void listen()
{
  if (listen (Descriptor, 1) == -1) {
    close (Descriptor);
    return -1;
  }
}

int Socket::createInetSocket()
{
  this->descriptor =  socket(AF_INET, SOCK_STREAM, 0);
  return this->descriptor;
}

int Socket::createUnixSocket()
{
  this->descriptor =  socket(AF_UNIX, SOCK_STREAM, 0);
  return this->descriptor;
}

int Socket::bindSocket()
{
  struct sockaddr_in socketAddres;
  struct sockaddr client;
  socklen_t clientLength;
  
  socketAddres.sin_family = this->domain;
  socketAddres.sin_port = this->port;
  socketAddres.sin_addr.s_addr =INADDR_ANY;
  
  if (bind(this->descriptor, (struct sockaddr *)&socketAddres, sizeof(socketAddres)) == -1) {
    this->close();
    return -1;
  }
}

void Socket::close()
{
  close(this->descriptor);
}
