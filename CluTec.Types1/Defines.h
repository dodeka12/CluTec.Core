////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      Defines.h
//
// summary:   Declares the defines class
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

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A macro that defines clu exception. </summary>
///
/// <param name="theMsg">	Message describing the. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

#define CLU_EXCEPTION(theMsg) \
	Clu::CIException(theMsg, __FILE__, __FUNCTION__, __LINE__)

#ifdef __NVCC__
#	include "assert.h"
#	define CLU_ASSERT(theCond) assert(theCond)
#else
#	ifdef _WIN32
#		define CLU_ASSERT(theCond) _ASSERTE(theCond)
#	else
#		ifdef _DEBUG
#			define CLU_ASSERT(theCond) if (!(theCond)) throw CLU_EXCEPTION("Assertion failed")
#		else
#			define CLU_ASSERT(theCond) 
#		endif
#	endif
#endif


#if !defined(__NVCC__)
#	define __CUDA_H__ 
#	define __CUDA_D__ 
#	define __CUDA_HD__ 
#	define __CUDA_DI__ 
#	define __CUDA_HDI__ 
#	define __CUDA_UNROLL_ALL__ 
#	define __CUDA_ALIGN__(theAlign) 
#else
#	define __CUDA_H__ __host__
#	define __CUDA_D__ __device__
#	define __CUDA_HD__ __host__ __device__
#	define __CUDA_DI__ __device__ __forceinline__
#	define __CUDA_HDI__ __host__ __device__ __forceinline__
#	define __CUDA_UNROLL_ALL__ #pragma unroll
#	define __CUDA_ALIGN__(theAlign) __align__(theAlign)
#endif

/// <summary>	A macro that defines clu s. </summary>
#define CLU_S Clu::CIString() << 
