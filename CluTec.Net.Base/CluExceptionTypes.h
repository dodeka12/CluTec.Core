////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Net.Base
// file:      CluExceptionTypes.h
//
// summary:   Declares the clu exception types class
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
	namespace Net
	{
		namespace ExceptionType
		{

			public ref class Unknown
			{
			protected:

				System::Guid m_guidType;
				System::String^ m_sTypeName;

			public:
				property System::Guid TypeId
				{
					System::Guid get()
					{
						return m_guidType;
					}
				}

				property System::String^ TypeName
				{
					System::String^ get()
					{
						return m_sTypeName;
					}
				}

			public:
				Unknown(System::Guid xGuid, System::String^ sTypeName)
				{
					m_guidType = xGuid;
					m_sTypeName = sTypeName;
				}
			};

			public ref class Standard : public Unknown
			{
			public:
				// {3921E1CD-BB34-45AE-94E8-61072537BA07}
				static property System::Guid StaticTypeId
				{
					System::Guid get()
					{
						return System::Guid(0x3921e1cd, 
							(short)0xbb34, 
							0x45ae, 
							0x94, 
							0xe8, 0x61, 0x7, 0x25, 0x37, 0xba, 0x07);
					}
				}

				static property System::String^ StaticTypeName
				{
					System::String^ get()
					{
						return gcnew System::String("Exception");
					}
				}

			public:
				Standard() : Unknown(Standard::StaticTypeId, Standard::StaticTypeName)
				{}
			};


			public ref class OutOfMemory : public Unknown
			{
			public:
				// {8F7094E3-7C55-4018-AF8E-0D7E4FBAFE26}
				static property System::Guid StaticTypeId
				{
					System::Guid get()
					{
						return System::Guid(0x8f7094e3, 0x7c55, 0x4018, 0xaf, 0x8e, 0xd, 0x7e, 0x4f, 0xba, 0xfe, 0x26);
					}
				}

				static property System::String^ StaticTypeName
				{
					System::String^ get()
					{
						return gcnew System::String("Out of Memory");
					}
				}

			public:
				OutOfMemory() : Unknown(OutOfMemory::StaticTypeId, OutOfMemory::StaticTypeName)
				{}

			};


			public ref class RuntimeError : public Unknown
			{
			public:
				// {449A95DA-79F0-456D-8705-1491846B4DF4}
				static property System::Guid StaticTypeId
				{
					System::Guid get()
					{
						return System::Guid(0x449a95da, 0x79f0, 0x456d, 0x87, 0x5, 0x14, 0x91, 0x84, 0x6b, 0x4d, 0xf4);
					}
				}

				static property System::String^ StaticTypeName
				{
					System::String^ get()
					{
						return gcnew System::String("Runtime Error");
					}
				}

			public:
				RuntimeError() : Unknown(RuntimeError::StaticTypeId, RuntimeError::StaticTypeName)
				{}

			};

		} // namespace ExceptionType
	} // namespace Net
} // namespace Clu