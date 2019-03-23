////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      Guid.cpp
//
// summary:   Implements the unique identifier class
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
#include "Guid.h"

#include <regex>
#include <iomanip>
#include <sstream>

namespace Clu
{
	
	CGuid& CGuid::operator= (const char* pcGuid)
	{
		std::regex xRegEx(
			"[^[:xdigit:]]*"
			"([[:xdigit:]]{8})"
			"[^[:xdigit:]]+"
			"([[:xdigit:]]{4})"
			"[^[:xdigit:]]+"
			"([[:xdigit:]]{4})"
			"[^[:xdigit:]]+"
			"([[:xdigit:]]{2})"
			"([[:xdigit:]]{2})"
			"[^[:xdigit:]]+"
			"([[:xdigit:]]{2})"
			"([[:xdigit:]]{2})"
			"([[:xdigit:]]{2})"
			"([[:xdigit:]]{2})"
			"([[:xdigit:]]{2})"
			"([[:xdigit:]]{2})"
			);

		std::string sGuid(pcGuid);
		std::smatch xMatch;

		std::regex_search(sGuid, xMatch, xRegEx);

		if (xMatch.size() != 12)
		{
			throw std::runtime_error("Invalid GUID string");
		}

		m_uPart1 = std::stoi(xMatch[1].str(), nullptr, 16);
		m_uPart2 = std::stoi(xMatch[2].str(), nullptr, 16);
		m_uPart3 = std::stoi(xMatch[3].str(), nullptr, 16);

		for (int i = 0; i < 8; ++i)
		{
			m_puPart4[i] = std::stoi(xMatch[4 + i].str(), nullptr, 16);
		}

		return *this;
	}

	CIString CGuid::ToString() const
	{
		char pcText[256];

		sprintf_s(pcText, "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"
			, m_uPart1, m_uPart2, m_uPart3, m_puPart4[0], m_puPart4[1]
			, m_puPart4[2], m_puPart4[3], m_puPart4[4], m_puPart4[5]
			, m_puPart4[6], m_puPart4[7]);

		return CIString(pcText);

		//std::stringstream xText;

		//xText << std::hex << std::setfill('0');
		//xText << std::setw(8) << m_uPart1 << "-";
		//xText << std::setw(4) << m_uPart2 << "-";
		//xText << std::setw(4) << m_uPart3 << "-";

		//xText << std::setw(2);
		//for (int i = 0; i < 2; ++i)
		//{
		//	xText << (unsigned int)m_puPart4[i];
		//}

		//xText << "-";

		//for (int i = 2; i < 8; ++i)
		//{
		//	xText << (unsigned int)m_puPart4[i];
		//}

		//return CIString(xText.str().c_str());
	}

} // namespace Clu

