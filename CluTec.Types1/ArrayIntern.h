////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      ArrayIntern.h
//
// summary:   Declares the array intern class
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

#include <vector>


template<typename TValue>
class CArrayIntern
{
public:
	using TThis = CArrayIntern<TValue>;

protected:
	std::vector<TValue> m_vecData;

public:
	CArrayIntern()
	{}

	~CArrayIntern()
	{}

	CArrayIntern(const TThis& xArray) = default;
	CArrayIntern(TThis&& xArray) = default;

	TThis& operator= (const TThis& xArray) = default;
	TThis& operator= (TThis&& xArray) = default;

	void CopyFrom(const TThis& xArray)
	{
		*this = xArray;
	}

	void Create(size_t nElementCount)
	{
		m_vecData.resize(nElementCount);
	}

	void Create(size_t nElementCount, const TValue *pData)
	{
		m_vecData.resize(nElementCount);
		memcpy(m_vecData.data(), pData, nElementCount * sizeof(TValue));
	}

	void Resize(size_t nElementCount)
	{
		m_vecData.resize(nElementCount);
	}

	void Destroy()
	{
		m_vecData.clear();
		m_vecData.shrink_to_fit();
	}

	void PushBack(const TValue& xValue)
	{
		m_vecData.push_back(xValue);
	}

	TValue& operator[] (size_t nIdx)
	{
		return m_vecData[nIdx];
	}

	const TValue& operator[] (size_t nIdx) const
	{
		return m_vecData[nIdx];
	}

	size_t ElementCount()
	{
		return m_vecData.size();
	}

	TValue* DataPointer()
	{
		return m_vecData.data();
	}

	const TValue* DataPointer() const
	{
		return m_vecData.data();
	}
};

