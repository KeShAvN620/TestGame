#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include<vector>
class Player
{
	enum {idleFrame = 4 , runFrame = 6 , spriteSize = 32 , scale = 2 , zero = 0 };
private:
	sf::Texture texture;
	sf::Sprite sprite;
private:
	std::vector<sf::IntRect> idleAnimation;
	std::vector<sf::IntRect> rightAnimation;
	std::vector<sf::IntRect> leftAnimation;
	sf::Vector2f playerSpeed;
	float speed;
	unsigned int counterLeft;
	unsigned int counterRight;
	unsigned int counterIdle;
	bool isMovingRight;
	bool isMovingLeft;
	float animationTime;
	float animationSpeed;


public:
	Player();

public:
	void Load();
	void Update( float& deltaTime);
	void InputHandle(float &deltaTime);
	void AnimationUpdate(float &deltatime);
	void Draw(std::shared_ptr<sf::RenderWindow> window);

};

