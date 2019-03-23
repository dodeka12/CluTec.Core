////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.ImgProc
// file:      Camera.IO.h
//
// summary:   Declares the camera. i/o class
//
//            Copyright (c) 2016 CluTec. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "CluTec.Types1/IArrayDouble.h"

#include "Camera.Enums.h"
#include "Camera.Pinhole.h"
#include "Camera.StereoPinhole.h"

namespace Clu
{
	namespace Camera
	{
		template<EStyle eStyle>
		struct PinholeIO
		{};

		template<> struct PinholeIO<EStyle::OpenCV>
		{
			template<typename TValue>
			static void Read(_CPinhole<TValue>& camPinhole, const Clu::CIString& sFilename
				, const Clu::CIString& sId_KMatrix
				, const Clu::CIString& sId_RMatrix
				, const Clu::CIString& sId_TVector
				, const Clu::CIString& sId_Distortion
				, const Clu::CIString& sId_Resolution);
		};

		// //////////////////////////////////////////////////////////////////////////////////////////////
		// //////////////////////////////////////////////////////////////////////////////////////////////
		// //////////////////////////////////////////////////////////////////////////////////////////////


		template<EStyle eStyle>
		struct StereoPinholeIO
		{};

		// //////////////////////////////////////////////////////////////////////////////////////////////
		template<> struct StereoPinholeIO<EStyle::Middlebury>
		{
		public:

			template<typename TValue>
			static void Read(_CStereoPinhole<TValue>& scamPinhole, const Clu::CIString& sFilename);

		protected:

			template<typename TValue, uint32_t t_nDim, uint32_t t_nRowMajor>
			static void _ReadMatrix(_SMatrix<TValue, t_nDim, t_nRowMajor>& matA, const std::string& sName, const std::string& sText);

			template<typename TValue>
			static void _ReadValue(TValue& fA, const std::string& sName, const std::string& sText);

		};

		// //////////////////////////////////////////////////////////////////////////////////////////////
		template<> struct StereoPinholeIO<EStyle::Halcon>
		{
		public:

			template<typename TValue>
			static void Set(_CStereoPinhole<TValue>& scamPinhole, const Clu::CIArrayDouble& aCamParamL, const Clu::CIArrayDouble& aCamParamR
							, const Clu::CIArrayDouble& aRelPose);

		};



	}
}