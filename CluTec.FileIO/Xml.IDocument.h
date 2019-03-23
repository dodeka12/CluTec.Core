////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.FileIO.rtl
// file:      Xml.IDocument.h
//
// summary:   Declares the xml. i document class
//
//            Copyright (c) 2016 CluTec. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once


#ifdef CLU_FILEIO_EXPORTS
#define CLU_FILEIO_API __declspec(dllexport)
#else
#define CLU_FILEIO_API __declspec(dllimport)
#endif

#include "CluTec.Types1/IString.h"

namespace Clu
{
	namespace Xml
	{
		class CIXPath;
		class CIDocumentImpl;

		class CLU_FILEIO_API CIDocument
		{
		public:

		private:
			CIDocumentImpl *m_pImpl;

		public:
			CIDocument();
			CIDocument(CIDocument&& xXml);
			CIDocument(const CIDocument& xXml);

			~CIDocument();

			CIDocument& operator= (CIDocument&& xXml);
			CIDocument& operator= (const CIDocument& xXml);

			bool IsValidRef() const;
			bool IsValid() const;


			void CreateFromFile(const CIString& sFilename);
			void Destroy();
			void Release();

			CIXPath operator() (const CIString& sXPath);
		};
	} // namespace Xml
} // namespace Clu

#pragma make_public(Clu::Xml::CIDocument)
