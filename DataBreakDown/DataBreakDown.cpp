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