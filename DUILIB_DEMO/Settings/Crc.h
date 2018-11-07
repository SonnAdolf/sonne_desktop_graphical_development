#pragma once
#include <stdint.h>

namespace CRC
{

	uint16_t CrcCompute(uint8_t *src, uint16_t len, uint16_t crc)
	{
		//	#define CRC_DFE_POLY    0x8005
		uint8_t uc;
		for (uint16_t j = 0; j < len; j++)
		{
			uc = *(src + j);
			for(uint16_t i = 0; i < 8; i++)
			{
				crc = ((uc ^ (uint8_t)(crc >> 8)) & 0x80) ? ((crc << 1) ^ 0x8005) : (crc << 1);
				uc <<= 1;
			}
		}
		return crc;
	}

	void make_crc(uint8_t *src,uint16_t dat_len)
	{
		uint16_t crc;
		uint8_t crc1;
		uint8_t crc2;
		crc = CrcCompute(src, dat_len, 0);
		crc1 = (crc >> 8)  & 0xff;
		crc2 = crc  & 0xff;
		*(src+dat_len) = crc1;
		*(src+dat_len+1) = crc2;
	}

}