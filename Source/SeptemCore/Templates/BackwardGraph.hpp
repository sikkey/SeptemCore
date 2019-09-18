// Copyright (c) 2013-2019 7Mersenne All Rights Reserved.

#pragma once

#include "DirectedGraph.hpp"

namespace Septem
{
	namespace GraphTheory
	{
		template<typename VT, typename ET>
		class TBackwardGraph : public TDirectedGraph<VT, ET>
		{
		public:
			TBackwardGraph();
			virtual ~TBackwardGraph();

			virtual void AddVertex(VT& InVT) override;
			virtual void AddVertex(VT&& InVT) override;
			virtual bool AddEdge(TEdge<ET>& InEdge) override;
			virtual void Reset() override;
		protected:
			TArray< EdgeAdjustList > ParentEdges;
		};

		
		template<typename VT, typename ET>
		TBackwardGraph<VT, ET>::TBackwardGraph()
			:TDirectedGraph<VT, ET>()
		{
		}

		template<typename VT, typename ET>
		TBackwardGraph<VT, ET>::~TBackwardGraph()
		{
		}

		template<typename VT, typename ET>
		inline void TBackwardGraph<VT, ET>::AddVertex(VT & InVT)
		{
			EdgeAdjustList eal(this->VertexArray.Num());
			TDirectedGraph<VT, ET>::AddVertex(InVT);
			ParentEdges.Add(eal);
		}

		template<typename VT, typename ET>
		inline void TBackwardGraph<VT, ET>::AddVertex(VT && InVT)
		{
			EdgeAdjustList eal(this->VertexArray.Num());
			TDirectedGraph<VT, ET>::AddVertex(InVT);
			ParentEdges.Add(eal);
		}

		template<typename VT, typename ET>
		inline bool TBackwardGraph<VT, ET>::AddEdge(TEdge<ET>& InEdge)
		{
			if (TDirectedGraph<VT, ET>::AddEdge(InEdge))
			{
				ParentEdges[InEdge.EndId].AdjustVertexes.Add(InEdge.StartId);
				return true;
			}
			return false;
		}

		template<typename VT, typename ET>
		inline void TBackwardGraph<VT, ET>::Reset()
		{
			TDirectedGraph<VT, ET>::Reset();
			ParentEdges.Reset();
		}

	}
}