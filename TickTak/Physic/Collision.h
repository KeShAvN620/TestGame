//collision.h
#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include"../Resources/Utility.h"
#include<memory>
#include<vector>
#include"../Map/BackGround.h"
#include"../Map/Map1.h"
class Collision
{
private: // use by all
    sf::FloatRect bounds1;
    sf::FloatRect bounds2;
    sf::Vector2f position1;
    sf::Vector2f position2;
private:// by path player
    float tolerance;
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
    void PathPlayerCollidionDetection(const sf::RectangleShape& sprite1, const sf::RectangleShape& sprite2,
        sf::Sprite& sprite3, bool& boxLeft, bool& boxRight, bool& boxTop, bool& boxBottom);
    void PreliminarySearch(std::vector<std::shared_ptr<BackGround>>& level1 , std::vector<bool>&left , 
        std::vector<bool>& right , std::vector<bool>& top, std::vector<bool>& bottom 
        , std::vector<bool>&alreadydone);
    void PreliminarySearch(std::vector<std::shared_ptr<BackGround>>& level1, Map1::PathData& VS);
    //void PreliminarySerachV2(std::vector<std::shared_ptr<BackGround>>& level , const unsigned int i);
    //bool PlayerOnGround(sf::Sprite& sprite, std::vector<std::shared_ptr<BackGround>>& level);
    void BoundFinder();
    void BoolFinder();
    void ExpandBound(sf::FloatRect& bound);
};
