////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Base
// file:      StdAlgo.h
//
// summary:   Declares the standard algo class
//
//            Copyright (c) 2019 by Christian Perwass.
//
//            This file is part of the CluTecLib library.
//
//            The CluTecLib library is free software: you can redistribute it and / or modify
//            it under the terms of the GNU Lesser General Public License as published by
//            the Free Software Foundation, either version 3 of the License, or
//            (at your option) any later version.
//
//            The CluTecLib library is distributed in the hope that it will be useful,
//            but WITHOUT ANY WARRANTY; without even the implied warranty of
//            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//            GNU Lesser General Public License for more details.
//
//            You should have received a copy of the GNU Lesser General Public License
//            along with the CluTecLib library.
//            If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace Clu
{
	template<typename TContainer, typename TFunctor>
	void ForEach(TContainer& xContainer, TFunctor Functor)
	{
		typename TContainer::iterator itEl, itEnd = xContainer.end();
		for (itEl = xContainer.begin(); itEl != itEnd; ++itEl)
		{
			Functor(*itEl);
		}
	}

	template<typename TContainer, typename TFunctor>
	void ForEach(const TContainer& xContainer, TFunctor Functor)
	{
		typename TContainer::const_iterator itEl, itEnd = xContainer.cend();
		for (itEl = xContainer.cbegin(); itEl != itEnd; ++itEl)
		{
			Functor(*itEl);
		}
	}

	template<typename TContainer, typename TFunctor>
	void ForEachIndex(TContainer& xContainer, TFunctor Functor)
	{
		size_t nIdx;
		typename TContainer::iterator itEl, itEnd = xContainer.end();
		for (itEl = xContainer.begin(), nIdx = 0; itEl != itEnd; ++itEl, ++nIdx)
		{
			Functor(*itEl, nIdx);
		}
	}

	template<typename TContainer, typename TFunctor>
	void ForEachIndex(const TContainer& xContainer, TFunctor Functor)
	{
		size_t nIdx;
		typename TContainer::const_iterator itEl, itEnd = xContainer.cend();
		for (itEl = xContainer.cbegin(), nIdx = 0; itEl != itEnd; ++itEl, ++nIdx)
		{
			Functor(*itEl, nIdx);
		}
	}

	template<typename TContainer, typename TFunctor>
	void ForEachPair(TContainer& xContainer, TFunctor Functor)
	{
		typename TContainer::iterator itEl, itEnd = xContainer.end();
		for (itEl = xContainer.begin(); itEl != itEnd; ++itEl)
		{
			Functor(itEl->first, itEl->second);
		}
	}

	template<typename TContainer, typename TFunctor>
	void ForEachPair(const TContainer& xContainer, TFunctor Functor)
	{
		typename TContainer::const_iterator itEl, itEnd = xContainer.cend();
		for (itEl = xContainer.cbegin(); itEl != itEnd; ++itEl)
		{
			Functor(itEl->first, itEl->second);
		}
	}

	template<typename TContainerA, typename TContainerB, typename TFunctor>
	void ForEachPair(TContainerA& xContainerA, TContainerB& xContainerB, TFunctor Functor)
	{
		typename TContainerA::iterator itElA  = xContainerA.begin();
		typename TContainerA::iterator itEndA = xContainerA.end();
		typename TContainerB::iterator itElB  = xContainerB.begin();

		for (; itElA != itEndA; ++itElA, ++itElB)
		{
			Functor(*itElA, *itElB);
		}
	}

	template<typename TContainerA, typename TContainerB, typename TFunctor>
	void ForEachPair(const TContainerA& xContainerA, const TContainerB& xContainerB, TFunctor Functor)
	{
		typename TContainerA::const_iterator itElA  = xContainerA.begin();
		typename TContainerA::const_iterator itEndA = xContainerA.end();
		typename TContainerB::const_iterator itElB  = xContainerB.begin();

		for (; itElA != itEndA; ++itElA, ++itElB)
		{
			Functor(*itElA, *itElB);
		}
	}

	template<typename TContainerA, typename TContainerB, typename TFunctor>
	void ForEachPairIndex(TContainerA& xContainerA, TContainerB& xContainerB, TFunctor Functor)
	{
		size_t nIdx                  = 0;
		typename TContainerA::iterator itElA  = xContainerA.begin();
		typename TContainerA::iterator itEndA = xContainerA.end();
		typename TContainerB::iterator itElB  = xContainerB.begin();

		for (; itElA != itEndA; ++itElA, ++itElB, ++nIdx)
		{
			Functor(*itElA, *itElB, nIdx);
		}
	}

	template<typename TContainerA, typename TContainerB, typename TFunctor>
	void ForEachPairIndex(const TContainerA& xContainerA, const TContainerB& xContainerB, TFunctor Functor)
	{
		size_t nIdx                        = 0;
		typename TContainerA::const_iterator itElA  = xContainerA.begin();
		typename TContainerA::const_iterator itEndA = xContainerA.end();
		typename TContainerB::const_iterator itElB  = xContainerB.begin();

		for (; itElA != itEndA; ++itElA, ++itElB, ++nIdx)
		{
			Functor(*itElA, *itElB, nIdx);
		}
	}

	template<typename TContainerA, typename TContainerB, typename TFunctor>
	void Transform(TContainerA& xContainerA, const TContainerB& xContainerB, TFunctor Functor)
	{
		typename TContainerA::iterator itElA       = xContainerA.begin();
		typename TContainerA::iterator itEndA      = xContainerA.end();
		typename TContainerB::const_iterator itElB = xContainerB.begin();

		for (; itElA != itEndA; ++itElA, ++itElB)
		{
			Functor(*itElA, *itElB);
		}
	}

	template<typename TContainerA, typename TContainerB, typename TFunctor>
	void TransformIndex(TContainerA& xContainerA, const TContainerB& xContainerB, TFunctor Functor)
	{
		size_t nIdx                       = 0;
		typename TContainerA::iterator itElA       = xContainerA.begin();
		typename TContainerA::iterator itEndA      = xContainerA.end();
		typename TContainerB::const_iterator itElB = xContainerB.begin();

		for (; itElA != itEndA; ++itElA, ++itElB, ++nIdx)
		{
			Functor(*itElA, *itElB, nIdx);
		}
	}

	template<typename TContainer, typename TFunctor>
	bool ForEachTest(TContainer& xContainer, TFunctor Functor)
	{
		typename TContainer::iterator itEl, itEnd = xContainer.end();
		for (itEl = xContainer.begin(); itEl != itEnd; ++itEl)
		{
			if (!Functor(*itEl))
			{
				return false;
			}
		}

		return true;
	}

	template<typename TContainer, typename TFunctor>
	bool ForEachTest(const TContainer& xContainer, TFunctor Functor)
	{
		typename TContainer::const_iterator itEl, itEnd = xContainer.end();
		for (itEl = xContainer.begin(); itEl != itEnd; ++itEl)
		{
			if (!Functor(*itEl))
			{
				return false;
			}
		}

		return true;
	}

	template<typename TContainer, typename TFunctor>
	bool ForEachIndexTest(TContainer& xContainer, TFunctor Functor)
	{
		size_t nIdx;
		typename TContainer::iterator itEl, itEnd = xContainer.end();
		for (itEl = xContainer.begin(), nIdx = 0; itEl != itEnd; ++itEl, ++nIdx)
		{
			if (!Functor(*itEl, nIdx))
			{
				return false;
			}
		}

		return true;
	}

	template<typename TContainer, typename TFunctor>
	bool ForEachIndexTest(const TContainer& xContainer, TFunctor Functor)
	{
		size_t nIdx;
		typename TContainer::const_iterator itEl, itEnd = xContainer.end();
		for (itEl = xContainer.begin(), nIdx = 0; itEl != itEnd; ++itEl, ++nIdx)
		{
			if (!Functor(*itEl, nIdx))
			{
				return false;
			}
		}

		return true;
	}

	template<typename TContainer, typename TObject>
	bool Contains(const TContainer& xContainer, const TObject& xObject)
	{
		return xContainer.find(xObject) != xContainer.end();
	}

	template<typename TContainer, typename TObject>
	bool Contains(typename TContainer::iterator& itEl, TContainer& xContainer, const TObject& xObject)
	{
		return (itEl = xContainer.find(xObject)) != xContainer.end();
	}

	template<typename TContainer, typename TObject>
	bool Contains(typename TContainer::const_iterator& itEl, const TContainer& xContainer, const TObject& xObject)
	{
		return (itEl = xContainer.find(xObject)) != xContainer.end();
	}


	template<size_t t_nCount, typename T, typename T2>
	void MemCpy(T* pTrg, const T2* pSrc)
	{
		for (size_t nIdx = 0; nIdx < t_nCount; ++nIdx, ++pTrg, ++pSrc)
		{
			*pTrg = T(*pSrc);
		}
	}

	template<size_t t_uTrgCount, size_t t_nSrcCount, typename T, typename T2>
	void MemCpy(T(&pTrg)[t_uTrgCount], const T2(&pSrc)[t_nSrcCount])
	{
		static_assert((t_uTrgCount >= t_nSrcCount), "Target memory size must be larger or equal than source memory block");

		T* _pTrg = pTrg;
		const T2* _pSrc = pSrc;

		for (size_t nIdx = 0; nIdx < t_nSrcCount; ++nIdx, ++_pTrg, ++_pSrc)
		{
			*_pTrg = T(*_pSrc);
		}
	}

	template<typename T, typename T2>
	void MemCpy(T* pTrg, const T2* pSrc, size_t nCount)
	{
		for (size_t nIdx = 0; nIdx < nCount; ++nIdx, ++pTrg, ++pSrc)
		{
			*pTrg = T(*pSrc);
		}
	}

	template<size_t t_nCount, typename T, typename T2>
	void MemSet(T* pTrg, const T2& _tValue)
	{
		T tValue = T(_tValue);

		for (size_t nIdx = 0; nIdx < t_nCount; ++nIdx, ++pTrg)
		{
			*pTrg = tValue;
		}
	}

	template<size_t t_nCount, typename T, typename T2>
	void MemSet(T(&pTrg)[t_nCount], const T2& _tValue)
	{
		T* _pTrg = pTrg;
		T tValue = T(_tValue);

		for (size_t nIdx = 0; nIdx < t_nCount; ++nIdx, ++_pTrg)
		{
			*_pTrg = tValue;
		}
	}

	template<typename T, typename T2>
	void MemSet(T* pTrg, const T2& _tValue, size_t nCount)
	{
		T tValue = T(_tValue);

		for (size_t nIdx = 0; nIdx < nCount; ++nIdx, ++pTrg)
		{
			*pTrg = tValue;
		}
	}

}
