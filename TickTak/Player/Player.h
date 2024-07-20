//Player.h
#pragma once
#include <SFML/Graphics.hpp>
#include<vector>
#include<string>
class Player
{
private:
	struct Bool {
		bool isMovingRight = false;
		bool isMovingLeft = false;
		bool isJumping = false;
		bool isJumpBoost = false;
		bool isGravityAffecting = false;
	};
	struct Animation {
		float animationTime = 0;
		float animationSpeed = 8.0f * 0.0166667f;
		float jumpTime = 0;
		float jumpRate = 18.0f * 0.0166667f;
		float jumpAnimationTime = 0;
		float jumpAnimationRate = 18.0f * 0.0166667f;
	};
	struct Counter {
		unsigned int counterLeft = 0;
		unsigned int counterRight = 0;
		unsigned int counterIdle = 0;
		unsigned int jumpAnimationcounter = 0;
	};
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape playerCollisionBox;
private:
	std::vector<sf::IntRect> idleAnimation;
	std::vector<sf::IntRect> runAnimation;
	std::vector<sf::IntRect> jumpAnimation;
private:
	sf::Text playerPositionText;
	sf::Vector2f playerSpeed;
	sf::Vector2f gravity;
	sf::Vector2f counterGravity;
private:
	Bool b;
	Animation a;
	Counter c;  
private:
	float deltaTime;
	float speed;
public:
	Player();
public:
	inline sf::Sprite& GetPlayerSprite() { return sprite;}
	inline sf::RectangleShape& GetPlayerCollisionBox() { return playerCollisionBox;}
	inline bool& IsJumping() { return b.isJumping; }
	inline bool& IsGravityBoost() { return b.isJumpBoost; }
	inline bool& IsGravityAffecting() { return b.isGravityAffecting; }

public:
	void Load();
	void Update( const float& deltatime);
	void Draw(std::shared_ptr<sf::RenderWindow> window);

private: //load stuff
	void ImportantLoad();
	void PositionTxtLoader();
	void PositionTxtUpdate();
	void CollisionLoad();
	void ReInitializer();
private: //update stuff
	void GravityAffect();
	void InputHandle();
	void AnimationHandle();
	void InputMovement();
	void AnimationMovement();
	void InputJump();
	void JumpAnimation();
};

