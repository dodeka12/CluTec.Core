////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Static.Vector.IO.h
//
// summary:   Declares the static. vector. i/o class
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
#include <strstream>

#include "CluTec.Base/Exception.h"
#include "CluTec.Base/Conversion.h"
#include "Static.Vector.h"

namespace Clu
{
	template<typename TValue, uint32_t t_nDim>
	std::string ToString(const _SVector<TValue, t_nDim>& vA, const std::string& sFormat)
	{
		std::stringstream sText;

		vA.ForEachElementIdx([&sText, &sFormat](const TValue& xValue, uint32_t i)
		{
			char pcValue[256];

			sprintf_s(pcValue, sFormat.c_str(), xValue);
			sText << pcValue;

			if (i < t_nDim - 1)
			{
				sText << ", ";
			}
		});

		return sText.str();
	}

	template<typename TValue, uint32_t t_nDim>
	Clu::CIString ToIString(const _SVector<TValue, t_nDim>& vA, const Clu::CIString& sFormat)
	{
		return Clu::CIString(ToString(vA, std::string(sFormat.ToCString())).c_str());
	}

	template<typename TValue, uint32_t t_nDim>
	void ReadVector(_SVector<TValue, t_nDim>& vA, const std::string& sText)
	{

		using TVec = _SVector<TValue, t_nDim>;
		using TIdx = TVec::TIdx;


		std::vector<TValue> vecData = ToNumberList<TValue>(sText);

		if (vecData.size() != vA.ElementCount)
		{
			throw CLU_EXCEPTION("Given string does not contain a sufficient number of values");
		}

		vA.ForEachElementIdx([&vecData](TValue& xValue, TIdx iIdx)
		{
			xValue = vecData[iIdx];
		});
	}

}