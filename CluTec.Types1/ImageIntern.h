////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      ImageIntern.h
//
// summary:   Declares the image intern class
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

#include "ImageFormat.h"

namespace Clu
{
	class CImageIntern
	{
	public:
		using TData = unsigned char;

	private:
		Clu::SImageFormat m_xFormat;

		TData *m_pucData;
		bool m_bDataOwner;

	protected:
		void _Reset();

	public :

	public:
		CImageIntern();
		CImageIntern(CImageIntern&& xImage);
		CImageIntern(const CImageIntern& xImage);
		CImageIntern(const SImageFormat& xStruct);
		CImageIntern(const SImageFormat& xStruct, const void *pImageData, bool bCopyData = true);
		~CImageIntern();

		CImageIntern& operator= (CImageIntern&& xImage);
		CImageIntern& operator= (const CImageIntern& xImage);

		
		void CopyFrom(const CImageIntern& xImage);
		void CropFrom(const CImageIntern& xImage, int iX, int iY, int iWidth, int iHeight, bool bYOriginAtTop = true);
		void Insert(const CImageIntern& xImage, int iX, int iY, bool bYOriginAtTop = true);

		void Create(const SImageFormat& xStruct);
		void Create(const SImageFormat& xStruct, const void *pImageData, bool bCopyData = true);
		
		void Destroy();


		bool IsValid() const
		{
			return m_pucData != nullptr;
		}

		bool IsDataOwner() const
		{
			return m_bDataOwner;
		}

		bool IsOfType(Clu::EDataType eDataType, Clu::EPixelType ePixelType)
		{
			return (m_xFormat.eDataType == eDataType && m_xFormat.ePixelType == ePixelType);
		}

		bool IsOfType(const CImageIntern& xImage)
		{
			return IsOfType(xImage.m_xFormat.eDataType, xImage.m_xFormat.ePixelType);
		}

		const SImageFormat& Format() const
		{
			return m_xFormat;
		}

		size_t BytesPerPixel() const
		{
			return m_xFormat.BytesPerPixel();
		}

		size_t PixelCount() const
		{
			return m_xFormat.PixelCount();
		}

		size_t ByteCount() const
		{
			return m_xFormat.ByteCount();
		}

		int Width() const
		{
			return m_xFormat.iWidth;
		}

		int Height() const
		{
			return m_xFormat.iHeight;
		}

		void GetSize(int& nWidth, int& nHeight) const
		{
			nWidth = m_xFormat.iWidth;
			nHeight = m_xFormat.iHeight;
		}

		Clu::EDataType DataType() const
		{
			return m_xFormat.eDataType;
		}

		Clu::EPixelType PixelType() const
		{
			return m_xFormat.ePixelType;
		}

		const SImageType& Type() const
		{
			return (const SImageType&)m_xFormat;
		}

		void* DataPointer()
		{
			return (void *)m_pucData;
		}

		const void* DataPointer() const
		{
			return (const void *)m_pucData;
		}

	};


}
