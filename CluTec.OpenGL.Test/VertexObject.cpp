#include "stdafx.h"
#include "CppUnitTest.h"

#include "CluTec.Types1/IDataContainer.h"
#include "CluTec.OpenGL/Vertex.MeshObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CluTecOpenGLTest
{		
	TEST_CLASS(VertexObject)
	{
	public:
		
		TEST_METHOD(MeshObject)
		{
			using namespace Clu::OpenGL;
			using TMesh = Vertex::CMeshObject<Vertex::EType::Standard>;

			Clu::CIDataContainer xBox;
			TMesh xMesh;
			
			//xMesh.CreateTriangleStrip(1.0f, 5, 5, 0, 1, 2, EBufferUsage::StaticDraw);

			Logger::WriteMessage(TMesh::TypeId.ToString().ToCString());

			xBox.Insert("Test", Clu::SDataObject(TMesh::TypeId, &xMesh));


		}

	};
}