////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.FileIO.rtl
// file:      Xml.IDocument.cpp
//
// summary:   Implements the xml. i document class
//
//            Copyright (c) 2016 CluTec. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Xml.IDocument.h"
#include "Xml.IDocumentImpl.h"
#include "Xml.Document.h"
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

		CIDocument::CIDocument()
		{
			try
			{
				m_pImpl = new CIDocumentImpl();
				if (m_pImpl == nullptr)
					return;

				REF.New();
			}
			CLU_CATCH_RETHROW_ALL("Error in constructor")
		}


		CIDocument::~CIDocument()
		{
			delete m_pImpl;
		}


		CIDocument::CIDocument(CIDocument&& xEx)
		{
			m_pImpl = nullptr;
			*this = std::forward<CIDocument>(xEx);
		}

		CIDocument& CIDocument::operator= (CIDocument&& xEx)
		{
			delete m_pImpl;
			m_pImpl = xEx.m_pImpl;
			xEx.m_pImpl = nullptr;
			return *this;
		}

		CIDocument::CIDocument(const CIDocument& xEx)
		{
			m_pImpl = new CIDocumentImpl(*xEx.m_pImpl);
		}

		CIDocument& CIDocument::operator= (const CIDocument& xImg)
		{
			if (m_pImpl != nullptr && xImg.m_pImpl != nullptr)
			{
				REF = REF_(xImg);
			}

			return *this;
		}


		bool CIDocument::IsValidRef() const
		{
			if (m_pImpl == nullptr)
				return false;

			if (!REF.IsValid())
				return false;

			return true;
		}

		bool CIDocument::IsValid() const
		{
			if (!IsValidRef())
				return false;

			if (!REF->IsValid())
				return false;

			return true;
		}


		void CIDocument::CreateFromFile(const CIString& sFilename)
		{
			try
			{
				if (!IsValidRef())
					throw CLU_EXCEPTION("Invalid XML instance");

				REF->CreateFromFile(sFilename);
			}
			CLU_CATCH_RETHROW_ALL("Eror creating XML object from file")
		}


		void CIDocument::Destroy()
		{
			try
			{
				if (!IsValid())
					throw CLU_EXCEPTION("Invalid XML instance");

				REF->Destroy();
			}
			CLU_CATCH_RETHROW_ALL("Error destroying XML object")
		}

		void CIDocument::Release()
		{
			try
			{
				if (!IsValidRef())
					throw CLU_EXCEPTION("Invalid XML instance");

				REF.Release();
			}
			CLU_CATCH_RETHROW_ALL("Error releasing XML object reference")
		}


		CIXPath CIDocument::operator() (const CIString& sXPath)
		{
			try
			{
				if (!IsValidRef())
					throw CLU_EXCEPTION("Invalid XML instance");

				CIXPath xPath;
				xPath.m_pImpl->Get()->Create(REF->DocumentPointer(), sXPath);
				return xPath;
			}
			CLU_CATCH_RETHROW_ALL("Error creating XPath object")
		}

	}
} // namespace Clu
