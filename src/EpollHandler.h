#ifndef EPOLLHANDLER_H
#define EPOLLHANDLER_H

#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <openssl/ssl.h> 
#include <openssl/err.h> 
#include <fcntl.h> 
#include <sys/epoll.h> 
#include <sys/time.h> 
#include <sys/resource.h>
#include <map>
#include <string>

#include "SocketInclude.h"
#include "Tiny.h"
#include "Logger.h"

class Tiny;

class EpollHandler
{
public:
  /**
   * Constructor
   */
  EpollHandler(Tiny *tiny);
  EpollHandler();
  
  /**
   * Destructor
   */
  ~EpollHandler();
  
  /**
   * Agrega una nuevo socket al mapa de Sockets
   */
  void add(Socket *socket);
  void loop();
  
protected:
  typedef std::map<SOCKET_t, Socket *> sockets_map;

  void remove(Socket *);

  void init();
private:

  int handle_message (int new_fd);
  static const int MAX_POLL_SIZE = 10;
  
  /* Descriptor del epoll */
  int epoll_fd;
  
  /* Descriptores de los clientes conectados */
  int f_descriptors;
  static struct epoll_event events[MAX_POLL_SIZE], ev;
  //struct sigaction act;
  
  sockets_map activeSockets;
  sockets_map addedSockets;
  
  Tiny *tiny;
};

#endif /* EPOLLHANDLER_H */
