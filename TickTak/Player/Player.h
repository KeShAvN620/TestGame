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
	std::vector<sf::IntRect> jumpAnimation;
	sf::Vector2f playerSpeed;
	sf::Vector2f gravity;

private:
	float deltaTime;
	float speed;
	float animationTime;
	float animationSpeed;
	bool isMovingRight;
	bool isMovingLeft;
	bool isJumping;
	bool isJumpBoost;
	unsigned int counterLeft;
	unsigned int counterRight;
	unsigned int counterIdle;
	float jumpTime;
	float jumpRate;


public:
	Player();
public:
	inline sf::Sprite& GetPlayerSprite() { return sprite;}
	inline sf::RectangleShape& GetPlayerCollisionBox() { return playerCollisionBox;}
	inline bool& IsJumping() { return isJumping; }
public:
	void Load();
	void Update( const float& deltatime);
	void GravityAffect();
	void InputHandle();
	void AnimationHandle();
	void InputMovement();
	void AnimationMovement();
	void InputJump();
	void JumpAnimation();
	void Draw(std::shared_ptr<sf::RenderWindow> window);
};

