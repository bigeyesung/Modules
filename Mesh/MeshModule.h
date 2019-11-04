#pragma once
#include <cinder\app\AppBase.h>
#include "cinder/gl/gl.h"
#include "../include/ClientConst.h"

using namespace ci::app;
using namespace ci;

using namespace std;

class CustomMesh
{
public:
	CustomMesh();
	~CustomMesh();
	void CreatMesh(int Width, int Height, int ColNum, int RowNum, vector<vec2> VertexPos, vector<vec2> VertexScreenPos);

	void CreatMesh(int Width, int Height, int ColNum, int RowNum, vector<joints> VertexPos);

    gl::VboMeshRef &GetVboMesh() { return m_VboMesh; }
private:
	//MeshRef
	gl::VboMeshRef m_VboMesh;

};