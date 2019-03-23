////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Base
// file:      Conversion.cpp
//
// summary:   Implements the conversion class
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

#include <string>

#include "Conversion.h"

namespace Clu
{

		std::string ToStdString(const char* pcText)
		{
			return std::string(pcText);
		}

		std::string ToStdString(const std::string& sText)
		{
			return sText;
		}

		std::string ToStdString(const std::stringstream& sxText)
		{
			return sxText.str();
		}

		std::string ToStdString(const std::ostringstream& sxText)
		{
			return sxText.str();
		}

		std::string ToStdString(const std::basic_ostream<char>& sxText)
		{
			std::stringstream sxA;
			sxA << sxText.rdbuf();
			return sxA.str();
		}

		std::string ToStdString(const Clu::CIString& sText)
		{
			return std::string(sText.ToCString());
		}



		Clu::CIString ToIString(const char* pcText)
		{
			return Clu::CIString(pcText);
		}

		Clu::CIString ToIString(const std::string& sText)
		{
			return Clu::CIString(sText.c_str());
		}

		Clu::CIString ToIString(const std::stringstream& sxText)
		{
			return Clu::CIString(sxText.str().c_str());
		}

		Clu::CIString ToIString(const std::ostringstream& sxText)
		{
			return Clu::CIString(sxText.str().c_str());
		}

		Clu::CIString ToIString(const std::basic_ostream<char>& sxText)
		{
			std::stringstream sxA;
			sxA << sxText.rdbuf();
			return Clu::CIString(sxA.str().c_str());
		}

		Clu::CIString ToIString(const Clu::CIString& sText)
		{
			return sText;
		}


		template<>
		int ToNumber<int>(const std::string& sText)
		{
			return std::stoi(sText);
		}

		template<>
		unsigned int ToNumber<unsigned int>(const std::string& sText)
		{
			return (unsigned int) std::stol(sText);
		}


		template<>
		long ToNumber<long>(const std::string& sText)
		{
			return std::stol(sText);
		}

		template<>
		unsigned long ToNumber<unsigned long>(const std::string& sText)
		{
			return std::stoul(sText);
		}

		template<>
		long long ToNumber<long long>(const std::string& sText)
		{
			return std::stoll(sText);
		}

		template<>
		unsigned long long ToNumber<unsigned long long>(const std::string& sText)
		{
			return std::stoull(sText);
		}

		template<>
		float ToNumber<float>(const std::string& sText)
		{
			return std::stof(sText);
		}

		template<>
		double ToNumber<double>(const std::string& sText)
		{
			return std::stod(sText);
		}

		template<>
		long double ToNumber<long double>(const std::string& sText)
		{
			return std::stold(sText);
		}


		template<>
		int ToNumber<int>(const std::string& sText, size_t &nRetIdx)
		{
			return std::stoi(sText, &nRetIdx);
		}

		template<>
		unsigned int ToNumber<unsigned int>(const std::string& sText, size_t &nRetIdx)
		{
			return (unsigned int) std::stol(sText, &nRetIdx);
		}


		template<>
		long ToNumber<long>(const std::string& sText, size_t &nRetIdx)
		{
			return std::stol(sText, &nRetIdx);
		}

		template<>
		unsigned long ToNumber<unsigned long>(const std::string& sText, size_t &nRetIdx)
		{
			return std::stoul(sText, &nRetIdx);
		}

		template<>
		long long ToNumber<long long>(const std::string& sText, size_t &nRetIdx)
		{
			return std::stoll(sText, &nRetIdx);
		}

		template<>
		unsigned long long ToNumber<unsigned long long>(const std::string& sText, size_t &nRetIdx)
		{
			return std::stoull(sText, &nRetIdx);
		}

		template<>
		float ToNumber<float>(const std::string& sText, size_t &nRetIdx)
		{
			return std::stof(sText, &nRetIdx);
		}

		template<>
		double ToNumber<double>(const std::string& sText, size_t &nRetIdx)
		{
			return std::stod(sText, &nRetIdx);
		}

		template<>
		long double ToNumber<long double>(const std::string& sText, size_t &nRetIdx)
		{
			return std::stold(sText, &nRetIdx);
		}

		//template std::vector<float> ToNumberList<float>(const std::string& _sText);


} // namespace Clu