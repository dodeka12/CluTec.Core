////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.ImgProc
// file:      Camera.IO.cpp
//
// summary:   Implements the camera. i/o class
//
//            Copyright (c) 2016 CluTec. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <sstream>

#include "Camera.IO.h"
#include "CluTec.Types1/ExceptionTypes.h"
#include "CluTec.Base/Exception.h"
#include "CluTec.FileIO/Xml.h"
#include "CluTec.System/FileInfo.h"


#include "CluTec.Base/Conversion.h"
#include "CluTec.Math/Conversion.h"
#include "CluTec.Math/Static.Matrix.h"
#include "CluTec.Math/Static.Matrix.IO.h"
#include "CluTec.Math/Static.Vector.h"
#include "CluTec.Math/Static.Vector.IO.h"


namespace Clu
{
	namespace Camera
	{


		template<typename TValue>
		static void PinholeIO<EStyle::OpenCV>::Read(_CPinhole<TValue>& camPinhole, const Clu::CIString& sFilename
			, const Clu::CIString& sId_KMatrix
			, const Clu::CIString& sId_RMatrix
			, const Clu::CIString& sId_TVector
			, const Clu::CIString& sId_Distortion
			, const Clu::CIString& sId_Resolution)
		{
			using TMat3 = _SMatrix<TValue, 3>;
			using TVec3 = _SVector<TValue, 3>;
			using TVec5 = _SVector<TValue, 5>;
			using TUVec2 = _SVector<TMat3::TIdx, 2>;

			try
			{
				// Test whether file exists
				CFileInfo xFile(sFilename);

				if (!xFile.Exists())
				{
					throw CLU_EXCEPT_TYPE(FileNotFound, CLU_S "File '" << sFilename << "' could not be found");
				}

				Xml::CIDocument xDoc;
				xDoc.CreateFromFile(sFilename);

				Xml::CIXPath xPath = xDoc("/opencv_storage");
				if (xPath.Count() == 0)
				{
					throw CLU_EXCEPTION("Given XML file is not OpenCV storage type");
				}

				TMat3 mK, mR;
				TVec3 vT;
				TVec5 vDist;
				TUVec2 vRes;

				Clu::CIString sPathBase = "/opencv_storage/";
				Clu::CIString sPathData = "/data";

				Clu::CIString sName, sData;
				sName = sPathBase + sId_KMatrix + sPathData;
				xPath = xDoc(sName);
				sData = xPath.Content(0);
				ReadMatrix(mK, sData.ToCString(), true);

				sData = xDoc((sPathBase + sId_RMatrix + sPathData)).Content(0);
				ReadMatrix(mR, sData.ToCString(), true);

				sData = xDoc((sPathBase + sId_TVector + sPathData)).Content(0).ToCString();
				ReadVector(vT, sData.ToCString());

				sData = xDoc((sPathBase + sId_Distortion + sPathData)).Content(0).ToCString();
				ReadVector(vDist, sData.ToCString());

				sData = xDoc((sPathBase + sId_Resolution)).Content(0).ToCString();
				ReadVector(vRes, sData.ToCString());

				camPinhole.CreateFromStyle<EStyle::OpenCV>(mK, mR, vT, vRes, TValue(5.5e-6));

				_CPinhole<TValue>::TDistort xDistort;
				xDistort.Create(vDist[2], vDist[3], vDist[0], vDist[1], vDist[4], TValue(0), TValue(0), TValue(0));

				camPinhole.SetDistortion(xDistort);
			}
			CLU_CATCH_RETHROW_ALL("Error reading pinhole camera from OpenCV storage XML file")
		}



		template void PinholeIO<EStyle::OpenCV>::Read(_CPinhole<float>& camPinhole, const Clu::CIString& sFilename
			, const Clu::CIString& sId_KMatrix
			, const Clu::CIString& sId_RMatrix
			, const Clu::CIString& sId_TVector
			, const Clu::CIString& sId_Distortion
			, const Clu::CIString& sId_Resolution);

		template void PinholeIO<EStyle::OpenCV>::Read(_CPinhole<double>& camPinhole, const Clu::CIString& sFilename
			, const Clu::CIString& sId_KMatrix
			, const Clu::CIString& sId_RMatrix
			, const Clu::CIString& sId_TVector
			, const Clu::CIString& sId_Distortion
			, const Clu::CIString& sId_Resolution);

		// ///////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ///////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ///////////////////////////////////////////////////////////////////////////////////////////////////////////


