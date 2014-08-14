#ifndef PACKET_H
#define PACKET_H

#ifdef __cplusplus
#	include <cstdint>
#	include <cstring>
#else
#	include <stdint.h>
#	include <string.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "networking.h"
#include "address.h"

#define PACKET_DEFAULT_PROTOCOL 0xdeadbeef

#define PACKET_SIZE 32 //256 bits (32 bytes)

#define PACKET_HEADER_SIZE sizeof(uint32_t)*2 + sizeof(uint8_t) //72 bits (9 bytes)

#define PACKET_TYPE_STREAM    0x00000001
#define PACKET_TYPE_HEARTBEAT 0x00000002
#define PACKET_TYPE_IMPORTANT 0x00000003
#define PACKET_TYPE_RESPONSE  0x00000004

typedef struct Packet{
	 uint8_t data[PACKET_SIZE];
}Packet;
/*
typedef struct PacketData{
    uint8_t data[PACKET_SIZE - PACKET_HEADER_SIZE]; // 184 bits (23 bytes)
}PacketData;
*/
void NETWORKING_API_ENTRY Packet_WriteProtocol(Packet *packet, uint32_t protocol);
void NETWORKING_API_ENTRY Packet_WriteType(Packet *packet, uint8_t type);
void NETWORKING_API_ENTRY Packet_WriteNumber(Packet *packet, uint32_t number);
void NETWORKING_API_ENTRY Packet_WriteData(Packet *packet, void *data, size_t size);

uint32_t NETWORKING_API_ENTRY Packet_ReadProtocol(Packet *packet);
uint32_t NETWORKING_API_ENTRY Packet_ReadNumber(Packet *packet);
uint8_t NETWORKING_API_ENTRY Packet_ReadType(Packet *packet);
void NETWORKING_API_ENTRY *Packet_ReadData(Packet *packet);

int NETWORKING_API_ENTRY Packet_Recv(Packet *packet, int file_descriptor);
int NETWORKING_API_ENTRY Packet_Send(Packet *packet, int file_descriptor);

int NETWORKING_API_ENTRY Packet_RecvFrom(Packet *packet, int file_descriptor, AddressInfo *address);
int NETWORKING_API_ENTRY Packet_SendTo(Packet *packet, int file_descriptor, AddressInfo *address);

#ifdef __cplusplus
}
#endif

#endif /* PACKET_H */
