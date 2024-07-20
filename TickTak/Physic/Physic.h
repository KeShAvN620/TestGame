//physic.h
#pragma once
#include <SFML/Graphics.hpp>
#include"../Resources/Utility.h"
#include"Collision.h"
#include<vector>
#include<memory>
class Physic
{
    sf::FloatRect bounds1;
    sf::FloatRect bounds2;
private:
    float overlapLeft;
    float overlapRight;
    float overlapTop;
    float overlapBottom;
private:
    bool fromTop;
public:
	Physic();
public:
    //void PreliminarySearch(std::vector<std::shared_ptr<BackGround>>* level);
};