		template<typename TValue>
		static void StereoPinholeIO<EStyle::Middlebury>::Read(_CStereoPinhole<TValue>& scamPinhole, const Clu::CIString& sFilename)
		{
			using TPinhole = _CStereoPinhole<TValue>::TPinhole;
			using TUVec2 = TPinhole::TUVec2;

			using TMat3 = Clu::_SMatrix<TValue, 3>;
			using TVec3 = Clu::_SVector<TValue, 3>;
			using TVec2 = Clu::_SVector<TValue, 2>;

			// //////////////////////////////////////////////////////////////////////////////////
			// Test whether file exists
			// //////////////////////////////////////////////////////////////////////////////////
			CFileInfo xFile(sFilename);

			if (!xFile.Exists())
			{
				throw CLU_EXCEPT_TYPE(FileNotFound, CLU_S "File '" << sFilename << "' could not be found");
			}

			// //////////////////////////////////////////////////////////////////////////////////
			// Read file contents into string
			// //////////////////////////////////////////////////////////////////////////////////
			std::ifstream xFileStream(sFilename.ToCString());

			if (!xFileStream)
			{
				throw CLU_EXCEPTION(CLU_S "Cannot open file '" << sFilename << "'");
			}

			std::string sText;
			std::stringstream sxText;
			sxText << xFileStream.rdbuf();
			sText = sxText.str();
			xFileStream.close();

			// //////////////////////////////////////////////////////////////////////////////////
			// Parse file contents to read values
			// //////////////////////////////////////////////////////////////////////////////////

			TMat3 matK[2];
			TValue fOffsetX, fBaselineMM;
			int iWidthPX, iHeightPX;

			_ReadMatrix(matK[0], "cam0", sText);
			_ReadMatrix(matK[1], "cam1", sText);
			_ReadValue(fOffsetX, "doffs", sText);
			_ReadValue(fBaselineMM, "baseline", sText);
			_ReadValue(iWidthPX, "width", sText);
			_ReadValue(iHeightPX, "height", sText);

			// Pixel pitch of Canon EOS 450D used for 2014 Middlebury data
			TValue fPixelPitchMM = TValue(0.00519);

			// /////////////////////////////////////////////////////////////////////////////
			// Create Stereo Camera System
			// /////////////////////////////////////////////////////////////////////////////
			TMat3 matR;
			TVec3 vT;
			TUVec2 vuRes;
			TValue fHalfBaselineM = fBaselineMM / TValue(2) * TValue(1e-3);
			TValue fPixelPitchM = fPixelPitchMM * TValue(1e-3);

			matR.SetIdentity();
			vuRes.SetElements(iWidthPX, iHeightPX);

			vT.SetElements(-fHalfBaselineM, 0, 0);
			scamPinhole[0].CreateFromStyle<EStyle::Middlebury>(matK[0], matR, vT, vuRes, fPixelPitchM);
			
			vT.SetElements(fHalfBaselineM, 0, 0);
			scamPinhole[1].CreateFromStyle<EStyle::Middlebury>(matK[1], matR, vT, vuRes, fPixelPitchM);
		}


		template<typename TValue, uint32_t t_nDim, uint32_t t_nRowMajor>
		static void StereoPinholeIO<EStyle::Middlebury>::_ReadMatrix(Clu::_SMatrix<TValue, t_nDim, t_nRowMajor>& matA, const std::string& sName, const std::string& sText)
		{
			using TMat = Clu::_SMatrix<TValue, t_nDim, t_nRowMajor>;

			std::smatch xMatch;
			std::string srxVar = sName + R"(=\[(.*)\])";
			std::regex rxNumber(R"([\d\.]+)");
			std::vector<TValue> vecValue;

			// Read Camera matrix values
			if (!std::regex_search(sText, xMatch, std::regex(srxVar)))
			{
				throw CLU_EXCEPTION(CLU_S "Entry for '" << sName.c_str() << "' not found");
			}

			auto itStart = xMatch[1].first;
			auto itEnd = xMatch[1].second;


			for (; regex_search(itStart, itEnd, xMatch, rxNumber); itStart = xMatch.suffix().first)
			{
				vecValue.push_back(Clu::ToNumber<TValue>(xMatch.str()));
			}

			if (vecValue.size() != TMat::ElementCount)
			{
				throw CLU_EXCEPTION(CLU_S "Invalid number of values in matrix '" << sName.c_str() << "'");
			}

			int iPos = 0;
			for (int iRow = 0; iRow < TMat::RowCount; ++iRow)
			{
				for (int iCol = 0; iCol < TMat::ColCount; ++iCol, ++iPos)
				{
					matA(iRow, iCol) = vecValue[iPos];
				}
			}
		}


