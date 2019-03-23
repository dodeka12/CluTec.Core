////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      Pixel.h
//
// summary:   Declares the pixel class
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

#include <cstdint>
#include <limits>

#include "Defines.h"
#include "ImageTypes.h"

namespace Clu
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Information about the pixel type. </summary>
	///
	/// <typeparam name="t_ePixelType"> 	Type of the pixel type. </typeparam>
	/// <typeparam name="t_uColorCount">	Type of the color count. </typeparam>
	/// <typeparam name="t_uAlphaCount">	Type of the alpha count. </typeparam>
	/// <typeparam name="t_uRedIdx">		Type of the red index. </typeparam>
	/// <typeparam name="t_uGreenIdx">  	Type of the green index. </typeparam>
	/// <typeparam name="t_uBlueIdx">   	Type of the blue index. </typeparam>
	/// <typeparam name="t_uAlphaIdx">  	Type of the alpha index. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////

#define STATIC_FUNC(theName, theValue) \
	__CUDA_HDI__ static T theName() { return T(theValue); }

#define STATIC_CONST(theName, theValue) \
	static const T theName = T(theValue)


	template<EPixelType t_ePixelType>
	struct SPixelTypeInfo
	{
		using T = int;

		static const EPixelType PixelTypeId = t_ePixelType;

		STATIC_CONST(ColorCount, 0);
		STATIC_CONST(AlphaCount, 0);
		STATIC_CONST(ChannelCount, ColorCount + AlphaCount);
		STATIC_CONST(RedIndex, -1);
		STATIC_CONST(GreenIndex, -1);
		STATIC_CONST(BlueIndex, -1);
		STATIC_CONST(AlphaIndex, -1);
	};

#define DECL_PIXEL_TYPE(theId, ColCnt, AlphaCnt, RedIdx, GreenIdx, BlueIdx, AlphaIdx) \
	template<> struct SPixelTypeInfo<theId> \
									{ \
		using T = int; \
		static const EPixelType PixelTypeId = theId; \
		STATIC_CONST(ColorCount, ColCnt); \
		STATIC_CONST(AlphaCount, AlphaCnt); \
		STATIC_CONST(ChannelCount, ColorCount + AlphaCount); \
		STATIC_CONST(RedIndex, RedIdx); \
		STATIC_CONST(GreenIndex, GreenIdx); \
		STATIC_CONST(BlueIndex, BlueIdx); \
		STATIC_CONST(AlphaIndex, AlphaIdx); \
	}

	DECL_PIXEL_TYPE(EPixelType::Lum, 1, 0, 0, 0, 0, 0);
	DECL_PIXEL_TYPE(EPixelType::LumA, 1, 1, 0, 0, 0, 1);

	DECL_PIXEL_TYPE(EPixelType::RGB, 3, 0, 0, 1, 2, 0);
	DECL_PIXEL_TYPE(EPixelType::RGBA, 3, 1, 0, 1, 2, 3);

	DECL_PIXEL_TYPE(EPixelType::BGR, 3, 0, 2, 1, 0, 0);
	DECL_PIXEL_TYPE(EPixelType::BGRA, 3, 1, 2, 1, 0, 3);

#undef DECL_PIXEL_TYPE

	using T_Lum = SPixelTypeInfo<EPixelType::Lum>;
	using T_LumA = SPixelTypeInfo<EPixelType::LumA>;

	using T_RGB = SPixelTypeInfo<EPixelType::RGB>;
	using T_RGBA = SPixelTypeInfo<EPixelType::RGBA>;

	using T_BGR = SPixelTypeInfo<EPixelType::BGR>;
	using T_BGRA = SPixelTypeInfo<EPixelType::BGRA>;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Information about the data type. </summary>
	///
	/// <typeparam name="t_eDataType">	Type of the data type. </typeparam>
	/// <typeparam name="_TData">	  	Type of the data. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<EDataType t_eDataType>
	struct SDataTypeInfo
	{
		//using TData = void;
		//static const EDataType DataTypeId = t_eDataType;

		//static const int Bytes = int(sizeof(TData));
		//static const int Bits = int(8 * Bytes);
	};

