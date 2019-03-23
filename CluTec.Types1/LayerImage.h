////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      LayerImage.h
//
// summary:   Declares the layer image class
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
#include <vector>

#include "IException.h"
#include "ImageFormat.h"

namespace Clu
{
	class CLayerImage
	{
	public:
		using TData = unsigned char;
		using TLayerVec = std::vector<TData*>;

	private:
		Clu::SImageFormat m_xFormat;

		TLayerVec m_vecLayerPtr;
		bool m_bDataOwner;
		bool m_bIsCompactMemoryBlock;

	protected:
		void _Reset();

	public :

	public:
		CLayerImage();
		CLayerImage(CLayerImage&& xImage);
		CLayerImage(const CLayerImage& xImage);
		CLayerImage(const SImageFormat& xFormat);
		CLayerImage(const SImageFormat& xFormat, const void **ppImageLayerData, size_t nLayerCount, bool bCopyData = true);
		~CLayerImage();

		CLayerImage& operator= (CLayerImage&& xImage);
		CLayerImage& operator= (const CLayerImage& xImage);

		
		void CopyFrom(const CLayerImage& xImage);
		void CropFrom(const CLayerImage& xImage, int iX, int iY, int iWidth, int iHeight, bool bYOriginAtTop = true);
		void Insert(const CLayerImage& xImage, int iX, int iY, bool bYOriginAtTop = true);

		void Create(const SImageFormat& xFormat);
		void Create(const SImageFormat& xFormat, const void **ppImageLayerData, size_t nLayerCount, bool bCopyData = true);

		template<typename T>
		void Create(const SImageFormat& xFormat, const std::vector<T*>& vecLayerData, bool bCopyData = true)
		{
			Create(xFormat, (const void **) vecLayerData.data(), vecLayerData.size(), bCopyData);
		}

		void Destroy();


		bool IsValid() const
		{
			if (m_vecLayerPtr.size() == 0)
				return false;

			for (auto pLayer : m_vecLayerPtr)
			{
				if (pLayer == nullptr)
				{
					return false;
				}
			}

			return true;
		}

		bool IsDataOwner() const
		{
			return m_bDataOwner;
		}

		bool IsCompactMemoryBlock() const
		{
			return m_bIsCompactMemoryBlock;
		}

		bool IsOfType(Clu::EDataType eDataType, Clu::EPixelType ePixelType)
		{
			return (m_xFormat.eDataType == eDataType && m_xFormat.ePixelType == ePixelType);
		}

		bool IsOfType(const CLayerImage& xImage)
		{
			return IsOfType(xImage.m_xFormat.eDataType, xImage.m_xFormat.ePixelType);
		}

		const SImageFormat& Format() const
		{
			return m_xFormat;
		}

		size_t LayerCount() const
		{
			return m_vecLayerPtr.size();
		}

		size_t BytesPerPixel() const
		{
			return m_xFormat.BytesPerPixel();
		}

		size_t BytesPerLayerPixel() const
		{
			return SImageFormat::SizeOf(m_xFormat.eDataType);
		}

		size_t PixelCount() const
		{
			return m_xFormat.PixelCount();
		}

		size_t LayerByteCount() const
		{
			return m_xFormat.PixelCount() * SImageType::SizeOf(m_xFormat.eDataType);
		}

		size_t TotalByteCount() const
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

		void* DataPointer(size_t nLayerId)
		{
			if (nLayerId >= m_vecLayerPtr.size())
			{
				throw CLU_EXCEPTION("Invalid layer id");
			}

			return (void *)m_vecLayerPtr[nLayerId];
		}

		const void* DataPointer(size_t nLayerId) const
		{
			if (nLayerId >= m_vecLayerPtr.size())
			{
				throw CLU_EXCEPTION("Invalid layer id");
			}

			return (void *)m_vecLayerPtr[nLayerId];
		}

	};


}
