// Copyright (c) 2013-2019 7Mersenne All Rights Reserved.

#pragma once

#include <CoreMinimal.h>
#include <Containers/Array.h>

namespace Septem
{
	namespace GraphTheory
	{
		template<typename VT>
		struct Vertex
		{
			int32 Index;
			VT Value;
		};

		/*
		*	edge startId O -> O endId
		*	template weight
		*/
		template<typename ET>
		struct Edge
		{
			int32 StartId;
			int32 EndId;
			ET Weight;
		};

		template<typename VT, typename ET>
		class DirectedGraph
		{
		public:
			DirectedGraph();

			void AddVertex(VT& InVT);
			void AddVertex(VT&& InVT);
			bool AddEdge(Edge<ET>& InEdge);
			bool IsValidVertexIndex(int32 InIndex);
			int32 VertexCount();
			int32 EdgeCount();
		private:
			TArray<Vertex<VT>> VertexArray;
			TSet<Edge<ET>> EdgeSet;
			bool bDirectSelf;
		};

		template<typename VT, typename ET>
		DirectedGraph<VT, ET>::DirectedGraph()
			:bDirectSelf(false)
		{
		}

		template<typename VT, typename ET>
		inline void DirectedGraph<VT, ET>::AddVertex(VT & InVT)
		{
			Vertex<VT> vertex;

			// push vertex back to the array
			vertex.Index = VertexArray.Num();
			vertex.Value = InVT;

			VertexArray.Add(vertex);
		}

		template<typename VT, typename ET>
		inline void DirectedGraph<VT, ET>::AddVertex(VT && InVT)
		{
			Vertex<VT> vertex;

			// push vertex back to the array
			vertex.Index = VertexArray.Num();
			vertex.Value = InVT;

			VertexArray.Add(vertex);
		}
		template<typename VT, typename ET>
		inline bool DirectedGraph<VT, ET>::AddEdge(Edge<ET>& InEdge)
		{
			if (InEdge.StartId == InEdge.EndId)
			{
				if (bDirectSelf)
					return false;
			}

			if (IsValidVertexIndex(InEdge.StartId) && IsValidVertexIndex(InEdge.EndId))
			{
				if (EdgeSet.Contains(InEdge))
					return false;
				EdgeSet.Add(InEdge);
				return true;
			}

			return false;
		}
		template<typename VT, typename ET>
		inline bool DirectedGraph<VT, ET>::IsValidVertexIndex(int32 InIndex)
		{
			return InIndex >= 0 && InIndex < VertexArray.Num();
		}
		template<typename VT, typename ET>
		inline int32 DirectedGraph<VT, ET>::VertexCount()
		{
			return VertexArray.Num();
		}
		template<typename VT, typename ET>
		inline int32 DirectedGraph<VT, ET>::EdgeCount()
		{
			return EdgeSet.Num();
		}
	}
}