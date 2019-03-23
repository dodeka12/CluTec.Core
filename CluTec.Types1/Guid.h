////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      Guid.h
//
// summary:   Declares the unique identifier class
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

#ifdef CLU_INTEROP_EXPORTS
#define CLU_TYPES1_API __declspec(dllexport)
#else
#define CLU_TYPES1_API __declspec(dllimport)
#endif

#include <cstdint>
#include "IString.h"


namespace Clu
{

	class CLU_TYPES1_API CGuid
	{
	protected:
		uint32_t m_uPart1;
		uint16_t m_uPart2;
		uint16_t m_uPart3;
		uint8_t m_puPart4[8];

	public:
		CGuid()
		{
			m_uPart1 = 0;
			m_uPart2 = 0;
			m_uPart3 = 0;
			for (int i = 0; i < 8; ++i)
			{
				m_puPart4[i] = 0;
			}
		}

		CGuid(const CGuid&) = default;
		CGuid& operator=(const CGuid&) = default;


		explicit CGuid(const char* pcGuid)
		{
			*this = pcGuid;
		}

		CGuid(uint32_t uPart1, uint16_t uPart2, uint16_t uPart3
			, uint8_t uPart41, uint8_t uPart42, uint8_t uPart43, uint8_t uPart44
			, uint8_t uPart45, uint8_t uPart46, uint8_t uPart47, uint8_t uPart48)
		{
			m_uPart1 = uPart1;
			m_uPart2 = uPart2;
			m_uPart3 = uPart3;
			m_puPart4[0] = uPart41;
			m_puPart4[1] = uPart42;
			m_puPart4[2] = uPart43;
			m_puPart4[3] = uPart44;
			m_puPart4[4] = uPart45;
			m_puPart4[5] = uPart46;
			m_puPart4[6] = uPart47;
			m_puPart4[7] = uPart48;
		}

		CGuid& operator= (const char* pcGuid);

		CIString ToString() const;

		bool operator== (const CGuid& xGuid)
		{
			return m_uPart1 == xGuid.m_uPart1 && m_uPart2 == xGuid.m_uPart2 && m_uPart3 == xGuid.m_uPart3
				&& m_puPart4[0] == xGuid.m_puPart4[0] && m_puPart4[1] == xGuid.m_puPart4[1] && m_puPart4[2] == xGuid.m_puPart4[2]
				&& m_puPart4[3] == xGuid.m_puPart4[3] && m_puPart4[4] == xGuid.m_puPart4[4] && m_puPart4[5] == xGuid.m_puPart4[5]
				&& m_puPart4[6] == xGuid.m_puPart4[6] && m_puPart4[7] == xGuid.m_puPart4[7];
		}

		bool operator!= (const CGuid& xGuid)
		{
			return !(*this == xGuid);
		}
	};
}

#pragma make_public(Clu::CGuid)
