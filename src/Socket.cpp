#include "Socket.h"

Socket::Socket(const Socket &socket)
{
  this->domain = socket.getDomain();
  this->port = socket.getPort();
  this->type = socket.getType();

}

Socket::Socket(int d, int t, unsigned int p) :
  domain(d), type(t), port (p)
{
  init();
}

Socket::Socket(int descriptor, struct sockaddr &socket_s) :
  socketDesc(descriptor)
{
  this->port = ::ntohs(((struct sockaddr_in*)&socket_s)->sin_port);
  this->domain = (&socket_s)->sa_family;
}

void Socket::create()
{
  this->socketDesc = ::socket(domain, type, 0);
  if (this->bindSocket() == -1) {
    std::cout << "Ha ocurrido un error asociando el Socket." << std::endl;
  }
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
    std::cout << "+++Ha ocurrido un error asociando el Socket." << this->socketDesc << std::endl;
    this->close();
    return -1;
  }
  return 1;
}

void Socket::listen()
{
  if (::listen(this->socketDesc, 1) == -1) {
    std::cout << "¡Oops, ha ocurrido un error al escuchar!" <<std::endl;
    this->close();
  }
}

void Socket::close()
{
  ::close(this->socketDesc);
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

std::string Socket::RecvData(int bufferSize)
{
  std::string ret;
  char buf[bufferSize];
  while (1) {
    
    /*u_long arg = 0;
    if (ioctlsocket(s_, FIONREAD, &arg) != 0)
      break;

    if (arg == 0)
      break;

    if (arg > 1024) arg = 1024;*/
    int rv = read(this->socketDesc, buf, bufferSize/*arg*/);
    if (rv <= 0) break;
    std::string t;

    t.assign (buf, rv);
    ret += t;
  }
  return ret;
}

int Socket::SendBytes(const std::string& s) {
  //std::cout << "Enviando: " << s << std::endl;
  //write(this->socketDesc, s.c_str(), s.length());
  std::string str(s);
  return this->SendLine(str);
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


int Socket::getPort() const
{
  return this->port;
}
  
int Socket::getDomain() const
{
  return this->domain;
}
  
int Socket::getType() const
{
  return this->type;
}
