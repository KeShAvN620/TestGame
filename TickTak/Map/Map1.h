//Map1.h
#pragma once
#include<vector>
#include<memory>
#include"BackGround.h"
class Map1
{
private:
	std::vector<std::shared_ptr<BackGround>> level1;

public:
	Map1();

public:
	void Load();
	void Update();
	void Draw(std::shared_ptr<sf::RenderWindow>& window);
private:
	inline float GetProperScaleX(const float xPosition);
	inline float GetProperScaleY(const float yPosition);
};

