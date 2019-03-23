////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      DataContainer.h
//
// summary:   Declares the data container class
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

#include <map>

#include "DataObject.h"
#include "IString.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: Clu
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Clu
{
	/// <summary>	A data container. </summary>
	class CDataContainer
	{
	public:
		using TDataMap = std::map<std::string, SDataObject>;

	private:

	protected:
		void _Reset();

	public :
		TDataMap m_mapData;
		TDataMap::const_iterator m_itData;

	public:
		/// <summary>	Default constructor. </summary>
		CDataContainer();
		CDataContainer(CDataContainer&& xData);
		CDataContainer(const CDataContainer& xData);
		~CDataContainer();

		CDataContainer& operator= (CDataContainer&& xData);
		CDataContainer& operator= (const CDataContainer& xData);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Inserts. </summary>
		///
		/// <param name="sName">	The name. </param>
		/// <param name="xData">	The data. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void Insert(const CIString& sName, const SDataObject& xData);
		const SDataObject& At(const CIString& sName) const;
		void Clear();

		bool HasElement(const CIString& sName) const;

		bool IsValid() const;

		size_t Count() const;

		bool First(CIString& sName, SDataObject& xData);
		bool Next(CIString& sName, SDataObject& xData);

	};


}
