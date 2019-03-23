////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.System
// file:      FileInfo.h
//
// summary:   Declares the file information class
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

#include <string>
#include <regex>
#include <map>
#include "CluTec.Types1/IString.h"

namespace Clu
{
	enum class ELocationType
	{
		Unknown = 0,
		LocalDrive,
		NetDrive,
	};

	class CFileInfo
	{
	public:
		using TLocMap = std::map<Clu::ELocationType, std::regex>;

	private:

	protected:

		/// \brief The complete path to the file including the filename and extension. You can pass this to a function to open the file.
		std::string m_sFullPath;

		/// \brief The location is either the drive followed with a ':' or the network location, i.e. the first entry after "\\".
		std::string m_sLocation;

		/// \brief This is the directory with the location but without the filename.
		std::string m_sDirectory;

		/// \brief The filename without path but with extension.
		std::string m_sFilename;

		/// \brief The name of the file without path and extension.
		std::string m_sName;

		/// \brief The file extension including the '.'.
		std::string m_sExt;


		ELocationType m_eLocationType;

	public:
		CFileInfo()
		{
			Clear();
		}

		explicit CFileInfo(const std::string& sFilePath)
		{
			SetFilePath(sFilePath);
		}

		explicit CFileInfo(const Clu::CIString& sFilePath)
		{
			SetFilePath(sFilePath.ToCString());
		}

		explicit CFileInfo(const char* pcFilePath)
		{
			SetFilePath(pcFilePath);
		}

		void Clear()
		{
			m_sFullPath.clear();
			m_sLocation.clear();
			m_sDirectory.clear();
			m_sFilename.clear();
			m_sName.clear();
			m_sExt.clear();
			m_eLocationType = ELocationType::Unknown;
		}

		ELocationType GetLocationType()
		{
			return m_eLocationType;
		}

		std::string GetFullPath()
		{
			return m_sFullPath;
		}

		std::string GetLocation()
		{
			return m_sLocation;
		}

		std::string GetDirectory()
		{
			return m_sDirectory;
		}

		std::string GetFilename()
		{
			return m_sFilename;
		}

		std::string GetName()
		{
			return m_sName;
		}

		std::string GetExt()
		{
			return m_sExt;
		}

		void SetFilePath(const std::string& sFilePath);

		bool Exists();
	};

}