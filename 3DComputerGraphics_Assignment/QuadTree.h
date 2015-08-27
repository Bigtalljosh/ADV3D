#ifndef _QUADTREE_H_
#define _QUADTREE_H_

//Globals
const int MAX_TRIANGLES = 10000;

#include "TerrainHandle.h"
#include "Frustum.h"
#include "TerrainShader.h"

class QuadTree
{
	public:
		QuadTree();
		~QuadTree();

		bool Initialize(TerrainHandle*, ID3D11Device*);
		void Shutdown();
		void Render(Frustum*, ID3D11DeviceContext*, TerrainShader*);

		int GetDrawCount();
		bool GetHeightAtPosition(float, float, float&);

	private:
		//Structs
		struct VertexType
		{
			D3DXVECTOR3 position;
			D3DXVECTOR2 texture;
			D3DXVECTOR3 normal;
		};

		struct VectorType
		{
			float x, y, z;
		};

		struct NodeType
		{
			float positionX, positionZ, width;
			int triangleCount;
			ID3D11Buffer *vertexBuffer, *indexBuffer;
			VectorType* vertexArray;
			NodeType* nodes[4];
		};

		void CalculateMeshDimensions(int, float&, float&, float&);
		void CreateTreeNode(NodeType*, float, float, float, ID3D11Device*);
		int CountTriangles(float, float, float);
		bool IsTriangleContained(int, float, float, float);
		void ReleaseNode(NodeType*);
		void RenderNode(NodeType*, Frustum*, ID3D11DeviceContext*, TerrainShader*);

		void FindNode(NodeType*, float, float, float&);
		bool CheckHeightOfTriangle(float, float, float&, float[3], float[3], float[3]);

		int m_triangleCount, m_drawCount;
		VertexType* m_vertexList;
		NodeType* m_parentNode;
};
#endif