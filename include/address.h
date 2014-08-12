#ifndef ADDRESS_H
#define ADDRESS_H

#ifdef __cplusplus
#	include <cstring>
#else
#	include <string.h>
#endif

#ifdef _WIN32
#   include <WinSock2.h>
#   include <ws2tcpip.h>
#else
#   include <sys/socket.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "networking.h"

typedef struct AddressInfo{
	struct sockaddr address;
	socklen_t address_size;
}AddressInfo;

int NETWORKING_API_ENTRY AddressInfo_ResolveHost(AddressInfo *address, char host[], char service[]);
int NETWORKING_API_ENTRY AddressInfo_ResolveService(AddressInfo *address, char service[]);
int NETWORKING_API_ENTRY AddressInfo_IsEqual(AddressInfo *addr1, AddressInfo *addr2);
int NETWORKING_API_ENTRY AddressInfo_ToString(AddressInfo *address, char *string);

#ifdef __cplusplus
}
#endif

#endif /* ADDRESS_H */
