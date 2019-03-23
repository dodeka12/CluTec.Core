////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Net.Base
// file:      ImageType.cpp
//
// summary:   Implements the image type class
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
#include "ImageType.h"

namespace Clu
{
	namespace Net
	{

		size_t ImageType::SizeOf(DataTypes eDataType)
		{
			switch (eDataType)
			{
			case DataTypes::Unknown:
				return 0;
			case DataTypes::Int8:
				return 1;
			case DataTypes::UInt8:
				return 1;
			case DataTypes::Int16:
				return 2;
			case DataTypes::UInt16:
				return 2;
			case DataTypes::Int32:
				return 4;
			case DataTypes::UInt32:
				return 4;
			case DataTypes::Single:
				return 4;
			case DataTypes::Double:
				return 8;

			default:
				return 0;
			}
		}

		size_t ImageType::DimOf(PixelTypes ePixelType)
		{
			switch (ePixelType)
			{
			case PixelTypes::Unknown:
				return 0;
			case PixelTypes::RGB:
				return 3;
			case PixelTypes::RGBA:
				return 4;
			case PixelTypes::BGR:
				return 3;
			case PixelTypes::BGRA:
				return 4;
			case PixelTypes::Lum:
				return 1;
			case PixelTypes::LumA:
				return 2;
			case PixelTypes::BayerRG:
				return 1;
			case PixelTypes::BayerBG:
				return 1;
			case PixelTypes::BayerGR:
				return 1;
			case PixelTypes::BayerGB:
				return 1;
			default:
				return 0;
				break;
			}
		}

		bool ImageType::IsBayerPixelType(PixelTypes ePixelType)
		{
			return (ePixelType >= PixelTypes::BayerFirst && ePixelType <= PixelTypes::BayerLast);
		}

	} // namespace Net
} // namespace Clu
