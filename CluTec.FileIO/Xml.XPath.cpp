////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.FileIO.rtl
// file:      Xml.XPath.cpp
//
// summary:   Implements the xml. x coordinate path class
//
//            Copyright (c) 2016 CluTec. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CluTec.Types1\Defines.h"
#include "CluTec.Base\Exception.h"

#include "Xml.XPath.h"

#include <utility>


namespace Clu
{
	namespace Xml
	{


		CXPath::CXPath()
		{
			_Reset();
		}


		CXPath::~CXPath()
		{
			Destroy();
		}


		CXPath::CXPath(CXPath&& xImage)
		{
			*this = std::forward<CXPath>(xImage);
		}

		CXPath& CXPath::operator= (CXPath&& xPath)
		{
			Destroy();

			m_pContext = xPath.m_pContext;
			m_pObject = xPath.m_pObject;
			m_sPath = xPath.m_sPath;

			xPath._Reset();
			return *this;
		}


		void CXPath::Create(xmlDocPtr pDoc, const CIString& sXPath)
		{
			if (pDoc == nullptr)
			{
				throw CLU_EXCEPTION("Invalid document");
			}

			Destroy();

			m_pContext = xmlXPathNewContext(pDoc);
			if (m_pContext == nullptr)
			{
				throw CLU_EXCEPTION("Error creating document x-path context");
			}

			m_pObject = xmlXPathEvalExpression((const xmlChar*)sXPath.ToCString(), m_pContext);
			if (m_pObject == nullptr)
			{
				Destroy();
				throw CLU_EXCEPTION("Error evaluating x-path expression");
			}

			m_sPath = sXPath;
		}


		void CXPath::_Reset()
		{
			m_pContext = nullptr;
			m_pObject = nullptr;
			m_sPath = "";
		}


		void CXPath::Destroy()
		{
			if (m_pObject)
			{
				xmlXPathFreeObject(m_pObject);
			}

			if (m_pContext)
			{
				xmlXPathFreeContext(m_pContext);
			}

			_Reset();
		}

		Clu::CIString CXPath::Path() const
		{
			if (!IsValid())
			{
				throw CLU_EXCEPTION("XPath not initialized");
			}

			return m_sPath;
		}

		size_t CXPath::Count() const
		{
			if (!IsValid())
			{
				throw CLU_EXCEPTION("XPath not initialized");
			}

			return (size_t)m_pObject->nodesetval->nodeNr;
		}

		CIString CXPath::Content(size_t nIdx) const
		{
			if (!IsValid())
			{
				throw CLU_EXCEPTION("XPath not initialized");
			}

			if (nIdx >= Count())
			{
				if (Count() > 0)
				{
					throw CLU_EXCEPTION(CLU_S "Index '" << nIdx << "' out of range at path '" << m_sPath << "'");
				}
				else
				{
					throw CLU_EXCEPTION(CLU_S "No content at path '" << m_sPath << "'");
				}
			}

			Clu::CIString sContent;
			xmlNodePtr pNode = m_pObject->nodesetval->nodeTab[nIdx];
			if (pNode->children != nullptr)
			{
				_xmlNode *pChild = pNode->children;
				if (pChild->type == XML_TEXT_NODE)
				{
					const char* pcContent = (const char*)(pChild->content);
					if (pcContent != nullptr)
					{
						sContent = pcContent;
					}

				}
			}


			return sContent;
		}


	}
} // namespace Clu

