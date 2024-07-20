//Background.h
#pragma once
#include <SFML/Graphics.hpp>
#include<memory>
#include<string>

class BackGround
{	
private:
	sf::RectangleShape backGroundPath;
	sf::Vector2f pathSize;
	sf::Vector2f pathPosition;
	sf::Vector2f playerPosition;

public:
	sf::Color pathColor;
	bool skipCollisionCheckLeft;
	bool skipCollisionCheckRight;
	bool skipCollisionCheckTop;
	bool skipCollisionCheckBottom;

public:
	BackGround(const float wPositionScale, const float hPositionScale ,unsigned int colorcode = 6);
public:
	sf::RectangleShape& GetPathSprite() { return backGroundPath; }
public:
	void Load();
	void Update();
	void CollisonDetection();
	void Draw(std::shared_ptr<sf::RenderWindow>& window);
};

