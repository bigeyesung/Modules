#include "DataBreakDown.h"

DataBreakDown::DataBreakDown()
{

}
DataBreakDown::~DataBreakDown()
{

}

void DataBreakDown::IntDataToString(const vector<int> & inData, string & outData)
{
	ostringstream out;
	out << inData.size() << ' ';
	for (int i = 0; i < inData.size(); i++)
	{
		out << inData[i] << ' ';
    }
	outData = out.str();
}

void DataBreakDown::StringToIntData(const string & inData, vector<int> & outData)
{
	//istringstream in(inData);
	in.str("");
	in.clear();
	in.str(inData);
	int Num = 0;
	in >> Num;
    if (Num < 0)
		outData.resize(1);
	else
		outData.resize(Num);
	for (int i = 0; i <Num; i++)
	{
		in >> outData[i];
	}
}

void DataBreakDown::StringToIntData(const string & inData, vector<int> & outData, string& EndString)
{
	//istringstream in(inData);
	in.str("");
	in.clear();
	in.str(inData);
	int Num = 0;
	in >> Num;
	if (Num < 0)
		outData.resize(1);
    else
		outData.resize(Num);
	for (int i = 0; i <Num; i++)
	{
		in >> outData[i];
	}
	EndString = "";
    getline(in, EndString);
	if (EndString != "")
	{
		//�h�Ů�
		EndString.erase(0, 1);
	}
}

void DataBreakDown::FloatDataToString(const vector<float> & inData, string & outData)
{
	ostringstream out;
	out.precision(6);
	out << inData.size() << ' ';
	for (int i = 0; i < inData.size(); i++)
    {
		out << inData[i] << ' ';
	}
	outData = out.str();
}

void DataBreakDown::StringToFloatData(const string & inData, vector<float> & outData, string& EndString)
{
	//istringstream in(inData);
	in.str("");
	in.clear();
	in.str(inData);
	int Num = 0;
	in >> Num;
	if (Num < 0)
        outData.resize(1);
	else
		outData.resize(Num);
	for (int i = 0; i <Num; i++)
	{
		in >> outData[i];
	}
	EndString = "";
    getline(in, EndString);
	if (EndString != "")
	{
		EndString.erase(0, 1);
	}
}

void DataBreakDown::PointArrayToString(const vector<Point2f>& inData, string & outData)
{
	ostringstream out;
	out.precision(6);
	out << inData.size() << ' ';
	Point2f tempP2f;
	for (int i = 0; i < inData.size(); i++)
	{
		tempP2f = inData[i];
		out << tempP2f.x << ' ';
		out << tempP2f.y << ' ';
	}
    outData = out.str();
}

void DataBreakDown::PointArrayToString(const vector<vector<Point2f>>& inData, string & outData)
{
	ostringstream out;
	out.precision(6);
	int TotalNum = 0;
	for (int i = 0; i < inData.size(); i++)
	{
		TotalNum += inData[i].size();
	}
    out << TotalNum << ' ';
	Point2f tempP2f;
	for (int i = 0; i < inData.size(); i++)
	{
		for (int j = 0; j < inData[i].size(); j++)
		{
			tempP2f = inData[i][j];
			out << tempP2f.x << ' ';
			out << tempP2f.y << ' ';
		}
	}
	outData = out.str();
}

void DataBreakDown::StringToPointArray(const string & inData, vector<Point2f>& outData)
{
	//istringstream in(inData);
	in.str("");
	in.clear();
	in.str(inData);
	int Num = 0;
	in >> Num;
    if (Num < 0)
		outData.resize(1);
	else
		outData.resize(Num);
	Point2f tempP2f;
	for (int i = 0; i < Num; i++)
	{
		in >> tempP2f.x;
		in >> tempP2f.y;
		outData[i] = tempP2f;
	}
}