#define DECL_DATA_TYPE(theId, theType) \
	template<> struct SDataTypeInfo<theId> \
	{ \
			using TData = theType; \
			static const EDataType DataTypeId = theId; \
			static const int Bytes = int(sizeof(TData)); \
			static const int Bits = int(8 * Bytes); \
	}

	DECL_DATA_TYPE(EDataType::Int8, int8_t);
	DECL_DATA_TYPE(EDataType::Int16, int16_t);
	DECL_DATA_TYPE(EDataType::Int32, int32_t);

	DECL_DATA_TYPE(EDataType::UInt8,  uint8_t);
	DECL_DATA_TYPE(EDataType::UInt16, uint16_t);
	DECL_DATA_TYPE(EDataType::UInt32, uint32_t);

	DECL_DATA_TYPE(EDataType::Single, float);
	DECL_DATA_TYPE(EDataType::Double, double);

#undef DECL_DATA_TYPE

	using T_Int8 = SDataTypeInfo<EDataType::Int8>;
	using T_Int16 = SDataTypeInfo<EDataType::Int16>;
	using T_Int32 = SDataTypeInfo<EDataType::Int32>;

	using T_UInt8 = SDataTypeInfo<EDataType::UInt8>;
	using T_UInt16 = SDataTypeInfo<EDataType::UInt16>;
	using T_UInt32 = SDataTypeInfo<EDataType::UInt32>;

	using T_Single = SDataTypeInfo<EDataType::Single>;
	using T_Double = SDataTypeInfo<EDataType::Double>;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	A pixel. </summary>
	///
	/// <typeparam name="TPixelTypeInfo">	Type of the pixel type information. </typeparam>
	/// <typeparam name="TDataTypeInfo"> 	Type of the data type information. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename TPixelTypeInfo, typename TDataTypeInfo>
	struct SPixel
	{
		using TPixelType = TPixelTypeInfo;
		using TDataType = TDataTypeInfo;
		using TThis = SPixel<TPixelType, TDataType>;
		using T = typename TPixelTypeInfo::T;
		using TData = typename TDataTypeInfo::TData;
		static const EDataType DataTypeId = TDataTypeInfo::DataTypeId;
		static const EPixelType PixelTypeId = TPixelTypeInfo::PixelTypeId;

		static const T ColorCount = TPixelTypeInfo::ColorCount;
		static const T AlphaCount = TPixelTypeInfo::AlphaCount;
		static const T ChannelCount = TPixelTypeInfo::ChannelCount;
		static const T RedIndex = TPixelTypeInfo::RedIndex;
		static const T GreenIndex = TPixelTypeInfo::GreenIndex;
		static const T BlueIndex = TPixelTypeInfo::BlueIndex;
		static const T AlphaIndex = TPixelTypeInfo::AlphaIndex;

		static const T BytesPerChannel = TDataTypeInfo::Bytes;
		static const T BitsPerChannel = TDataTypeInfo::Bits;

		TData pPixel[ChannelCount];

		template<typename TPixel2>
		__CUDA_HDI__ TThis& operator= (const TPixel2& xPixel)
		{
			r() = xPixel.r();
			g() = xPixel.g();
			b() = xPixel.b();
			a() = xPixel.a();
		}

		__CUDA_HDI__ TData& operator[] (unsigned uIdx)
		{
			return pPixel[uIdx];
		}

		__CUDA_HDI__ const TData& operator[] (unsigned uIdx) const
		{
			return pPixel[uIdx];
		}

		__CUDA_HDI__ void SetZero()
		{
			for (int i = 0; i < ChannelCount; ++i)
			{
				pPixel[i] = TData(0);
			}
		}

		__CUDA_HDI__ TData& r()
		{
			return pPixel[RedIndex];
		}

		__CUDA_HDI__ TData& g()
		{
			return pPixel[GreenIndex];
		}

		__CUDA_HDI__ TData& b()
		{
			return pPixel[BlueIndex];
		}

		__CUDA_HDI__ TData& a()
		{
			return pPixel[AlphaIndex];
		}

		__CUDA_HDI__ const TData& r() const
		{
			return pPixel[RedIndex];
		}

		__CUDA_HDI__ const TData& g() const
		{
			return pPixel[GreenIndex];
		}

		__CUDA_HDI__ const TData& b() const
		{
			return pPixel[BlueIndex];
		}

		__CUDA_HDI__ const TData& a() const
		{
			return pPixel[AlphaIndex];
		}

	};