		template<typename TValue>
		static void StereoPinholeIO<EStyle::Middlebury>::_ReadValue(TValue& fA, const std::string& sName, const std::string& sText)
		{
			std::smatch xMatch;
			std::string srxVar = sName + R"(=([\d\.]+))";

			if (!std::regex_search(sText, xMatch, std::regex(srxVar)))
			{
				throw CLU_EXCEPTION(CLU_S "Value '" << sName.c_str() << "' not found");
			}

			fA = Clu::ToNumber<TValue>(xMatch[1].str());
		}


		template void StereoPinholeIO<EStyle::Middlebury>::Read(_CStereoPinhole<float>& scamPinhole, const Clu::CIString& sFilename);
		template void StereoPinholeIO<EStyle::Middlebury>::Read(_CStereoPinhole<double>& scamPinhole, const Clu::CIString& sFilename);


		// ///////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ///////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ///////////////////////////////////////////////////////////////////////////////////////////////////////////



		
		template<typename TValue>
		static void StereoPinholeIO<EStyle::Halcon>::Set(_CStereoPinhole<TValue>& scamPinhole
			, const Clu::CIArrayDouble& aCamParamL, const Clu::CIArrayDouble& aCamParamR
			, const Clu::CIArrayDouble& aRelPose)
		{
			using TMat3 = Clu::_SMatrix<TValue, 3>;
			using TVec3 = Clu::_SVector<TValue, 3>;
			using TVec2 = Clu::_SVector<TValue, 2>;

			unsigned uAfterDistOffset;

			if (aCamParamL.ElementCount() == 12)
			{
				// Polynomial distortion
				uAfterDistOffset = 6;
			}
			else
			{
				// Inversion model distortion
				uAfterDistOffset = 2;
			}

			TMat3 matR;
			TVec3 vT, vX, vY, vZ;

			vX.SetElements(1.0, 0.0, 0.0);
			vY.SetElements(0.0, 1.0, 0.0);
			vZ.SetElements(0.0, 0.0, 1.0);

			matR.SetIdentity();
			vT.SetZero();

			scamPinhole[0].CreateFromStyle_Halcon(
				aCamParamL[0] // Focal length
				, aCamParamL[uAfterDistOffset + 0], aCamParamL[uAfterDistOffset + 1] // Pixel size
				, aCamParamL[uAfterDistOffset + 2], aCamParamL[uAfterDistOffset + 3] // Principal point in pixels
				, unsigned(aCamParamL[uAfterDistOffset + 4]), unsigned(aCamParamL[uAfterDistOffset + 5]) // Pixel Count on Sensor
				, matR, vT); // External pose


			// Check type of pose
			if (unsigned(aRelPose[6]) == 0)
			{
				vT.SetElements(aRelPose[0], aRelPose[1], aRelPose[2]);
				matR = RotMat3(DegToRad((TValue)aRelPose[3]), vX) * RotMat3(DegToRad((TValue)aRelPose[4]), vY) * RotMat3(DegToRad((TValue)aRelPose[5]), vZ);
			}
			else
			{
				throw CLU_EXCEPTION("Unsupported camera pose type");
			}

			scamPinhole[1].CreateFromStyle_Halcon(
				aCamParamR[0] // Focal length
				, aCamParamR[uAfterDistOffset + 0], aCamParamR[uAfterDistOffset + 1] // Pixel size
				, aCamParamR[uAfterDistOffset + 2], aCamParamR[uAfterDistOffset + 3] // Principal point in pixels
				, unsigned(aCamParamR[uAfterDistOffset + 4]), unsigned(aCamParamR[uAfterDistOffset + 5]) // Pixel Count on Sensor
				, matR, vT); // External pose

		}


		template void StereoPinholeIO<EStyle::Halcon>::Set(_CStereoPinhole<float>& scamPinhole
			, const Clu::CIArrayDouble& aCamParamL, const Clu::CIArrayDouble& aCamParamR
			, const Clu::CIArrayDouble& aRelPose);

		template void StereoPinholeIO<EStyle::Halcon>::Set(_CStereoPinhole<double>& scamPinhole
			, const Clu::CIArrayDouble& aCamParamL, const Clu::CIArrayDouble& aCamParamR
			, const Clu::CIArrayDouble& aRelPose);
	}
}