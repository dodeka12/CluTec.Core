////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      Exception.cpp
//
// summary:   Implements the exception class
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
#include "Exception.h"

#include <sstream>

namespace Clu
{

	CIExceptionImpl CIExceptionImpl::GetFirst() const
	{
		CIExceptionImpl refInEx(*this);

		while (refInEx->Nested())
		{
			refInEx = refInEx->Nested();
		}

		return refInEx;
	}



	std::vector<std::string> CIExceptionImpl::ToStringList() const
	{
		std::vector<std::string> vecText;

		CIExceptionImpl refInEx(*this);

		do
		{
			vecText.emplace_back(refInEx->ToString());
			refInEx = refInEx->Nested();
			//
		} while (refInEx);

		return vecText;
	}

	std::string CIExceptionImpl::ToStringComplete() const
	{
		std::vector<std::string> vecText(ToStringList());

		std::string sText;
		int iIndent = 0;

		for (auto sLine : vecText)
		{
			sText.append(iIndent++, '>');
			sText.append(" ");
			sText.append(sLine);
			sText.append("\n");
		}

		return sText;
	}


	std::string CException::ToString() const
	{
		std::stringstream sxText;

		sxText
			<< m_xType.GetTypeName().ToCString() << ": "
			<< m_sMsg << " in "
			<< m_sFunc << " ['"
			<< m_sFile << "' : "
			<< m_iLine << "]";

		return sxText.str();
	}


}