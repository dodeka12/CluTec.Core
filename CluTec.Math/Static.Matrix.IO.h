////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Static.Matrix.IO.h
//
// summary:   Declares the static. matrix. i/o class
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
#include <vector>

#include "CluTec.Base/Exception.h"
#include "CluTec.Base/Conversion.h"
#include "Static.Matrix.h"

namespace Clu
{
	template<typename TValue, uint32_t t_nDim, uint32_t t_nRowMajor>
	std::string ToString(const _SMatrix<TValue, t_nDim, t_nRowMajor>& mA, const std::string& sFormat)
	{
		using TMat = _SMatrix<TValue, t_nDim, t_nRowMajor>;
		using TIdx = typename TMat::TIdx;

		char pcValue[256];
		std::stringstream sText;

		for (TIdx iRow = 0; iRow < TMat::RowCount; ++iRow)
		{
			for (TIdx iCol = 0; iCol < TMat::ColCount; ++iCol)
			{
				sprintf_s(pcValue, sFormat.c_str(), mA(iRow, iCol));
				sText << " | " << pcValue;
			}
			sText << " |\n";
		}

		return sText.str();
	}


	template<typename TValue, uint32_t t_nDim, uint32_t t_nRowMajor>
	Clu::CIString ToIString(const _SMatrix<TValue, t_nDim, t_nRowMajor>& mA, const Clu::CIString& sFormat)
	{
		return Clu::CIString(ToString(mA, std::string(sFormat.ToCString())).c_str());
	}

	template<typename TValue, uint32_t t_nDim, uint32_t t_nRowMajor>
	void ReadMatrix(_SMatrix<TValue, t_nDim, t_nRowMajor>& mA, const std::string& sText, bool bIsRowMajor)
	{

		using TMat = _SMatrix<TValue, t_nDim, t_nRowMajor>;
		using TIdx = typename TMat::TIdx;
		

		std::vector<TValue> vecData = ToNumberList<TValue>(sText);

		if (vecData.size() != mA.ElementCount)
		{
			throw CLU_EXCEPTION("Given string does not contain a sufficient number of values");
		}

		if (bIsRowMajor)
		{
			TIdx iPos = 0;
			for (TIdx iRow = 0; iRow < TMat::RowCount; ++iRow)
			{
				for (TIdx iCol = 0; iCol < TMat::ColCount; ++iCol)
				{
					mA(iRow, iCol) = vecData[iPos];
					++iPos;
				}
			}
		}
		else
		{
			TIdx iPos = 0;
			for (TIdx iCol = 0; iCol < TMat::ColCount; ++iCol)
			{
				for (TIdx iRow = 0; iRow < TMat::RowCount; ++iRow)
				{
					mA(iRow, iCol) = vecData[iPos];
					++iPos;
				}
			}
		}

	}

}