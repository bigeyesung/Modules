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