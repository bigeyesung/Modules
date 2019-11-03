#pragma once
#include <string>
#include "cinder/app/App.h"

using namespace std;

using namespace ci::app;

class DebugClass
{
public:
	DebugClass();
	~DebugClass();

	//cinder console
	void CinderConsole(string Massage);
	void CinderConsoleNextLine(string Massage);
	void CinderConsoleNextLine(int Massage);