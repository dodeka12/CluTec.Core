////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.FileIO.rtl
// file:      Xml.IXPathImpl.h
//
// summary:   Declares the xml. index path implementation class
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

		class CXPath;


		class CIXPathImpl : public Clu::CReference<CXPath>
		{
		public:
			CIXPathImpl() : CReference()
			{}

			CIXPathImpl(CIXPathImpl&& xImpl)
				: CReference(xImpl)
			{}

			CIXPathImpl& operator= (CIXPathImpl&& xImpl)
			{
				CReference::operator=(xImpl);
				return *this;
			}

			CIXPathImpl(const CIXPathImpl& xImpl)
				: CReference(xImpl)
			{}

			CIXPathImpl& operator= (const CIXPathImpl& xImpl)
			{
				CReference::operator=(xImpl);
				return *this;
			}

			~CIXPathImpl()
			{}

			void New()
			{
				CReference::operator=(CReference<CXPath>::New());
			}
		};

	}
}
