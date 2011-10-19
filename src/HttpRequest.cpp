#include "HttpRequest.h"

HttpRequest::HttpRequest(Socket* socket)
{
  this->socket = socket;
}

void HttpRequest::setHeaders()
{
  //headers += "Date: " + Utils::getUTCTime();
}

std::string HttpRequest::data()
{
  dataReceived = this->socket->RecvLine();
  return dataReceived;
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

  this->socket->SendBytes("HTTP/1.1 ");
  this->socket->SendLine("Date: " + Utils::getUTCTime());
  this->socket->SendLine(std::string("Server: Mesero"));
  this->socket->SendLine("Connection: close");
  this->socket->SendLine("Content-Type: text/html; charset=ISO-8859-1");
  this->socket->SendLine("Content-Length: "  + resp_length.str());
  this->socket->SendLine("");
  this->socket->SendLine(this->response);
  this->socket->Close();
}
