////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.System
// file:      FileInfo.cpp
//
// summary:   Implements the file information class
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
#include "CluTec.Base/Exception.h"

#include "FileInfo.h"
#include "FilePath.h"

#include <fstream>

namespace Clu
{

	void CFileInfo::SetFilePath(const std::string& sFilePath)
	{
		std::smatch xMatch;

		Clear();


		TLocMap sm_mapLocationRegEx = {
			{ ELocationType::LocalDrive, std::regex(R"((^[[:alpha:]]{1}:\\))") }
			, { ELocationType::NetDrive, std::regex(R"(^(\\\\[[:alnum:]]+\\))") }
		};


		// Set complete File Path
		m_sFullPath = sFilePath;

		// Ensure that the file path is an absolute path
		m_sFullPath = Clu::CFilePath::MakeAbsolute(m_sFullPath);

		// Extract location part from full path
		for (auto xPair : sm_mapLocationRegEx)
		{
			std::regex_search(m_sFullPath, xMatch, xPair.second);
			if (xMatch.size() == 2)
			{
				m_sLocation = xMatch.str();
				m_eLocationType = xPair.first;
				break;
			}
		}

		if (m_eLocationType == ELocationType::Unknown)
		{
			throw CLU_EXCEPTION("Invalid file path");
		}

		// Extract path from complete File Path
		auto nStartIdx = size_t(0); 
		auto nEndIdx = std::string::npos;

		if ((nEndIdx = m_sFullPath.find_last_of(CLU_PATH_SLASH)) != std::string::npos)
		{
			m_sDirectory = m_sFullPath.substr(nStartIdx, nEndIdx - nStartIdx + 1);
		}

		nStartIdx += m_sDirectory.size();
		if (nStartIdx >= m_sFullPath.size())
		{
			throw CLU_EXCEPTION("Given file path does not contain a filename");
		}

		if ((nEndIdx = m_sFullPath.find_last_of('.')) != std::string::npos)
		{
			m_sName = m_sFullPath.substr(nStartIdx, nEndIdx - nStartIdx);
			m_sExt = m_sFullPath.substr(nEndIdx);
		}
		else
		{
			m_sName = m_sFullPath.substr(nStartIdx);
			m_sExt.clear();
		}

		m_sFilename = m_sName + m_sExt;

	}


	bool CFileInfo::Exists()
	{
		std::ifstream fxFile(m_sFullPath);
		return static_cast<bool>(fxFile);
	}


}