//Map1.h
#pragma once
#include<vector>
#include<memory>
#include"BackGround.h"

class Map1
{
public:
	struct PathData {
		std::vector<float> xPosition;
		std::vector<float> yPosition;
		std::vector<unsigned int> colorCode;
		std::vector<bool> skipLeft;
		std::vector<bool> skipRight;
		std::vector<bool> skipTop;
		std::vector<bool> skipBottom;
		std::vector<bool> alreadySkipCalculated;
	};

private:
	std::vector<std::shared_ptr<BackGround>> level1;
	sf::Vector2f playerPosition;
	sf::Vector2f pathPosition;
	PathData pathdatas;


public:
	Map1();
	inline 	std::vector<std::shared_ptr<BackGround>>& GetPathVector() { return level1; }
public:
	void Load();
	void Update();
	void Draw(std::shared_ptr<sf::RenderWindow>& window);
private:
	void VectorsOverWrite();
	inline float GetProperScaleX(const float xPosition);
	inline float GetProperScaleY(const float yPosition);
};

