////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.FileIO.rtl
// file:      Xml.IXPath.cpp
//
// summary:   Implements the xml. index path class
//
//            Copyright (c) 2016 CluTec. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Xml.IXPath.h"
#include "Xml.IXPathImpl.h"
#include "Xml.XPath.h"

#include "CluTec.Base\Exception.h"


namespace Clu
{
	namespace Xml
	{

#define REF (*m_pImpl)
#define REF_(theVar) (*theVar.m_pImpl)

#define INTERN (*(m_pImpl->Get()))
#define INTERN_(theVar) (*(theVar.m_pImpl->Get()))

		CIXPath::CIXPath()
		{
			try
			{
				m_pImpl = new CIXPathImpl();
				if (m_pImpl == nullptr)
					return;

				REF.New();
			}
			CLU_CATCH_RETHROW_ALL("Error in constructor")
		}


		CIXPath::~CIXPath()
		{
			delete m_pImpl;
		}


		CIXPath::CIXPath(CIXPath&& xEx)
		{
			m_pImpl = nullptr;
			*this = std::forward<CIXPath>(xEx);
		}

		CIXPath& CIXPath::operator= (CIXPath&& xEx)
		{
			delete m_pImpl;
			m_pImpl = xEx.m_pImpl;
			xEx.m_pImpl = nullptr;
			return *this;
		}

		CIXPath::CIXPath(const CIXPath& xEx)
		{
			m_pImpl = new CIXPathImpl(*xEx.m_pImpl);
		}

		CIXPath& CIXPath::operator= (const CIXPath& xImg)
		{
			if (m_pImpl != nullptr && xImg.m_pImpl != nullptr)
			{
				REF = REF_(xImg);
			}

			return *this;
		}


		bool CIXPath::IsValidRef() const
		{
			if (m_pImpl == nullptr)
				return false;

			if (!REF.IsValid())
				return false;

			return true;
		}

		bool CIXPath::IsValid() const
		{
			if (!IsValidRef())
				return false;

			if (!REF->IsValid())
				return false;

			return true;
		}



		void CIXPath::Destroy()
		{
			try
			{
				if (!IsValid())
					throw CLU_EXCEPTION("Invalid XML instance");

				REF->Destroy();
			}
			CLU_CATCH_RETHROW_ALL("Error destroying XML object")
		}

		void CIXPath::Release()
		{
			try
			{
				if (!IsValidRef())
					throw CLU_EXCEPTION("Invalid XML instance");

				REF.Release();
			}
			CLU_CATCH_RETHROW_ALL("Error releasing XML object reference")
		}

		Clu::CIString CIXPath::Path() const
		{
			try
			{
				if (!IsValid())
					throw CLU_EXCEPTION("Invalid XML instance");

				return REF->Path();
			}
			CLU_CATCH_RETHROW_ALL("Error obtaining X-Path path")
		}


		size_t CIXPath::Count() const
		{
			try
			{
				if (!IsValid())
					throw CLU_EXCEPTION("Invalid XML instance");

				return REF->Count();
			}
			CLU_CATCH_RETHROW_ALL("Error obtaining X-Path element count")
		}

		CIString CIXPath::Content(size_t nIdx) const
		{
			try
			{
				if (!IsValid())
					throw CLU_EXCEPTION("Invalid XML instance");

				return REF->Content(nIdx);
			}
			CLU_CATCH_RETHROW_ALL("Error obtaining X-Path element content")
		}

	}
} // namespace Clu
