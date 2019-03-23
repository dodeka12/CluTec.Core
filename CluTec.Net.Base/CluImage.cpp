////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Net.Base
// file:      CluImage.cpp
//
// summary:   Implements the clu image class
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
#include "CluImage.h"

#pragma managed (push, off)
#include "CluTec.Types1/IImage.h"
#pragma managed (pop)


namespace Clu
{
	namespace Net
	{

		CluImage::CluImage()
		{
			m_pImage = new Clu::CIImage();
		}

		CluImage::~CluImage()
		{
			if (m_pImage != nullptr)
			{
				this->!CluImage();
			}
		}

		CluImage::!CluImage()
		{
			delete m_pImage;
			m_pImage = nullptr;
		}


		CluImage::CluImage(const Clu::CIImage& xImage)
		{
			m_pImage = new Clu::CIImage(xImage);
		}

		CluImage::CluImage(Clu::Net::ImageFormat^ xS)
		{
			m_pImage = new Clu::CIImage(Clu::SImageFormat(xS->Width, xS->Height, Clu::EPixelType(xS->PixelType), Clu::EDataType(xS->DataType)));
		}


		Clu::Net::ImageFormat^ CluImage::Format::get()
		{
			return gcnew Clu::Net::ImageFormat(m_pImage->Format());
		}


		void CluImage::CopyFrom(const Clu::CIImage& xImage)
		{
			*m_pImage = xImage.Copy();
		}

		CluImage^ CluImage::Copy()
		{
			return gcnew CluImage(m_pImage->Copy());
		}

		bool CluImage::IsValid()
		{
			if (m_pImage == nullptr)
				return false;

			return m_pImage->IsValid();
		}

		void CluImage::Create(Clu::Net::ImageFormat^ xS)
		{
			m_pImage->Create(Clu::SImageFormat(xS->Width, xS->Height, Clu::EPixelType(xS->PixelType), Clu::EDataType(xS->DataType)));
		}

		System::IntPtr CluImage::DataPointer()
		{
			return System::IntPtr(m_pImage->DataPointer());
		}


		Clu::CIImage CluImage::ToIImage()
		{
			return Clu::CIImage(*m_pImage);
		}

	} // namespace Net
} // namespace Clu
