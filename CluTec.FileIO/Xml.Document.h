////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.FileIO.rtl
// file:      Xml.Document.h
//
// summary:   Declares the xml. document class
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


		class CDocument
		{
		public:
			using TData = unsigned char;

		private:
			static unsigned sm_uInstanceCounter;

			xmlDocPtr m_pDoc;

		protected:
			void _Reset();

		public:

		public:
			CDocument();
			CDocument(CDocument&& xImage);
			CDocument(const CDocument& xImage) = delete;
			~CDocument();

			CDocument& operator= (CDocument&& xImage);
			CDocument& operator= (const CDocument& xImage) = delete;


			void CreateFromFile(const CIString& sFilename);
			void Destroy();

			bool IsValid() const
			{
				return m_pDoc != nullptr;
			}

			xmlDocPtr DocumentPointer()
			{
				return m_pDoc;
			}
		};

	}
}
