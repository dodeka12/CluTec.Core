////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math.Test
// file:      MathTest1.cpp
//
// summary:   Implements the mathematics test 1 class
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
#include "CppUnitTest.h"

#include <limits>

#include "CluTec.Types1/IString.h"

#include "CluTec.Math/Static.Vector.h"
#include "CluTec.Math/Static.Vector.IO.h"
#include "CluTec.Math/Static.Matrix.h"
#include "CluTec.Math/Static.Matrix.IO.h"
#include "CluTec.Math/Static.Polynomial.h"
#include "CluTec.Math/Static.Geometry.h"
#include "CluTec.Math/Conversion.h"
#include "CluTec.Math/Frame3D.h"
#include "CluTec.Math/Constants.h"
#include "CluTec.Math/MapPixelValue.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CluTecMathTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		template<typename T>
		using TLim = std::numeric_limits<T>;

	public:
		
		TEST_METHOD(ImplementVector)
		{
			Clu::CIString sText;
			Clu::SVector<double, 5> xVecD5;

			xVecD5.SetZero();
			Assert::IsTrue(xVecD5.GetElement(4) == double(0), L"Access OK");

			xVecD5.SetElements(1.0, 2, 3, 4, 5);

			sText << "Vector: " << Clu::ToIString(xVecD5, "%g");
			Logger::WriteMessage(sText.ToCString());

			xVecD5.SetElements(-1, -2);
			sText = "Vector: ";
			sText << Clu::ToIString(xVecD5, "%g");
			Logger::WriteMessage(sText.ToCString());

		}

		TEST_METHOD(ImplementMatrix)
		{
			Clu::SMatrix<double, 4> xMatD4, mA, mB, mC;

			xMatD4.SetIdentity();
			Assert::IsTrue(xMatD4(2,2) == double(1), L"Access OK");

			mA.SetIdentity();
			mB.SetIdentity();
			mC.SetZero();

			Clu::MatrixProduct<0, 0>(mC, mA, mB);
		}

		TEST_METHOD(ImplementPolynomial)
		{
			Clu::SPolynomial<double, 4> xPolyD4;;

			xPolyD4.SetZero();
			xPolyD4[1] = 2.0;

			Assert::IsTrue(xPolyD4(2.0) == double(4.0), L"Access OK");
		}

		TEST_METHOD(ImplementGeometry)
		{
			Clu::_SAlignedRect2D<double> xRect;
			Clu::SCircle2D<double> xCircle2D;
			Clu::SConic2D<double> xConic2D;
			Clu::SEllipse2D<double> xEllipse2D;
			Clu::SLine3D<double> xLine3D;
			Clu::SPlane3D<double> xPlane3D;
			Clu::SPlaneSegment3D<double> xPlaneSeg3D;
			Clu::_SLine2D<double> xLine2D;
			Clu::_SLineSegment2D<double> xLineSeg2D;
			Clu::_SQuad2D<double> xQuad;

		}

		template<typename T, uint32_t t_nDim>
		void Print(const char* pcName, const Clu::_SVector<T, t_nDim>& vA)
		{
			Clu::CIString sText;
			sText = pcName;
			sText << ": " << Clu::ToIString(vA, "%g");
			Logger::WriteMessage(sText.ToCString());
		}

