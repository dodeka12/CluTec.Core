////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Congruence.h
//
// summary:   Declares the congruence class
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

#include <functional>

#include "CluTec.Base/Defines.h"
#include "StandardMath.h"

namespace Clu
{
	template<typename T>
	class CCongruence_Float
	{
	public:

		CCongruence_Float()
		{ }

		bool Map(T& tResult, const T& tValue) const
		{
			tResult = tValue;
			return true;
		}

		bool InvMap(T& tResult, const T& tValue) const
		{
			if (tValue == T(0))
			{
				return false;
			}

			tResult = T(1) / tValue;
			return true;
		}
	};

	template<typename T>
	class CCongruence_HMod
	{
	public:

		CCongruence_HMod()
		{
			m_tMod = T(1);
		}

		CCongruence_HMod(T tMod)
		{
			m_tMod = tMod;
		}

		bool Map(T& tResult, const T& tValue) const
		{
			tResult = Clu::HalfMod(tValue, m_tMod);
			return true;
		}

		bool InvMap(T& tResult, const T& tValue) const
		{
			tResult = Clu::HalfModInv(tValue, m_tMod);

			return tResult != T(0);
		}

	private:

		T m_tMod;
	};
}
