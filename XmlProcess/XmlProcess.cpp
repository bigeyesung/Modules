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
        m_Xml->getNodeValue({ TypeName ,"OperatingMode" }, inData.OperatingMode);
		//m_Xml->getNodeValue({ TypeName ,"ServerIP" }, inData.ServerIP);
		//m_Xml->getNodeValue({ TypeName ,"TCPport" }, inData.TCPport);
		m_Xml->getNodeValue({ TypeName ,"FluorescentPoint" }, tempInt);
		inData.FluorescentPoint = tempInt;
		m_Xml->getNodeValue({ TypeName ,"WallIntact" }, tempInt);
		inData.WallIntact = tempInt;
		m_Xml->getNodeValue({ TypeName ,"CaptureChangeType" }, inData.CaptureChangeType);
		m_Xml->getNodeValue({ TypeName ,"CameraRotaType" }, inData.CameraRotaType);
		m_Xml->getNodeValue({ TypeName ,"BlendPhase" }, inData.BlendPhase);


		return true;
	}
    else
	{
		inData.DisplayNum = ci::Display::getDisplays().size();
		inData.WindowsOffset = 0;		
		//inData.DisplayNum = 1;
		//inData.WindowsOffset = 1;
		inData.WindowsWidth = 1920;
		inData.WindowsHigh = 1080;
		inData.m_aliquots_w = 32;
		inData.m_aliquots_h = 25;
		inData.OverWidth = 4;
		inData.OverHigh = 0;
		inData.OverWidthP = inData.OverWidth / (inData.m_aliquots_w + 1);
		inData.OverHighP = inData.OverHigh / (inData.m_aliquots_h + 1);
		inData.WorldWidth = 100;
		inData.WorldHigh = 70;
		inData.VideoName.resize(inData.DisplayNum);
		for (int i = 0; i < inData.VideoName.size(); i++)
		{
			inData.VideoName[i] = "NoVideo";
		}

        inData.OperatingMode = OperatingMode_Client;
		//inData.ServerIP = "127.0.0.1";
		//inData.TCPport = 1000;
		inData.FluorescentPoint = false;
		inData.WallIntact = true;
		inData.CaptureChangeType = 0;
		inData.CameraRotaType = 0;
		inData.BlendPhase = 0;
		//�w�]���| �ɦW
		//inData.FilePath=
		return false;
	}
}

bool XmlProcess::GetData(vector<vector<joints>>& inData)
{
	string TypeName, TypeName1, TypeName2, TypeName3;
	int ProDataNum;
	double tempD;
	string tempS;
	vector<bool> DataExist;
	bool tempB = true;
	TypeName = "ProjectorData";
	m_Xml->getNodesNum({ TypeName }, ProDataNum);
    inData.resize(ProDataNum);
	DataExist.resize(inData.size());
	for (int i = 0; i < DataExist.size(); i++)
		DataExist[i] = false;
	for (int i = 0; i < ProDataNum; i++)
	{
		TypeName1 = "Projector" + to_string(i);
		TypeName2 = "ControlPoint";
		int PointNum = 0;
		DataExist[i] = m_Xml->getNodesNum({ TypeName, TypeName1, TypeName2 }, PointNum);
		inData[i].clear();
		inData[i].resize(PointNum);
        if (PointNum == inData[i].size())
		{
			for (int j = 0; j < inData[i].size(); j++)
			{
				TypeName3 = "P" + to_string(j);
				m_Xml->getAttrValue({ TypeName, TypeName1, TypeName2, TypeName3 }, "x", tempD);
				inData[i][j].final.x = tempD;
				m_Xml->getAttrValue({ TypeName, TypeName1, TypeName2, TypeName3 }, "y", tempD);
				inData[i][j].final.y = tempD;
			}
		}
		else
		{
			DataExist[i] = false;
			tempB = false;
			break;
		}
	}
	return tempB;
}

bool XmlProcess::GetData(vector<s_ShaderSetData> & inData)
{
	string TypeName, TypeName1, TypeName2;
	int ProDataNum;
	string tempS;
	vector<bool> DataExist;
	bool tempB = true;
	TypeName = "ProjectorData";
	m_Xml->getNodesNum({ TypeName }, ProDataNum);	
