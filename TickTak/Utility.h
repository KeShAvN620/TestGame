#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>


class Utiluty
{
public:
	static void UpdateAnimation(sf::Sprite& animationSprite, unsigned int& animationCounter, std::vector<sf::IntRect>& animationFrame);
	static void AABBCollisionDetection(const sf::Sprite& sprite1, const sf::RectangleShape& sprite2);
};

