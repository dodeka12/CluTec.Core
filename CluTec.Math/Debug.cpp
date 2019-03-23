////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Debug.cpp
//
// summary:   Implements the debug class
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

#include "Debug.h"

namespace Clu
{
	namespace Debug
	{
		namespace Script
		{

			Clu::CIString ToScript(EColor eColor)
			{
				switch (eColor)
				{
				case Clu::Debug::Script::EColor::Red:
					return CIString("Red");

				case Clu::Debug::Script::EColor::Green:
					return CIString("Green");

				case Clu::Debug::Script::EColor::Blue:
					return CIString("Blue");

				case Clu::Debug::Script::EColor::Magenta:
					return CIString("Magenta");

				case Clu::Debug::Script::EColor::Yellow:
					return CIString("Yellow");

				case Clu::Debug::Script::EColor::Cyan:
					return CIString("Cyan");

				case Clu::Debug::Script::EColor::White:
					return CIString("White");

				case Clu::Debug::Script::EColor::Black:
					return CIString("Black");

				default:
					break;
				}

				return "Unknown_Color";
			}

		}
	}
}
