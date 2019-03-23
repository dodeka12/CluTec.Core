////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.FileIO.rtl
// file:      Xml.XPath.h
//
// summary:   Declares the xml. x coordinate path class
//
//            Copyright (c) 2016 CluTec. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>

extern "C" {
#include "libxml\tree.h"
#include "libxml\parser.h"
#include "libxml\xpath.h"
#include "libxml\xpathInternals.h"
}

#include "CluTec.Types1\IString.h"

namespace Clu
{
	namespace Xml
	{
		class CDocument;

		class CXPath
		{
		public:
			using TData = unsigned char;

		private:
			static unsigned sm_uInstanceCounter;

			xmlXPathContextPtr m_pContext;
			xmlXPathObjectPtr m_pObject;

			Clu::CIString m_sPath;
		protected:
			void _Reset();

		public:

		public:
			CXPath();
			CXPath(CXPath&& xImage);
			CXPath(const CXPath& xImage) = delete;
			~CXPath();

			CXPath& operator= (CXPath&& xImage);
			CXPath& operator= (const CXPath& xImage) = delete;


			void Create(xmlDocPtr pDoc, const CIString& sXPath);
			void Destroy();


			bool IsValid() const
			{
				return (m_pObject != nullptr) && (m_pContext != nullptr);
			}

			Clu::CIString Path() const;
			size_t Count() const;
			CIString Content(size_t nIdx) const;
		};

	}
}
