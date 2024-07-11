//Player.cpp
#include "Player.h"
#include"../GameObject.h"

Player::Player()
	: speed(100.0f), playerSpeed(0.0f, 0.0f), counterLeft(0),counterRight(0), 
	counterIdle(0), isMovingRight(false), isMovingLeft(false),
	animationTime(0), animationSpeed(8.0f * 0.0166667f) {
	if (!texture.loadFromFile("Assets/Adventure/AD_IDLE_RUN_V2.png")) {
		std::cout << "failed to load player texture " << std::endl;
	}
	for (unsigned int i = 0; i < GameMagicNumbers::idleFrame; i++) {
		this->idleAnimation.push_back(sf::IntRect(i * GameMagicNumbers::spriteSize, GameMagicNumbers::zero, GameMagicNumbers::spriteSize, GameMagicNumbers::spriteSize));
	}
	for (unsigned int i = 0; i < GameMagicNumbers::runFrame; i++) {
		this->rightAnimation.push_back(sf::IntRect(i * GameMagicNumbers::spriteSize, GameMagicNumbers::spriteSize, GameMagicNumbers::spriteSize, GameMagicNumbers::spriteSize));
	}
	for (unsigned int i = 0; i < GameMagicNumbers::runFrame; i++) {
		this->leftAnimation.push_back(sf::IntRect(i * GameMagicNumbers::spriteSize, 2 * GameMagicNumbers::spriteSize, GameMagicNumbers::spriteSize, GameMagicNumbers::spriteSize));
	}
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(this->idleAnimation[GameMagicNumbers::zero]);
	this->playerCollisionBox.setOutlineThickness(GameMagicNumbers::collisionBoxThickness);
	this->playerCollisionBox.setOutlineColor(sf::Color::Green);
	this->playerCollisionBox.setFillColor(sf::Color::Transparent);
}


void Player::Load(){
	this->sprite.setPosition(sf::Vector2f(300.f, 300.f)); // random starting point todo change it by a GameMagicNumbers
	this->sprite.setScale(sf::Vector2f(GameMagicNumbers::playerScale, GameMagicNumbers::playerScale));


	this->playerCollisionBox.setPosition(sprite.getPosition());
	this->playerCollisionBox.setSize(sf::Vector2f(GameMagicNumbers::playerScale * GameMagicNumbers::spriteSize * GameMagicNumbers::collisionBoxSizeScale, GameMagicNumbers::playerScale * GameMagicNumbers::spriteSize));
}

void Player::Update(float& deltaTime){
	InputHandle(deltaTime);
	AnimationHandle(deltaTime);
	GravityAffect(deltaTime);
}


void Player::InputHandle(float& deltaTime){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->playerSpeed.x = -this->speed * deltaTime;
		this->isMovingRight = false;
		this->isMovingLeft = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->playerSpeed.x = this->speed * deltaTime;
		this->isMovingRight = true;
		this->isMovingLeft = false;
	}
	else{
		this->isMovingRight = false;
		this->isMovingLeft = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->playerSpeed.y = -this->speed * deltaTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->playerSpeed.y = this->speed * deltaTime;
	}
}

void Player::AnimationHandle(float& deltaTime) {
	this->animationTime += deltaTime;
	if (this->animationTime >= this->animationSpeed) {
		this->animationTime -= this->animationSpeed;
		if (this->isMovingRight) {
			if (rightAnimation.empty()) {
				std::cerr << "Error: rightAnimation is empty!" << std::endl;
			}
			else {
				gameObject.utility.UpdateAnimation(sprite, counterRight, rightAnimation);
			}
		}
		else if (this->isMovingLeft) {
			if (leftAnimation.empty()) {
				std::cerr << "Error: leftAnimation is empty!" << std::endl;
			}
			else {
				gameObject.utility.UpdateAnimation(sprite, counterLeft, leftAnimation);
			}
		}
		else {
			if (idleAnimation.empty()) {
				std::cerr << "Error: idleAnimation is empty!" << std::endl;
			}
			else {
				gameObject.utility.UpdateAnimation(sprite, counterIdle, idleAnimation);
			}
		}
	}
}

void Player::GravityAffect(const float& deltaTime){
	this->sprite.move(playerSpeed + gameObject.physic.AffectGravity(sprite,gameObject.backGroundPath->GetPathSprite(), deltaTime));
	this->playerCollisionBox.setPosition(sprite.getPosition() + sf::Vector2f(GameMagicNumbers::collisionBoxPositionOffset, 0.f));
	this->playerSpeed = sf::Vector2f(0.0f, 0.0f);
}

void Player::Draw(std::shared_ptr<sf::RenderWindow> window){
	window->draw(this->sprite);
	window->draw(this->playerCollisionBox);
}
