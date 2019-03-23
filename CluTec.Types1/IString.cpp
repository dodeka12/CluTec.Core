////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      IString.cpp
//
// summary:   Declares the IString interface
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
#include "Defines.h"
#include "IException.h"
#include "IString.h"

#include <string>



namespace Clu
{
	struct CIString::SImpl
	{
		std::string sData;
	};


	const size_t CIString::Invalid = std::string::npos;


	CIString::CIString()
	{
		m_pImpl = new SImpl();
	}


	CIString::~CIString()
	{
		delete m_pImpl;
	}


	bool CIString::operator!=(const CIString& xString) const
	{
		if (!IsValid() || !xString.IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		return m_pImpl->sData != xString.m_pImpl->sData;
	}

	bool CIString::operator==(const CIString& xString) const
	{
		if (!IsValid() || !xString.IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		return m_pImpl->sData == xString.m_pImpl->sData;
	}

	CIString::CIString(const char* pcString)
	{
		m_pImpl = new SImpl();
		
		*this = pcString;
	}

	CIString::CIString(const CIString& xString)
	{
		m_pImpl = new SImpl(*xString.m_pImpl);
	}

	CIString::CIString(CIString&& xString)
	{
		m_pImpl = xString.m_pImpl;
		xString.m_pImpl = nullptr;
	}


	bool CIString::IsNullOrEmpty() const
	{
		if (!IsValid())
			return true;

		return m_pImpl->sData.length() == 0;
	}


	size_t CIString::Length() const
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		return m_pImpl->sData.length();
	}


	void CIString::Clear()
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		m_pImpl->sData.clear();
	}


	size_t CIString::Find(const CIString& sWhat, size_t nOffset) const
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		return m_pImpl->sData.find(sWhat.ToCString(), nOffset);
	}

	size_t CIString::FindFromBack(const CIString& sWhat, size_t nOffset) const
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		return m_pImpl->sData.rfind(sWhat.ToCString(), nOffset);
	}

	size_t CIString::FindFirstOf(const CIString& sWhat, size_t nOffset) const
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		return m_pImpl->sData.find_first_of(sWhat.ToCString(), nOffset);
	}

	size_t CIString::FindFirstNotOf(const CIString& sWhat, size_t nOffset) const
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		return m_pImpl->sData.find_first_not_of(sWhat.ToCString(), nOffset);
	}

	size_t CIString::FindLastOf(const CIString& sWhat, size_t nOffset) const
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		return m_pImpl->sData.find_last_of(sWhat.ToCString(), nOffset);
	}

	size_t CIString::FindLastNotOf(const CIString& sWhat, size_t nOffset) const
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		return m_pImpl->sData.find_last_not_of(sWhat.ToCString(), nOffset);
	}


	CIString CIString::SubString(size_t nIdx, size_t nCnt) const
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		return CIString(m_pImpl->sData.substr(nIdx, nCnt).c_str());
	}


	CIString& CIString::Replace(const CIString& _sSearch, const CIString& _sReplace)
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		const std::string& sSearch = _sSearch.m_pImpl->sData;
		const std::string& sReplace = _sReplace.m_pImpl->sData;
		std::string& sData = m_pImpl->sData;

		size_t nIdx = 0;
		size_t nSearchCnt = sSearch.length();
		size_t nReplaceCnt = sReplace.length();

		if (nSearchCnt == nReplaceCnt)
		{
			while ((nIdx = sData.find(sSearch, nIdx)) != std::string::npos)
			{
				sData.replace(nIdx, nReplaceCnt, sReplace);
				nIdx++;
			}
		}
		else if (nSearchCnt > nReplaceCnt)
		{
			size_t nDiff = nSearchCnt - nReplaceCnt;
			while ((nIdx = sData.find(sSearch, nIdx)) != std::string::npos)
			{
				sData.erase(nIdx, nDiff);
				sData.replace(nIdx, nReplaceCnt, sReplace);
				nIdx++;
			}
		}
		else 
		{
			size_t nDiff = nReplaceCnt - nSearchCnt;
			while ((nIdx = sData.find(sSearch, nIdx)) != std::string::npos)
			{
				sData.insert(nIdx, nDiff, ' ');
				sData.replace(nIdx, nReplaceCnt, sReplace);
				nIdx++;
			}
		}

		return *this;
	}



	const char* CIString::ToCString() const
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		return m_pImpl->sData.c_str();
	}

	CIString& CIString::operator= (const char* pcString)
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		if (pcString == nullptr)
		{
			throw CLU_EXCEPTION("Invalid string pointer given");
		}

		m_pImpl->sData = pcString;

		return *this;
	}

	CIString& CIString::operator= (const CIString& xString)
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		m_pImpl->sData = xString.m_pImpl->sData;

		return *this;
	}

	CIString& CIString::operator= (CIString&& xString)
	{
		delete this->m_pImpl;
		m_pImpl = xString.m_pImpl;
		xString.m_pImpl = nullptr;

		return *this;
	}

	CIString& CIString::operator+= (const CIString& xString)
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		m_pImpl->sData += xString.m_pImpl->sData;
		return *this;
	}

	CIString& CIString::operator+= (const char *pcString)
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		m_pImpl->sData += pcString;
		return *this;
	}

	CIString& CIString::operator+= (char xValue)
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		m_pImpl->sData += xValue;
		return *this;
	}

	CIString& CIString::operator+= (int32_t xValue)
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		m_pImpl->sData += std::to_string(xValue);
		return *this;
	}

	CIString& CIString::operator+= (uint32_t xValue)
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		m_pImpl->sData += std::to_string(xValue);
		return *this;
	}

	CIString& CIString::operator+= (int64_t xValue)
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		m_pImpl->sData += std::to_string(xValue);
		return *this;
	}

	CIString& CIString::operator+= (uint64_t xValue)
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		m_pImpl->sData += std::to_string(xValue);
		return *this;
	}


	CIString& CIString::operator+= (float xValue)
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		m_pImpl->sData += std::to_string(xValue);
		return *this;
	}

	CIString& CIString::operator+= (double xValue)
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid string object");
		}

		m_pImpl->sData += std::to_string(xValue);
		return *this;
	}


}

