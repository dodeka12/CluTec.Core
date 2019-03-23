////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Net.Base
// file:      ImageType.h
//
// summary:   Declares the image type class
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
#include "CluTec.Types1/ImageType.h"
#pragma managed (pop)

#include "ImageTypes.h"


namespace Clu
{
	namespace Net
	{
		public ref struct ImageType
		{
			Clu::Net::DataTypes DataType;
			Clu::Net::PixelTypes PixelType;

			ImageType()
			{
				Clear();
			}

			ImageType(ImageType^ xType)
			{
				DataType = xType->DataType;
				PixelType = xType->PixelType;
			}

			ImageType(PixelTypes ePT, DataTypes eDT)
			{
				DataType = eDT;
				PixelType = ePT;
			}

			ImageType(const Clu::SImageType& xType)
			{
				DataType = DataTypes(xType.eDataType);
				PixelType = PixelTypes(xType.ePixelType);
			}

			bool operator== (ImageType^ xType)
			{
				return (DataType == xType->DataType) && (PixelType == xType->PixelType);
			}

			bool operator!= (ImageType^ xType)
			{
				return !(*this == xType);
			}

			void Clear()
			{
				DataType = DataTypes::Unknown;
				PixelType = PixelTypes::Unknown;
			}

			size_t BytesPerPixel()
			{
				return SizeOf(DataType) * DimOf(PixelType);
			}

			bool IsBayerPixelType()
			{
				return IsBayerPixelType(PixelType);
			}

			static size_t SizeOf(DataTypes eDataType);
			static size_t DimOf(PixelTypes ePixelType);
			static bool IsBayerPixelType(PixelTypes ePixelType);

		};
	} // namespace Net
} // namespace Clu

