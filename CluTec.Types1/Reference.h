////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      Reference.h
//
// summary:   Declares the reference class
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

#include <memory>

namespace Clu
{

	template<typename _TObject>
	class CReference
	{
	public:
		using TObject = _TObject;

	protected:
		std::shared_ptr<TObject> m_pRef;

	public:

		static CReference New()
		{
			CReference xRef;
			xRef.m_pRef = std::make_shared<TObject>();
			return xRef;
		}

		static CReference New(TObject&& xObj)
		{
			CReference xRef;
			xRef.m_pRef = std::make_shared<TObject>(xObj);
			return xRef;
		}

		static CReference New(const TObject& xObj)
		{
			CReference xRef;
			xRef.m_pRef = std::make_shared<TObject>(xObj);
			return xRef;
		}

		CReference()
		{}

		CReference(CReference&& xRef)
			: m_pRef(std::move(xRef.m_pRef))
		{}

		CReference& operator= (CReference&& xRef)
		{
			m_pRef = std::move(xRef.m_pRef);
			return *this;
		}

		CReference(const CReference& xRef)
			: m_pRef(xRef.m_pRef)
		{}

		CReference& operator= (const CReference& xRef)
		{
			m_pRef = xRef.m_pRef;
			return *this;
		}

		bool IsValid() const
		{
			return Count() > 0;
		}

		void Release()
		{
			m_pRef.reset();
		}

		operator bool() const
		{
			return IsValid();
		}

		TObject* operator -> ()
		{
			return m_pRef.get();
		}

		TObject& operator * ()
		{
			return *m_pRef.get();
		}

		TObject* Get()
		{
			return m_pRef.get();
		}

		const TObject* operator -> () const
		{
			return m_pRef.get();
		}

		const TObject& operator * () const
		{
			return *m_pRef.get();
		}

		void Reset()
		{
			m_pRef.reset();
		}

		size_t Count() const
		{
			return m_pRef.use_count();
		}

	};

} // namespace Clu