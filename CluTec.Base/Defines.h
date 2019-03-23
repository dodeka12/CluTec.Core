////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Base
// file:      Defines.h
//
// summary:   Declares the defines class
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

#include "CluTec.Types1/Defines.h"

#ifdef _DEBUG
#	define CLU_TEST_PROD_OVERFLOW(theValA, theValB) \
					if (Clu::Intrinsics::ProductWillOverflow(theValA, theValB)) \
					{ throw CLU_EXCEPTION("Overflow in product"); }

#	define CLU_TEST_SUM_OVERFLOW(theValA, theValB) \
					if (Clu::Intrinsics::SumWillOverflow(theValA, theValB)) \
					{ throw CLU_EXCEPTION("Sum overflow"); }

#else
#	define CLU_TEST_PROD_OVERFLOW(theValA, theValB) __noop
#	define CLU_TEST_SUM_OVERFLOW(theValA, theValB) __noop
#endif


