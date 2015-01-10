#ifndef PACKET_H
#define PACKET_H

#ifdef __cplusplus
#   include <cstdint> /* uint8_t, unt32_t */
#   include <cstring> /* size_t */
#else
#   include <stdint.h> /* uint8_t, uint32_t */
#   include <string.h> /* size_t */
#endif

#include "networking.h" /* entry point */
#include "address.h" /* AddressInfo */

#define PACKET_DEFAULT_PROTOCOL 0xdeadbeef

#define PACKET_SIZE 32 //256 bits (32 bytes)

#define PACKET_HEADER_SIZE sizeof(uint32_t)*2 + sizeof(uint8_t) //72 bits (9 bytes)

#define PACKET_TYPE_STREAM    0x00000001 /* Unimportant data. */
#define PACKET_TYPE_HEARTBEAT 0x00000002 /* To maintain a connection. */
#define PACKET_TYPE_IMPORTANT 0x00000003 /* Data that needs a response. */
#define PACKET_TYPE_RESPONSE  0x00000004 /* For arrival of important data. */

/* This struct represents a buffered UDP
packet. It contains one field to avoid
padding. */
typedef struct Packet{
     uint8_t data[PACKET_SIZE];
}Packet;

#ifdef __cplusplus
extern "C" {
#endif
/* Writes a value to the first 32 bits of the packet. The value should
match PACKET_DEFAULT_PROTOCOL. Any packet that does not have a header
matching PACKET_DEFAULT_PROTOCOL is automatically discarded on arrival. */
void NETWORKING_API_ENTRY Packet_WriteProtocol(Packet *packet, uint32_t protocol);
/* Writes the specified value into the packet header. The value should
match one of the following enumerations: PACKET_TYPE_STREAM, PACKET_TYPE_HEARTBEAT,
PACKET_TYPE_IMPORTANT and PACKET_TYPE_RESPONSE */
void NETWORKING_API_ENTRY Packet_WriteType(Packet *packet, uint8_t type);
/* Writes the specified value to the packet header. This value is intended
to check that packets arrive in sequence and should be used as such. */
void NETWORKING_API_ENTRY Packet_WriteNumber(Packet *packet, uint32_t number);
/* Attempts to write the data into the packet's body. If the body is too
small, the function will write as many bytes as possible. */
void NETWORKING_API_ENTRY Packet_WriteData(Packet *packet, void *data, size_t size);
/* This group of functions is used to read data from the packet header.
These functions correspond to the ones above. */
uint32_t NETWORKING_API_ENTRY Packet_ReadProtocol(Packet *packet);
uint32_t NETWORKING_API_ENTRY Packet_ReadNumber(Packet *packet);
uint8_t NETWORKING_API_ENTRY Packet_ReadType(Packet *packet);
void NETWORKING_API_ENTRY *Packet_ReadData(Packet *packet);
/* These functions are used to send/receive data from sockets.
On UNIX, these can be any file descriptor. On Windows, these
are WinSock sockets. */
int NETWORKING_API_ENTRY Packet_Recv(Packet *packet, int file_descriptor);
int NETWORKING_API_ENTRY Packet_Send(Packet *packet, int file_descriptor);
/* This function is the same as it's above counterpart, except it stores
the sender's address in an AddressInfo struct. This allows the user
to send packets back. */
int NETWORKING_API_ENTRY Packet_RecvFrom(Packet *packet, int file_descriptor, AddressInfo *address);
/* This function sends a packet to the specified
address, via the specified file descriptor. */
int NETWORKING_API_ENTRY Packet_SendTo(Packet *packet, int file_descriptor, AddressInfo *address);
#ifdef __cplusplus
}
#endif

#endif /* PACKET_H */
