////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      IArrayString.cpp
//
// summary:   Declares the IArrayString interface
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
#include "IArrayString.h"
#include "ArrayIntern.h"
#include "IArrayStringImpl.h"


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

	CIArrayString::CIArrayString()
	{
		try
		{
			m_pImpl = new CIArrayStringImpl();
			if (m_pImpl == nullptr)
				return;

			REF.New();
		}
		CLU_CATCH_RETHROW_ALL("Error in constructor")
	}


	CIArrayString::~CIArrayString()
	{
		delete m_pImpl;
	}


	CIArrayString::CIArrayString(CIArrayString&& xEx)
	{
		m_pImpl = nullptr;
		*this = std::forward<CIArrayString>(xEx);
	}

	CIArrayString& CIArrayString::operator= (CIArrayString&& xEx)
	{
		delete m_pImpl;
		m_pImpl = xEx.m_pImpl;
		xEx.m_pImpl = nullptr;
		return *this;
	}

	CIArrayString::CIArrayString(const CIArrayString& xEx)
	{
		m_pImpl = new CIArrayStringImpl(*xEx.m_pImpl);
	}

	CIArrayString& CIArrayString::operator= (const CIArrayString& xArray)
	{
		if (m_pImpl != nullptr && xArray.m_pImpl != nullptr)
		{
			REF = REF_(xArray);
		}

		return *this;
	}

	CIArrayString::CIArrayString(size_t nElementCount)
	{
		try
		{
			m_pImpl = new CIArrayStringImpl();

			if (m_pImpl == nullptr)
				return;

			REF.New();

			Create(nElementCount);
		}
		CLU_CATCH_RETHROW_ALL("Error constructing array")
	} 

	CIArrayString::CIArrayString(size_t nElementCount, const TValue *pData)
	{
		try
		{
			m_pImpl = new CIArrayStringImpl();

			if (m_pImpl == nullptr)
				return;

			REF.New();

			Create(nElementCount, pData);
		}
		CLU_CATCH_RETHROW_ALL("Error constructing array")
	}

	bool CIArrayString::IsValidRef() const
	{
		if (m_pImpl == nullptr)
			return false;

		if (!REF.IsValid())
			return false;

		return true;
	}

	bool CIArrayString::IsValid() const
	{
		if (!IsValidRef())
			return false;

		return true;
	}


	CIArrayString CIArrayString::Copy() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid array instance");

			CIArrayString xArray;
			INTERN_(xArray).CopyFrom(INTERN);
			return xArray;
		}
		CLU_CATCH_RETHROW_ALL("Error copying array")
	}


	void CIArrayString::Create(size_t nElementCount)
	{
		try
		{
			if (!IsValidRef())
				throw CLU_EXCEPTION("Invalid array instance");

			REF->Create(nElementCount);
		}
		CLU_CATCH_RETHROW_ALL("Eror creating array")
	}

	void CIArrayString::Create(size_t nElementCount, const TValue *pData)
	{
		try
		{
			if (!IsValidRef())
				throw CLU_EXCEPTION("Invalid array instance");

			REF->Create(nElementCount, pData);
		}
		CLU_CATCH_RETHROW_ALL("Error creating array")
	}

	void CIArrayString::Resize(size_t nElementCount)
	{
		try
		{
			if (!IsValidRef())
				throw CLU_EXCEPTION("Invalid array instance");

			REF->Resize(nElementCount);
		}
		CLU_CATCH_RETHROW_ALL("Error resizing array")
	}

	void CIArrayString::Destroy()
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid array instance");

			REF->Destroy();
		}
		CLU_CATCH_RETHROW_ALL("Error destroying array")
	}

	void CIArrayString::Release()
	{
		try
		{
			if (!IsValidRef())
				throw CLU_EXCEPTION("Invalid array instance");

			REF.Release();
		}
		CLU_CATCH_RETHROW_ALL("Error releasing array reference")
	}

	void CIArrayString::PushBack(const TValue& xValue)
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid array instance");

			REF->PushBack(xValue);
		}
		CLU_CATCH_RETHROW_ALL("Error releasing array reference")
	}

	CIArrayString::TValue& CIArrayString::operator[](size_t nIdx)
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid array instance");

			return REF->operator[](nIdx);
		}
		CLU_CATCH_RETHROW_ALL("Error releasing array reference")
	}

	const CIArrayString::TValue& CIArrayString::operator[](size_t nIdx) const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid array instance");

			return REF->operator[](nIdx);
		}
		CLU_CATCH_RETHROW_ALL("Error releasing array reference")
	}

	size_t CIArrayString::ElementCount() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid array instance");

			return REF->ElementCount();
		}
		CLU_CATCH_RETHROW_ALL("Error getting array element count")
	}


	CIArrayString::TValue* CIArrayString::DataPointer()
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid array instance");

			return REF->DataPointer();
		}
		CLU_CATCH_RETHROW_ALL("Error getting data pointer")
	}

	const CIArrayString::TValue* CIArrayString::DataPointer() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid array instance");

			return REF->DataPointer();
		}
		CLU_CATCH_RETHROW_ALL("Error getting data pointer")
	}

} // namespace Clu
