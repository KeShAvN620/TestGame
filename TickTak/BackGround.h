//Background.h
#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include<memory>

class BackGround
{	
	struct PathSpecification { // formula to find the required scale   reqScale = maxDimension/(maxDimension - requiredDimesion)
		float pathWidthSizeScale = 1.6f;  // Scale factor for path width , make the path width to (1/1.6)th of orginal window width
		float pathHeightSizeScale = 12.0f; // Scale factor for path height, make the path height to (1/12)th of orginal window width
		float pathWidthPositionScale = 16.0f/13.0f; // Scale factor for path width position,
		float pathHeightPositionScale = 3.0f; // Scale factor for path height position
	} Dimension;

private:
	sf::RectangleShape backGroundPath;
	sf::Vector2f pathSize;
	sf::Vector2f pathPosition;
public:
	BackGround(const float& windowMinWidth, const float& windowMaxWidth, const float& windowMinHeight, const float& windowMaxHeight);
public:
	sf::RectangleShape& GetGlobalBoundry() { return backGroundPath; }

public:
	void Load();
	void Draw(std::shared_ptr<sf::RenderWindow> window);
};

