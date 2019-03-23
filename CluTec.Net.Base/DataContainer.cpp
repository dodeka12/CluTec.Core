////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Net.Base
// file:      DataContainer.cpp
//
// summary:   Implements the data container class
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

#include "stdafx.h"
#include "DataContainer.h"

#pragma managed (push, off)
#include "CluTec.Types1/IDataContainer.h"
#pragma managed (pop)

namespace Clu
{
	namespace Net
	{
		DataContainer::DataContainer()
		{
			m_pData = new Clu::CIDataContainer();
		}

		DataContainer::~DataContainer()
		{
			if (m_pData != nullptr)
			{
				this->!DataContainer();
			}
		}

		DataContainer::!DataContainer()
		{
			delete m_pData;
			m_pData = nullptr;
		}


		DataContainer::DataContainer(const Clu::CIDataContainer& xData)
		{
			m_pData = new Clu::CIDataContainer(xData);
		}

		Clu::CIDataContainer DataContainer::ToIDataContainer()
		{
			return Clu::CIDataContainer(*m_pData);
		}

	}
}