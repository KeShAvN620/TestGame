//Player.h
#pragma once
#include <SFML/Graphics.hpp>
#include<vector>
class Player
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape playerCollisionBox;

private:
	std::vector<sf::IntRect> idleAnimation;
	std::vector<sf::IntRect> rightAnimation;
	std::vector<sf::IntRect> leftAnimation;
	sf::Vector2f playerSpeed;

private:
	float speed;
	float animationTime;
	float animationSpeed;
	bool isMovingRight;
	bool isMovingLeft;
	unsigned int counterLeft;
	unsigned int counterRight;
	unsigned int counterIdle;


public:
	Player();
public:
	inline sf::Sprite& GetPlayerSprite() { return sprite;}
	inline sf::RectangleShape& GetPlayerCollisionBox() { return playerCollisionBox;}
public:
	void Load();
	void Update( float& deltaTime);
	void InputHandle(float &deltaTime);
	void AnimationHandle(float &deltatime);
	void GravityAffect(const float &deltaTime);
	void Draw(std::shared_ptr<sf::RenderWindow> window);

};

