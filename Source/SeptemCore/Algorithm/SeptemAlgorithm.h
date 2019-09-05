// Copyright (c) 2013-2019 7Mersenne All Rights Reserved.

#pragma once

#include "SeptemBuffer.h"

namespace Septem
{
	// system timestamp
	static uint64 UnixTimestampMillisecond()
	{
		return (FDateTime::UtcNow().GetTicks() - FDateTime(1970, 1, 1).GetTicks()) / ETimespan::TicksPerMillisecond;
	}
}