////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      IArrayStringImpl.h
//
// summary:   Declares the IArrayStringImpl interface
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
#include "IString.h"

namespace Clu
{

	using TArray = CArrayIntern<Clu::CIString>;

	class CIArrayStringImpl : public CReference<TArray>
	{
	public:
		CIArrayStringImpl() : CReference()
		{}

		CIArrayStringImpl(CIArrayStringImpl&& xImpl)
			: CReference(xImpl)
		{}

		CIArrayStringImpl& operator= (CIArrayStringImpl&& xImpl)
		{
			CReference::operator=(xImpl);
			return *this;
		}

		CIArrayStringImpl(const CIArrayStringImpl& xImpl)
			: CReference(xImpl)
		{}

		CIArrayStringImpl& operator= (const CIArrayStringImpl& xImpl)
		{
			CReference::operator=(xImpl);
			return *this;
		}

		~CIArrayStringImpl()
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
