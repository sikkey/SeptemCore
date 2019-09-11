// Copyright (c) 2013-2019 7Mersenne All Rights Reserved.

#pragma once

#include "GraphType.hpp"
#include <Containers/Array.h>
#include <Containers/Map.h>


namespace Septem
{
	namespace GraphTheory
	{
		/*
		*	Directed Graph
		*	No Thread Safe
		*/
		template<typename VT, typename ET>
		class TDirectedGraph
		{
		public:
			TDirectedGraph();
			virtual ~TDirectedGraph();

			virtual void AddVertex(VT& InVT);
			virtual void AddVertex(VT&& InVT);
			virtual bool AddEdge(TEdge<ET>& InEdge);
			virtual void Reset();
			/*
			* unsafe call to get vertex&
			* need to check IsValidVertexIndex before
			*/
			TVertex<VT>& GetVertex(int32 InIndex);
			/*
			* unsafe call to get edge&
			* need to check IsValidEdge before 
			*/
			TEdge<ET>& GetEdge(int32 InStartIndex, int32 InEndIndex);
			/*
			* unsafe call to get edge&
			* need to check IsValidEdge before
			*/
			TEdge<ET>& GetEdge(uint64 InKey);
			/*
			* get keys array of edge map
			* @ return	the count of the keys
			*/
			int32 GetEdgeKeys(TArray<uint64>& OutKeys);
			bool IsValidVertexIndex(int32 InIndex);
			bool IsValidEdge(int32 InStartId, int32 InEndId);
			int32 VertexCount();
			int32 EdgeCount();
			static uint64 HashEdgeKey(uint64 InStartId, uint64 InEndId);

			void Seriallize(uint8* OutBuffer, size_t& OutSize);
			void Deseriallize(uint8* InBuffer, size_t InSize);
		protected:
			TArray<TVertex<VT>> VertexArray;
			TMap<uint64, TEdge<ET> > EdgeMap;
			/// can direct to self , default = false
			bool bDirectSelf;
		};

		template<typename VT, typename ET>
		TDirectedGraph<VT, ET>::TDirectedGraph()
			:bDirectSelf(false)
		{
		}

		template<typename VT, typename ET>
		TDirectedGraph<VT, ET>::~TDirectedGraph()
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
				if (!bDirectSelf)
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
		inline void TDirectedGraph<VT, ET>::Reset()
		{
			VertexArray.Reset();
			EdgeMap.Reset();
		}

		template<typename VT, typename ET>
		inline TVertex<VT> & TDirectedGraph<VT, ET>::GetVertex(int32 InIndex)
		{
			return VertexArray[InIndex];
		}
		template<typename VT, typename ET>
		inline TEdge<ET>& TDirectedGraph<VT, ET>::GetEdge(int32 InStartIndex, int32 InEndIndex)
		{
			uint64 key = HashEdgeKey(InStartIndex, InEndIndex);
			return EdgeMap[key];
		}

		template<typename VT, typename ET>
		inline TEdge<ET>& TDirectedGraph<VT, ET>::GetEdge(uint64 InKey)
		{
			return EdgeMap[InKey];
		}
		
		template<typename VT, typename ET>
		inline int32 TDirectedGraph<VT, ET>::GetEdgeKeys(TArray<uint64>& OutKeys)
		{
			return EdgeMap.GetKeys(OutKeys);
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
			return (InStartId << 32ui16) | InEndId;
		}

