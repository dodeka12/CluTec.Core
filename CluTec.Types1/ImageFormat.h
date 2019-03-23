////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
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

#include "Defines.h"
#include "ImageType.h"

#ifdef CLU_INTEROP_EXPORTS
#define CLU_TYPES1_API __declspec(dllexport)
#else
#define CLU_TYPES1_API __declspec(dllimport)
#endif

namespace Clu
{

	struct /*__CUDA_ALIGN__(16)*/ _SImageFormat: public _SImageType
	{
		int iWidth;
		int iHeight;

		__CUDA_HDI__ _SImageFormat& operator= (const _SImageFormat& xFormat)
		{
			_SImageType::operator=(xFormat);
			iWidth = xFormat.iWidth;
			iHeight = xFormat.iHeight;
			return *this;
		}

		__CUDA_HDI__ bool IsValid() const
		{
			return (iWidth > 0) && (iHeight > 0) && _SImageType::IsValid();
		}

		template<typename TPixel>
		__CUDA_HDI__ bool IsOfType() const
		{
			return _SImageType::IsOfType<TPixel>();
		}

		template<typename TPixel>
		__CUDA_HDI__ bool IsOfType(const TPixel& xPix) const
		{
			return _SImageType::IsOfType(xPix);
		}

		__CUDA_HDI__ bool IsEqualSize(const _SImageFormat& xFormat) const
		{
			return (iWidth == xFormat.iWidth) && (iHeight == xFormat.iHeight);
		}

		__CUDA_HDI__ bool IsEqualType(const _SImageType& xType) const
		{
			return _SImageType::operator==(xType);
		}

		__CUDA_HDI__ bool IsEqualType(EPixelType ePixelType, EDataType eDataType) const
		{
			return _SImageType::IsEqualType(ePixelType, eDataType);
		}


		__CUDA_HDI__ bool IsEqualDataType(const _SImageFormat& xFormat) const
		{
			return eDataType == xFormat.eDataType;
		}

		__CUDA_HDI__ bool IsEqualPixelType(const _SImageFormat& xFormat) const
		{
			return ePixelType == xFormat.ePixelType;
		}


		__CUDA_HDI__ bool IsInside(int iX, int iY) const
		{
			return (iX >= 0) && (iX < iWidth) && (iY >= 0) && (iY < iHeight);
		}

		__CUDA_HDI__ bool IsInside(int iX, int iY, int iBorderWidth, int iBorderHeight) const
		{
			return (iX >= iBorderWidth) && (iX < iWidth - iBorderWidth) && (iY >= iBorderHeight) && (iY < iHeight - iBorderHeight);
		}

		__CUDA_HDI__ bool IsRectInside(int iLeftX, int iTopY, int iSizeX, int iSizeY) const
		{
			return (iLeftX >= 0) && (iLeftX + iSizeX <= iWidth) && (iTopY >= 0) && (iTopY + iSizeY <= iHeight);
		}

		__CUDA_HDI__ bool operator== (const _SImageFormat& xFormat) const
		{
			return IsEqualSize(xFormat) && IsEqualType(xFormat);
		}

		__CUDA_HDI__ bool operator!= (const _SImageFormat& xFormat) const
		{
			return !(*this == xFormat);
		}

		__CUDA_HDI__ size_t GetPixelIndex(int iX, int iY) const
		{
			return size_t(iY) * size_t(iWidth) + size_t(iX);
		}

		__CUDA_HDI__ void Clear()
		{
			iWidth = 0;
			iHeight = 0;
			_SImageType::Clear();
		}

		__CUDA_HDI__ size_t PixelCount() const
		{
			return size_t(iWidth) * size_t(iHeight);
		}

		__CUDA_HDI__ size_t ByteCount() const
		{
			return PixelCount() * BytesPerPixel();
		}

	};


	struct SImageFormat : public _SImageFormat
	{
		SImageFormat()
		{
			Clear();
		}

		SImageFormat(const SImageFormat& xFormat)
		{
			*this = xFormat;
		}

		SImageFormat(const _SImageFormat& xFormat)
		{
			*this = xFormat;
		}

		SImageFormat(int _nWidth, int _nHeight, EPixelType ePT, EDataType eDT)
		{
			Init(ePT, eDT);
			iWidth = _nWidth;
			iHeight = _nHeight;
		}

		SImageFormat(int _nWidth, int _nHeight, const _SImageType& xType)
		{
			Init(xType);
			iWidth = _nWidth;
			iHeight = _nHeight;
		}

		SImageFormat& operator= (const SImageFormat& xFormat)
		{
			_SImageFormat::operator=(xFormat);
			return *this;
		}

		SImageFormat& operator= (const _SImageFormat& xFormat)
		{
			_SImageFormat::operator=(xFormat);
			return *this;
		}

	};

}

#pragma make_public(Clu::_SImageFormat)
#pragma make_public(Clu::SImageFormat)
