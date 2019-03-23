////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Net.Base
// file:      ImageFormat.h
//
// summary:   Declares the image format class
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

#pragma managed (push, off)
#include "CluTec.Types1/ImageFormat.h"
#pragma managed (pop)

#include "ImageType.h"


namespace Clu
{
	namespace Net
	{
		public ref struct ImageFormat : public ImageType
		{
			int Width;
			int Height;

			ImageFormat()
			{
				Clear();
			}

			ImageFormat(ImageFormat^ xS) 
				: ImageType(xS)
			{
				Width = xS->Width;
				Height = xS->Height;
			}

			ImageFormat(int _nWidth, int _nHeight, PixelTypes ePT, DataTypes eDT)
				: ImageType(ePT, eDT)
			{
				Width = _nWidth;
				Height = _nHeight;
			}

			ImageFormat(int _nWidth, int _nHeight, ImageType^ xType)
				: ImageType(xType)
			{
				Width = _nWidth;
				Height = _nHeight;
			}

			ImageFormat(const Clu::SImageFormat& xS)
				: ImageType(xS)
			{
				Width = xS.iWidth;
				Height = xS.iHeight;
			}

			bool operator== (ImageFormat^ xType)
			{
				return (Width == xType->Width) && (Height == xType->Height) && ImageType::operator==(xType);
			}

			bool operator!= (ImageFormat^ xType)
			{
				return !(*this == xType);
			}

			void Clear()
			{
				Width = 0;
				Height = 0;
				ImageType::Clear();
			}

			size_t PixelCount()
			{
				return size_t(Width) * size_t(Height);
			}

			size_t ByteCount() 
			{
				return PixelCount() * BytesPerPixel();
			}

		};
	} // namespace Net
} // namespace Clu

