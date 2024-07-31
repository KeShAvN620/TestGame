#pragma once
#include<iostream>
#include<memory>
#include<vector>
#include<fstream>
#include"../Map/Map1.h"
class FileRead
{
private: // Maps path
	//std::vector<float> xPosition;
	//std::vector<float> yPosition;
	//std::vector<unsigned int> colorCode;
	//std::vector<bool> skipLeft;
	//std::vector<bool> skipRight;
	//std::vector<bool> skipTop;
	//std::vector<bool> skipBottom;
	//std::vector<bool> alreadySkipCalculated;
public:
	FileRead();
public:
	//std::vector<float>& getXPosition() { return xPosition; }
	//std::vector<float>& getYPosition() { return yPosition; }
	//std::vector<unsigned int>& getColorCode() { return colorCode; }
	//std::vector<bool>& GetSkipLeft() { return skipLeft; }
	//std::vector<bool>& GetSkipRight() { return skipRight; }
	//std::vector<bool>& GetSkipTop() { return skipTop; }
	//std::vector<bool>& GetSkipBottom() { return skipBottom; }
	//std::vector<bool>& GetAlreadySkipCalculated() { return alreadySkipCalculated; 

public:
	void ReadMapData(Map1::PathData& vectors);
	void WriteMapData(Map1::PathData& vectors);

};

