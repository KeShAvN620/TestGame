#include "FileRead.h"

FileRead::FileRead(){
	std::vector<float> xPosition;
	std::vector<float> yPosition;
	std::vector<unsigned int> colorCode;
	std::vector<bool> skipLeft;
	std::vector<bool> skipRight;
	std::vector<bool> skipTop;
	std::vector<bool> skipBottom;
	std::vector<bool> alreadySkipCalculated;
}

void FileRead::ReadMapData(Map1::PathData& vectors){
	std::ifstream Read;
	Read.open("FileHandlingDetails/Map1/Map1PathData.txt");
	if (!Read.is_open()) {
		std::cerr << "unable to read Map1 data" << std::endl;
		Read.close();
		return;
	}
	float xpos, ypos; unsigned int ccode; bool left, right, top, bottom, alreadydone;
	while (Read >> xpos >> ypos >> ccode >> left >> right >> top >> bottom >> alreadydone) {
		if (Read.fail()) {
			std::cerr << "Error reading data at line: " << Read.tellg() << std::endl;
			break;
		}
		vectors.xPosition.push_back(xpos);
		vectors.yPosition.push_back(ypos);
		vectors.colorCode.push_back(ccode);
		vectors.skipLeft.push_back(left);
		vectors.skipRight.push_back(right);
		vectors.skipTop.push_back(top);
		vectors.skipBottom.push_back(bottom);
		vectors.alreadySkipCalculated.push_back(alreadydone);
	}
	Read.close();
	return;
}

void FileRead::WriteMapData(Map1::PathData& vectors){
	std::ofstream Write;
	Write.open("FileHandlingDetails/Map1/Map1PathData.txt");
	if (!Write.is_open()) {
		std::cerr << "unable to write Map1 data" << std::endl;
		Write.close();
		return;
	}
	for (unsigned int i = 0; i < vectors.xPosition.size(); i++) {
		Write << vectors.xPosition[i]<<" " << vectors.yPosition[i] << " " << vectors.colorCode[i] << " " << vectors.skipLeft[i] << " "
			<< vectors.skipRight[i] << " " << vectors.skipTop[i] << " " << vectors.skipBottom[i] << " " << vectors.alreadySkipCalculated[i]<< std::endl;
	}

	//std::cout << "Write file Mapdata" << std::endl;
	Write.close();
	return;
}
