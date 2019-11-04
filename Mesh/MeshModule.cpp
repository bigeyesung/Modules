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