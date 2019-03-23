////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.System
// file:      FilePath.h
//
// summary:   Declares the file path class
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

#ifdef WIN32
#	define CLU_PATH_SLASH '\\'
#else
#	define CLU_PATH_SLASH '/'
#endif

namespace Clu
{
	class CFilePath
	{
	public:
		static std::string GetCurrentDir();
		static std::string NormalizeSlashes(const std::string& sPath);
		static std::string Normalize(const std::string& sPath);
		static std::string ConcatPaths(const std::string& sPath1, const std::string& sPath2);
		static void AddToPath(std::string& sPath, const std::string& sAdd);

		static std::string MakeAbsolute(const std::string& sRelPath, const std::string& sWorkPath);
		static std::string MakeAbsolute(const std::string& sRelPath);
	};
}