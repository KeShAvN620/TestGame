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
private:
    bool left;
    bool right;
    bool top;
    bool bottom;

public:
    inline bool CollisionOnTop(){ return fromTop; }
    inline bool CollisionOnBottom() { return fromBottom; }
public:
    Collision();
    void CollisionReseter();
    void UpdateAnimation(sf::Sprite& animationSprite, unsigned int& animationCounter, std::vector<sf::IntRect>& animationFrame);
    bool PathPlayerCollidionDetection(const sf::RectangleShape& sprite1, const sf::RectangleShape& sprite2, sf::Sprite& sprite3, bool& boxLeft, bool& boxRight, bool& boxTop, bool& boxBottom);
    void PreliminarySearch(std::vector<std::shared_ptr<BackGround>>& level1);
};
