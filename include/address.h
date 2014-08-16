#ifndef ADDRESS_H
#define ADDRESS_H

#ifdef _WIN32
#   include <WinSock2.h> /* sockaddr */
#else
#   include <sys/socket.h> /* sockaddr */
#endif

#include "networking.h" /* entry point */

/* This struct contains all the necessary
data to represent an IP address. */
typedef struct AddressInfo{
	struct sockaddr address;
	socklen_t address_size;
}AddressInfo;

#ifdef __cplusplus
extern "C" {
#endif
/* This function resolves a human readable addresses (host:service)
into a computer readable IP address. If successful it returns 0,
if unsuccessful it returns -1. */
int NETWORKING_API_ENTRY AddressInfo_ResolveHost(AddressInfo *address, char host[], char service[]);
/* This function resolves a human readable service written as a port
number or protocol (for example: HTTP, SSH, etc). The resulting address
can be used to connect to the local machine. If successful it
returns 0, if unsuccessful it returns -1. */
int NETWORKING_API_ENTRY AddressInfo_ResolveService(AddressInfo *address, char service[]);
/* This function returns a non-zero if the two provided AddressInfo structures
contain the same address. If the addresses do not match it returns 0. */
int NETWORKING_API_ENTRY AddressInfo_IsEqual(AddressInfo *addr1, AddressInfo *addr2);
/* This function allways returns -1 */
int NETWORKING_API_ENTRY AddressInfo_ToString(AddressInfo *address, char *string);
#ifdef __cplusplus
}
#endif

#endif /* ADDRESS_H */
