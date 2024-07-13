#pragma once
#include <SFML/Graphics.hpp>
#include"../Resources/Utility.h"
#include"Collision.h"
class Physic
{
private:
	sf::Vector2f gravity;
	sf::Vector2f velocityOfGravity;
private:
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
	sf::Vector2f AffectGravity(const sf::RectangleShape collisionBox, const sf::RectangleShape& path ,const float& deltatime);
};

