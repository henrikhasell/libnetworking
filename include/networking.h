#ifndef NETWORKING_H
#define NETWORKING_H

#ifdef _WIN32
#   ifdef NETWORKING_API_STATIC
#       define NETWORKING_API_ENTRY
#   else
#       ifdef NETWORKING_API_EXPORTS
#           define NETWORKING_API_ENTRY __declspec(dllexport)
#       else
#           define NETWORKING_API_ENTRY __declspec(dllimport)
#       endif
#   endif
#else
#   define NETWORKING_API_ENTRY
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#   include <WinSock2.h>
#   include <ws2tcpip.h>
#else
#   include <sys/socket.h>
#   include <sys/types.h>
#   include <netdb.h>
#   include <fcntl.h>
#   include <unistd.h>
#endif

#ifdef __cplusplus
#   include <cstdint>
#else
#   include <stdint.h>
#endif

int NETWORKING_API_ENTRY Networking_Initialise();

int NETWORKING_API_ENTRY Networking_Cleanup();

uint32_t NETWORKING_API_ENTRY HTONL(uint32_t data);
uint32_t NETWORKING_API_ENTRY NTOHL(uint32_t data);
uint16_t NETWORKING_API_ENTRY HTONS(uint16_t data);
uint16_t NETWORKING_API_ENTRY NTOHS(uint16_t data);

#ifdef __cplusplus
}
#endif

#endif /* NETWORKING_H */
