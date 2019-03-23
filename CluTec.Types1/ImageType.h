////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
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

#include "Defines.h"
#include "ImageTypes.h"
#include "Pixel.h"

#ifdef CLU_INTEROP_EXPORTS
#define CLU_TYPES1_API __declspec(dllexport)
#else
#define CLU_TYPES1_API __declspec(dllimport)
#endif

namespace Clu
{

	struct /*__CUDA_ALIGN__(8)*/ _SImageType
	{
		EDataType eDataType;
		EPixelType ePixelType;

		__CUDA_HDI__ _SImageType& operator= (const _SImageType& xType)
		{
			eDataType = xType.eDataType;
			ePixelType = xType.ePixelType;
			return *this;
		}

		__CUDA_HDI__ void Init(const _SImageType& xType)
		{
			*this = xType;
		}

		__CUDA_HDI__ void Init(EPixelType ePT, EDataType eDT)
		{
			eDataType = eDT;
			ePixelType = ePT;
		}

		__CUDA_HDI__ bool IsValid() const
		{
			return (eDataType != EDataType::Unknown && ePixelType != EPixelType::Unknown);
		}

		template<typename TPixel>
		__CUDA_HDI__ bool IsOfType() const
		{
			return (eDataType == TPixel::DataTypeId) && (ePixelType == TPixel::PixelTypeId);
		}

		template<typename TPixel>
		__CUDA_HDI__ bool IsOfType(const TPixel& xPix) const
		{
			return (eDataType == TPixel::DataTypeId) && (ePixelType == TPixel::PixelTypeId);
		}

		__CUDA_HDI__ bool IsEqualType(EPixelType _ePixelType, EDataType _eDataType) const
		{
			return (ePixelType == _ePixelType && eDataType == _eDataType);
		}

		__CUDA_HDI__ bool operator== (const _SImageType& xType) const
		{
			return (eDataType == xType.eDataType) && (ePixelType == xType.ePixelType);
		}

		__CUDA_HDI__ bool operator!= (const _SImageType& xType) const
		{
			return !(*this == xType);
		}

		__CUDA_HDI__ void Clear()
		{
			eDataType = EDataType::Unknown;
			ePixelType = EPixelType::Unknown;
		}

		__CUDA_HDI__ size_t BytesPerPixel() const
		{
			return SizeOf(eDataType) * DimOf(ePixelType);
		}

		__CUDA_HDI__ bool IsBayerPixelType() const
		{
			return IsBayerPixelType(ePixelType);
		}

		static __CUDA_HD__ size_t SizeOf(EDataType eDataType)
		{
			switch (eDataType)
			{
			case EDataType::Unknown:
				return 0;
			case EDataType::Int8:
				return SDataTypeInfo<EDataType::Int8>::Bytes;
			case EDataType::UInt8:
				return SDataTypeInfo<EDataType::UInt8>::Bytes;
			case EDataType::Int16:
				return SDataTypeInfo<EDataType::Int16>::Bytes;
			case EDataType::UInt16:
				return SDataTypeInfo<EDataType::UInt16>::Bytes;
			case EDataType::Int32:
				return SDataTypeInfo<EDataType::Int32>::Bytes;
			case EDataType::UInt32:
				return SDataTypeInfo<EDataType::UInt32>::Bytes;
			case EDataType::Single:
				return SDataTypeInfo<EDataType::Single>::Bytes;
			case EDataType::Double:
				return SDataTypeInfo<EDataType::Double>::Bytes;

			default:
				return 0;
			}
		}

