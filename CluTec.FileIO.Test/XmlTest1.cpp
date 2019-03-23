#include "stdafx.h"
#include "CppUnitTest.h"

#include "CluTec.Types1/IException.h"
#include "CluTec.FileIO/Xml.h"

#include "CluTec.Base/Conversion.h"
#include "CluTec.Math/Static.Matrix.h"
#include "CluTec.Math/Static.Matrix.IO.h"
#include "CluTec.Math/Static.Vector.h"
#include "CluTec.Math/Static.Vector.IO.h"

#include "CluTec.ImgProc/Camera.Pinhole.h"
#include "CluTec.ImgProc/Camera.IO.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CluTecFileIOTest
{		
	TEST_CLASS(XmlTest1)
	{
	public:
		
		TEST_METHOD(TestXPath1)
		{
			using TMat = Clu::SMatrix<float, 3>;

			try
			{

				Clu::Xml::CIDocument xDoc;

				xDoc.CreateFromFile(R"(X:\_Images\TIS\bilder_christian\cam0.xml)");

				Clu::Xml::CIXPath xCam = xDoc("/opencv_storage/cam0_K/data");

				size_t nCount = xCam.Count();
				Clu::CIString sContent = xCam.Content(0);

				TMat mA;
				Clu::ReadMatrix(mA, Clu::ToStdString(sContent), true);

				Logger::WriteMessage(sContent.ToCString());
			}
			catch (Clu::CIException & xEx)
			{

				Logger::WriteMessage(xEx.ToStringComplete().ToCString());
				Assert::IsTrue(false, L"Exception thrown");
			}
		}

		TEST_METHOD(TestReadPinholeCamera)
		{
			using TMat = Clu::SMatrix<float, 3>;
			using TPinhole = Clu::Camera::_CPinhole<float>;

			try
			{
				TPinhole camPinhole;

				Clu::CIString sFilename = R"(X:\_Images\TIS\bilder_christian\cam0.xml)";

				int iCamId = 0;
				Clu::CIString sCamBase = "cam";
				sCamBase += iCamId;
				sCamBase += "_";

				Clu::Camera::PinholeIO<Clu::Camera::EStyle::OpenCV>::Read(camPinhole, sFilename
					, sCamBase + "K"
					, sCamBase + "R"
					, sCamBase + "T"
					, sCamBase + "dist"
					, sCamBase + "res");

				Clu::CIString sText;
				sText << "Frame R:\n" << ToIString(camPinhole.Sensor().FrameM_s_w().Basis_l_r(), "%6.2f") << "\n";
				sText << "Origin:\n" << ToIString(camPinhole.Sensor().FrameM_s_w().Translation_l_r(), "%6.2f") << "\n";
				Logger::WriteMessage(sText.ToCString());
			}
			catch (Clu::CIException & xEx)
			{

				Logger::WriteMessage(xEx.ToStringComplete().ToCString());
				Assert::IsTrue(false, L"Exception thrown");
			}
		}

	};
}