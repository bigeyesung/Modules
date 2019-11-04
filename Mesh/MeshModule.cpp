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

    for (int i = 0; i < g_PointOne.size(); i++)
	{
		Vertex_Pos.x = VertexPos[g_PointOne[i]].x;
		Vertex_Pos.y = VertexPos[g_PointOne[i]].y;
		Vertex_Pos.z = 0.0;
		Vertex_Normal.x = 0.0;
		Vertex_Normal.y = 0.0;
		Vertex_Normal.z = 0.0;
		//���� = UV
		Vertex_Coord.x = VertexScreenPos.at(g_PointOne[i]).x / Width;		
		Vertex_Coord.y = 1 - VertexScreenPos.at(g_PointOne[i]).y / Height;

		VboVertices.push_back(Vertex_Pos);
		VboNormals.push_back(Vertex_Normal);
		VboTexCoords.push_back(Vertex_Coord);
		VboIndices.push_back(j);

        Vertex_Pos.x = VertexPos[g_PointTwo[i]].x;
		Vertex_Pos.y = VertexPos[g_PointTwo[i]].y;
		Vertex_Pos.z = 0.0;
		Vertex_Normal.x = 0.0;
		Vertex_Normal.y = 0.0;
		Vertex_Normal.z = 0.0;
		Vertex_Coord.x = VertexScreenPos.at(g_PointTwo[i]).x / Width;
		Vertex_Coord.y = 1 - VertexScreenPos.at(g_PointTwo[i]).y / Height;

		VboVertices.push_back(Vertex_Pos);
		VboNormals.push_back(Vertex_Normal);
		VboTexCoords.push_back(Vertex_Coord);
		VboIndices.push_back(j + 1);

        Vertex_Pos.x = VertexPos[g_PointThree[i]].x;
		Vertex_Pos.y = VertexPos[g_PointThree[i]].y;
		Vertex_Pos.z = 0.0;
		Vertex_Normal.x = 0.0;
		Vertex_Normal.y = 0.0;
		Vertex_Normal.z = 0.0;
		Vertex_Coord.x = VertexScreenPos.at(g_PointThree[i]).x / Width;
		Vertex_Coord.y = 1 - VertexScreenPos.at(g_PointThree[i]).y / Height;
		
		VboVertices.push_back(Vertex_Pos);
		VboNormals.push_back(Vertex_Normal);
		VboTexCoords.push_back(Vertex_Coord);
		VboIndices.push_back(j + 2);

		j += 3;
	}