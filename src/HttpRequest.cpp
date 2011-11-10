#include "HttpRequest.h"

HttpRequest::HttpRequest(Socket* socket)
{
  this->socket = socket;
}

void HttpRequest::processRequest()
{
  this->setRequest();
  this->setHeaders();
}

void HttpRequest::setHeaders()
{
  std::string line;
  static const std::string authorization   = "Authorization: Basic ";
  static const std::string accept          = "Accept: ";
  static const std::string accept_language = "Accept-Language: ";
  static const std::string accept_encoding = "Accept-Encoding: ";
  static const std::string accept_charset  = "Accept-Charset: ";
  static const std::string user_agent      = "User-Agent: ";

  while(1) {
    line = this->socket->recvLine();

    if (line.empty()) break;

    unsigned int pos_cr_lf = line.find_first_of("\x0a\x0d");
    if (pos_cr_lf == 0) break;

    line = line.substr(0, pos_cr_lf);

    if (line.substr(0, authorization.size()) == authorization) {
      /*req.authentication_given_ = true;
      std::string encoded = line.substr(authorization.size());
      std::string decoded = base64_decode(encoded);

      unsigned int pos_colon = decoded.find(":");

      req.username_ = decoded.substr(0, pos_colon);
      req.password_ = decoded.substr(pos_colon+1 );*/
    }
    else if (line.substr(0, accept.size()) == accept) {
      this->accept = line.substr(accept.size());
    }
    else if (line.substr(0, accept_language.size()) == accept_language) {
      this->acceptLanguage = line.substr(accept_language.size());
    }
    else if (line.substr(0, accept_encoding.size()) == accept_encoding) {
      this->acceptEncoding = line.substr(accept_encoding.size());
    }
    else if (line.substr(0, user_agent.size()) == user_agent) {
      this->userAgent = line.substr(user_agent.size());
    }
    else if (line.substr(0, accept_charset.size()) == accept_charset) {
      this->charset = line.substr(accept_charset.size());
    }
  }
}

/*
 * Obtiene el método de la petición, la ruta solicitada y los paramatros.
 */
void HttpRequest::setRequest()
{
  std::string line = this->socket->recvLine();
  
  if (line.empty()) {
    //return 1;
  }
  
  /*
   * Busca el método de la petición.
   * GET, POST
   */
  if (line.find("GET") == 0) {
    this->method = "GET";
  }
  else if (line.find("POST") == 0) {
    this->method ="POST";
  }

  size_t posStartPath = line.find_first_not_of(" ",3);

  UrlHelper::parseGetRequest(line.substr(posStartPath), this->path, this->params);
}

void HttpRequest::write(std::string response)
{
  this->response += response + '\n';
}

void HttpRequest::end(std::string response)
{
  this->response += response;
  this->end();
}

void HttpRequest::end()
{
  std::stringstream resp_length;
  resp_length << this->response.size();

  this->socket->sendBytes("HTTP/1.1 ");
  this->socket->sendLine("Date: " + Utils::getUTCTime());
  this->socket->sendLine(std::string("Server: Mesero"));
  this->socket->sendLine("Connection: close");
  this->socket->sendLine("Content-Type: text/html; charset=ISO-8859-1");
  this->socket->sendLine("Content-Length: "  + resp_length.str());
  this->socket->sendLine("");
  this->socket->sendLine(this->response);
  this->socket->close();
}
