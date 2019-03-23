////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Base
// file:      Exception.h
//
// summary:   Declares the exception class
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

#include <exception>
#include <string>
#include <sstream>
#include <memory>
#include <vector>

#include "CluTec.Types1/IException.h"

#include "Defines.h"
#include "Conversion.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief A macro that defines a clu exception with the current source filename, function name and source line.
///
/// \param	theMsg Message describing the actual exception.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef CLU_EXCEPTION
#	undef CLU_EXCEPTION
#endif

#define CLU_EXCEPTION(theMsg) \
	Clu::CreateException(theMsg, __FILE__, __FUNCTION__, __LINE__)

#define CLU_EXCEPT_TYPE(theType, theMsg) \
	Clu::CreateException(Clu::ExceptionType::theType(), theMsg, __FILE__, __FUNCTION__, __LINE__)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief A macro that defines a nested clu exception. Creates an exception with the current source filename, function name and source line
/// 	   and adds the given exception as inner exception to this exception.
///
/// \param	theMsg Message describing the exception.
/// \param	theEx  The nested or inner exception.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define CLU_EXCEPTION_NEST(theMsg, theEx) \
	Clu::CreateException(theMsg, __FILE__, __FUNCTION__, __LINE__, theEx)


#define CLU_EXCEPT_TYPE_NEST(theType, theMsg, theEx) \
	Clu::CreateException(Clu::ExceptionType::theType(), theMsg, __FILE__, __FUNCTION__, __LINE__, theEx)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Catch std::exception and Clu::CIException and rethrow both as Clu::CIException. </summary>
///
/// <param name="theMsg">	Message describing the. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

#define CLU_CATCH_RETHROW_ALL(theMsg) \
	catch (std::exception& xEx) \
	{ \
		throw CLU_EXCEPTION_NEST(theMsg, xEx); \
	} \
	catch (Clu::CIException& xEx) \
	{ \
		throw CLU_EXCEPTION_NEST(theMsg, std::move(xEx)); \
	} 

namespace Clu
{
	
	template<typename T1, typename T2, typename T3>
	inline CIException CreateException(const T1& xMsg, const T2& xFile, const T3& xFunc, const int & iLine)
	{
		return CIException(ToIString(xMsg), ToIString(xFile), ToIString(xFunc), iLine);
	}

	template<typename T1, typename T2, typename T3>
	inline CIException CreateException(const T1& xMsg, const T2& xFile, const T3& xFunc, const int & iLine, CIException&& xEx)
	{
		return CIException(ToIString(xMsg), ToIString(xFile), ToIString(xFunc), iLine, std::forward<CIException>(xEx));
	}


	template<typename T1, typename T2, typename T3>
	inline CIException CreateException(const Clu::ExceptionType::Unknown& xType, const T1& xMsg, const T2& xFile, const T3& xFunc, const int & iLine)
	{
		return CIException(xType, ToIString(xMsg), ToIString(xFile), ToIString(xFunc), iLine);
	}

	template<typename T1, typename T2, typename T3>
	inline CIException CreateException(const Clu::ExceptionType::Unknown& xType, const T1& xMsg, const T2& xFile, const T3& xFunc, const int & iLine, CIException&& xEx)
	{
		return CIException(xType, ToIString(xMsg), ToIString(xFile), ToIString(xFunc), iLine, std::forward<CIException>(xEx));
	}


	template<typename T1, typename T2, typename T3>
	inline CIException CreateException(const T1& xMsg, const T2& xFile, const T3& xFunc, const int & iLine, const std::exception &xEx)
	{
		Clu::CIString sMsg = ToIString(xMsg);
		if (sMsg.Length() > 0)
		{
			sMsg += " : ";
		}
		sMsg += xEx.what();

		return CIException(sMsg, ToIString(xFile), ToIString(xFunc), iLine);
	}


} // namespace Clu

