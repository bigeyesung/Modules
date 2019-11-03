#include <string>
#include <sstream>
#include "cinder/app/App.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

public:
	DataBreakDown();
	~DataBreakDown();
	//int
	void IntDataToString(const vector<int> & inData, string & outData);
	void StringToIntData(const string & inData, vector<int> & outData);
	void StringToIntData(const string & inData, vector<int>& outData, string& EndString);

    void FloatDataToString(const vector<float>& inData, string & outData);

	void StringToFloatData(const string & inData, vector<float>& outData, string& EndString);
	