#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include"../Resources/Utility.h"
class Collision
{
private:
    sf::FloatRect bounds1;
    sf::FloatRect bounds2;
private:
    float overlapLeft;
    float overlapRight;
    float overlapTop;
    float overlapBottom;
private:
    bool fromLeft;
    bool fromRight;
    bool fromTop;
    bool fromBottom;
    int errorManagement; // here  +1 is error management for collosion from bottom and right
public:
    Collision();
    void UpdateAnimation(sf::Sprite& animationSprite, unsigned int& animationCounter, std::vector<sf::IntRect>& animationFrame);
    bool PathPlayerCollidionDetection(sf::RectangleShape& sprite1, const sf::RectangleShape& sprite2, sf::Sprite& sprite3);
};
