#pragma once
#include <SFML/Graphics.hpp>
#include"../Resources/Utility.h"
#include"Collision.h"
class Physic
{
private:
	sf::Vector2f gravity;
	sf::Vector2f velocityOfGravity;
public:
	Physic();
public:
	sf::Vector2f AffectGravity(const sf::Sprite& sprite, const sf::RectangleShape& path ,const float& deltatime);
};

