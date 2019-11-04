#include "MeshModule.h"

CustomMesh::CustomMesh()
{

}
CustomMesh::~CustomMesh()
{
	
}

void CustomMesh::CreatMesh(int Width, int Height,int ColNum,int RowNum,vector<vec2> VertexPos, vector<vec2> VertexScreenPos)
{
	vector<vec2> VboTexCoords;
	vector<vec3> VboVertices;
	vector<vec3> VboNormals;
	vector<uint16_t> VboIndices;

	vector<int> g_PointOne;
	vector<int> g_PointTwo;
	vector<int> g_PointThree;

    int index = 0;
	for (int i = 0; i < RowNum - 1; i++)
	{
		for (int j = 0; j < ColNum - 1; j++)
		{
			index = i*ColNum + j;

			g_PointOne.push_back(index);
			g_PointTwo.push_back(index + 1);
			g_PointThree.push_back(index + ColNum + 1);

            g_PointOne.push_back(index);
			g_PointTwo.push_back(index + ColNum + 1);
			g_PointThree.push_back(index + ColNum);
		}
	}

	vec3 Vertex_Pos;
	vec3 Vertex_Normal;
	vec2 Vertex_Coord;

	int j = 0;