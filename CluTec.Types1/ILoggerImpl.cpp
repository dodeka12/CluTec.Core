////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      ILoggerImpl.cpp
//
// summary:   Declares the ILoggerImpl interface
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
#include "ILoggerImpl.h"

#include "stdio.h"

namespace Clu
{
	unsigned CILoggerImpl::sm_uThreadCount = 0;

	CILoggerImpl::CILoggerImpl()
	{
	}


	CILoggerImpl::~CILoggerImpl()
	{
	}

	CILoggerImpl::TTime& CILoggerImpl::GetLastTime(std::thread::id nThreadId)
	{
		TLockGuard xLock(m_muxLog);
		
		auto itEl = m_mapTime.find(nThreadId);
		if (itEl == m_mapTime.end())
		{
			m_mapTime[nThreadId] = TClock::now();
		}

		return m_mapTime[nThreadId];
	}


	unsigned CILoggerImpl::GetLogId(std::thread::id nThreadId)
	{
		TLockGuard xLock(m_muxLog);

		auto itEl = m_mapLogId.find(nThreadId);
		if (itEl == m_mapLogId.end())
		{
			m_mapLogId[nThreadId] = sm_uThreadCount++;
		}

		return m_mapLogId[nThreadId];
	}


	void CILoggerImpl::Log(const Clu::CIString& sText, const char* pcFunc, const int iLine)
	{
		TLockGuard xLock(m_muxLog);

		auto nThreadId = std::this_thread::get_id();
		TTime &xPrevTime = GetLastTime(nThreadId);
		TTime xTime = TClock::now();
		TDuration xDeltaTime = xTime - xPrevTime;
		xPrevTime = xTime;

		auto xMicro = std::chrono::duration_cast<std::chrono::microseconds>(xDeltaTime);
		auto uSeconds = xMicro.count() / 1000000;
		auto uMilli = (xMicro.count() % 1000000) / 1000;
		auto uMicro = (xMicro.count() % 1000);

		if (pcFunc == nullptr || iLine < 0)
		{
			printf("<%d> [%I64d:%I64d:%I64d] %s\n", GetLogId(nThreadId), uSeconds, uMilli, uMicro, sText.ToCString());
		}
		else
		{
			printf("<%d> [%I64d:%I64d:%I64d] %s (%d): %s\n", GetLogId(nThreadId), uSeconds, uMilli, uMicro, pcFunc, iLine, sText.ToCString());
		}

	}

}
