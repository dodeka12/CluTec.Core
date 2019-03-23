////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      IException.cpp
//
// summary:   Declares the IException interface
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
#include "IException.h"
#include "IString.h"
#include "Guid.h"

#include <exception>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

#include "Exception.h"

namespace Clu
{

	#define REF (*m_pImpl)

	CIException::CIException()
	{
		m_pImpl = new CIExceptionImpl();
		if (m_pImpl == nullptr)
			return;

		REF.New();

		REF->Line() = -1;
	}


	CIException::~CIException()
	{
		delete m_pImpl;
	}


	CIException::CIException(CIException&& xEx)
	{
		m_pImpl = nullptr;
		*this = std::forward<CIException>(xEx);
	}

	CIException& CIException::operator= (CIException&& xEx)
	{
		delete m_pImpl;
		m_pImpl = xEx.m_pImpl;
		xEx.m_pImpl = nullptr;
		return *this;
	}

	CIException::CIException(const CIException& xEx)
	{
		m_pImpl = new CIExceptionImpl(*xEx.m_pImpl);
	}

	CIException& CIException::operator= (const CIException& xEx)
	{
		if (m_pImpl != nullptr && xEx.m_pImpl != nullptr)
		{
			*m_pImpl = *xEx.m_pImpl;
		}

		return *this;
	}

	CIException::CIException(const CIString& sMsg, const CIString& sFile, const CIString& sFunc, int iLine)
	{
		m_pImpl = new CIExceptionImpl();

		if (m_pImpl == nullptr)
			return;

		REF.New();

		_SetData(sMsg, sFile, sFunc, iLine);
	}

	CIException::CIException(const CIString& sMsg, const CIString& sFile, const CIString& sFunc, int iLine, CIException&& xEx)
	{
		m_pImpl = new CIExceptionImpl();

		if (m_pImpl == nullptr)
			return;

		REF.New();

		_SetData(sMsg, sFile, sFunc, iLine);

		REF->Nested() = std::move(*xEx.m_pImpl);
	}

	CIException::CIException(const ExceptionType::Unknown& xType, const CIString& sMsg, const CIString& sFile, const CIString& sFunc, int iLine)
	{
		m_pImpl = new CIExceptionImpl();

		if (m_pImpl == nullptr)
			return;

		REF.New();

		_SetData(xType, sMsg, sFile, sFunc, iLine);
	}
	
	
	CIException::CIException(const ExceptionType::Unknown& xType, const CIString& sMsg, const CIString& sFile, const CIString& sFunc, int iLine, CIException&& xEx)
	{
		m_pImpl = new CIExceptionImpl();

		if (m_pImpl == nullptr)
			return;

		REF.New();

		_SetData(xType, sMsg, sFile, sFunc, iLine);

		REF->Nested() = std::move(*xEx.m_pImpl);
	}


	void CIException::_SetData(const ExceptionType::Unknown& xType, const CIString& sMsg, const CIString& sFile, const CIString& sFunc, const int & iLine)
	{
		REF->Type() = xType;
		_SetData(sMsg, sFile, sFunc, iLine);
	}


	void CIException::_SetData(const CIString& sMsg, const CIString& sFile, const CIString& sFunc, const int & iLine)
	{
		std::string sFilename = sFile.ToCString();

		size_t nIdx = 0;

		while ((nIdx = sFilename.find("/", nIdx)) != CIString::Invalid)
		{
			sFilename.replace(nIdx, 1, "\\");
			nIdx++;
		}

		nIdx = sFilename.find_last_of("\\");
		if (nIdx != std::string::npos)
		{
			if (nIdx == 0)
			{
				sFilename = sFilename.substr(1);
			}
			else
			{
				if ((nIdx = sFilename.rfind('\\', nIdx - 1)) != std::string::npos)
				{
					sFilename = "..." + sFilename.substr(nIdx);
				}
			}
		}

		REF->Message() = sMsg.ToCString();
		REF->File() = sFilename;
		REF->Function() = sFunc.ToCString();
		REF->Line() = iLine;

		REF->Nested().Reset();
	}

	Clu::ExceptionType::Unknown CIException::GetType() const
	{
		if (!IsValid())
			return Clu::ExceptionType::Unknown();

		return REF->Type();
	}

	CGuid CIException::GetTypeGuid() const
	{
		if (!IsValid())
			return CGuid();

		return REF->Type().GetGuid();
	}

	CIString CIException::GetTypeName() const
	{
		if (!IsValid())
			return CIString();

		return CIString(REF->Type().GetTypeName());
	}

	CIString CIException::GetText() const
	{
		if (!IsValid())
			return CIString();

		return CIString(REF->Message().c_str());
	}

	CIString CIException::GetFile() const
	{
		if (!IsValid())
			return CIString();

		return CIString(REF->File().c_str());
	}

	CIString CIException::GetFunc() const
	{
		if (!IsValid())
			return CIString();

		return CIString(REF->Function().c_str());
	}

	int CIException::GetLine() const
	{
		if (!IsValid())
			return -1;

		return REF->Line();
	}


	bool CIException::HasNested() const
	{
		if (!IsValid())
			return false;

		return (bool)REF->Nested();
	}

	bool CIException::IsValid() const
	{
		if (m_pImpl == nullptr)
			return false;

		if (!REF.IsValid())
			return false;

		return true;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Gets the nested exception if there is one or a null pointer. You MUST NOT store this pointer
	/// for later use, as it may become invalid if the parent object goes out of scope.
	/// </summary>
	///
	/// <remarks>	Perwass,. </remarks>
	///
	/// <returns>	null if it fails, else the nested. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	CIException CIException::GetNested() const
	{
		if (!IsValid())
			return CIException();
		
		CIException xEx;
		*xEx.m_pImpl = REF->Nested();

		return xEx;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Gets the first exception thrown in the nested list. You MUST NOT store this pointer for later
	/// use, as it may become invalid if the parent object goes out of scope.
	/// </summary>
	///
	/// <remarks>	Perwass,. </remarks>
	///
	/// <returns>	null if it fails, else the first. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	CIException CIException::GetFirst() const
	{
		if (!IsValid())
			return CIException();

		CIException xEx;
		*xEx.m_pImpl = REF.GetFirst();

		return xEx;
	}

	CIString CIException::ToString() const
	{
		if (!IsValid())
			return CIString();

		return CIString(REF->ToString().c_str());
	}

	CIString CIException::ToStringComplete() const
	{
		if (!IsValid())
			return CIString();

		return CIString(REF.ToStringComplete().c_str());
	}

} // namespace Clu
