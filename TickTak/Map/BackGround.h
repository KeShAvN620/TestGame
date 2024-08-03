//Background.h
#pragma once
#include <SFML/Graphics.hpp>
#include<memory>
#include<string>


class BackGround
{	public:
	struct Cleck {
		bool skipLeft;
		bool skipRight;
		bool skipTop;
		bool skipBottom;
		bool DetectionAlreadyDone;
	};
	Cleck c;
private:
	sf::RectangleShape backGroundPath;
	sf::Vector2f pathSize; 
	sf::Vector2f pathPosition;
	sf::Vector2f playerPosition;
	sf::Color pathColor;

	
public:
	BackGround(float xPosSacle, float yPosSacle, unsigned int colorCode , bool left, bool right , bool top , bool bottom , bool done);
public:
	sf::RectangleShape& GetPathSprite() { return backGroundPath; }
public:
	void Load();
	void Update();
	void CollisonDetection();
	void Draw(std::shared_ptr<sf::RenderWindow>& window);
};

