#include "Socket.h"

Socket::Socket(const Socket &socket)
{
  this->domain = socket.domain;
  this->port = socket.port;
  this->type = socket.type;
}

Socket::Socket(int port)
{
  this->port = port;
  this->createInetSocket();
}

Socket::Socket(int domain, int type, unsigned int port)
{
  this->domain = domain;
  this->type = type;
  this->port = port;
}

Socket::Socket(int descriptor, struct sockaddr &socket_s)
{
  this->socketDesc = descriptor;
  this->port = ntohs(((struct sockaddr_in*)&socket_s)->sin_port);
  this->domain = (&socket_s)->sa_family;
}

void Socket::Listen()
{
  if (::listen(this->socketDesc, 1) == -1) {
    std::cout << "¡Oops, ha ocurrido un error al escuchar!" <<std::endl;
    this->Close();
  }
}

int Socket::createInetSocket()
{
  this->socketDesc = socket(AF_INET, SOCK_STREAM, 0);
  bindSocket();
  return this->socketDesc;
}

int Socket::createUnixSocket()
{
  this->socketDesc =  socket(AF_UNIX, SOCK_STREAM, 0);
  bindSocket();
  return this->socketDesc;
}

int Socket::bindSocket()
{
  struct sockaddr_in socketAddres;
  //struct sockaddr client;
  //socklen_t clientLength;
  
  socketAddres.sin_family = this->domain;
  socketAddres.sin_port = htons(this->port);
  socketAddres.sin_addr.s_addr = INADDR_ANY;
  
  if (bind(this->socketDesc, (struct sockaddr *)&socketAddres, sizeof(socketAddres)) == -1) {
    this->Close();
    return -1;
  }
}

void Socket::Close()
{
  close(this->socketDesc);
}

std::string Socket::RecvLine() {
  std::string line;
  while (1) {
    char r;

    switch(read(this->socketDesc, &r, 1)) {
      case 0: // not connected anymore;
              // ... but last line sent
              // might not end in \n,
              // so return line anyway.
        return line;
      case -1:
        return "";
//      if (errno == EAGAIN) {
//        return line;
//      } else {
//      // not connected anymore
//      return "";
//      }
    }
    line += r;
    if (r == '\n')  return line;
  }
}

std::string Socket::RecvHeaders()
{
  std::string line;
  std::string headers;
  do {
    line = this->RecvLine();
    headers += line;
  } while (line != "\r\n");
  return headers;
}

std::string Socket::RecvData()
{
  std::string ret;
  char buf[200];
  while (1) {
    
    /*u_long arg = 0;
    if (ioctlsocket(s_, FIONREAD, &arg) != 0)
      break;

    if (arg == 0)
      break;

    if (arg > 1024) arg = 1024;*/
    int rv = read(this->socketDesc, buf, 200/*arg*/);
    if (rv <= 0) break;
    std::string t;

    t.assign (buf, rv);
    ret += t;
  }
  return ret;
}

void Socket::SendBytes(const std::string& s) {
  //std::cout << "Enviando: " << s << std::endl;
  //write(this->socketDesc, s.c_str(), s.length());
  std::string str(s);
  this->SendLine(str);
}

int Socket::SendLine(std::string str)
{
  str += '\n';
  //write(this->socketDesc, str.c_str(), str.length());
  
  char* data = (char*)str.c_str();
  int length = str.length();
  int written = 0;
  int aux = 0;
  
  if ((this->socketDesc == -1) || (data == NULL) || (length < 1) ) {
    return -1;
  }
  
  while (written < length)
  {
    aux = write(this->socketDesc, data + written, length - written);
    if (aux > 0)
    {
      /*
      * Si hemos conseguido escribir caracteres, se actualiza la
      * variable written
      */
      written = written + aux;
    }
    else
    {
      /*
      * Si se ha cerrado el socket, devolvemos el numero de caracteres
      * leidos.
      * Si ha habido error, devolvemos -1
      */
      if (aux == 0)
        return written;
      else
        return -1;
    }
  }

  /*
  * Devolvemos el total de caracteres leidos
  */
  return written;
}
