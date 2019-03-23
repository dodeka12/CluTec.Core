////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Net.Base
// file:      Converter.h
//
// summary:   Declares the converter class
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

#pragma managed (push, off)
#include <utility>
#include <vector>
#include "CluTec.Types1/IString.h"
#include "CluTec.Types1/IException.h"
#pragma managed (pop)

#include "CluException.h"
#include "CluExceptionTypes.h"

using namespace System;

namespace Clu 
{
	namespace Net
	{
		public ref class Converter
		{
		public:
			static System::String^ ToString(const char* sValue)
			{
				return gcnew System::String(sValue);
			}

			static System::String^ ToString(const Clu::CIString& sValue)
			{
				return gcnew System::String(sValue.ToCString());
			}

			static Clu::CIString ToIString(System::String^ sValue)
			{
				try
				{
					// Get pointer from System::String^
					const char* pcChars = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sValue)).ToPointer();

					// Copy data to CIString
					CIString sResult(pcChars);

					// Free pointer
					System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void*)pcChars));

					return sResult;
				}
				catch (System::Exception^ Ex)
				{
					throw gcnew System::Exception("Error converting to CIString", Ex);
				}
			}

			static System::Guid ToGuid(const Clu::CGuid xGuid)
			{
				System::Guid xSysGuid;
				
				xSysGuid.Parse(ToString(xGuid.ToString()));
				return xSysGuid;
			}

			static Clu::Net::ExceptionType::Unknown^ ToExceptionType(const Clu::ExceptionType::Unknown& xType)
			{
				System::String^ sGuid = ToString(xType.GetGuid().ToString());
				System::String^ sSysId = Clu::Net::ExceptionType::Standard::StaticTypeId.ToString();

				
				if (sGuid->Equals(sSysId, System::StringComparison::CurrentCultureIgnoreCase))
				{
					return gcnew Clu::Net::ExceptionType::Standard();
				}

				sSysId = Clu::Net::ExceptionType::OutOfMemory::StaticTypeId.ToString();
				if (sGuid->Equals(sSysId, System::StringComparison::CurrentCultureIgnoreCase))
				{
					return gcnew Clu::Net::ExceptionType::OutOfMemory();
				}

				sSysId = Clu::Net::ExceptionType::RuntimeError::StaticTypeId.ToString();
				if (sGuid->Equals(sSysId, System::StringComparison::CurrentCultureIgnoreCase))
				{
					return gcnew Clu::Net::ExceptionType::RuntimeError();
				}

				return gcnew Clu::Net::ExceptionType::Unknown(ToGuid(xType.GetGuid()), ToString(xType.GetTypeName()));
			}



			static Clu::Net::CluException^ ToException(Clu::CIException& xEx)
			{
				Clu::CIException xLoopEx(std::move(xEx));
				std::vector<Clu::CIException> vecEx;

				// Get flat list of whole exception tree
				do 
				{
					vecEx.push_back(xLoopEx);
					xLoopEx = xLoopEx.GetNested();
				} while (xLoopEx.IsValid());

				System::String^ sMessage = ToString(vecEx.back().GetText());
				System::String^ sFunc = ToString(vecEx.back().GetFunc());
				System::String^ sFile = ToString(vecEx.back().GetFile());
				int iLine = vecEx.back().GetLine();

				Clu::Net::ExceptionType::Unknown^ xType = ToExceptionType(vecEx.back().GetType());

				Clu::Net::CluException^ xCluEx = gcnew Clu::Net::CluException(xType, sMessage, sFile, sFunc, iLine);

				auto itEx = vecEx.rbegin();
				auto itEnd = vecEx.rend();
				// Start at second from back and reverse iterate
				for (++itEx; itEx != itEnd; ++itEx)
				{
					sMessage = ToString(itEx->GetText());
					sFunc = ToString(itEx->GetFunc());
					sFile = ToString(itEx->GetFile());
					int iLine = itEx->GetLine();

					Clu::Net::ExceptionType::Unknown^ xType = ToExceptionType(itEx->GetType());

					xCluEx = gcnew Clu::Net::CluException(xType, sMessage, sFile, sFunc, iLine, xCluEx);
				}

				return xCluEx;
			}
		};

	} // namespace Net
} // namespace Clu

