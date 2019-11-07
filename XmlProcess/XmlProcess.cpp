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