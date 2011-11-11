#include "EpollHandler.h"

struct epoll_event EpollHandler::events[MAX_POLL_SIZE], EpollHandler::ev;

EpollHandler::EpollHandler()
{
  init();
}

EpollHandler::EpollHandler(Tiny *_server): tiny(_server)
{
  init();
}

void EpollHandler::init()
{
  struct rlimit rt;
  
  // http://www.delorie.com/gnu/docs/glibc/libc_448.html
  rt.rlim_max = rt.rlim_cur = MAX_POLL_SIZE; 
  if (setrlimit(RLIMIT_NOFILE, &rt) == -1) { 
    ERROR("rlimit");
    ::exit(1); 
  } else {
    LOG("System resources successfully!");
  }
  
  SOCKET_t fd_server = tiny->socketServer->getDescriptor();
  
  /**
   * Crea el Loop de eventos (epoll)
   */
  epoll_fd = epoll_create(MAX_POLL_SIZE);
  if (epoll_fd == -1) {
    ERROR("epoll_create");
  }
  
  /* Agregamos el Socket del servidor al loop de eventos. */
  ev.events = EPOLLIN | EPOLLERR | EPOLLHUP | EPOLLET;
  ev.data.fd = fd_server;
  if (epoll_ctl (epoll_fd, EPOLL_CTL_ADD, fd_server, &ev) == -1) { 
    ERROR("epoll_ctl");
  }
}

void EpollHandler::loop()
{
  int maxEvents = 1;
  int connections = 0;
  while(1) {
    /**
     * Esperendo por un evento
     */ 
    f_descriptors = epoll_wait(epoll_fd, events, maxEvents, -1);
    if (f_descriptors < 0) {
      ERROR("Error: epoll_wait");
      break;
    } else {
      INFO("MAX EVENTS " << maxEvents << " CONN: " << ++connections);
      for (int i = 0; i < f_descriptors; i++) {
        /**
         * Evento lanzado por el socket servidor.
         */
        if (events[i].data.fd == tiny->Server()->getDescriptor()) {
          /**************************************
           *Aqui es donde acepta a nuevos clientes.
           *************************************/
          Socket *cliente = tiny->Server()->Accept();
          /**
           * Agregamos el Socket del Cliente al mapa de sockets.
           */
          this->add(cliente);
          
          /**
           * Agregamos el descriptor del Socket al loop de eventos (epoll)
           */
          ev.events = EPOLLIN | EPOLLET; 
          ev.data.fd = cliente->getDescriptor(); 
          if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, /*Descriptor Cliente*/ cliente->getDescriptor(), &ev) <0) { 
            //fprintf (stderr, "the socket '%d' added epoll failed!%s \n", cliente, strerror (errno));
            ERROR("Fallo al agregar el socket cliente " << cliente->getDescriptor() << " al loop de eventos.");
            //return -1;
            return;
          } 
          maxEvents++; 
        } 
        /**
         * Eventos lanzado por los clientes
         */
        else {
          int ret;
          sockets_map::iterator itmp = addedSockets.find(events[i].data.fd);
          /**********************************
           * Aqui manejamos la respuesta a del servidor
           //ret = handle_message(events[n].data.fd);
           *********************************/
           
          //ret = handle_message(events[i].data.fd); 
          if (itmp != addedSockets.end()) {
            Socket *p = itmp->second;
            tiny->request = HttpRequest(p);
            //tiny->request.processRequest();
            ret = tiny->respond();
            if (ret < 1 && errno != 11) {
              DEBUG("RET: " << ret);
              epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, &ev); 
              maxEvents--; 
            } 
          } else {
            ERROR("GetSocket/handler/2" << "Did not find expected socket using file descriptor");
          }
        }
      }
    }
  }
  tiny->Server()->close();
  ::exit(EXIT_SUCCESS);
}

void EpollHandler::add(Socket *socket)
{
  //DEBUG("MAP SIZE " << (int)addedSockets.size());
  if (socket->getDescriptor() == INVALID_SOCKET) {
    ERROR("Error, Descriptor invalido.");
    return;
  }
  if (addedSockets.find(socket->getDescriptor()) != addedSockets.end())
  {
    //NOTICE("Attempt to add socket already in add queue");
    //m_delete.push_back(p);
    return;
  }
  addedSockets[socket->getDescriptor()] = socket;
  
  //server = socket;
}
