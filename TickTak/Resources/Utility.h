#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>


struct GameMagicNumbers {
    // for windows
    static constexpr float windowMinWidth = 0.0f;
    static constexpr float windowMaxWidth = 800.0f;
    static constexpr float windowMinHeight = 0.0f;
    static constexpr float windowMaxHeight = 600.0f;
    static constexpr unsigned int maxFrameRate = 60;

    // for player
    static constexpr float gravity = 160.0f;
    static constexpr float gravityCounter = 3 * gravity;
    static constexpr unsigned int idleFrame = 4;
    static constexpr unsigned int runFrame = 6;
    static constexpr unsigned int spriteSize = 32;
    static constexpr unsigned int zero = 0;
    static constexpr unsigned int one = 1;
    static constexpr float errorManagement = 1.5f;
    static constexpr float playerScale = 1.75f;
    static constexpr float collisionBoxThickness = 1.0f;
    static constexpr float collisionBoxSizeScale = (3.1f / 4.0f);
    static constexpr float collisionBoxPositionOffset = playerScale * ( 1 + 4.0f / playerScale);
    

    // for path or background path
    // formula to find the required scale   reqScale = maxDimension/(maxDimension - requiredDimension)
    static constexpr float pathSize = 2*(spriteSize - 1);
    static constexpr float pathWidthPositionScale = 13.0f / 16.0f; // Scale factor for path width position,
    static constexpr float pathHeightPositionScale = 1/3.0f; // Scale factor for path height position
};


class Utiluty
{
    sf::Font font;
    public:
    Utiluty();
public:
    sf::Font GetFont();
    void UpdateAnimation(sf::Sprite& animationSprite, unsigned int& animationCounter, std::vector<sf::IntRect>& animationFrame);
};

