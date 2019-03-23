////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Net.Base
// file:      Vector.h
//
// summary:   Declares the vector class
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

		public value struct Vector3 
		{
			Vector3(double _x, double _y, double _z)
			{
				Set(_x, _y, _z);
			}

			void Set(double _x, double _y, double _z)
			{
				x = _x;
				y = _y;
				z = _z;
			}

			double x, y, z;

		};

	} // namespace Net
} // namespace Clu
