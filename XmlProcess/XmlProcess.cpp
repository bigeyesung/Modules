#include "XmlProcess.h"
XmlProcess::XmlProcess()
{
	CanSave = false;
	XmlExist = false;
	m_Xml = NULL;
}
XmlProcess::~XmlProcess()
{
	CloseXml();
}

void XmlProcess::ReadXml(const string& FilePath)
{
	if (m_Xml == NULL)
	{
		m_Xml= new XmlParser();
	}
	else
	{
		CloseXml();
		m_Xml = new XmlParser();
	}

    if (m_Xml->readXmlFile(FilePath) != XmlParser::RET_SUCCESS)
	{
		m_Xml->createXmlFile("ClientData");
		m_Xml->addNode({ "Root" }, "InitData");
		m_Xml->addNode({ "Root" }, "ProjectorData");

		//m_Xml->addNode({ "Root" }, "ShaderData");
		//m_Xml->addNode({ "Root" }, "WebcamData");
		//m_Xml->addNode({ "Root" }, "WallPoint");
		//m_Xml->addNode({ "Root" }, "ControlPoint");

		XmlExist = false;
	}
    else
	{
		XmlExist = true;
	}

	//����
	//XmlExist = true;
	CanSave = true;
}

bool XmlProcess::GetData(s_InitData & inData)
{
	if (XmlExist)
	{
		string TypeName, TypeName1;
		int tempInt;
		TypeName = "InitData";

		m_Xml->getNodeValue({ TypeName ,"ProjectorNum" }, inData.DisplayNum);
		m_Xml->getNodeValue({ TypeName ,"WindowsOffset" }, inData.WindowsOffset);
		m_Xml->getAttrValue({ TypeName ,"WindowsSize" }, "Width", inData.WindowsWidth);
		m_Xml->getAttrValue({ TypeName ,"WindowsSize" }, "High", inData.WindowsHigh);
		m_Xml->getAttrValue({ TypeName ,"PointNum" }, "Width", inData.m_aliquots_w);
		inData.m_aliquots_w--;
		m_Xml->getAttrValue({ TypeName ,"PointNum" }, "High", inData.m_aliquots_h);
		inData.m_aliquots_h--;
        m_Xml->getAttrValue({ TypeName ,"OverPointNum" }, "Width", inData.OverWidth);
		m_Xml->getAttrValue({ TypeName ,"OverPointNum" }, "High", inData.OverHigh);
		m_Xml->getAttrValue({ TypeName ,"WorldPos" }, "Width", inData.WorldWidth);
		m_Xml->getAttrValue({ TypeName ,"WorldPos" }, "High", inData.WorldHigh);
		m_Xml->getNodesNum({ TypeName ,"VideoName" }, tempInt);
		inData.VideoName.resize(tempInt);
		for (int i = 0; i < inData.VideoName.size(); i++)
		{
			TypeName1 = "Name" + to_string(i);
			m_Xml->getNodeValue({ TypeName ,"VideoName", TypeName1 }, inData.VideoName[i]);
		}