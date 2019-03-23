////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.FileIO.rtl
// file:      Xml.IDocumentImpl.h
//
// summary:   Declares the xml. i document implementation class
//
//            Copyright (c) 2016 CluTec. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CluTec.Types1\Reference.h"

namespace Clu
{
	namespace Xml
	{

		class CDocument;


		class CIDocumentImpl : public Clu::CReference<CDocument>
		{
		public:
			CIDocumentImpl() : CReference()
			{}

			CIDocumentImpl(CIDocumentImpl&& xImpl)
				: CReference(xImpl)
			{}

			CIDocumentImpl& operator= (CIDocumentImpl&& xImpl)
			{
				CReference::operator=(xImpl);
				return *this;
			}

			CIDocumentImpl(const CIDocumentImpl& xImpl)
				: CReference(xImpl)
			{}

			CIDocumentImpl& operator= (const CIDocumentImpl& xImpl)
			{
				CReference::operator=(xImpl);
				return *this;
			}

			~CIDocumentImpl()
			{}

			void New()
			{
				CReference::operator=(CReference<CDocument>::New());
			}

		};

	}
}
