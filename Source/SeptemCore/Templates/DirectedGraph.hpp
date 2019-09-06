// Copyright (c) 2013-2019 7Mersenne All Rights Reserved.

#pragma once

#include "GraphType.hpp"
#include <Containers/Array.h>
#include <Containers/Map.h>


namespace Septem
{
	namespace GraphTheory
	{
		template<typename VT, typename ET>
		class TDirectedGraph
		{
		public:
			TDirectedGraph();

			virtual void AddVertex(VT& InVT);
			virtual void AddVertex(VT&& InVT);
			virtual bool AddEdge(TEdge<ET>& InEdge);
			bool IsValidVertexIndex(int32 InIndex);
			bool IsValidEdge(int32 InStartId, int32 InEndId);
			int32 VertexCount();
			int32 EdgeCount();
		private:
			static uint64 HashEdgeKey(uint64 InStartId, uint64 InEndId);
			TArray<TVertex<VT>> VertexArray;
			TMap<uint64, TEdge<ET> > EdgeMap;
			bool bDirectSelf;
		};

		template<typename VT, typename ET>
		TDirectedGraph<VT, ET>::TDirectedGraph()
			:bDirectSelf(false)
		{
		}

		template<typename VT, typename ET>
		inline void TDirectedGraph<VT, ET>::AddVertex(VT & InVT)
		{
			TVertex<VT> vertex
				= { VertexArray.Num(),InVT };
			/*
			// push vertex back to the array
			vertex.Index = VertexArray.Num();
			vertex.Value = InVT;
			*/

			VertexArray.Add(vertex);
		}

		template<typename VT, typename ET>
		inline void TDirectedGraph<VT, ET>::AddVertex(VT && InVT)
		{
			TVertex<VT> vertex 
				= {VertexArray.Num(),InVT};

			/*
			// push vertex back to the array
			vertex.Index = VertexArray.Num();
			vertex.Value = InVT;
			*/

			VertexArray.Add(vertex);
		}
		template<typename VT, typename ET>
		inline bool TDirectedGraph<VT, ET>::AddEdge(TEdge<ET>& InEdge)
		{
			if (InEdge.StartId == InEdge.EndId)
			{
				if (bDirectSelf)
					return false;
			}

			if (IsValidVertexIndex(InEdge.StartId) && IsValidVertexIndex(InEdge.EndId))
			{
				uint64 key = HashEdgeKey(InEdge.StartId, InEdge.EndId);//((uint64)InEdge.StartId << 32) | (uint64)InEdge.EndId;
				if (EdgeMap.Contains(key))
					return false;
				EdgeMap.Add(key, InEdge);
				return true;
			}

			return false;
		}
		template<typename VT, typename ET>
		inline bool TDirectedGraph<VT, ET>::IsValidVertexIndex(int32 InIndex)
		{
			return InIndex >= 0 && InIndex < VertexArray.Num();
		}
		template<typename VT, typename ET>
		inline bool TDirectedGraph<VT, ET>::IsValidEdge(int32 InStartId, int32 InEndId)
		{
			uint64 key = HashEdgeKey((uint64)InStartId, (uint64)InEndId);

			return EdgeMap.Contains(key);
		}
		template<typename VT, typename ET>
		inline int32 TDirectedGraph<VT, ET>::VertexCount()
		{
			return VertexArray.Num();
		}
		template<typename VT, typename ET>
		inline int32 TDirectedGraph<VT, ET>::EdgeCount()
		{
			return EdgeMap.Num();
		}

		template<typename VT, typename ET>
		uint64 TDirectedGraph<VT, ET>::HashEdgeKey(uint64 InStartId, uint64 InEndId)
		{
			return (InEdge.StartId << 32ui16) | InEdge.EndId;
		}
	}
}