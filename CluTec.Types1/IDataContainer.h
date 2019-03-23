////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      IDataContainer.h
//
// summary:   Declares the IDataContainer interface
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

#include "DataObject.h"
#include "IString.h"

namespace Clu
{
	class CIDataContainerImpl;

	class CLU_TYPES1_API CIDataContainer
	{
	public:

	private:
		CIDataContainerImpl *m_pImpl;

	public:
		CIDataContainer();
		CIDataContainer(CIDataContainer&& xData);
		CIDataContainer(const CIDataContainer& xData);

		~CIDataContainer();

		CIDataContainer& operator= (CIDataContainer&& xData);
		CIDataContainer& operator= (const CIDataContainer& xData);

		bool IsValidRef() const;
		bool IsValid() const;
		void Release();

		void Clear();
		void Insert(const CIString& sName, const SDataObject& xData);
		const SDataObject& At(const CIString& sName) const;

		bool HasElement(const CIString& sName) const;

		size_t Count() const;

		bool First(CIString& sName, SDataObject& xData);
		bool Next(CIString& sName, SDataObject& xData);


	};

} // namespace Clu

#pragma make_public(Clu::CIDataContainer)
