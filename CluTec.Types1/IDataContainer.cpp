////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      IDataContainer.cpp
//
// summary:   Declares the IDataContainer interface
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
#include "IDataContainer.h"
#include "IDataContainerImpl.h"
#include "DataContainer.h"


#include "IException.h"

#define CLU_EXCEPTION(theMsg) \
	Clu::CIException(theMsg, __FILE__, __FUNCTION__, __LINE__)

#define CLU_CATCH_RETHROW_ALL(theMsg) \
	catch (std::exception& xEx) \
		{ \
		throw Clu::CIException(Clu::CIString(theMsg) << " : " << xEx.what(), __FILE__, __FUNCTION__, __LINE__); \
		} \
	catch (Clu::CIException& xEx) \
		{ \
		throw Clu::CIException(Clu::CIString(theMsg), __FILE__, __FUNCTION__, __LINE__, std::move(xEx)); \
		} 

namespace Clu
{

#define REF (*m_pImpl)
#define REF_(theVar) (*theVar.m_pImpl)

#define INTERN (*(m_pImpl->Get()))
#define INTERN_(theVar) (*(theVar.m_pImpl->Get()))

	CIDataContainer::CIDataContainer()
	{
		try
		{
			m_pImpl = new CIDataContainerImpl();
			if (m_pImpl == nullptr)
				return;

			REF.New();
		}
		CLU_CATCH_RETHROW_ALL("Error in constructor")
	}


	CIDataContainer::~CIDataContainer()
	{
		delete m_pImpl;
	}


	CIDataContainer::CIDataContainer(CIDataContainer&& xEx)
	{
		m_pImpl = nullptr;
		*this = std::forward<CIDataContainer>(xEx);
	}

	CIDataContainer& CIDataContainer::operator= (CIDataContainer&& xEx)
	{
		delete m_pImpl;
		m_pImpl = xEx.m_pImpl;
		xEx.m_pImpl = nullptr;
		return *this;
	}

	CIDataContainer::CIDataContainer(const CIDataContainer& xEx)
	{
		m_pImpl = new CIDataContainerImpl(*xEx.m_pImpl);
	}

	CIDataContainer& CIDataContainer::operator= (const CIDataContainer& xData)
	{
		if (m_pImpl != nullptr && xData.m_pImpl != nullptr)
		{
			REF = REF_(xData);
		}

		return *this;
	}


	bool CIDataContainer::IsValidRef() const
	{
		if (m_pImpl == nullptr)
			return false;

		if (!REF.IsValid())
			return false;

		return true;
	}

	bool CIDataContainer::IsValid() const
	{
		if (!IsValidRef())
			return false;

		if (!REF->IsValid())
			return false;

		return true;
	}


	void CIDataContainer::Release()
	{
		try
		{
			if (!IsValidRef())
				throw CLU_EXCEPTION("Invalid data container instance");

			REF.Release();
		}
		CLU_CATCH_RETHROW_ALL("Error releasing data container reference")
	}

	void CIDataContainer::Clear()
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid data container instance");

			REF->Clear();
		}
		CLU_CATCH_RETHROW_ALL("Error destroying data container")
	}

	void CIDataContainer::Insert(const CIString& sName, const SDataObject& xData)
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid data container instance");

			REF->Insert(sName, xData);
		}
		CLU_CATCH_RETHROW_ALL("Error inserting data object")

	}

	const Clu::SDataObject& CIDataContainer::At(const CIString& sName) const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid data container instance");

			return REF->At(sName);
		}
		CLU_CATCH_RETHROW_ALL("Error obtaining data object")
	}

	bool CIDataContainer::HasElement(const CIString& sName) const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid data container instance");

			return REF->HasElement(sName);
		}
		CLU_CATCH_RETHROW_ALL("Error testing for element")
	}

	size_t CIDataContainer::Count() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid data container instance");

			return REF->Count();
		}
		CLU_CATCH_RETHROW_ALL("Error obtaining element count")
	}

	bool CIDataContainer::First(CIString& sName, SDataObject& xData)
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid data container instance");

			return REF->First(sName, xData);
		}
		CLU_CATCH_RETHROW_ALL("Error obtaining first element")
	}

	bool CIDataContainer::Next(CIString& sName, SDataObject& xData)
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid data container instance");

			return REF->Next(sName, xData);
		}
		CLU_CATCH_RETHROW_ALL("Error obtaining next element")

	}

} // namespace Clu
