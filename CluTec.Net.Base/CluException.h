////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Net.Base
// file:      CluException.h
//
// summary:   Declares the clu exception class
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

#include "CluExceptionTypes.h"

namespace Clu
{
	namespace Net
	{

		public ref class CluException : public System::Exception
		{
		private:
			Clu::Net::ExceptionType::Unknown^ m_xType;

			System::String^ m_sFile;
			System::String^ m_sFunc;
			int m_iLine;

		public:
			CluException()
			{
				m_xType = gcnew Clu::Net::ExceptionType::Standard();
				m_sFile = "";
				m_sFunc = "";
				m_iLine = -1;
			}

			CluException(System::String^ sMessage, System::String^ sFile, System::String^ sFunc, int iLine)
				: System::Exception(sMessage)
			{
				m_xType = gcnew Clu::Net::ExceptionType::Standard();

				m_sFile = sFile;
				m_sFunc = sFunc;
				m_iLine = iLine;
			}

			CluException(Clu::Net::ExceptionType::Unknown^ xType, System::String^ sMessage, System::String^ sFile, System::String^ sFunc, int iLine)
				: System::Exception(sMessage)
			{
				m_xType = xType;

				m_sFile = sFile;
				m_sFunc = sFunc;
				m_iLine = iLine;
			}

			CluException(System::String^ sMessage, System::String^ sFile, System::String^ sFunc, int iLine, System::Exception^ xEx)
				: System::Exception(sMessage, xEx)
			{
				m_xType = gcnew Clu::Net::ExceptionType::Standard();

				m_sFile = sFile;
				m_sFunc = sFunc;
				m_iLine = iLine;
			}

			CluException(Clu::Net::ExceptionType::Unknown^ xType, System::String^ sMessage, System::String^ sFile, System::String^ sFunc, int iLine, System::Exception^ xEx)
				: System::Exception(sMessage, xEx)
			{
				m_xType = xType;

				m_sFile = sFile;
				m_sFunc = sFunc;
				m_iLine = iLine;
			}

		public:
			property Clu::Net::ExceptionType::Unknown^ Type
			{
				Clu::Net::ExceptionType::Unknown^ get()
				{
					return m_xType;
				}
			}

			property System::String^ Filename
			{
				System::String^ get()
				{
					return m_sFile;
				}
			}

			property System::String^ Function
			{
				System::String^ get()
				{
					return m_sFunc;
				}
			}

			property int Line
			{
				int get()
				{
					return m_iLine;
				}
			}

		public:
			System::String^ ToString() override
			{
				return System::String::Format("{0}: {1} in {2} ['{3}' : {4}]", Type->TypeName, Message, Function, Filename, Line);
			}

			System::String^ ToStringComplete()
			{
				System::String^ sText = "";
				CluException^ xEx = this;

				do 
				{
					sText += xEx->ToString() + "\n";
					xEx = dynamic_cast<CluException^>(xEx->InnerException);
				} while (xEx != nullptr);

				return sText;
			}
		};

	} // namespace Net
} // namespace Clu
