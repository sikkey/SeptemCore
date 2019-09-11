// Copyright (c) 2013-2019 7Mersenne All Rights Reserved.

#pragma once

#include <CoreMinimal.h>
#include <Containers/Set.h>

#pragma pack(push)
#pragma pack(8)

namespace Septem
{
	namespace GraphTheory
	{

		template<typename VT>
		struct TVertex
		{
			int32 Index;
			VT Value;
		};

		/*
		*	edge startId O -> O endId
		*	template weight
		*/
		template<typename ET>
		struct TEdge
		{
			int32 StartId;
			int32 EndId;
			ET Weight;
		};

		/*
		*	edge with adjust link list
		*/
		struct EdgeAdjustList
		{
			int32 Index;
			TSet<int32> AdjustVertexes;

			EdgeAdjustList(int32 InIndex = 0)
				:Index(0)
			{}
		};
		
	}
}
#pragma pack(pop)