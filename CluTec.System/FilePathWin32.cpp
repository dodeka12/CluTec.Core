////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.System
// file:      FilePathWin32.cpp
//
// summary:   Implements the file path window 32 class
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
#include "FilePath.h"

#ifdef WIN32
#include <stdio.h>
#include <direct.h>

#include "Shlwapi.h"
#include "shlobj.h"

#include "CluTec.Base/Exception.h"

#define GetCWD _getcwd



namespace Clu
{

	std::string CFilePath::NormalizeSlashes(const std::string& sPath)
	{
		std::string sNewPath(sPath);

		// Change to standard slashes for file path
		for (char &cSymbol : sNewPath)
		{
			if (cSymbol == '/')
			{
				cSymbol = '\\';
			}
		}

		return sNewPath;
	}

	std::string CFilePath::GetCurrentDir()
	{
		char pcCurPath[FILENAME_MAX];

		if (GetCWD(pcCurPath, sizeof(pcCurPath)) == nullptr)
		{
			throw CLU_EXCEPTION("Cannot get current working directory");
		}

		return std::string(pcCurPath);
	}

	std::string CFilePath::Normalize(const std::string& sPath)
	{
		std::string sNewPath(NormalizeSlashes(sPath));

		char pcNormPath[_MAX_PATH];

		if (PathCanonicalizeA(pcNormPath, sNewPath.c_str()) == FALSE)
		{
			throw CLU_EXCEPTION("Error normalizing path");
		}

		return std::string(pcNormPath);
	}


	std::string CFilePath::ConcatPaths(const std::string& sPath1, const std::string& sPath2)
	{
		std::string sResult(sPath1);

		CFilePath::AddToPath(sResult, sPath2);

		return sResult;
	}

	void CFilePath::AddToPath(std::string& sPath, const std::string& sAdd)
	{
		if (sPath.back() != '/' && sPath.back() != '\\')
		{
			sPath.push_back('\\');
		}

		sPath += sAdd;
	}

	std::string CFilePath::MakeAbsolute(const std::string& sRelPath, const std::string& sWorkPath)
	{
		std::string sNewPath(NormalizeSlashes(sRelPath));

		if (sNewPath.find(":") == std::string::npos && sNewPath.find("\\\\") != 0)
		{
			std::string sCurWorkPath = sWorkPath;

			if (sCurWorkPath.find_last_of("\\") != sCurWorkPath.length() - 1)
			{
				sCurWorkPath += "\\";
			}

			if (sNewPath.find(".\\") == 0)
			{
				sNewPath = sNewPath.substr(2);
			}
			else if (sNewPath.find("\\") == 0)
			{
				sNewPath = sNewPath.substr(1);
			}

			sNewPath = sCurWorkPath + sNewPath;
		}

		return Normalize(sNewPath);
	}


	std::string CFilePath::MakeAbsolute(const std::string& sRelPath)
	{
		return MakeAbsolute(sRelPath, GetCurrentDir());
	}

}

#endif // if WIN32
