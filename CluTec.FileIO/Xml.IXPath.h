////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.FileIO.rtl
// file:      Xml.IXPath.h
//
// summary:   Declares the xml. index path class
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

#include "CluTec.Types1\IString.h"

namespace Clu
{
	namespace Xml
	{
		class CIDocument;

		class CIXPathImpl;

		class CLU_FILEIO_API CIXPath
		{
		public:
			friend class CIDocument;

		protected:
			CIXPathImpl *m_pImpl;

		public:
			CIXPath();
			CIXPath(CIXPath&& xXml);
			CIXPath(const CIXPath& xXml);

			~CIXPath();

			CIXPath& operator= (CIXPath&& xXml);
			CIXPath& operator= (const CIXPath& xXml);

			bool IsValidRef() const;
			bool IsValid() const;

			void Destroy();
			void Release();

			Clu::CIString Path() const;

			size_t Count() const;
			CIString Content(size_t nIdx) const;

		};
	}
} // namespace Clu

#pragma make_public(Clu::Xml::CIXPath)
