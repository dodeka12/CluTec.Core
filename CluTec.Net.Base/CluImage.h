////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Net.Base
// file:      CluImage.h
//
// summary:   Declares the clu image class
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
	class CIImage;

	namespace Net
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Managed wrapper class for native Clu::CIImage. This class follows the PIMPL idiom. CIImage
		/// itself is a reference to an image. To copy the content of an image into a new instance use
		/// Copy() to copy this instance and CopyFrom() to copy from a CIImage instance.
		/// </summary>
		///
		/// <remarks>	Perwass,. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		public ref class CluImage
		{
		private:
			Clu::CIImage *m_pImage;

		public:
			CluImage();

			CluImage(const Clu::CIImage& xImage);
			CluImage(Clu::Net::ImageFormat^ xS);

			~CluImage();
			!CluImage();

			property Clu::Net::ImageFormat^ Format
			{
				Clu::Net::ImageFormat^ get();
			}

			void CopyFrom(const Clu::CIImage& xImage);
			
			CluImage^ Copy();

			bool IsValid();

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Creates an image. </summary>
			///
			/// <param name="xS">	The x coordinate s. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			void Create(Clu::Net::ImageFormat^ xS);

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Get the image data pointer. </summary>
			///
			/// <returns>	A System::IntPtr. </returns>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			System::IntPtr DataPointer();

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Converts this object to a native CIImage instance. </summary>
			///
			/// <returns>	This object as a Clu::CIImage. </returns>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			Clu::CIImage ToIImage();

		};

	} // namespace Net
} // namespace Clu