#define PRINT_VEC(theVec) Print(#theVec, theVec)

		TEST_METHOD(ImplementFrame3D)
		{
			Clu::CIString sText;
			Clu::SVector3<float> vP, vX, vY, vZ, vA, vB, vC;
			Clu::CFrame3D<float> xFrameA;

			float fPi = Clu::Math::Constants<float>::Pi();

			vP.SetElements(1, 0, 0);
			vZ.SetElements(1, 1, 1);
			xFrameA.Create(vZ, Clu::DegToRad(45.0f), vP);

			xFrameA.GetBasis_l_r(vX, vY, vZ);
			PRINT_VEC(vX);
			PRINT_VEC(vY);
			PRINT_VEC(vZ);

			Assert::IsTrue(Clu::Dot(vX, vY) < 0.0001, L"X/Y axes are not perpendicular");
			Assert::IsTrue(Clu::Dot(vX, vZ) < 0.0001, L"X/Z axes are not perpendicular");
			Assert::IsTrue(Clu::Dot(vY, vZ) < 0.0001, L"Y/Z axes are not perpendicular");

			vA.SetElements(0, 1, 0);
			vB = xFrameA.MapIntoFrame(vA);
			vC = xFrameA.MapOutOfFrame(vB);

			PRINT_VEC(vA);
			PRINT_VEC(vB);
			PRINT_VEC(vC);

			Assert::IsTrue(Clu::DistanceSquare(vA, vC) < 0.0001, L"Mapping into and out of frame does not return the same vector");
		}

		template<typename TResult, typename TValue>
		TResult Test_ToNormFloat(TValue xValue)
		{
			Clu::CIString sText;
			TResult xResult;

			xResult = Clu::ToNormFloat<TResult>(xValue);
			sText << "Value (" << typeid(TValue).name() << ") " << (int64_t)xValue << " <=> (" << typeid(TResult).name() << ") " << xResult;
			Logger::WriteMessage(sText.ToCString());

			return xResult;
		}

		template<typename TResult ,typename TValue>
		void Test_ToNormFloat_MinMaxMap()
		{
			Logger::WriteMessage("-------------------------------");

			Assert::IsTrue(Test_ToNormFloat<TResult>(TLim<TValue>::max()) == TResult(1));

			if (TLim<TValue>::is_signed)
			{
				Assert::IsTrue(Test_ToNormFloat<TResult>(TLim<TValue>::min()) == TResult(-1));
			}
			else
			{
				Assert::IsTrue(Test_ToNormFloat<TResult>(TLim<TValue>::min()) == TResult(0));
			}
		}

		template<typename TResult, typename TValue>
		TValue Test_ToNormFloatAndBack(TValue xValue)
		{
			Clu::CIString sText;
			TResult xResult;
			TValue xValue2;

			xResult = Clu::ToNormFloat<TResult>(xValue);
			xValue2 = Clu::NormFloatTo<TValue>(xResult);

			sText << "(" << typeid(TValue).name() << ") " << (int64_t)xValue; 
			sText << " => (" << typeid(TResult).name() << ") " << xResult;
			sText << " => (" << typeid(TValue).name() << ") " << (int64_t)xValue2;
			Logger::WriteMessage(sText.ToCString());

			Assert::IsTrue(xValue == xValue2, L"Original value is not the same as to and for conversion");

			return xValue2;
		}


		TEST_METHOD(Conversion)
		{
			Test_ToNormFloat_MinMaxMap<float, char>();
			Test_ToNormFloat_MinMaxMap<float, unsigned char>();
			Test_ToNormFloat_MinMaxMap<double, int64_t>();


			//Test_ToNormFloatAndBack<float, char>(10);
			//Test_ToNormFloatAndBack<float, unsigned char>(10);
			Test_ToNormFloatAndBack<float, int64_t>(Clu::NumericLimits<int64_t>::Min());


			//using TPixVal = uint8_t;
			//using TNormVal = float;

			//Clu::CIString sText;

			//TPixVal xPix = 1;
			//TNormVal xF = Clu::ToNormFloat<TNormVal>(xPix);
			//TPixVal xPix2 = Clu::NormFloatTo<TPixVal>(xF);

			//sText << (int64_t)xPix << " => " << xF << " => " << (int64_t) xPix2;
			//Logger::WriteMessage(sText.ToCString());

			//char cMin = Clu::NumericLimits<int8_t>::Min();
			//sText = "";
			//sText << "Min: " << (int64_t) cMin;
			//Logger::WriteMessage(sText.ToCString());
		}

		template<typename TResult, typename TValue>
		void Test_MapPixelValue(TValue xValue)
		{
			Clu::CIString sText;
			TResult xResult;
			TValue xValue2;

			xResult = Clu::MapPixelValue<TResult>(xValue);
			xValue2 = Clu::MapPixelValue<TValue>(xResult);

			sText << "(" << typeid(TValue).name() << ") " << xValue;
			sText << " => (" << typeid(TResult).name() << ") " << xResult;
			sText << " => (" << typeid(TValue).name() << ") " << xValue2;

			Logger::WriteMessage(sText.ToCString());

			Assert::IsTrue(xValue == xValue2, L"Original value is not the same as to and from conversion");
		}

		TEST_METHOD(MapPixelData)
		{
			Clu::CIString sText;

			uint8_t ui8V = 0;
			uint16_t ui16V = 1 << 8;
			uint32_t ui32V = 1 << 24;
			// ///////////////////////////////////////////////////////////////////////////////
			// Unsigned -> Unsigned
			
			Logger::WriteMessage("\n===============================================\nUnsigned -> Unsigned");
			Test_MapPixelValue<uint8_t>(Clu::NumericLimits<uint16_t>::Max());
			Test_MapPixelValue<uint8_t>((uint16_t)(Clu::NumericLimits<uint16_t>::Max() >> 1));
			Test_MapPixelValue<uint16_t>((uint8_t)(Clu::NumericLimits<uint8_t>::Max() >> 1));

			// ///////////////////////////////////////////////////////////////////////////////
			// Unsigned -> Signed 

			Logger::WriteMessage("\n===============================================\nUnsigned -> Signed");
			Test_MapPixelValue<int8_t>(Clu::NumericLimits<uint8_t>::Max());
			Test_MapPixelValue<int8_t>(Clu::NumericLimits<uint8_t>::Min());
			Test_MapPixelValue<int8_t>(Clu::NumericLimits<uint16_t>::Max());
			Test_MapPixelValue<int8_t>(Clu::NumericLimits<uint16_t>::Min());

			Test_MapPixelValue<uint8_t>(Clu::NumericLimits<int8_t>::Max());
			Test_MapPixelValue<uint8_t>(Clu::NumericLimits<int8_t>::Min());
			Test_MapPixelValue<uint8_t>(Clu::NumericLimits<int16_t>::Max());
			Test_MapPixelValue<uint8_t>(Clu::NumericLimits<int16_t>::Min());

			// ///////////////////////////////////////////////////////////////////////////////
			// Signed -> Signed 

			Logger::WriteMessage("\n===============================================\nSigned -> Signed");
			Test_MapPixelValue<int8_t>(Clu::NumericLimits<int8_t>::Max());
			Test_MapPixelValue<int8_t>(Clu::NumericLimits<int8_t>::Min());

			Test_MapPixelValue<int8_t>(int16_t(0));
			Test_MapPixelValue<int8_t>(Clu::NumericLimits<int16_t>::Max());
			Test_MapPixelValue<int8_t>(Clu::NumericLimits<int16_t>::Min());

			Test_MapPixelValue<int16_t>(int8_t(0));
			Test_MapPixelValue<int16_t>(Clu::NumericLimits<int8_t>::Max());
			Test_MapPixelValue<int16_t>(Clu::NumericLimits<int8_t>::Min());

			// ///////////////////////////////////////////////////////////////////////////////
			// Float -> Unsigned
			Logger::WriteMessage("\n===============================================\nUnsigned -> Float");
			Test_MapPixelValue<float>(Clu::NumericLimits<uint8_t>::Max());
			Test_MapPixelValue<float>(Clu::NumericLimits<uint8_t>::Min());

			Logger::WriteMessage("\n===============================================\nSigned -> Float");
			Test_MapPixelValue<float>(Clu::NumericLimits<int8_t>::Max());
			Test_MapPixelValue<float>(Clu::NumericLimits<int8_t>::Min());

			Logger::WriteMessage("\n===============================================\nFloat -> Unsigned");
			Test_MapPixelValue<uint8_t>(float(1.0));
			Test_MapPixelValue<uint8_t>(float(0.0));

			Logger::WriteMessage("\n===============================================\nFloat -> Signed");
			Test_MapPixelValue<int8_t>(float(1.0));
			Test_MapPixelValue<int8_t>(float(-1.0));

		}
	};
}