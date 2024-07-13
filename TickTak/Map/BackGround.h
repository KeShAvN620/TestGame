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
	sf::Font font;
	sf::Text backgoundcollisionText;
	std::string collosionText;
public:
	BackGround(const float& windowMinWidth, const float& windowMaxWidth, const float& windowMinHeight, const float& windowMaxHeight);
public:
	sf::RectangleShape& GetPathSprite() { return backGroundPath; }
	bool& IsCollisionWithPath() { return isCollidingWithPlayer; }
public:
	void Load();
	void Update();
	void CollisonDetection();
	void CollisionOfJump();
	void Draw(std::shared_ptr<sf::RenderWindow> window);
};

