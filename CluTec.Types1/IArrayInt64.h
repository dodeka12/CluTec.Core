////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      IArrayInt64.h
//
// summary:   Declares the IArrayInt64 interface
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
	class CIArrayInt64Impl;

	class CLU_TYPES1_API CIArrayInt64
	{
	public:
		using TValue = int64_t;

	private:
		CIArrayInt64Impl *m_pImpl;

	public:
		CIArrayInt64();
		CIArrayInt64(CIArrayInt64&& xImage);
		CIArrayInt64(const CIArrayInt64& xImage);

		CIArrayInt64(size_t nElementCount);
		CIArrayInt64(size_t nElementCount, const TValue *pData);

		~CIArrayInt64();

		CIArrayInt64& operator= (CIArrayInt64&& xImage);
		CIArrayInt64& operator= (const CIArrayInt64& xImage);

		bool IsValidRef() const;
		bool IsValid() const;


		CIArrayInt64 Copy() const;

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

#pragma make_public(Clu::CIArrayInt64)
