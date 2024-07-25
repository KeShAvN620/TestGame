//Player.h
#pragma once
#include <SFML/Graphics.hpp>
#include<vector>
#include<string>
#include<memory>
#include"../Projectile/AuraSlice.h"
class Player
{
private:
	struct GameMechanicTime {
		float tempdeltatime = 0.0166667f;
		float jumpBoostTimer = 0.0f;
		float jumpBoostRate = 20.0f * tempdeltatime;
		float dodgeBoostTimer = 0.0f;
		float dodgeBoostRate = 4.0f * tempdeltatime;
		float dodgeTimer = 0.0f;
		float dodgeRate = 70.0f * tempdeltatime;
		float fireTime = 0.0f;
		float fireRate = 100.0f * tempdeltatime;
	};

	struct AnimationTimer {
		float tempdeltatime = 0.0166667f;
		float animationTime = 0;
		float animationRate = 8.0f * tempdeltatime;
		float jumpAnimationTime = 0;
	};

	struct AnimationStartingPoint {
		unsigned int frequencyX;
		unsigned int frequencyY;
		unsigned int idle;
		unsigned int run;
		unsigned int slide;
		unsigned int jump;
		unsigned int jumpFirsthalf;
		unsigned int jumpSecondhalf;
		unsigned int attack1;
	};

	struct AnimationSize {
		unsigned int idleSize = 4;
		unsigned int animationSize;
		unsigned int jumpAndSlide = 2;
	};

	struct Bool {
		bool isMovingRight = false;
		bool isMovingLeft = false;
		bool isJumping = false;
		bool isJumpBoost = false;
		bool isGravityAffecting = false;
		bool isDodging = false; bool canDodge = true;
		bool isDodgeBoost = false;
		bool isFiring = false;
	};

	struct Counter {
		unsigned int counterLeft = 0;
		unsigned int counterRight = 0;
		unsigned int counterIdle = 0;
		unsigned int counterJumpFirst = 0;
		unsigned int counterJumpSecond = 0;
		unsigned int counterSlide = 0;
	};

private:
	sf::Texture texture;
	std::vector<unsigned int> textureId;
	sf::Sprite sprite;
	sf::RectangleShape playerCollisionBox;
private:
	std::vector<sf::IntRect> playerAnimation;

private:
	sf::Text playerPositionText;
	sf::Vector2f playerSpeed;
	sf::Vector2f gravity;
	sf::Vector2f counterGravity;

private:
	std::vector<std::unique_ptr<AuraSlice>>projectile;

private:// struct variables
	AnimationTimer aT;
	GameMechanicTime gT;
	AnimationStartingPoint aSP;
	AnimationSize aS;
	Bool b;
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
	inline bool& CanDodging() { return b.canDodge;}

public:
	void Load();
	void Update( const float& deltatime);
	void Draw(std::shared_ptr<sf::RenderWindow>& window);



private://init
	void StructInit();
private: //load stuff
	void ImportantLoad();
	void PositionTxtLoader();
	void PositionTxtUpdate();
	void CollisionLoad();
private: //update stuff
	void GravityAffect();
	void InputHandle();
	void InputMovement();
	void InputShift();
	void AnimationHandle();
	void MovementAnimation();
	void ShiftAnimation();
	void InputJump();
	void JumpAnimation();


	// for projectile
private:
	void ProjectileLoad();
	void ProjectielUpdate();
	void ProjectileDraw();

};

