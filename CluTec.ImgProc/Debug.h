////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.ImgProc
// file:      Camera.Debug.h
//
// summary:   Declares the camera. debug class
//
//            Copyright (c) 2016 CluTec. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CluTec.Types1/Defines.h"
#include "CluTec.Types1/IString.h"
#include "CluTec.Math/Debug.h"
#include "Camera.Pinhole.h"

namespace Clu
{
	namespace Debug
	{
		namespace Script
		{
			template<typename TValue>
			void Add(Clu::Debug::Script::CText& xScript, const Clu::Camera::_CPinhole<TValue>& xCamera, const Clu::CIString& sSub
				, EColor eColA, EColor eColB)
			{
				using TPinhole = Clu::Camera::_CPinhole<TValue>;
				using TVec3 = typename TPinhole::TVec3;

				TVec3 vX, vY, vZ, vT, vPinhole;
				xCamera.Sensor().FrameM_s_w().GetBasis_l_r(vX, vY, vZ);
				vT = xCamera.Sensor().FrameM_s_w().Translation_l_r();
				vPinhole = xCamera.PinholeM_w();
				double dF = xCamera.FocalLength();

				Clu::CIString sT = CLU_S "vT" << "_" << sSub;
				Clu::CIString sX = CLU_S "vX" << "_" << sSub;
				Clu::CIString sY = CLU_S "vY" << "_" << sSub;
				Clu::CIString sZ = CLU_S "vZ" << "_" << sSub;
				Clu::CIString sP = CLU_S "vP" << "_" << sSub;

				TValue dScale = 10.0;
				vT *= dScale;
				vPinhole *= dScale;
				dF *= dScale;

				vX *= dF;
				vY *= dF;
				vZ *= dF;

				xScript.DefineVar(sT, vT);
				xScript.DefineVar(sX, vX);
				xScript.DefineVar(sY, vY);
				xScript.DefineVar(sZ, vZ);
				xScript.DefineVar(sP, vPinhole);

				xScript.DrawLinePyramid(sP, sT, sX, sY, sZ, eColA);
				xScript.DrawLine(CLU_S sP << " + " << sZ, sT, eColB);

			}

		}
	}
}

