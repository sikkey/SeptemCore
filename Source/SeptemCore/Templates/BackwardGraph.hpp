// Copyright (c) 2013-2019 7Mersenne All Rights Reserved.

#pragma once

#include "DirectedGraph.hpp"

namespace Septem
{
	namespace GraphTheory
	{
		template<typename VT, typename ET>
		class BackwardGraph : DirectedGraph<VT, ET>
		{
		public:
			BackwardGraph();

			virtual void AddVertex(VT& InVT) override;
			virtual void AddVertex(VT&& InVT) override;
			virtual bool AddEdge(TEdge<ET>& InEdge) override;
		private:
			TArray< EdgeAdjustList > ParentEdges;
		};

		
		template<typename VT, typename ET>
		BackwardGraph<VT, ET>::BackwardGraph()
			:DirectedGraph<VT, ET>()
		{
		}

		template<typename VT, typename ET>
		inline void BackwardGraph<VT, ET>::AddVertex(VT & InVT)
		{
			EdgeAdjustList eal(VertexArray.Num());
			DirectedGraph<VT, ET>::AddVertex(InVT);
			ParentEdges.Add(eal);
		}

		template<typename VT, typename ET>
		inline void BackwardGraph<VT, ET>::AddVertex(VT && InVT)
		{
			EdgeAdjustList eal(VertexArray.Num());
			DirectedGraph<VT, ET>::AddVertex(InVT);
			ParentEdges.Add(eal);
		}

		template<typename VT, typename ET>
		inline bool BackwardGraph<VT, ET>::AddEdge(TEdge<ET>& InEdge)
		{
			if (DirectedGraph<VT, ET>::AddEdge(InEdge))
			{
				ParentEdges[InEdge.EndId].AdjustVertexes.Add(InEdge.StartId);
				return true;
			}
			return false;
		}

	}
}