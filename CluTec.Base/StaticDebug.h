////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Base
// file:      StaticDebug.h
//
// summary:   Declares the static debug class
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
/// <summary>
/// Print aant size_t value at compile time. This can also be a template parameter.
/// </summary>
///
/// <remarks>	Perwass </remarks>
///
/// <typeparam name="nSize">	Type of the size. </typeparam>
////////////////////////////////////////////////////////////////////////////////////////////////////


template<typename T = int>
struct STATIC_DEBUG
{

#if !defined(CLU_STATIC_DEBUG)

template<size_t nSize>
static void PRINT_size_t()
{}

#else

	template<size_t nSize>
	static void PRINT_size_t() 
	{
	#pragma message("Unsupported value")
	}

	template<> static void PRINT_size_t<0>() 
	{
	#pragma message("0")
	}

	template<> static void PRINT_size_t<1>() 
	{
	#pragma message("1")
	}

	template<> static void PRINT_size_t<2>() 
	{
	#pragma message("2")
	}

	template<> static void PRINT_size_t<3>() 
	{
	#pragma message("3")
	}

	template<> static void PRINT_size_t<4>() 
	{
	#pragma message("4")
	}

	template<> static void PRINT_size_t<5>() 
	{
#pragma message("5")
	}

	template<> static void PRINT_size_t<6>() 
	{
#pragma message("6")
	}

	template<> static void PRINT_size_t<7>() 
	{
#pragma message("7")
	}

	template<> static void PRINT_size_t<8>() 
	{
#pragma message("8")
	}

	template<> static void PRINT_size_t<9>() 
	{
#pragma message("9")
	}

	template<> static void PRINT_size_t<10>() 
	{
#pragma message("10")
	}

#endif
};
