////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.System
// file:      FilePathLinux.cpp
//
// summary:   Implements the file path linux class
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

#ifndef WIN32

#include <stdio.h>
#include <unistd.h>

#define GetCWD getcwd


namespace Clu
{
	namespace Path
	{

		std::string NormalizeSlashes(const std::string& sPath)
		{
			std::string sNewPath(sPath);

			// Change to standard slashes for file path
			for (char &cSymbol : sNewPath)
			{
				if (cSymbol == '\\')
				{
					cSymbol = '/';
				}
			}

			return sNewPath;
		}

		std::string GetCurrentDir()
		{
			char pcCurPath[FILENAME_MAX];

			if (GetCWD(pcCurPath, sizeof(pcCurPath)) == nullptr)
			{
				throw CLU_EXCEPTION("Cannot get current working directory");
			}

			return std::string(pcCurPath);
		}

		std::string MakeAbsolute(const std::string& sRelPath, const std::string& sWorkPath)
		{
			throw CLU_EXCEPTION("Not implemented");
		}

		std::string MakeAbsolute(const std::string& sRelPath)
		{
			return MakeAbsolute(sRelPath, GetCurrentDir());
		}

	}
}

#endif // !WIN32