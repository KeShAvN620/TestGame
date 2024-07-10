#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include<vector>
#include"Utility.h"

class Player
{
	static enum {idleFrame = 4 , runFrame = 6 , spriteSize = 32 , zero = 0 };
private:
	sf::Texture texture;
	sf::Sprite sprite;

private:
	std::vector<sf::IntRect> idleAnimation;
	std::vector<sf::IntRect> rightAnimation;
	std::vector<sf::IntRect> leftAnimation;
	sf::Vector2f playerSpeed;

private:
	float speed;
	float animationTime;
	float animationSpeed;
	float scale;
	unsigned int counterLeft;
	unsigned int counterRight;
	unsigned int counterIdle;
	bool isMovingRight;
	bool isMovingLeft;


public:
	Player();
public:
	sf::Sprite& GetGlobalBoundry() { return sprite;}
public:
	void Load();
	void Update( float& deltaTime);
	void InputHandle(float &deltaTime);
	void AnimationHandle(float &deltatime);
	void Draw(std::shared_ptr<sf::RenderWindow> window);

};

