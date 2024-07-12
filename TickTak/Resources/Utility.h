#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>


struct GameMagicNumbers {
    // for windows
    static constexpr float windowMinWidth = 0.0f;
    static constexpr float windowMaxWidth = 800.0f;
    static constexpr float windowMinHeight = 0.0f;
    static constexpr float windowMaxHeight = 600.0f;

    // for player
    static constexpr float gravity = 200.0f;
    static constexpr unsigned int idleFrame = 4;
    static constexpr unsigned int runFrame = 6;
    static constexpr unsigned int spriteSize = 32;
    static constexpr unsigned int zero = 0;
    static constexpr int errorManagement = 1;
    static constexpr float playerScale = 1.75f;
    static constexpr float collisionBoxThickness = 1.0f;
    static constexpr float collisionBoxSizeScale = (3.1f / 4.0f);
    static constexpr float collisionBoxPositionOffset = playerScale * ( 1 + 4.0f / playerScale);
    

    // for path or background path
    // formula to find the required scale   reqScale = maxDimension/(maxDimension - requiredDimension)
    static constexpr float pathWidthSizeScale = 1.6f;  // Scale factor for path width, make the path width to (1/1.6)th of original window width
    static constexpr float pathHeightSizeScale = 12.0f; // Scale factor for path height, make the path height to (1/12)th of original window width
    static constexpr float pathWidthPositionScale = 16.0f / 13.0f; // Scale factor for path width position,
    static constexpr float pathHeightPositionScale = 3.0f; // Scale factor for path height position
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