		/*
		*	{ Graph Memory }
		*	+	VertexArray.Num()
		*	+	[	VertexArray		]	x	VertexArray.Num()
		*	+	EdgeMap.Num()
		*	+	[	EdgeMapKeys	]	x	EdgeMap.Num()
		*	+	[	EdgeMapValues	]	x	EdgeMap.Num()
		*	+ sizeof(bDirectSelf)
		*	Total Size = 
		*		sizeof(VertexArray.Num()) + sizeof(TVertex<VT>) * VertexArray.Num()	+ sizeof(EdgeMap.Num()) + sizeof(uint64)*EdgeMap.Num() + sizeof(TEdge<ET>)*EdgeMap.Num() + sizeof(bDirectSelf)
		*/
		template<typename VT, typename ET>
		inline void TDirectedGraph<VT, ET>::Seriallize(uint8 * OutBuffer, size_t & OutSize)
		{
			size_t _tvertexSize = sizeof(TVertex<VT>);
			size_t _tedgeSize = sizeof(TEdge<ET>);
			OutSize = sizeof(int32) + sizeof(TVertex<VT>) * VertexArray.Num() + sizeof(int32) + sizeof(uint64)*EdgeMap.Num() + sizeof(TEdge<ET>)*EdgeMap.Num() + sizeof(bool);
			OutBuffer = malloc(OutSize);
			size_t _index = 0;
			size_t _Size = 0;

			// *	{ Graph Memory }
			// *	+	VertexArray.Num()
			int32 VertexCount = VertexArray.Num();
			_Size = sizeof(int32);
			memcpy(OutBuffer + _index, &VertexCount, _Size);
			_index += _Size;
			// *	+	[	VertexArray		]	x	VertexArray.Num()
			_Size = sizeof(TVertex<VT>);
			for (int32 i = 0; i < VertexCount; ++i)
			{
				memcpy(OutBuffer + _index, &VertexArray[i], _Size);
				_index += _Size;
			}
			// *	+	EdgeMap.Num()
			TArray<uint64> _edgekeys;
			int32 EdgeCount = EdgeMap.GetKeys(_edgekeys)
			_Size = sizeof(int32);
			memcpy(OutBuffer + _index, &EdgeCount, _Size);
			_index += _Size;
			// *	+	[	EdgeMapKeys	]	x	EdgeMap.Num()
			_Size = sizeof(uint64);
			for (int32 i = 0; i < EdgeCount; ++i)
			{
				memcpy(OutBuffer + _index, &_edgekeys[i], _Size);
				_index += _Size;
			}
			// *	+	[	EdgeMapValues	]	x	EdgeMap.Num()
			_Size = sizeof(TEdge<ET>);
			for (int32 i = 0; i < EdgeCount; ++i)
			{
				memcpy(OutBuffer + _index, &EdgeMap[_edgekeys[i]], _Size);
				_index += _Size;
			}

			// *	+ sizeof(bDirectSelf)
			_Size = sizeof(bDirectSelf);
			memcpy(OutBuffer + _index, &bDirectSelf, _Size);
			_index += _Size;
		}

		/*
		*	{ Graph Memory }
		*	int32					+	VertexArray.Num()
		*	TVertex<VT>	+	[	VertexArray		]	x	VertexArray.Num()
		*	int32					+	EdgeMap.Num()
		*	uint64				+	[	EdgeMapKeys	]	x	EdgeMap.Num()
		*	TEdge<ET>	+	[	EdgeMapValues	]	x	EdgeMap.Num()
		*	bool					+ sizeof(bDirectSelf)
		*	Total Size =
		*		sizeof(VertexArray.Num()) + sizeof(TVertex<VT>) * VertexArray.Num()	+ sizeof(EdgeMap.Num()) + sizeof(uint64)*EdgeMap.Num() + sizeof(TEdge<ET>)*EdgeMap.Num() + sizeof(bDirectSelf)
		*/
		template<typename VT, typename ET>
		inline void TDirectedGraph<VT, ET>::Deseriallize(uint8 * InBuffer, size_t InSize)
		{
			size_t _tvertexSize = sizeof(TVertex<VT>);
			size_t _tedgeSize = sizeof(TEdge<ET>);

			size_t _index = 0;
			size_t _Size = 0;

			Reset();

			// *	{ Graph Memory }
			// *	+	VertexArray.Num()

			int32 VertexCount = 0;// VertexArray.Num();
			_Size = sizeof(int32);
			memcpy(&VertexCount, InBuffer + _index, _Size);
			_index += _Size;
			VertexArray.Reset(VertexCount);

			// *	+	[	VertexArray		]	x	VertexArray.Num()
			_Size = sizeof(TVertex<VT>);
			TVertex<VT> _tvertex;
			for (int32 i = 0; i < VertexCount; ++i)
			{
				
				memcpy(&_tvertex, InBuffer + _index, _Size);
				_index += _Size;
				AddVertex(_tvertex.Value);
			}

			// *	+	EdgeMap.Num()
			TArray<uint64> _edgekeys;
			int32 EdgeCount = 0;
			_Size = sizeof(int32);
			memcpy(&EdgeCount, InBuffer + _index, _Size);
			_index += _Size;

			// *	+	[	EdgeMapKeys	]	x	EdgeMap.Num()
			_edgekeys.Reset(EdgeCount);
			_Size = sizeof(uint64);
			uint64 _key;
			for (int32 i = 0; i < EdgeCount; ++i)
			{
				memcpy(&key, InBuffer + _index, _Size);
				_index += _Size;
				_edgekeys.Add(_key);
			}

			// *	+	[	EdgeMapValues	]	x	EdgeMap.Num()
			EdgeMap.Reset();
			_Size = sizeof(TEdge<ET>);
			TEdge<ET> _value;
			for (int32 i = 0; i < EdgeCount; ++i)
			{
				memcpy(&_value, InBuffer + _index, _Size);
				_index += _Size;
				AddEdge(_value);
			}

			// *	+ sizeof(bDirectSelf)
			_Size = sizeof(bDirectSelf);
			memcpy(&bDirectSelf, InBuffer + _index, _Size);
			_index += _Size;
		}

	}
}