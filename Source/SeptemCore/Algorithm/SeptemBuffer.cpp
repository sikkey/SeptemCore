// Copyright (c) 2013-2019 7Mersenne All Rights Reserved.

#include "SeptemBuffer.h"

int32 Septem::BufferBufferSyncword(uint8 * Buffer, int32 BufferSize, int32 Syncword)
{
	int32 index = 0;
	int32 maxdex = BufferSize - 4;
	while (index < maxdex)
	{
		int32* ptr = (int32*)(Buffer + index);
		if (*ptr == Syncword)
			return index;

		++index;
	}

	return -1;
}
