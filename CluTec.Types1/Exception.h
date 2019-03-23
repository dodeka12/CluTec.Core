////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      Exception.h
//
// summary:   Declares the exception class
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

#include "ExceptionTypes.h"
#include "Reference.h"
#include <string>
#include <vector>

namespace Clu
{
	class CException;


	class CIExceptionImpl : public CReference<CException>
	{
	public:
		CIExceptionImpl() : CReference()
		{}

		CIExceptionImpl(CIExceptionImpl&& xImpl)
			: CReference(xImpl)
		{}

		CIExceptionImpl& operator= (CIExceptionImpl&& xImpl)
		{
			CReference::operator=(xImpl);
			return *this;
		}

		CIExceptionImpl(const CIExceptionImpl& xImpl)
			: CReference(xImpl)
		{}

		CIExceptionImpl& operator= (const CIExceptionImpl& xImpl)
		{
			CReference::operator=(xImpl);
			return *this;
		}

		~CIExceptionImpl()
		{}

		void New()
		{
			CReference::operator=(CReference<CException>::New());
		}

		CIExceptionImpl GetFirst() const;
		std::vector<std::string> ToStringList() const;
		std::string ToStringComplete() const;
	};


	class CException
	{
	protected:
		ExceptionType::Unknown m_xType;

		std::string m_sMsg;
		std::string m_sFile;
		std::string m_sFunc;
		int m_iLine;

		CIExceptionImpl m_refNestedException;

	public:
		CException()
		{	
			m_xType = ExceptionType::Standard();
		}


		ExceptionType::Unknown& Type()
		{
			return m_xType;
		}

		std::string& Message()
		{
			return m_sMsg;
		}

		std::string& File()
		{
			return m_sFile;
		}

		std::string& Function()
		{
			return m_sFunc;
		}

		int& Line()
		{
			return m_iLine;
		}

		CIExceptionImpl& Nested()
		{
			return m_refNestedException;
		}

		std::string ToString() const;
	};


}