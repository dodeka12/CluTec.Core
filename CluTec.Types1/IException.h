////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      IException.h
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

#pragma once

#ifdef CLU_INTEROP_EXPORTS
#define CLU_TYPES1_API __declspec(dllexport)
#else
#define CLU_TYPES1_API __declspec(dllimport)
#endif

#include "ExceptionTypes.h"


namespace Clu
{
	class CLU_TYPES1_API CGuid;
	class CLU_TYPES1_API CIString;
	class CLU_TYPES1_API CIExceptionPtr;

	class CIExceptionImpl;

	class CLU_TYPES1_API CIException
	{
	protected:

		CIExceptionImpl* m_pImpl;

		void _SetData(const CIString& sMsg, const CIString& sFile, const CIString& sFunc, const int & iLine);
		void _SetData(const ExceptionType::Unknown& xType, const CIString& sMsg, const CIString& sFile, const CIString& sFunc, const int & iLine);

	public:
		CIException();
		CIException(CIException&& xEx);
		CIException(const CIException& xEx);

		CIException(const CIString& xMsg, const CIString& xFile, const CIString& xFunc, int iLine);
		CIException(const CIString& xMsg, const CIString& xFile, const CIString& xFunc, int iLine, CIException&& xEx);

		CIException(const ExceptionType::Unknown& xType, const CIString& xMsg, const CIString& xFile, const CIString& xFunc, int iLine);
		CIException(const ExceptionType::Unknown& xType, const CIString& xMsg, const CIString& xFile, const CIString& xFunc, int iLine, CIException&& xEx);

		~CIException();

		CIException& operator= (CIException&& xEx);
		CIException& operator= (const CIException& xEx);
		
		Clu::ExceptionType::Unknown GetType() const;
		CGuid GetTypeGuid() const;
		CIString GetTypeName() const;

		CIString GetText() const;
		CIString GetFile() const;
		CIString GetFunc() const;
		int GetLine() const;

		bool IsValid() const;
		bool HasNested() const;

		template<typename T>
		bool IsOfType()
		{
			return GetTypeGuid() == T::Guid;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Gets the nested exception if there is one or a null pointer. 
		/// </summary>
		///
		/// <remarks>	Perwass,. </remarks>
		///
		/// <returns>	null if it fails, else the nested. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		CIException GetNested() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Gets the first exception thrown in the nested list. 
		/// </summary>
		///
		/// <remarks>	Perwass,. </remarks>
		///
		/// <returns>	null if it fails, else the first. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		CIException GetFirst() const;

		CIString ToString() const;
		CIString ToStringComplete() const;

	};

}

#pragma make_public(Clu::CIException)