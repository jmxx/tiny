#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <map>
#include <sstream>

#include "Socket.h"
#include "UrlHelper.h"
#include "Utils.h"
#include "Logger.h"

class HttpRequest
{
public:

  HttpRequest(){}
  HttpRequest(Socket* socket);
  ~HttpRequest();

  void processRequest();
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
  std::string       charset;
  
  std::string       status;
  std::string       response;
  
private:
  std::string       headers;
  std::string       dataReceived;
  void setHeaders();
  void setRequest();
};

#endif /* HTTP_REQUEST_H */