#undef STATIC_FUNC
#undef STATIC_CONST

	using TPixel_Lum_Int8  = SPixel<T_Lum, T_Int8>;
	using TPixel_Lum_Int16 = SPixel<T_Lum, T_Int16>;
	using TPixel_Lum_Int32 = SPixel<T_Lum, T_Int32>;
	using TPixel_Lum_UInt8 = SPixel<T_Lum, T_UInt8>;
	using TPixel_Lum_UInt16 = SPixel<T_Lum, T_UInt16>;
	using TPixel_Lum_UInt32 = SPixel<T_Lum, T_UInt32>;
	using TPixel_Lum_Single = SPixel<T_Lum, T_Single>;
	using TPixel_Lum_Double = SPixel<T_Lum, T_Double>;

	using TPixel_LumA_Int8  = SPixel<T_LumA, T_Int8>;
	using TPixel_LumA_Int16 = SPixel<T_LumA, T_Int16>;
	using TPixel_LumA_Int32 = SPixel<T_LumA, T_Int32>;
	using TPixel_LumA_UInt8 = SPixel<T_LumA, T_UInt8>;
	using TPixel_LumA_UInt16 = SPixel<T_LumA, T_UInt16>;
	using TPixel_LumA_UInt32 = SPixel<T_LumA, T_UInt32>;
	using TPixel_LumA_Single = SPixel<T_LumA, T_Single>;
	using TPixel_LumA_Double = SPixel<T_LumA, T_Double>;

	using TPixel_RGB_Int8  = SPixel<T_RGB, T_Int8>;
	using TPixel_RGB_Int16 = SPixel<T_RGB, T_Int16>;
	using TPixel_RGB_Int32 = SPixel<T_RGB, T_Int32>;
	using TPixel_RGB_UInt8 = SPixel<T_RGB, T_UInt8>;
	using TPixel_RGB_UInt16 = SPixel<T_RGB, T_UInt16>;
	using TPixel_RGB_UInt32 = SPixel<T_RGB, T_UInt32>;
	using TPixel_RGB_Single = SPixel<T_RGB, T_Single>;
	using TPixel_RGB_Double = SPixel<T_RGB, T_Double>;

	using TPixel_RGBA_Int8  = SPixel<T_RGBA, T_Int8>;
	using TPixel_RGBA_Int16 = SPixel<T_RGBA, T_Int16>;
	using TPixel_RGBA_Int32 = SPixel<T_RGBA, T_Int32>;
	using TPixel_RGBA_UInt8 = SPixel<T_RGBA, T_UInt8>;
	using TPixel_RGBA_UInt16 = SPixel<T_RGBA, T_UInt16>;
	using TPixel_RGBA_UInt32 = SPixel<T_RGBA, T_UInt32>;
	using TPixel_RGBA_Single = SPixel<T_RGBA, T_Single>;
	using TPixel_RGBA_Double = SPixel<T_RGBA, T_Double>;

	using TPixel_BGR_Int8  = SPixel<T_BGR, T_Int8>;
	using TPixel_BGR_Int16 = SPixel<T_BGR, T_Int16>;
	using TPixel_BGR_Int32 = SPixel<T_BGR, T_Int32>;
	using TPixel_BGR_UInt8 = SPixel<T_BGR, T_UInt8>;
	using TPixel_BGR_UInt16 = SPixel<T_BGR, T_UInt16>;
	using TPixel_BGR_UInt32 = SPixel<T_BGR, T_UInt32>;
	using TPixel_BGR_Single = SPixel<T_BGR, T_Single>;
	using TPixel_BGR_Double = SPixel<T_BGR, T_Double>;

	using TPixel_BGRA_Int8  = SPixel<T_BGRA, T_Int8>;
	using TPixel_BGRA_Int16 = SPixel<T_BGRA, T_Int16>;
	using TPixel_BGRA_Int32 = SPixel<T_BGRA, T_Int32>;
	using TPixel_BGRA_UInt8 = SPixel<T_BGRA, T_UInt8>;
	using TPixel_BGRA_UInt16 = SPixel<T_BGRA, T_UInt16>;
	using TPixel_BGRA_UInt32 = SPixel<T_BGRA, T_UInt32>;
	using TPixel_BGRA_Single = SPixel<T_BGRA, T_Single>;
	using TPixel_BGRA_Double = SPixel<T_BGRA, T_Double>;


	// ////////////////////////////////////////////////////////////////////////////////////////
	// Map type ids to pixel type
	// ////////////////////////////////////////////////////////////////////////////////////////

	template<Clu::EPixelType t_ePixelType, Clu::EDataType t_eDataType>
	struct CastToPixel
	{
		using Type = void;
	};

