//collision.h
#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include"../Resources/Utility.h"
#include<memory>
#include<vector>
#include"../Map/BackGround.h"
class Collision
{
private: // use by all
    sf::FloatRect bounds1;
    sf::FloatRect bounds2;
private:// by path player
    float overlapLeft;
    float overlapRight;
    float overlapTop;
    float overlapBottom;
private:// by path player
    bool fromLeft;
    bool fromRight;
    bool fromTop;
    bool fromBottom;
private: //by DoCollisionNearPlayer
    bool isGravityAffecting;
public:
    Collision();
    void CollisionReseter();
    void UpdateAnimation(sf::Sprite& animationSprite, unsigned int& animationCounter, std::vector<sf::IntRect>& animationFrame);
    bool PathPlayerCollidionDetection(const sf::RectangleShape& sprite1, const sf::RectangleShape& sprite2, sf::Sprite& sprite3, bool& boxLeft, bool& boxRight, bool& boxTop, bool& boxBottom);
    void PreliminarySearch(std::vector<std::shared_ptr<BackGround>>& level1);
    bool PlayerOnGround(sf::Sprite& sprite, std::vector<std::shared_ptr<BackGround>>& level);
};
