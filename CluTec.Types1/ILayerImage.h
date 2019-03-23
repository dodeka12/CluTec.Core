////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      ILayerImage.h
//
// summary:   Declares the ILayerImage interface
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
	class CILayerImageImpl;

	class CLU_TYPES1_API CILayerImage
	{
	public:

	private:
		CILayerImageImpl *m_pImpl;

	public:
		CILayerImage();
		CILayerImage(CILayerImage&& xImage);
		CILayerImage(const CILayerImage& xImage);

		CILayerImage(const SImageFormat& xStruct);
		CILayerImage(const SImageFormat& xStruct, const void **ppImageLayerData, size_t nLayerCount, bool bCopyData = true);

		~CILayerImage();

		CILayerImage& operator= (CILayerImage&& xImage);
		CILayerImage& operator= (const CILayerImage& xImage);

		bool IsValidRef() const;
		bool IsValid() const;
		bool IsCompactMemoryBlock() const;
		bool IsDataOwner() const;

		template<typename TPixel>
		bool IsOfType()
		{
			return (TPixel::PixelTypeId == PixelType()) && (TPixel::DataTypeId == DataType());
		}

		CILayerImage Copy() const;
		CILayerImage Crop(int nX, int nY, int nWidth, int nHeight, bool bYOriginAtTop = true) const;
		void Insert(const CILayerImage& xImage, int nX, int nY, bool bYOriginAtTop = true);

		void Create(const SImageFormat& xStruct);
		void Create(const SImageFormat& xStruct, const void **ppImageLayerData, size_t nLayerCount, bool bCopyData = true);

		void Destroy();
		void Release();

		const SImageFormat& Format() const;

		int Width() const;
		int Height() const;
		void GetSize(int& nWidth, int& nHeight) const;

		Clu::EDataType DataType() const;
		Clu::EPixelType PixelType() const;
		const SImageType& GetType() const;

		size_t LayerCount() const;
		size_t BytesPerPixel() const;
		size_t BytesPerLayerPixel() const;
		size_t PixelCount() const;
		size_t LayerByteCount() const;
		size_t TotalByteCount() const;

		void* DataPointer(size_t nLayerId);
		const void* DataPointer(size_t nLayerId) const;
	};

} // namespace Clu

#pragma make_public(Clu::CILayerImage)
