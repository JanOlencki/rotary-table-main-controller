#ifndef __QC_H__
#define __QC_H__

typedef struct {
	uint8_t address, command;
	uint8_t crc;
} ComFrame;

typedef struct {
	uint8_t address, command;
	uint32_t payload;
	uint8_t crc;
} ComFrameLong;

#endif
