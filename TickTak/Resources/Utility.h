//utility.h
#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>


struct GMnumber {
    // for windows
    static constexpr float baseWidth = 800.0f;
    static constexpr float baseHeight = 600.0f;
    static constexpr float windowMinWidth = 0.0f;
    static constexpr float windowMaxWidth = 800.0f;
    static constexpr float windowMinHeight = 0.0f;
    static constexpr float windowMaxHeight = 600.0f;
    static constexpr unsigned int maxFrameRate = 60;

    // for player
   // static constexpr float tempdeltatime = 0.0166667f;
    static constexpr unsigned int playerId = 1000000;
    static constexpr unsigned int enemyId = 2000000;
    static constexpr float playerSpeed = 150.0f;
    static constexpr float gravity = 140.0f;
    static constexpr float gravityCounter = 3.0f * gravity;
    static constexpr unsigned int spriteSize = 32;
    static constexpr float oneAndHalf = 1.5f;
    static constexpr float playerScale = 1.75f;
    static constexpr float dodgepixel = 20.0f;

    // for collision box
    static constexpr unsigned int zero = 0;
    static constexpr unsigned int one = 1;
    static constexpr float quater = .25f;
    static constexpr float collisionBoxThickness = 1.0f;
    static constexpr float collisionBoxSizeScale = (2.2f / 4.0f);
    static constexpr float collisionBoxSizeX = playerScale * spriteSize * collisionBoxSizeScale - one;
    static constexpr float collisionBoxSizeY = playerScale * spriteSize - one;

    // for path or background path
    static constexpr float pathSize = 2*spriteSize;

    // for map 
    static constexpr unsigned int MapSize = 200;
    static constexpr float minimumDistance = 96.0f;
    static constexpr float minimumUpdateDistanceX = 400.0f;
    static constexpr float minimumUpdateDistanceY = minimumUpdateDistanceX * .75f;

    // for slice
    static constexpr float sliceSize = 15.0f;
    static constexpr unsigned int  newSliceSizeX = 25;
    static constexpr unsigned int  newSliceSizeY = 30;
    static constexpr float sliceCollisionSize = sliceSize - 1.0f;
    static constexpr float projectileScale = 2.0f * playerScale;
    static constexpr float projectileSpeed = 4.0f * playerSpeed;
    static constexpr float PI = 3.14159f;
    static constexpr unsigned int oneEightyDegree = 180;
    static constexpr unsigned int bulletMaxDistanceByPlayer = static_cast<unsigned int >(windowMaxWidth /3.30f);

};


class Utility
{
    sf::Font font;
    sf::Texture playerTexture;
    sf::Texture bulletTexture;
private:
    float dx;
    float dy;
    float distanceSquared;
    float minimumDistanceSquared;

    float length;
public:
    std::vector<sf::Color> colors;
public:
    Utility();

private:
    void ColorLoader();
    void LoadBullet();
public:
   inline sf::Font& GetFont() { return font; }
   inline sf::Texture& GetPlayerTexture() { return playerTexture;}
   inline sf::Texture& GetBulletTexture() { return bulletTexture;}
public:

   void UpdateAnimation(sf::Sprite& aSprite, std::vector<sf::IntRect>& aFrame, unsigned int& aCounter,const unsigned int& aStart , const unsigned int& aSize );
   bool UpdateAndDrawEnabler(const sf::Vector2f& playerPosition ,const  sf::Vector2f& pathPosition);
   bool MinimumDistanceCollisionUpdate( const sf::Vector2f& position1 ,const sf::Vector2f& position2);
   sf::Vector2f NormalizedVectors(sf::Vector2f& vector);
   
};

