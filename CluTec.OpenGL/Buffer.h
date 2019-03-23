////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.OpenGL
// file:      Buffer.h
//
// summary:   Declares the buffer class
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



namespace Clu
{
	namespace OpenGL
	{
		enum class EBufferUsage
		{
			StreamDraw = 0x88E0,
			StreamRead = 0x88E1,
			StreamCopy = 0x88E2,
			StaticDraw = 0x88E4,
			StaticRead = 0x88E5,
			StaticCopy = 0x88E6,
			DynamicDraw = 0x88E8,
			DynamicRead = 0x88E9,
			DynamicCopy = 0x88EA,
		};


		enum class EBufferType
		{
			Vertex = 0x8892,
			Element = 0x8893,
		};


		template<EBufferType t_eType, typename _TElement>
		class CBuffer
		{
		public:
			using TElement = _TElement;

			static const EBufferType Type = t_eType;

		protected:
			unsigned m_uId;
			size_t m_nCount;
			bool m_bIsBound;
			EBufferUsage m_eUsage;

		public:
			CBuffer();
			CBuffer(const CBuffer&) = delete;

			~CBuffer();

			CBuffer& operator= (const CBuffer&) = delete;

			bool IsValid() const
			{
				return m_uId > 0 && m_nCount > 0;
			}

			bool IsBound() const
			{
				return m_bIsBound;
			}

			size_t Count() const
			{
				return m_nCount;
			}

			size_t ByteCount() const
			{
				return m_nCount * sizeof(TElement);
			}

			unsigned Id() const
			{
				return m_uId;
			}

			void Create(size_t nCount, EBufferUsage eUsage);
			void Create(size_t nCount, EBufferUsage eUsage, const TElement* pData);
			void Update(const TElement* pData);
			void Destroy();

			void Bind();
			void Unbind();
		};


	}
}