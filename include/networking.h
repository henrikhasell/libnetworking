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

/* Include the appropriate headers for
both C and C++
Standard types: uint8_t, uint32_t */
#ifdef __cplusplus
#   include <cstdint>
#else
#   include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
/* This function initialises the networking library.
It must be called before any other function in the
library is used. */
int NETWORKING_API_ENTRY Networking_Initialise();
/* This function frees resources used by the library.
It should be called when the library is no longer
required by the application. */
int NETWORKING_API_ENTRY Networking_Cleanup();
/* These functions are used to rearrange multi-byte
data from host to network byte order and back.
HTONL(aabbccdd) = ddccbbaa */
uint32_t NETWORKING_API_ENTRY HTONL(uint32_t data);
uint32_t NETWORKING_API_ENTRY NTOHL(uint32_t data);
uint16_t NETWORKING_API_ENTRY HTONS(uint16_t data);
uint16_t NETWORKING_API_ENTRY NTOHS(uint16_t data);
#ifdef __cplusplus
}
#endif

#endif /* NETWORKING_H */
