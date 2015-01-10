#include "address.h"

#ifdef __cplusplus
#       include <cstring> /* memset */
#else
#       include <string.h> /* memset */
#endif

#ifdef _WIN32
#   include <ws2tcpip.h> /* getaddrinfo */
#else
#   include <netdb.h> /* getaddrinfo */
#endif

int NETWORKING_API_ENTRY AddressInfo_ResolveHost(AddressInfo *address, char host[], char service[]){
    /* These structures are used by the function to
    pass/receive socket information to/from getaddrinfo() */
    struct addrinfo hints, *list;
    /* The hints struct is being populated with
    guidelines for use by getaddrinfo() */
    memset(&hints, '\0', sizeof(struct addrinfo));
    hints.ai_protocol = IPPROTO_UDP;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_family = AF_INET;
    /* getaddrinfo() will now attempt to resolve the host/service
    to a computer readable IP address. This returns a linked list
    which must be manually feed from memory. */
    if (getaddrinfo(host, service, &hints, &list) != 0){
        /* An error occured during getaddrinfo().
        The method must stop and return an error. */
        return -1;
    }
    /* getaddrinfo() was successfull. Assign the first IP address
    to the AddressInfo structure and free the list from memory. */
    address->address = *list->ai_addr;
    address->address_size = list->ai_addrlen;
    freeaddrinfo(list);
    return 0;
}

int NETWORKING_API_ENTRY AddressInfo_ResolveService(AddressInfo *address, char service[]){
    /* These structures are used by the function to
    pass/receive socket information to/from getaddrinfo() */
    struct addrinfo hints, *list;
    /* The hints struct is being populated with
    guidelines for use by getaddrinfo() */
    memset(&hints, '\0', sizeof(struct addrinfo));
    hints.ai_protocol = IPPROTO_UDP;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_PASSIVE;
    /* getaddrinfo() will now attempt to resolve the host/service
    to a computer readable IP address. This returns a linked list
    which must be manually feed from memory. */
    if (getaddrinfo(NULL, service, &hints, &list) != 0){
        /* An error occured during getaddrinfo().
        The method must stop and return an error. */
        return -1;
    }
    /* getaddrinfo() was successfull. Assign the first IP address
    to the AddressInfo structure and free the list from memory. */
    address->address = *list->ai_addr;
    address->address_size = list->ai_addrlen;
    freeaddrinfo(list);
    return 0;
}

int NETWORKING_API_ENTRY AddressInfo_IsEqual(AddressInfo *addr1, AddressInfo *addr2){
    return addr1->address_size == addr2->address_size && !memcmp(addr1, addr2, addr1->address_size);
}

int NETWORKING_API_ENTRY AddressInfo_ToString(AddressInfo *address, char *string){
    return -1;
}
