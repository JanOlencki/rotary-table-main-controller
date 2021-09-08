#ifndef __COM_H__
#define __COM_H__

#include <stdint.h>

#define COM_PREAMBLE (0x5D)
#define COM_BROADCAST_ADDRESS (0xF)
#define COM_CONTROLLER_ADDRESS (0xE)
#define COM_COMMAND_GET_CONTROLLER_STATUS (0x5)
#define COM_RESP_CONTROLLER_STATUS_HEAD (0xE)

#define COM_REQUEST_FRAME_LENGTH (6)
typedef struct {
	uint8_t preamble;
	uint8_t address, command;
	uint8_t payload[3];
	uint8_t crc;
} COM_RequestFrame;

#define COM_RESPONSE_FRAME_LENGTH (9)
typedef struct {
	uint8_t preamble;
	uint8_t address, resp_header;
	uint8_t payload[6];
	uint8_t crc;
} COM_ResponseFrame;

COM_RequestFrame COM_parseRequest(uint8_t data[]);

uint8_t COM_calcCRC8(uint8_t data[], uint32_t len);
uint8_t COM_genResponse(uint8_t data[], COM_ResponseFrame *resp);

#endif
