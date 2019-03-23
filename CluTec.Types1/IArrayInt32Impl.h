////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      IArrayInt32Impl.h
//
// summary:   Declares the IArrayInt32Impl interface
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

	using TArray = CArrayIntern<int32_t>;

	class CIArrayInt32Impl : public CReference<TArray>
	{
	public:
		CIArrayInt32Impl() : CReference()
		{}

		CIArrayInt32Impl(CIArrayInt32Impl&& xImpl)
			: CReference(xImpl)
		{}

		CIArrayInt32Impl& operator= (CIArrayInt32Impl&& xImpl)
		{
			CReference::operator=(xImpl);
			return *this;
		}

		CIArrayInt32Impl(const CIArrayInt32Impl& xImpl)
			: CReference(xImpl)
		{}

		CIArrayInt32Impl& operator= (const CIArrayInt32Impl& xImpl)
		{
			CReference::operator=(xImpl);
			return *this;
		}

		~CIArrayInt32Impl()
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
