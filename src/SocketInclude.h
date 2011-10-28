#ifndef SOCKETS_INCLUDE_H
#define SOCKETS_INCLUDE_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

/**
 * Tipo de dato definido para socket
 */
typedef   int               socket_t
/**
 * Tipo de dato definido para puerto
 */
typedef   unsigned short    port_t


#define   INVALID_SOCKET    -1

#endif /* SOCKETS_INCLUDE_H */
