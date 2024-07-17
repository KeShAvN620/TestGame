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
private:
	bool isCollidingWithPlayer;
	int I;
	sf::Font font;
	sf::Text backgoundcollisionText;
	std::string collosionText;
public:
	bool skipCollisionCheckLeft;
	bool skipCollisionCheckRight;
	bool skipCollisionCheckTop;
	bool skipCollisionCheckBottom;
public:
	BackGround(const float pathWidthPositionScale, const float pathHeightPositionScale , const int i);
public:
	sf::RectangleShape& GetPathSprite() { return backGroundPath; }
	bool& IsCollisionWithPath() { return isCollidingWithPlayer; }
public:
	void Load();
	void Update();
	void CollisonDetection();
	void Draw(std::shared_ptr<sf::RenderWindow>& window);
};

