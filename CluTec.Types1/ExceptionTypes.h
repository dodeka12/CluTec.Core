////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      ExceptionTypes.h
//
// summary:   Declares the exception types class
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

#include "Guid.h"

namespace Clu
{
	namespace ExceptionType
	{
		class CLU_TYPES1_API Unknown
		{
		protected:
			CGuid m_xGuid;
			CIString m_sTypeName;

		public:
			Unknown()
			{}

			Unknown(Clu::CGuid xGuid, Clu::CIString sTypeName)
			{
				m_xGuid = xGuid;
				m_sTypeName = sTypeName;
			}

			CGuid GetGuid() const
			{
				return m_xGuid;
			}

			CIString GetTypeName() const
			{
				return m_sTypeName;
			}
		};


		class CLU_TYPES1_API Standard : public Unknown
		{
		public:
			// {3921E1CD-BB34-45AE-94E8-61072537BA07}
			static const CGuid Guid;
			static const char* TypeName;

		public:
			Standard() : Unknown(Standard::Guid, Standard::TypeName)
			{}
		};


		class CLU_TYPES1_API OutOfMemory : public Unknown
		{
		public:
			// {8F7094E3-7C55-4018-AF8E-0D7E4FBAFE26}
			static const CGuid Guid;
			static const char* TypeName;

		public:
			OutOfMemory() : Unknown(OutOfMemory::Guid, OutOfMemory::TypeName)
			{}
		};


		class CLU_TYPES1_API RuntimeError : public Unknown
		{
		public:
			// {449A95DA-79F0-456D-8705-1491846B4DF4}
			static const CGuid Guid;
			static const char* TypeName;

		public:
			RuntimeError() : Unknown(RuntimeError::Guid, RuntimeError::TypeName)
			{}
		};

		class CLU_TYPES1_API FileNotFound : public Unknown
		{
		public:
			// {B869A778-B33F-4F4E-97B5-3A1373294C94}
			static const CGuid Guid;
			static const char* TypeName;

		public:
			FileNotFound() : Unknown(FileNotFound::Guid, FileNotFound::TypeName)
			{}
		};

	}

}

#pragma make_public(Clu::ExceptionType::Unknown)
#pragma make_public(Clu::ExceptionType::Standard)
#pragma make_public(Clu::ExceptionType::OutOfMemory)
#pragma make_public(Clu::ExceptionType::RuntimeError)
