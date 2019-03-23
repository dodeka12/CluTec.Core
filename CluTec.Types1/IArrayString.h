////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      IArrayString.h
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

#pragma once


#ifdef CLU_INTEROP_EXPORTS
#define CLU_TYPES1_API __declspec(dllexport)
#else
#define CLU_TYPES1_API __declspec(dllimport)
#endif

#include "IString.h"

namespace Clu
{
	class CIArrayStringImpl;

	class CLU_TYPES1_API CIArrayString
	{
	public:
		using TValue = Clu::CIString;

	private:
		CIArrayStringImpl *m_pImpl;

	public:
		CIArrayString();
		CIArrayString(CIArrayString&& xImage);
		CIArrayString(const CIArrayString& xImage);

		CIArrayString(size_t nElementCount);
		CIArrayString(size_t nElementCount, const TValue *pData);

		~CIArrayString();

		CIArrayString& operator= (CIArrayString&& xImage);
		CIArrayString& operator= (const CIArrayString& xImage);

		bool IsValidRef() const;
		bool IsValid() const;


		CIArrayString Copy() const;

		void Create(size_t nElementCount);
		void Create(size_t nElementCount, const TValue *pData);

		void Resize(size_t nElementCount);

		void Destroy();
		void Release();

		void PushBack(const TValue& xValue);

		TValue& operator[] (size_t nIdx);
		const TValue& operator[] (size_t nIdx) const;

		size_t ElementCount() const;

		TValue* DataPointer();
		const TValue* DataPointer() const;
	};

} // namespace Clu

#pragma make_public(Clu::CIArrayString)
