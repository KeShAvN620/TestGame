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
	std::vector<sf::IntRect> runAnimation;
	std::vector<sf::IntRect> jumpAnimation;
	sf::Vector2f playerSpeed;
	sf::Vector2f gravity;
	sf::Vector2f counterGravity;

private:
	float deltaTime;
	float speed;
	float animationTime;
	float animationSpeed;
private:
	bool isMovingRight;
	bool isMovingLeft;
	bool isJumping;
	bool isJumpBoost;
	bool isGravityAffecting;
private:
	unsigned int counterLeft;
	unsigned int counterRight;
	unsigned int counterIdle;
	float jumpTime;
	float jumpRate;
	unsigned int jumpAnimationcounter;
	float jumpAnimationTime;
	float jumpAnimationRate;


public:
	Player();
public:
	inline sf::Sprite& GetPlayerSprite() { return sprite;}
	inline sf::RectangleShape& GetPlayerCollisionBox() { return playerCollisionBox;}
	inline bool& IsJumping() { return isJumping; }
	inline bool& IsGravityBoost() { return isJumpBoost; }
	inline bool& IsGravityAffecting() { return isGravityAffecting; }
public:
	void Load();
	void Update( const float& deltatime);
	void Draw(std::shared_ptr<sf::RenderWindow> window);
private:
	void ReInitializer();
	void GravityAffect();
	void InputHandle();
	void AnimationHandle();
	void InputMovement();
	void AnimationMovement();
	void InputJump();
	void JumpAnimation();
};

