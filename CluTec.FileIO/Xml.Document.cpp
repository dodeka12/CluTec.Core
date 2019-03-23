////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.FileIO.rtl
// file:      Xml.Document.cpp
//
// summary:   Implements the xml. document class
//
//            Copyright (c) 2016 CluTec. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CluTec.Types1\Defines.h"
#include "CluTec.Base\Exception.h"
#include "CluTec.System\FileInfo.h"

#include "Xml.Document.h"

#include <utility>


namespace Clu
{
	namespace Xml
	{

		unsigned CDocument::sm_uInstanceCounter = 0;

		CDocument::CDocument()
		{
			if (sm_uInstanceCounter == 0)
			{
				xmlInitParser();
			}
			++sm_uInstanceCounter;

			_Reset();
		}


		CDocument::~CDocument()
		{
			Destroy();

			--sm_uInstanceCounter;
			if (sm_uInstanceCounter == 0)
			{
				xmlCleanupParser();
			}
		}


		CDocument::CDocument(CDocument&& xImage)
		{
			*this = std::forward<CDocument>(xImage);
		}

		CDocument& CDocument::operator= (CDocument&& xXml)
		{
			Destroy();

			m_pDoc = xXml.m_pDoc;
			xXml._Reset();
			return *this;
		}


		void CDocument::CreateFromFile(const CIString& sFilename)
		{
			Destroy();

			Clu::CFileInfo xFile(sFilename);

			if (!xFile.Exists())
			{
				throw CLU_EXCEPT_TYPE(FileNotFound, (CLU_S "File '" << sFilename << "' not found"));
			}

			m_pDoc = xmlParseFile(sFilename.ToCString());
			if (m_pDoc == nullptr)
			{
				throw CLU_EXCEPTION("Error parsing XML file");
			}
		}


		void CDocument::_Reset()
		{
			m_pDoc = nullptr;
		}


		void CDocument::Destroy()
		{
			if (m_pDoc)
			{
				xmlFreeDoc(m_pDoc);
			}

			_Reset();
		}


	}
} // namespace Clu

