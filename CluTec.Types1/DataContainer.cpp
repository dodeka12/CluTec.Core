////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      DataContainer.cpp
//
// summary:   Implements the data container class
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

#include "stdafx.h"
#include "DataContainer.h"
#include "IException.h"
#include "Defines.h"

#include <utility>


namespace Clu
{

	CDataContainer::CDataContainer()
	{
		_Reset();
	}

	CDataContainer::~CDataContainer()
	{
		Clear();
	}


	CDataContainer::CDataContainer(CDataContainer&& xData)
	{
		*this = std::forward<CDataContainer>(xData);
	}

	CDataContainer& CDataContainer::operator= (CDataContainer&& xData)
	{
		m_mapData = std::move(xData.m_mapData);
		m_itData = m_mapData.cend();

		xData._Reset();
		return *this;
	}

	CDataContainer::CDataContainer(const CDataContainer& xData)
	{
		*this = xData;
	}

	CDataContainer& CDataContainer::operator=(const CDataContainer& xData)
	{
		if (this == &xData)
			return *this;

		m_mapData = xData.m_mapData;
		m_itData = m_mapData.cend();

		return *this;
	}


	void CDataContainer::_Reset()
	{
		m_mapData.clear();
		m_itData = m_mapData.cend();
	}


	void CDataContainer::Clear()
	{
		_Reset();
	}


	void CDataContainer::Insert(const CIString& sName, const SDataObject& xData)
	{
		std::string strName = sName.ToCString();

		auto itEl = m_mapData.end();
		if ((itEl = m_mapData.find(strName)) != m_mapData.end())
		{
			throw CLU_EXCEPTION(CLU_S "Element '" << strName.c_str() << "' already exists in container");
		}

		m_mapData[strName] = xData;
	}

	const SDataObject& CDataContainer::At(const CIString& sName) const
	{
		std::string strName = sName.ToCString();

		auto itEl = m_mapData.end();
		if ((itEl = m_mapData.find(strName)) == m_mapData.end())
		{
			throw CLU_EXCEPTION(CLU_S "Element '" << strName.c_str() << "' does not exist in container");
		}

		return m_mapData.at(strName);
	}

	bool CDataContainer::HasElement(const CIString& sName) const
	{
		std::string strName = sName.ToCString();

		return (m_mapData.find(strName) != m_mapData.end());
	}

	bool CDataContainer::IsValid() const
	{
		return true;
	}

	size_t CDataContainer::Count() const
	{
		return m_mapData.size();
	}

	bool CDataContainer::First(CIString& sName, SDataObject& xData)
	{
		m_itData = m_mapData.cbegin();
		if (m_itData == m_mapData.cend())
		{
			return false;
		}

		sName = m_itData->first.c_str();
		xData = m_itData->second;
		return true;
	}

	bool CDataContainer::Next(CIString& sName, SDataObject& xData)
	{
		if (m_itData == m_mapData.cend())
		{
			return false;
		}

		++m_itData;

		if (m_itData == m_mapData.cend())
		{
			return false;
		}

		sName = m_itData->first.c_str();
		xData = m_itData->second;
		return true;
	}


} // namespace Clu

