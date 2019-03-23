////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      ILayerImageImpl.h
//
// summary:   Declares the ILayerImageImpl interface
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

	class CLayerImage;


	class CILayerImageImpl : public CReference<CLayerImage>
	{
	public:
		CILayerImageImpl() : CReference()
		{}

		CILayerImageImpl(CILayerImageImpl&& xImpl)
			: CReference(xImpl)
		{}

		CILayerImageImpl& operator= (CILayerImageImpl&& xImpl)
		{
			CReference::operator=(xImpl);
			return *this;
		}

		CILayerImageImpl(const CILayerImageImpl& xImpl)
			: CReference(xImpl)
		{}

		CILayerImageImpl& operator= (const CILayerImageImpl& xImpl)
		{
			CReference::operator=(xImpl);
			return *this;
		}

		~CILayerImageImpl()
		{}

		void New()
		{
			CReference::operator=(CReference<CLayerImage>::New());
		}

		void New(const CLayerImage& xImg)
		{
			CReference::operator=(CReference<CLayerImage>::New(xImg));
		}
	};


}
