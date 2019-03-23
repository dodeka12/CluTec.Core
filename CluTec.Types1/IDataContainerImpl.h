////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      IDataContainerImpl.h
//
// summary:   Declares the IDataContainerImpl interface
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

namespace Clu
{

	class CDataContainer;


	class CIDataContainerImpl : public CReference<CDataContainer>
	{
	public:
		CIDataContainerImpl() : CReference()
		{}

		CIDataContainerImpl(CIDataContainerImpl&& xImpl)
			: CReference(xImpl)
		{}

		CIDataContainerImpl& operator= (CIDataContainerImpl&& xImpl)
		{
			CReference::operator=(xImpl);
			return *this;
		}

		CIDataContainerImpl(const CIDataContainerImpl& xImpl)
			: CReference(xImpl)
		{}

		CIDataContainerImpl& operator= (const CIDataContainerImpl& xImpl)
		{
			CReference::operator=(xImpl);
			return *this;
		}

		~CIDataContainerImpl()
		{}

		void New()
		{
			CReference::operator=(CReference<CDataContainer>::New());
		}

		void New(const CDataContainer& xImg)
		{
			CReference::operator=(CReference<CDataContainer>::New(xImg));
		}
	};


}
