#include "communication.h"

COM_RequestFrame COM_parseRequest(uint8_t data[]) {
	COM_RequestFrame req;
	req.preamble = data[0];
	req.address = data[1] >> 4;
	req.command = data[1] & 0xF;
	memcpy(&req.payload, &data[2], sizeof(req.payload));
	req.crc = data[5];
	return req;
}

uint8_t COM_calcCRC8(uint8_t data[], uint32_t len) {
	uint32_t crc = 0;
	int i, j;
	for (j = len; j; j--, data++) {
		crc ^= (*data << 8);
		for (i = 8; i; i--) {
			if (crc & 0x8000)
				crc ^= (0x1070 << 3);
			crc <<= 1;
		}
	}
	return (uint8_t) (crc >> 8);
}

uint8_t COM_genResponse(uint8_t data[], COM_ResponseFrame *resp) {
	data[0] = resp->preamble;
	data[1] = resp->address << 4;
	data[1] |= resp->resp_header;
	memcpy(&data[2], &resp->payload, sizeof(resp->payload));
	data[8] = COM_calcCRC8(data, 8);
	return data[8];
}
