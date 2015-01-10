#include "socket.h"

#ifndef _WIN32
#   include <sys/socket.h>
#   include <netinet/in.h>
#   include <fcntl.h>
#endif

int NETWORKING_API_ENTRY Socket_Create(Socket *socket_struct){
#ifdef _WIN32
    unsigned long non_blocking = 1;
#endif
    socket_struct->file_descriptor = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socket_struct->file_descriptor == -1){
        return -1;
    }
#ifdef _WIN32
    if (ioctlsocket(socket_struct->file_descriptor, FIONBIO, &non_blocking) == -1){
        Socket_Destroy(socket_struct);
        return -1;
    }
#else
    if (fcntl(socket_struct->file_descriptor, F_SETFL, O_NONBLOCK) == -1){
        Socket_Destroy(socket_struct);
        return -1;
    }
#endif
    return 0;
}

int NETWORKING_API_ENTRY Socket_Destroy(Socket *socket_struct){
#ifdef _WIN32
    return closesocket(socket_struct->file_descriptor);
#else
    return close(socket_struct->file_descriptor);
#endif
}

int NETWORKING_API_ENTRY Socket_Send(Socket *socket, Packet *packet){
    if(Packet_Send(packet, socket->file_descriptor) == 0){
        return 0;
    }
    return -1;
}

int NETWORKING_API_ENTRY Socket_Recv(Socket *socket, Packet *packet){
    if(Packet_Recv(packet, socket->file_descriptor) == 0){
        return 0;
    }
    return -1;
}

int NETWORKING_API_ENTRY Socket_SendTo(Socket *socket, Packet *packet, AddressInfo *address){
    if(Packet_SendTo(packet, socket->file_descriptor, address) == 0){
        return 0;
    }
    return -1;
}

int NETWORKING_API_ENTRY Socket_RecvFrom(Socket *socket, Packet *packet, AddressInfo *address){
    if(Packet_RecvFrom(packet, socket->file_descriptor, address) == 0){
        return 0;
    }
    return -1;
}

int NETWORKING_API_ENTRY Socket_Connect(Socket *socket, AddressInfo *address){
    if (connect(socket->file_descriptor, &address->address, address->address_size) == -1){
        return -1;
    }
    return 0;
}

int NETWORKING_API_ENTRY Socket_Bind(Socket *socket, AddressInfo *address){
    if (bind(socket->file_descriptor, &address->address, address->address_size) == -1){
        return -1;
    }
    return 0;
}
