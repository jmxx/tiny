#include "Socket.h"

class SocketServer : public Socket {
public:
   
  SocketServer(){}
  /**
   * Constructor de SocketServer
   */
  SocketServer(int port);
  Socket* Accept();
  std::string RecvHeaders();
  
  int client;

private:

};
