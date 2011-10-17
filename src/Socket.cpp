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
  std::cout << "Created Socket at " << this->port <<std::endl;
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
  std::cout << "Ready to listen at " << this->port <<std::endl;
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
  std::cout << "Binding Socket: yes!" << std::endl;
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

/*int Socket::RecvData(std::string str)
{
  char* data = (char*)str.c_str();
  int length = str.length();
  int well_read = 0;
  int aux = 0;

  if ((this->socketDesc == -1) || (data == NULL) || (length < 1) ) {
    return -1;
  }
  
  while (well_read < length) {
    aux = read(this->socketDesc, data + well_read, length - well_read);
    if (aux > 0) {
      well_read = well_read + aux;
    } else {
      if (aux == 0) {
        return well_read;
      } else if (aux < 0) {
        /*
         * En caso de error, la variable errno nos indica el tipo
         * de error. 
         * El error EINTR se produce si ha habido alguna
         * interrupcion del sistema antes de leer ningun dato. No
         * es un error realmente.
         * El error EGAIN significa que el socket no esta disponible
         * de momento, que lo intentemos dentro de un rato.
         * Ambos errores se tratan con una espera de 100 microsegundos
         * y se vuelve a intentar.
         * El resto de los posibles errores provocan que salgamos de 
         * la funcion con error.
         
        switch (errno) {
          case EINTR:
          case EAGAIN:
            usleep (100);
            break;
          default:
            return -1;
        }
      }
    }
  }
  return well_read;
}*/

void Socket::SendBytes(const std::string& s) {
  std::cout << "Enviando: " << s << std::endl;
  write(this->socketDesc, s.c_str(), s.length());
}

void Socket::SendLine(std::string str)
{
  std::cout << "Enviando: " << str << std::endl;
  str += '\n';
  write(this->socketDesc, str.c_str(), str.length());
  /*
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
    std::cout << "Escrito " << aux << std::endl;
    if (aux > 0)
    {
      /*
      * Si hemos conseguido escribir caracteres, se actualiza la
      * variable written
      
      written = written + aux;
    }
    else
    {
      /*
      * Si se ha cerrado el socket, devolvemos el numero de caracteres
      * leidos.
      * Si ha habido error, devolvemos -1
      
      if (aux == 0)
        return written;
      else
        return -1;
    }
  }

  /*
  * Devolvemos el total de caracteres leidos
  */
  //return written;
}
