////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.System.Test
// file:      FileInfoTest1.cpp
//
// summary:   Implements the file information test 1 class
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
#include "CluTec.System/FileInfo.h"

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CluTecCoreTest
{
	TEST_CLASS(FileInfoTest1)
	{
	public:

		TEST_METHOD(FileInfo_LocalDrive_01)
		{
			std::string sDrive("C:\\");
			std::string sPath("First\\Second\\");
			std::string sName("File.name");
			std::string sExt(".ext");
			std::string sFilePath = sDrive + sPath + sName + sExt;

			Clu::CFileInfo xFileInfo(sFilePath);

			Assert::IsTrue(xFileInfo.GetLocationType() == Clu::ELocationType::LocalDrive, L"Location is the local drive");

			std::stringstream sxText;

			sxText
				<< "Drive:     " << xFileInfo.GetLocation() << std::endl
				<< "Directory: " << xFileInfo.GetDirectory() << std::endl
				<< "Name:      " << xFileInfo.GetName() << std::endl
				<< "Extension: " << xFileInfo.GetExt() << std::endl
				<< "Filename:  " << xFileInfo.GetFilename() << std::endl;

			Logger::WriteMessage(sxText.str().c_str());

			Assert::IsTrue(xFileInfo.GetLocation() == sDrive, L"Drive matches");
			Assert::IsTrue(xFileInfo.GetDirectory() == sDrive + sPath, L"Directory matches");
			Assert::IsTrue(xFileInfo.GetName() == sName, L"Name of file matches");
			Assert::IsTrue(xFileInfo.GetExt() == sExt, L"Extension matches");

		}

		TEST_METHOD(FileInfo_LocalDrive_02)
		{
			std::string sDrive("C:\\");
			std::string sPath("First\\..\\Second\\");
			std::string sFilename("File.name");
			std::string sExt(".ext");
			std::string sFilePath = sDrive + sPath + sFilename + sExt;

			Clu::CFileInfo xFileInfo(sFilePath);

			Assert::IsTrue(xFileInfo.GetLocationType() == Clu::ELocationType::LocalDrive, L"Location is the local drive");

			std::stringstream sxText;

			sxText
				<< "Drive:     " << xFileInfo.GetLocation() << std::endl
				<< "Directory: " << xFileInfo.GetDirectory() << std::endl
				<< "Name:      " << xFileInfo.GetName() << std::endl
				<< "Extension: " << xFileInfo.GetExt() << std::endl
				<< "Filename:  " << xFileInfo.GetFilename() << std::endl;

			Logger::WriteMessage(sxText.str().c_str());

			Assert::IsTrue(xFileInfo.GetLocation() == sDrive, L"Drive matches");
			Assert::IsTrue(xFileInfo.GetDirectory() == sDrive + "Second\\", L"Path matches");
			Assert::IsTrue(xFileInfo.GetName() == sFilename, L"Filename matches");
			Assert::IsTrue(xFileInfo.GetExt() == sExt, L"Extension matches");

		}



		TEST_METHOD(FileInfo_NetPath_01)
		{
			try
			{

				Clu::CFileInfo xFileInfo(R"(\\Disk1\First\Second\File.name.ext)");

				Assert::IsTrue(xFileInfo.GetLocationType() == Clu::ELocationType::NetDrive, L"Location is a network drive");

				std::stringstream sxText;

				sxText
					<< "Drive:     " << xFileInfo.GetLocation() << std::endl
					<< "Directory: " << xFileInfo.GetDirectory() << std::endl
					<< "Name:      " << xFileInfo.GetName() << std::endl
					<< "Extension: " << xFileInfo.GetExt() << std::endl
					<< "Filename:  " << xFileInfo.GetFilename() << std::endl;

				Logger::WriteMessage(sxText.str().c_str());
			}
			catch (std::exception& xEx)
			{
				Logger::WriteMessage(xEx.what());
				Assert::IsTrue(false);
			}
		}


	};
}