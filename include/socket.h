#ifndef SOCKET_H
#define SOCKET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "networking.h"
#include "packet.h"

typedef struct Socket{
	int file_descriptor;
}Socket;

int NETWORKING_API_ENTRY Socket_Create(Socket *socket_struct);
int NETWORKING_API_ENTRY Socket_Destroy(Socket *socket_struct);

int NETWORKING_API_ENTRY Socket_Send(Socket *socket, Packet *packet);
int NETWORKING_API_ENTRY Socket_Recv(Socket *socket, Packet *packet);

int NETWORKING_API_ENTRY Socket_SendTo(Socket *socket, Packet *packet, AddressInfo *address);
int NETWORKING_API_ENTRY Socket_RecvFrom(Socket *socket, Packet *packet, AddressInfo *address);

int NETWORKING_API_ENTRY Socket_Connect(Socket *socket, AddressInfo *address);
int NETWORKING_API_ENTRY Socket_Bind(Socket *socket, AddressInfo *address);

#ifdef __cplusplus
}
#endif

#endif /* SOCKET_H */