#define DECL_PIXEL_CAST(thePT, theDT) \
	template<> struct CastToPixel<EPixelType::##thePT, EDataType::##theDT> \
	{ \
		using Type = TPixel_##thePT##_##theDT; \
	}

	DECL_PIXEL_CAST(Lum, Int8);
	DECL_PIXEL_CAST(Lum, Int16);
	DECL_PIXEL_CAST(Lum, Int32);
	DECL_PIXEL_CAST(Lum, UInt8);
	DECL_PIXEL_CAST(Lum, UInt16);
	DECL_PIXEL_CAST(Lum, UInt32);
	DECL_PIXEL_CAST(Lum, Single);
	DECL_PIXEL_CAST(Lum, Double);

	DECL_PIXEL_CAST(LumA, Int8);
	DECL_PIXEL_CAST(LumA, Int16);
	DECL_PIXEL_CAST(LumA, Int32);
	DECL_PIXEL_CAST(LumA, UInt8);
	DECL_PIXEL_CAST(LumA, UInt16);
	DECL_PIXEL_CAST(LumA, UInt32);
	DECL_PIXEL_CAST(LumA, Single);
	DECL_PIXEL_CAST(LumA, Double);

	DECL_PIXEL_CAST(RGB, Int8);
	DECL_PIXEL_CAST(RGB, Int16);
	DECL_PIXEL_CAST(RGB, Int32);
	DECL_PIXEL_CAST(RGB, UInt8);
	DECL_PIXEL_CAST(RGB, UInt16);
	DECL_PIXEL_CAST(RGB, UInt32);
	DECL_PIXEL_CAST(RGB, Single);
	DECL_PIXEL_CAST(RGB, Double);

	DECL_PIXEL_CAST(RGBA, Int8);
	DECL_PIXEL_CAST(RGBA, Int16);
	DECL_PIXEL_CAST(RGBA, Int32);
	DECL_PIXEL_CAST(RGBA, UInt8);
	DECL_PIXEL_CAST(RGBA, UInt16);
	DECL_PIXEL_CAST(RGBA, UInt32);
	DECL_PIXEL_CAST(RGBA, Single);
	DECL_PIXEL_CAST(RGBA, Double);

	DECL_PIXEL_CAST(BGR, Int8);
	DECL_PIXEL_CAST(BGR, Int16);
	DECL_PIXEL_CAST(BGR, Int32);
	DECL_PIXEL_CAST(BGR, UInt8);
	DECL_PIXEL_CAST(BGR, UInt16);
	DECL_PIXEL_CAST(BGR, UInt32);
	DECL_PIXEL_CAST(BGR, Single);
	DECL_PIXEL_CAST(BGR, Double);

	DECL_PIXEL_CAST(BGRA, Int8);
	DECL_PIXEL_CAST(BGRA, Int16);
	DECL_PIXEL_CAST(BGRA, Int32);
	DECL_PIXEL_CAST(BGRA, UInt8);
	DECL_PIXEL_CAST(BGRA, UInt16);
	DECL_PIXEL_CAST(BGRA, UInt32);
	DECL_PIXEL_CAST(BGRA, Single);
	DECL_PIXEL_CAST(BGRA, Double);


#undef DECL_PIXEL_CAST

} // namespace Clu
