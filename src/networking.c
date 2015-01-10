#include "networking.h"

#ifdef _WIN32
/* WSAStartup(), WSACleanup() */
#   include <WinSock2.h>
#endif

int NETWORKING_API_ENTRY Networking_Initialise(){
#ifdef _WIN32
    struct WSAData wsa_data;
    /* If on a Windows platform, initialise WinSock
    and ensure initialisation is successfull. */
    if(WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0){
        /* WinSock initialisation failure. */
        return 1;
    }
#endif
    return 0;
}

int NETWORKING_API_ENTRY Networking_Cleanup(){
#ifdef _WIN32
    /* If on a Windows platform, cleanup WinSock
    and ensure cleanup is successfull. */
    if(WSACleanup() != 0){
        /* WinSock cleanup failure. */
        return 1;
    }
#endif
    return 0;
}

uint32_t NETWORKING_API_ENTRY HTONL(uint32_t data){
    return htonl(data);
}
uint32_t NETWORKING_API_ENTRY NTOHL(uint32_t data){
    return ntohl(data);
}
uint16_t NETWORKING_API_ENTRY HTONS(uint16_t data){
    return htons(data);
}
uint16_t NETWORKING_API_ENTRY NTOHS(uint16_t data){
    return ntohs(data);
}
