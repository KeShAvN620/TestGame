#include "Player.h"

Player::Player():speed(60.0f), playerSpeed(0.0f, 0.0f),scale(2.0f), counterLeft(0),
counterRight(0), counterIdle(0), isMovingRight(false), isMovingLeft(false), 
animationTime(0), animationSpeed(8.0f * 0.0166667f) {
	if (!texture.loadFromFile("Assets/Adventure/AD_IDLE_RUN_V1.png")) {
		std::cout << "failed to load player texture " << std::endl;
	}
	for (unsigned int i = 0; i < idleFrame; i++) {
		this->idleAnimation.push_back(sf::IntRect( i * spriteSize , zero , spriteSize , spriteSize));
	}
	for (unsigned int i = 0; i < runFrame; i++) {
		this->rightAnimation.push_back(sf::IntRect(i * spriteSize, spriteSize, spriteSize, spriteSize));
	}
	for (unsigned int i = 0; i < runFrame; i++) {
		this->leftAnimation.push_back(sf::IntRect(i * spriteSize,2 * spriteSize, spriteSize, spriteSize));
	}
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(this->idleAnimation[0]);
}

void Player::Load()
{
	this->sprite.setPosition(sf::Vector2f(300.f, 300.f));
	this->sprite.setScale(sf::Vector2f(scale, scale));
}

void Player::Update(float& deltaTime)
{
	InputHandle(deltaTime);
	AnimationUpdate(deltaTime);
	this->sprite.move(playerSpeed);
	this->playerSpeed = sf::Vector2f(0.0f, 0.0f);
}


void Player::InputHandle(float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->playerSpeed.x =  -this->speed * deltaTime;
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
}

void Player::AnimationUpdate(float& deltaTime){
	this->animationTime += deltaTime;
	if (this->animationTime >= this->animationSpeed) {
		this->animationTime -= this->animationSpeed;
		if (this->isMovingRight) {
			counterRight = (this->counterRight + 1) % this->rightAnimation.size();
			this->sprite.setTextureRect(this->rightAnimation[this->counterRight]);
		}
		else if (this->isMovingLeft) {
			this->counterLeft = (this->counterLeft + 1) % this->leftAnimation.size();
			this->sprite.setTextureRect(this->leftAnimation[this->counterLeft]);
		}
		else {
			this->counterIdle = (this->counterIdle + 1) % idleAnimation.size();
			this->sprite.setTextureRect(this->idleAnimation[this->counterIdle]);
		}
	}
}

void Player::Draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(this->sprite);
}
