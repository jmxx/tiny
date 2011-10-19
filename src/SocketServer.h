#include "Socket.h"

class SocketServer : public Socket {
public:
  SocketServer(int port);
  Socket* Accept();
  std::string RecvHeaders();
  
  int client;
};
