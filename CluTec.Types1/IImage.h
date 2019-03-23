////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      IImage.h
//
// summary:   Declares the IImage interface
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


#ifdef CLU_INTEROP_EXPORTS
#define CLU_TYPES1_API __declspec(dllexport)
#else
#define CLU_TYPES1_API __declspec(dllimport)
#endif

#include "ImageFormat.h"

namespace Clu
{
	class CIImageImpl;

	class CLU_TYPES1_API CIImage
	{
	public:

	private:
		CIImageImpl *m_pImpl;

	public:
		CIImage();
		CIImage(CIImage&& xImage);
		CIImage(const CIImage& xImage);

		CIImage(const SImageFormat& xStruct);
		CIImage(const SImageFormat& xStruct, const void *pImageData, bool bCopyData = true);

		~CIImage();

		CIImage& operator= (CIImage&& xImage);
		CIImage& operator= (const CIImage& xImage);

		bool IsValidRef() const;
		bool IsValid() const;
		bool IsDataOwner() const;

		template<typename TPixel>
		bool IsOfType()
		{
			return (TPixel::PixelTypeId == PixelType()) && (TPixel::DataTypeId == DataType());
		}

		CIImage Copy() const;
		CIImage Crop(int nX, int nY, int nWidth, int nHeight, bool bYOriginAtTop = true) const;
		void Insert(const CIImage& xImage, int nX, int nY, bool bYOriginAtTop = true);

		void Create(const SImageFormat& xStruct);
		void Create(const SImageFormat& xStruct, const void *pImageData, bool bCopyData = true);

		void Destroy();
		void Release();

		const SImageFormat& Format() const;

		int Width() const;
		int Height() const;
		void GetSize(int& nWidth, int& nHeight) const;

		Clu::EDataType DataType() const;
		Clu::EPixelType PixelType() const;
		const SImageType& GetType() const;

		size_t BytesPerPixel() const;
		size_t PixelCount() const;
		size_t ByteCount() const;

		void* DataPointer();
		const void* DataPointer() const;
	};

} // namespace Clu

#pragma make_public(Clu::CIImage)
