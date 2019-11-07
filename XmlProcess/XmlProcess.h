#pragma once
#include "../3rdParty/XmlParser/XmlParser.h"
#include "../include/ClientConst.h"
#include "../include/ProjectionConst.h"
class XmlProcess
{
public:

	XmlProcess();
	~XmlProcess();

	void ReadXml(const string& FilePath);
	bool GetData(s_InitData& inData);
	bool GetData(vector<vector<joints>>& inData);
	bool GetData(vector<s_ShaderSetData>& inData);
	
	void CloseXml();	