		static __CUDA_HD__ size_t DimOf(EPixelType ePixelType)
		{
			switch (ePixelType)
			{
			case Clu::EPixelType::Unknown:
				return 0;
			case Clu::EPixelType::RGB:
				return SPixelTypeInfo<EPixelType::RGB>::ChannelCount;
			case Clu::EPixelType::RGBA:
				return SPixelTypeInfo<EPixelType::RGBA>::ChannelCount;
			case Clu::EPixelType::BGR:
				return SPixelTypeInfo<EPixelType::BGR>::ChannelCount;
			case Clu::EPixelType::BGRA:
				return SPixelTypeInfo<EPixelType::RGBA>::ChannelCount;
			case Clu::EPixelType::Lum:
				return SPixelTypeInfo<EPixelType::Lum>::ChannelCount;
			case Clu::EPixelType::LumA:
				return SPixelTypeInfo<EPixelType::LumA>::ChannelCount;
			case Clu::EPixelType::BayerRG:
				return 1;
			case Clu::EPixelType::BayerBG:
				return 1;
			case Clu::EPixelType::BayerGR:
				return 1;
			case Clu::EPixelType::BayerGB:
				return 1;
			default:
				return 0;
			}
		}

		static __CUDA_HD__ size_t ColorDimOf(EPixelType ePixelType)
		{
			switch (ePixelType)
			{
			case Clu::EPixelType::Unknown:
				return 0;
			case Clu::EPixelType::RGB:
				return SPixelTypeInfo<EPixelType::RGB>::ColorCount;
			case Clu::EPixelType::RGBA:
				return SPixelTypeInfo<EPixelType::RGBA>::ColorCount;
			case Clu::EPixelType::BGR:
				return SPixelTypeInfo<EPixelType::BGR>::ColorCount;
			case Clu::EPixelType::BGRA:
				return SPixelTypeInfo<EPixelType::RGBA>::ColorCount;
			case Clu::EPixelType::Lum:
				return SPixelTypeInfo<EPixelType::Lum>::ColorCount;
			case Clu::EPixelType::LumA:
				return SPixelTypeInfo<EPixelType::LumA>::ColorCount;
			case Clu::EPixelType::BayerRG:
				return 1;
			case Clu::EPixelType::BayerBG:
				return 1;
			case Clu::EPixelType::BayerGR:
				return 1;
			case Clu::EPixelType::BayerGB:
				return 1;
			default:
				return 0;
			}
		}

		static __CUDA_HD__ size_t AlphaDimOf(EPixelType ePixelType)
		{
			switch (ePixelType)
			{
			case Clu::EPixelType::Unknown:
				return 0;
			case Clu::EPixelType::RGB:
				return SPixelTypeInfo<EPixelType::RGB>::AlphaCount;
			case Clu::EPixelType::RGBA:
				return SPixelTypeInfo<EPixelType::RGBA>::AlphaCount;
			case Clu::EPixelType::BGR:
				return SPixelTypeInfo<EPixelType::BGR>::AlphaCount;
			case Clu::EPixelType::BGRA:
				return SPixelTypeInfo<EPixelType::RGBA>::AlphaCount;
			case Clu::EPixelType::Lum:
				return SPixelTypeInfo<EPixelType::Lum>::AlphaCount;
			case Clu::EPixelType::LumA:
				return SPixelTypeInfo<EPixelType::LumA>::AlphaCount;
			case Clu::EPixelType::BayerRG:
				return 1;
			case Clu::EPixelType::BayerBG:
				return 1;
			case Clu::EPixelType::BayerGR:
				return 1;
			case Clu::EPixelType::BayerGB:
				return 1;
			default:
				return 0;
			}
		}

		static __CUDA_HD__ bool IsBayerPixelType(EPixelType ePixelType)
		{
			return (ePixelType >= EPixelType::BayerFirst && ePixelType <= EPixelType::BayerLast);
		}

	};



	struct SImageType : public _SImageType
	{
		SImageType()
		{
			Clear();
		}

		SImageType(const SImageType& xType)
		{
			*this = xType;
		}

		SImageType(const _SImageType& xType)
		{
			*this = xType;
		}

		SImageType(EPixelType ePT, EDataType eDT)
		{
			Init(ePT, eDT);
		}

		SImageType& operator= (const SImageType& xType)
		{
			_SImageType::operator=(xType);
			return *this;
		}

		SImageType& operator= (const _SImageType& xType)
		{
			_SImageType::operator=(xType);
			return *this;
		}

	};
}

#pragma make_public(Clu::_SImageType)
#pragma make_public(Clu::SImageType)
