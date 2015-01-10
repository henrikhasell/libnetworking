#ifndef SOCKET_H
#define SOCKET_H

#include "networking.h" /* entry point */
#include "address.h" /* AddressInfo */
#include "packet.h" /* Packet */

/* This struct contains
all the necessary data
to represent a socket. */
typedef struct Socket{
    int file_descriptor;
}Socket;

#ifdef __cplusplus
extern "C" {
#endif
/* This function attmepts to initialise a socket. All sockets must
have this done to them before they are suitable to use.
Returns 0 on success and -1 on failure. */
int NETWORKING_API_ENTRY Socket_Create(Socket *socket_struct);
/* This function destroys an initialised socket. All sockets should
have this done to them when they are no longer required.
Returns 0 on success and -1 on failure. */
int NETWORKING_API_ENTRY Socket_Destroy(Socket *socket_struct);
/* This pair of functions is used to send and receive data.
The data is sent/received from the address the socket is
bound/connected to. See below for more information.
Returns 0 on success and -1 on failure. */
int NETWORKING_API_ENTRY Socket_Send(Socket *socket, Packet *packet);
int NETWORKING_API_ENTRY Socket_Recv(Socket *socket, Packet *packet);
/* This pair of functions is used to send/recieve data
to/from a given address. It returns 0 on success and
-1 on failure. */
int NETWORKING_API_ENTRY Socket_SendTo(Socket *socket, Packet *packet, AddressInfo *address);
int NETWORKING_API_ENTRY Socket_RecvFrom(Socket *socket, Packet *packet, AddressInfo *address);
/* This pair of functions is used to set an implicit address
for sockets to send/receive from. Servers needing to receive
data from a local port should use "bind". Clients should
use "connect".
Returns 0 on success and -1 on failure. */
int NETWORKING_API_ENTRY Socket_Connect(Socket *socket, AddressInfo *address);
int NETWORKING_API_ENTRY Socket_Bind(Socket *socket, AddressInfo *address);
#ifdef __cplusplus
}
#endif

#endif /* SOCKET_H */
