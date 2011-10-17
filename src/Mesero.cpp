#include "Mesero.h"

Mesero* Mesero::createApp(void)
{
  return new Mesero();
}

Mesero::Mesero()
{
  std::cout << "Constructor Mesero" << std::endl;
  this->ServerName = "Mesero";
  this->port = 8005;
  this->server = new SocketServer(this->port);
}

/*Mesero::Mesero(RequestFunction reqFn, unsigned int port)
{

}*/

int Mesero::listen()
{
  time_t ltime;
  time(&ltime);
  tm* gmt= gmtime(&ltime);
  char* asctime_remove_nl = asctime(gmt);
  asctime_remove_nl[24] = 0;
  std::string line;
  std::stringstream str_str;
  
  std::cout << "Listen Mesero at " << this->port << std::endl;
  this->client = this->server->Accept();
  if (this->client == NULL) {
    std::cout << "No se puede abrir socket de cliente\n";
    //exit(-1);
  }
  line = this->client->RecvLine();
  str_str << line.size();
  std::cout<< "Recibiendo: " << line << std::endl;
  this->client->SendBytes("HTTP/1.1 ");

  /*if (! req.auth_realm_.empty() ) {
    this->client->SendLine("401 Unauthorized");
    this->client->SendBytes("WWW-Authenticate: Basic Realm=\"");
    this->client->SendBytes(req.auth_realm_);
    this->client->SendLine("\"");
  }
  else {
    this->client->SendLine(req.status_);
  }*/
  this->client->SendLine(std::string("Date: ") + asctime_remove_nl + " GMT");
  this->client->SendLine(std::string("Server: ") + this->ServerName);
  this->client->SendLine("Connection: close");
  this->client->SendLine("Content-Type: text/html; charset=ISO-8859-1");
  this->client->SendLine("Content-Length: "  + str_str.str());
  this->client->SendLine("");
  this->client->SendLine(line);

  this->client->Close();
  
  
  std::cout << "Enviado: " << std::endl;
}
