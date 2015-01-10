#include "packet.h"

void NETWORKING_API_ENTRY Packet_WriteProtocol(Packet *packet, uint32_t protocol){
    /* Rearrange the data into network byte order. */
    protocol = htonl(protocol);
    /* Write the data to the appropriate
    place in the packet buffer. */
    memcpy(
        packet->data + 0x00,//8*0 (0)
        &protocol,
        sizeof(uint32_t)
        );
}

void NETWORKING_API_ENTRY Packet_WriteType(Packet *packet, uint8_t type){
    /* Write the data to the appropriate
    place in the packet buffer. */
    memcpy(
        packet->data + 0x04,//8*4 (32)
        &type,
        sizeof(uint8_t)
        );
}


void NETWORKING_API_ENTRY Packet_WriteNumber(Packet *packet, uint32_t number){
    /* Rearrange the data into network byte order. */
    number = htonl(number);
    /* Write the data to the appropriate
    place in the packet buffer. */
    memcpy(
        packet->data + 0x05,//8*5 (40)
        &number,
        sizeof(uint32_t)
        );
}

void NETWORKING_API_ENTRY Packet_WriteData(Packet *packet, void *data, size_t size){
    /* Write the data to the appropriate
    place in the packet buffer. */
    memcpy(
        packet->data + PACKET_HEADER_SIZE,
        data,
        size <= PACKET_SIZE - PACKET_HEADER_SIZE ? size : PACKET_SIZE - PACKET_HEADER_SIZE
        );
}

uint32_t NETWORKING_API_ENTRY Packet_ReadProtocol(Packet *packet){
    return ntohl(*(uint32_t*)(packet->data + 0x00));
}

uint8_t NETWORKING_API_ENTRY Packet_ReadType(Packet *packet){
    return *(packet->data + 0x04);
}

uint32_t NETWORKING_API_ENTRY Packet_ReadNumber(Packet *packet){
    return ntohl(*(uint32_t*)(packet->data + 0x05));
}

void NETWORKING_API_ENTRY *Packet_ReadData(Packet *packet){
    return (packet->data + PACKET_HEADER_SIZE);
}

int NETWORKING_API_ENTRY Packet_Recv(Packet *packet, int socket_descriptor){
    /* Attempt to received data from the socket.
    Note that this may cause the function to block. */
    int bytes_received = recv(socket_descriptor, (char*)packet, PACKET_SIZE, 0);
    /* Once the data has been received, make sure
    that it is a valid packet. */
    if(bytes_received < PACKET_SIZE || Packet_ReadProtocol(packet) != PACKET_DEFAULT_PROTOCOL){
        /* This packet is either incomplete or
        has an invalid header. Return an error. */
        return -1;
    }
    /* If we have not encountered an error at this stage
    the operation was successful. Return success. */
    //printf("Received a valid packet (success!)\n");
    return 0;
}

int NETWORKING_API_ENTRY Packet_Send(Packet *packet, int file_descriptor){
    /* We trust the host to send out a valid packet.
    Packet validation should be done by the recipient. */
    int bytes_sent = send(file_descriptor, (char*)packet, PACKET_SIZE, 0);
    /* Check that the entire packet has been sent.
    Return failure if appropriate. */
    if(bytes_sent < PACKET_SIZE){
        return -1;
    }
    /* If we have not encountered an error at this stage
    the operation was successful. Return success. */
    //printf("Sent a valid packet (success!)\n");
    return 0;
}

int NETWORKING_API_ENTRY Packet_RecvFrom(Packet *packet, int file_descriptor, AddressInfo *address){
    int bytes_received;
    /* Initialise the address_parameter to the size
    of the sockaddr structure. This conforms to the BSD
    socket API. */
    address->address_size = sizeof(struct sockaddr);
    /* Attempt to receive a packet from the socket descriptor,
    storing address data into the AddressInfo structure. */
    bytes_received = recvfrom(file_descriptor, (char*)packet, PACKET_SIZE, 0,
        &address->address, &address->address_size);
    /* Once the data has been received, make sure
    that it is a valid packet. */
    if(bytes_received < PACKET_SIZE || Packet_ReadProtocol(packet) != PACKET_DEFAULT_PROTOCOL){
        /* This packet is either incomplete or
        has an invalid header. Return an error. */
        return -1;
    }
    /* If we have not encountered an error at this stage
    the operation was successful. Return success. */
    //printf("Received a valid packet (success!)\n");
    return 0;
}

int NETWORKING_API_ENTRY Packet_SendTo(Packet *packet, int socket_descriptor, AddressInfo *address){
    /* This function assumes the AddresInfo struct is correctly initialised
    and performs no check or initiallisation to ensure validity. */
    int bytes_sent = sendto(socket_descriptor, (char*)packet, PACKET_SIZE, 0,
    &address->address, address->address_size);
    /* Check that the entire packet has been sent.
    Return failure if appropriate. */
    if(bytes_sent < PACKET_SIZE){
        return -1;
    }
    /* If we have not encountered an error at this stage
    the operation was successful. Return success. */
    //printf("Sent a valid packet (success!)\n");
    return 0;
}
