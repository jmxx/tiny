#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <map>
#include <sstream>

#include "SocketServer.h"
#include "Utils.h"

class HttpRequest
{
public:

  HttpRequest(Socket* socket);

  std::string data();
  void write(std::string response);
  void end(std::string response);
  void end();

  Socket*           socket;
  std::string       method;
  std::string       path;
  std::map<std::string, std::string>    params;
  std::string       accept;
  std::string       acceptLanguage;
  std::string       acceptEncoding;
  std::string       userAgent;
  
  std::string       status;
  std::string       response;
  
private:
  std::string       headers;
  std::string       dataReceived;
  void setHeaders();
};

#endif /* HTTP_REQUEST_H */