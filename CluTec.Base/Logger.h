////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Base
// file:      Logger.h
//
// summary:   Declares the logger class
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

#include "CluTec.Types1/ILogger.h"

#include "Defines.h"
#include "Exception.h"
#include "Conversion.h"

#define CLU_LOG_LOC(theMsg) \
	Clu::CILogger().Log(Clu::ToIString(theMsg), __FUNCTION__, __LINE__)

#define CLU_LOG(theMsg) \
	Clu::CILogger().Log(Clu::ToIString(theMsg))

#define CLU_LOG_DTOR_CATCH_ALL(theClass) \
			catch (std::exception &xEx) \
			{ \
				CLU_LOG_LOC(CLU_S "Exception in " #theClass " destructor: " << xEx.what()); \
			} \
			catch (Clu::CIException& xEx) \
			{ \
			CLU_LOG_LOC(CLU_S "Exception in " #theClass " destructor: " << xEx.ToStringComplete()); \
			} 
