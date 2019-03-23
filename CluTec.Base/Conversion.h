////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Base
// file:      Conversion.h
//
// summary:   Declares the conversion class
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
#include <sstream>
#include <vector>

#include "CluTec.Types1/IString.h"

namespace Clu
{
		std::string ToStdString(const char* pcText);
		std::string ToStdString(const std::string& sText);
		std::string ToStdString(const std::stringstream& sxText);
		std::string ToStdString(const std::ostringstream& sxText);
		std::string ToStdString(const std::basic_ostream<char>& sxText);
		std::string ToStdString(const Clu::CIString& sText);

		Clu::CIString ToIString(const char* pcText);
		Clu::CIString ToIString(const std::string& sText);
		Clu::CIString ToIString(const std::stringstream& sxText);
		Clu::CIString ToIString(const std::ostringstream& sxText);
		Clu::CIString ToIString(const std::basic_ostream<char>& sxText);
		Clu::CIString ToIString(const Clu::CIString& sText);


		template<typename TValue>
		TValue ToNumber(const std::string& sText);

		template<typename TValue>
		TValue ToNumber(const Clu::CIString& sText)
		{
			return ToNumber<TValue>(ToStdString(sText));
		}

		template<typename TValue>
		TValue ToNumber(const std::string& sText, size_t &nRetIdx);

		template<typename TValue>
		TValue ToNumber(const Clu::CIString& sText, size_t &nRetIdx)
		{
			return ToNumber<TValue>(ToStdString(sText), nRetIdx);
		}

		template<typename TValue>
		std::vector<TValue> ToNumberList(const std::string& _sText)
		{
			size_t nRetIdx = 0;
			std::vector<TValue> vecData;
			std::string sText(_sText);

			TValue xValue;

			try
			{
				xValue = ToNumber<TValue>(sText, nRetIdx);
				vecData.push_back(xValue);
			}
			catch (...)
			{ 
				return vecData;
			}

			while (nRetIdx < sText.length())
			{
				sText = sText.substr(nRetIdx);
				try
				{
					xValue = ToNumber<TValue>(sText, nRetIdx);
					vecData.push_back(xValue);
				}
				catch (...)
				{
					break;
				}
			}

			return vecData;
		}


} // namespace Clu