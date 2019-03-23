////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      IArrayDouble.cpp
//
// summary:   Declares the IArrayDouble interface
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
#include "IArrayDouble.h"
#include "ArrayIntern.h"
#include "IArrayDoubleImpl.h"


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

	CIArrayDouble::CIArrayDouble()
	{
		try
		{
			m_pImpl = new CIArrayDoubleImpl();
			if (m_pImpl == nullptr)
				return;

			REF.New();
		}
		CLU_CATCH_RETHROW_ALL("Error in constructor")
	}


	CIArrayDouble::~CIArrayDouble()
	{
		delete m_pImpl;
	}


	CIArrayDouble::CIArrayDouble(CIArrayDouble&& xEx)
	{
		m_pImpl = nullptr;
		*this = std::forward<CIArrayDouble>(xEx);
	}

	CIArrayDouble& CIArrayDouble::operator= (CIArrayDouble&& xEx)
	{
		delete m_pImpl;
		m_pImpl = xEx.m_pImpl;
		xEx.m_pImpl = nullptr;
		return *this;
	}

	CIArrayDouble::CIArrayDouble(const CIArrayDouble& xEx)
	{
		m_pImpl = new CIArrayDoubleImpl(*xEx.m_pImpl);
	}

	CIArrayDouble& CIArrayDouble::operator= (const CIArrayDouble& xArray)
	{
		if (m_pImpl != nullptr && xArray.m_pImpl != nullptr)
		{
			REF = REF_(xArray);
		}

		return *this;
	}

	CIArrayDouble::CIArrayDouble(size_t nElementCount)
	{
		try
		{
			m_pImpl = new CIArrayDoubleImpl();

			if (m_pImpl == nullptr)
				return;

			REF.New();

			Create(nElementCount);
		}
		CLU_CATCH_RETHROW_ALL("Error constructing array")
	}

	CIArrayDouble::CIArrayDouble(size_t nElementCount, const TValue *pData)
	{
		try
		{
			m_pImpl = new CIArrayDoubleImpl();

			if (m_pImpl == nullptr)
				return;

			REF.New();

			Create(nElementCount, pData);
		}
		CLU_CATCH_RETHROW_ALL("Error constructing array")
	}

	bool CIArrayDouble::IsValidRef() const
	{
		if (m_pImpl == nullptr)
			return false;

		if (!REF.IsValid())
			return false;

		return true;
	}

	bool CIArrayDouble::IsValid() const
	{
		if (!IsValidRef())
			return false;

		return true;
	}


	CIArrayDouble CIArrayDouble::Copy() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid array instance");

			CIArrayDouble xArray;
			INTERN_(xArray).CopyFrom(INTERN);
			return xArray;
		}
		CLU_CATCH_RETHROW_ALL("Error copying array")
	}


	void CIArrayDouble::Create(size_t nElementCount)
	{
		try
		{
			if (!IsValidRef())
				throw CLU_EXCEPTION("Invalid array instance");

			REF->Create(nElementCount);
		}
		CLU_CATCH_RETHROW_ALL("Eror creating array")
	}

	void CIArrayDouble::Create(size_t nElementCount, const TValue *pData)
	{
		try
		{
			if (!IsValidRef())
				throw CLU_EXCEPTION("Invalid array instance");

			REF->Create(nElementCount, pData);
		}
		CLU_CATCH_RETHROW_ALL("Error creating array")
	}

	void CIArrayDouble::Resize(size_t nElementCount)
	{
		try
		{
			if (!IsValidRef())
				throw CLU_EXCEPTION("Invalid array instance");

			REF->Resize(nElementCount);
		}
		CLU_CATCH_RETHROW_ALL("Error resizing array")
	}

	void CIArrayDouble::Destroy()
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid array instance");

			REF->Destroy();
		}
		CLU_CATCH_RETHROW_ALL("Error destroying array")
	}

	void CIArrayDouble::Release()
	{
		try
		{
			if (!IsValidRef())
				throw CLU_EXCEPTION("Invalid array instance");

			REF.Release();
		}
		CLU_CATCH_RETHROW_ALL("Error releasing array reference")
	}

	void CIArrayDouble::PushBack(const TValue& xValue)
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid array instance");

			REF->PushBack(xValue);
		}
		CLU_CATCH_RETHROW_ALL("Error releasing array reference")
	}

	CIArrayDouble::TValue& CIArrayDouble::operator[](size_t nIdx)
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid array instance");

			return REF->operator[](nIdx);
		}
		CLU_CATCH_RETHROW_ALL("Error releasing array reference")
	}

	const CIArrayDouble::TValue& CIArrayDouble::operator[](size_t nIdx) const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid array instance");

			return REF->operator[](nIdx);
		}
		CLU_CATCH_RETHROW_ALL("Error releasing array reference")
	}

	size_t CIArrayDouble::ElementCount() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid array instance");

			return REF->ElementCount();
		}
		CLU_CATCH_RETHROW_ALL("Error getting array element count")
	}


	CIArrayDouble::TValue* CIArrayDouble::DataPointer()
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid array instance");

			return REF->DataPointer();
		}
		CLU_CATCH_RETHROW_ALL("Error getting data pointer")
	}

	const CIArrayDouble::TValue* CIArrayDouble::DataPointer() const
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
