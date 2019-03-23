////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      IString.h
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

#pragma once

#ifdef CLU_INTEROP_EXPORTS
#define CLU_TYPES1_API __declspec(dllexport)
#else
#define CLU_TYPES1_API __declspec(dllimport)
#endif

#include <cstdint>

namespace Clu
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	A string PImpl  </summary>
	///
	/// <remarks>	Perwass,. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class CLU_TYPES1_API CIString
	{
	public:
		static const size_t Invalid;

	private:
		struct SImpl;

		SImpl *m_pImpl;

	public:
		CIString();
		CIString(const char* pcString);
		CIString(const CIString& xString);
		CIString(CIString&& xString);

		~CIString();

		CIString& operator= (const char* pcString);
		CIString& operator= (const CIString& xString);
		CIString& operator= ( CIString&& xString);

		bool operator== (const CIString& xString) const;
		bool operator!= (const CIString& xString) const;

		CIString& operator+= (const CIString& xString);
		CIString& operator+= (const char *pcString);

		CIString& operator+= (char xValue);
		CIString& operator+= (int32_t xValue);
		CIString& operator+= (uint32_t xValue);
		CIString& operator+= (int64_t xValue);
		CIString& operator+= (uint64_t xValue);
		CIString& operator+= (float xValue);
		CIString& operator+= (double xValue);

		CIString& operator<< (const CIString& xString)
		{
			return (*this += xString);
		}

		CIString& operator<< (const char *pcString)
		{
			return (*this += pcString);
		}

		CIString& operator<< (char xValue)
		{
			return (*this += xValue);
		}

		CIString& operator<< (int32_t xValue)
		{
			return (*this += xValue);
		}

		CIString& operator<< (uint32_t xValue)
		{
			return (*this += xValue);
		}

		CIString& operator<< (int64_t xValue)
		{
			return (*this += xValue);
		}

		CIString& operator<< (uint64_t xValue)
		{
			return (*this += xValue);
		}

		CIString& operator<< (float xValue)
		{
			return (*this += xValue);
		}

		CIString& operator<< (double xValue)
		{
			return (*this += xValue);
		}

		CIString operator+ (const CIString& sB) const
		{
			CIString sC(*this);
			sC += sB;
			return sC;
		}

		bool IsValid() const
		{
			return m_pImpl != nullptr;
		}

		bool IsNullOrEmpty() const;

		size_t Length() const;

		void Clear();

		size_t Find(const CIString& sWhat, size_t nOffset = 0) const;
		size_t FindFromBack(const CIString& sWhat, size_t nOffset = 0) const;

		size_t FindFirstOf(const CIString& sWhat, size_t nOffset = 0) const;
		size_t FindFirstNotOf(const CIString& sWhat, size_t nOffset = 0) const;
		size_t FindLastOf(const CIString& sWhat, size_t nOffset = 0) const;
		size_t FindLastNotOf(const CIString& sWhat, size_t nOffset = 0) const;

		CIString SubString(size_t nIdx, size_t nCnt = CIString::Invalid) const;

		CIString& Replace(const CIString& sSearch, const CIString& sReplace);

		const char* ToCString() const;
	};

}

#pragma make_public(Clu::CIString)
