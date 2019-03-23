////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Base.Test
// file:      ExceptionTest1.cpp
//
// summary:   Implements the exception test 1 class
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
#include "CppUnitTest.h"

#include <exception>
#include <stdexcept>
#include <iostream>

#include "CluTec.Base/Exception.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CluTecCoreTest
{
	TEST_CLASS(ExceptionTest1)
	{
	public:

		TEST_METHOD(Exception_01)
		{
			try
			{
				throw CLU_EXCEPTION("Hello World");
			}
			catch (Clu::CIException& xEx)
			{
				Clu::CIString sEx(xEx.ToString());

				Logger::WriteMessage(sEx.ToCString());
				Assert::IsFalse(xEx.HasNested());

			}
		}

		TEST_METHOD(Exception_02)
		{
			try
			{
				try
				{
					throw CLU_EXCEPTION("First");
				}
				catch (Clu::CIException& xEx)
				{
					Clu::CIString sEx(xEx.ToString());
					sEx += "\n";
					Logger::WriteMessage(sEx.ToCString());
					throw CLU_EXCEPTION_NEST("Second", std::move(xEx));
				}
			}
			catch (Clu::CIException& xEx)
			{
				Logger::WriteMessage(xEx.ToStringComplete().ToCString());

				Assert::IsTrue(xEx.HasNested(), L"Has inner exception");
			}
		}

		TEST_METHOD(Exception_03)
		{
			Clu::CIException xInnermost;

			try
			{
				try
				{
					try
					{
						throw CLU_EXCEPTION("First");
					}
					catch (Clu::CIException& xEx)
					{
						throw CLU_EXCEPTION_NEST("Second", std::move(xEx));
					}
				}
				catch (Clu::CIException& xEx)
				{
					Assert::IsTrue(xEx.HasNested(), L"Has inner exception");
					throw CLU_EXCEPTION_NEST("Third", std::move(xEx));
				}
			}
			catch (Clu::CIException& xEx)
			{
				Logger::WriteMessage(xEx.ToStringComplete().ToCString());
				Assert::IsTrue(xEx.HasNested(), L"Has inner exception");

				
				Assert::IsTrue(xEx.GetNested().HasNested(), L"Inner has inner exception");

				Logger::WriteMessage("\n\n");
				Clu::CIString sText = "Innermost: ";
				xInnermost = xEx.GetFirst();
				
				Assert::IsFalse(xInnermost.HasNested(), L"Innermost has no inner exception");

				sText += xInnermost.ToString();
				sText += "\n";
				Logger::WriteMessage(sText.ToCString());
			}

			Assert::IsTrue(xInnermost.IsValid(), L"Innermost exception still valid");

			Clu::CIString sText = "\n\n";
			sText += "Innermost stored: ";
			sText += xInnermost.ToStringComplete();
			Logger::WriteMessage(sText.ToCString());
		}

		TEST_METHOD(Exception_04)
		{
			Clu::CIException xInnermost;

			try
			{
				try
				{
					try
					{
						throw CLU_EXCEPT_TYPE(OutOfMemory, "First");
					}
					catch (Clu::CIException& xEx)
					{
						throw CLU_EXCEPT_TYPE_NEST(RuntimeError, "Second", std::move(xEx));
					}
				}
				catch (Clu::CIException& xEx)
				{
					throw CLU_EXCEPT_TYPE_NEST(Standard, "Third", std::move(xEx));
				}
			}
			catch (Clu::CIException& xEx)
			{
				Clu::CIException xEx2(std::move(xEx));

				Assert::IsFalse(xEx.IsValid(), L"xEx instance is invalidated by move");

				while (xEx2.HasNested())
				{
					Clu::CIString sMsg = xEx2.ToString();
					sMsg += "\n";

					Logger::WriteMessage(sMsg.ToCString());
					xEx2 = xEx2.GetNested();
				}
			}
		}



	};
}