////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      IArrayInt64Impl.h
//
// summary:   Declares the IArrayInt64Impl interface
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

#include "Reference.h"
#include "ArrayIntern.h"

namespace Clu
{

	using TArray = CArrayIntern<int64_t>;

	class CIArrayInt64Impl : public CReference<TArray>
	{
	public:
		CIArrayInt64Impl() : CReference()
		{}

		CIArrayInt64Impl(CIArrayInt64Impl&& xImpl)
			: CReference(xImpl)
		{}

		CIArrayInt64Impl& operator= (CIArrayInt64Impl&& xImpl)
		{
			CReference::operator=(xImpl);
			return *this;
		}

		CIArrayInt64Impl(const CIArrayInt64Impl& xImpl)
			: CReference(xImpl)
		{}

		CIArrayInt64Impl& operator= (const CIArrayInt64Impl& xImpl)
		{
			CReference::operator=(xImpl);
			return *this;
		}

		~CIArrayInt64Impl()
		{}

		void New()
		{
			CReference::operator=(CReference<TArray>::New());
		}

		void New(const TArray& xImg)
		{
			CReference::operator=(CReference<TArray>::New(xImg));
		}
	};


}
