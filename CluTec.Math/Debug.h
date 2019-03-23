////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Debug.h
//
// summary:   Declares the debug class
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

#include "CluTec.Types1/IString.h"

#include "Static.Vector.h"

namespace Clu
{
	namespace Debug
	{
		namespace Script
		{

			enum class EColor
			{
				Red,
				Green,
				Blue,
				Magenta,
				Yellow,
				Cyan,
				White,
				Black,
			};
			

			Clu::CIString ToScript(EColor eColor);

			template<typename TValue, uint32_t t_nDim>
			Clu::CIString ToScript(const _SVector<TValue, t_nDim>& vA)
			{
				Clu::CIString sValue;

				sValue << "VecE3(";

				bool bFirst = true;
				vA.ForEachElement([&sValue, &vA, &bFirst](const TValue& dValue)
				{
					if (!bFirst)
					{
						sValue << ", ";
					}

					sValue << dValue;
					bFirst = false;
				});

				sValue << ")";

				return sValue;
			}



			class CText
			{
			protected:
				Clu::CIString m_sScript;

			public:
				CText()
				{}

				~CText()
				{}

				void Clear()
				{
					m_sScript.Clear();
				}


				Clu::CIString ToString()
				{
					return m_sScript;
				}

				CText& operator << (const Clu::CIString& sText)
				{
					m_sScript << sText;
					return *this;
				}

				template<typename TValue>
				void DefineVar(const Clu::CIString& sName, const TValue& xValue)
				{
					m_sScript << sName << " = " << ToScript(xValue) << ";\n";
				}

				void DrawFrameBoxCoord(double dSize, unsigned uPartsX, unsigned uPartsY, unsigned uPartsZ)
				{
					m_sScript << "DrawFrame(" << dSize << ", \"box_coord\", ["
						<< uPartsX << ", " << uPartsY << ", " << uPartsZ << "], MWhite);\n";
				}

				void DrawArrowDir(const Clu::CIString& sOrigin, const Clu::CIString& sDir, EColor eColor)
				{
					m_sScript << "DrawArrow(" << sOrigin << ", " << sOrigin << " + " << sDir << ") :" << ToScript(eColor) << ";\n";
				}

				void DrawArrow(const Clu::CIString& sA, const Clu::CIString& sB, EColor eColor)
				{
					m_sScript << "DrawArrow(" << sA << ", " << sB << ") :" << ToScript(eColor) << ";\n";
				}

				void DrawLine(const Clu::CIString& sA, const Clu::CIString& sB, EColor eColor)
				{
					m_sScript << "DrawLine(" << sA << ", " << sB << ") :" << ToScript(eColor) << ";\n";
				}

				void DrawLineRect(const Clu::CIString& sCenter, const Clu::CIString& sDirX, const Clu::CIString& sDirY, EColor eColor)
				{
					DrawLine(CLU_S sCenter << " - 0.5 * " << sDirX << " - 0.5 * " << sDirY, CLU_S sCenter << " + 0.5 * " << sDirX << " - 0.5 * " << sDirY, eColor);
					DrawLine(CLU_S sCenter << " + 0.5 * " << sDirX << " - 0.5 * " << sDirY, CLU_S sCenter << " + 0.5 * " << sDirX << " + 0.5 * " << sDirY, eColor);
					DrawLine(CLU_S sCenter << " + 0.5 * " << sDirX << " + 0.5 * " << sDirY, CLU_S sCenter << " - 0.5 * " << sDirX << " + 0.5 * " << sDirY, eColor);
					DrawLine(CLU_S sCenter << " - 0.5 * " << sDirX << " + 0.5 * " << sDirY, CLU_S sCenter << " - 0.5 * " << sDirX << " - 0.5 * " << sDirY, eColor);
				}

				void DrawLinePyramid(const Clu::CIString& sCenter, const Clu::CIString& sDirX, const Clu::CIString& sDirY, const Clu::CIString& sDirZ, EColor eColor)
				{
					DrawLine(sCenter, CLU_S sCenter << " + " << sDirZ << " - 0.5 * " << sDirX << " - 0.5 * " << sDirY, eColor);
					DrawLine(sCenter, CLU_S sCenter << " + " << sDirZ << " - 0.5 * " << sDirX << " + 0.5 * " << sDirY, eColor);
					DrawLine(sCenter, CLU_S sCenter << " + " << sDirZ << " + 0.5 * " << sDirX << " - 0.5 * " << sDirY, eColor);
					DrawLine(sCenter, CLU_S sCenter << " + " << sDirZ << " + 0.5 * " << sDirX << " + 0.5 * " << sDirY, eColor);

					DrawLineRect(CLU_S sCenter << " + " << sDirZ, sDirX, sDirY, eColor);
				}

				void DrawLinePyramid(const Clu::CIString& sTip, const Clu::CIString& sBase, const Clu::CIString& sDirX, const Clu::CIString& sDirY, const Clu::CIString& sDirZ, EColor eColor)
				{
					DrawLine(sTip, CLU_S sBase << " - 0.5 * " << sDirX << " - 0.5 * " << sDirY, eColor);
					DrawLine(sTip, CLU_S sBase << " - 0.5 * " << sDirX << " + 0.5 * " << sDirY, eColor);
					DrawLine(sTip, CLU_S sBase << " + 0.5 * " << sDirX << " - 0.5 * " << sDirY, eColor);
					DrawLine(sTip, CLU_S sBase << " + 0.5 * " << sDirX << " + 0.5 * " << sDirY, eColor);

					DrawLineRect(CLU_S sBase, sDirX, sDirY, eColor);
				}
			};
		}
	}
}