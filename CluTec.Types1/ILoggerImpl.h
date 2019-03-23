////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      ILoggerImpl.h
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

#pragma once

#include <chrono>
#include <thread>
#include <mutex>
#include <map>
#include "IString.h"

namespace Clu
{
	class CILoggerImpl
	{
	public:
		using TClock = std::chrono::steady_clock;
		using TTime = TClock::time_point;
		using TDuration = TClock::duration;
		using TMutex = std::recursive_mutex;
		using TLockGuard = std::lock_guard<TMutex>;

	protected:
		static unsigned sm_uThreadCount;
		std::map<std::thread::id, TTime> m_mapTime;
		std::map<std::thread::id, unsigned> m_mapLogId;
		TMutex m_muxLog;

	public:
		CILoggerImpl();
		~CILoggerImpl();

		TTime& GetLastTime(std::thread::id nThreadId);
		unsigned GetLogId(std::thread::id nThreadId);

		void Log(const Clu::CIString& sText, const char* pcFunc, const int iLine);

	};

}
