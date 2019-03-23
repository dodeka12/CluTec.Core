////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      ILogger.cpp
//
// summary:   Declares the ILogger interface
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

#include "stdafx.h"

#include <memory>

#include "ILogger.h"
#include "ILoggerImpl.h"
#include "IException.h"


#define IMPL (*m_pImpl)

namespace Clu
{
	std::shared_ptr<CILoggerImpl> s_LoggerRef;


	CILogger::CILogger()
	{
		if (s_LoggerRef.use_count() == 0)
		{
			s_LoggerRef = std::shared_ptr<CILoggerImpl>(new CILoggerImpl());
		}
		m_pImpl = s_LoggerRef.get();
	}


	CILogger::~CILogger()
	{
		m_pImpl = nullptr;
	}

	void CILogger::Log(const Clu::CIString& sText, const char* pcFunc, const int iLine) const
	{
		if (m_pImpl == nullptr)
			throw Clu::CIException("Invalid CILogger instance.", __FILE__, __FUNCTION__, __LINE__);

		((CILoggerImpl*)m_pImpl)->Log(sText, pcFunc, iLine);
	}

}
