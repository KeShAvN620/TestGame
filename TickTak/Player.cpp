#include "Player.h"

Player::Player():speed(60.0f), playerSpeed(0.0f, 0.0f),counterLeft(0), 
counterRight(0), counterIdle(0), isMovingRight(false), isMovingLeft(false), 
animationTime(0), animationSpeed(5.0f * 0.0166667f) {
	if (!texture.loadFromFile("Assets/Adventure/AD_IDLE_RUN.png")) {
		std::cout << "failed to load player texture " << std::endl;
	}
	for (unsigned int i = 0; i < idleFrame; i++) {
		this->idleAnimation.push_back(sf::IntRect( i * spriteSize , 0 , spriteSize , spriteSize));
	}
	for (unsigned int i = 0; i < idleFrame; i++) {
		this->runAnimation.push_back(sf::IntRect(i * spriteSize, spriteSize, spriteSize, spriteSize));
	}
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(this->idleAnimation[0]);
}

void Player::Load()
{
	this->sprite.setPosition(sf::Vector2f(300.f, 300.f));
	this->sprite.setScale(sf::Vector2f(float(scale), float(scale)));
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
		this->playerSpeed.x = -speed * deltaTime;
		this->isMovingRight = false;
		this->isMovingLeft = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->playerSpeed.x = speed * deltaTime;
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
		if (isMovingRight) {
			counterRight = (counterRight + 1) % runAnimation.size();
			this->sprite.setTextureRect(this->runAnimation[counterRight]);
			if (this->sprite.getScale().x < 0) {
				this->sprite.setScale(sf::Vector2f(float(scale), float(scale)));
			}
		}
		else if (isMovingLeft) {
			counterLeft = (counterLeft + 1) % runAnimation.size();
			this->sprite.setTextureRect(this->runAnimation[counterLeft]);
			if (this->sprite.getScale().x > 0) {
				this->sprite.setScale(sf::Vector2f(-float(scale), float(scale)));
			}
		}
		else {
			counterIdle = (counterIdle + 1) % idleAnimation.size();
			this->sprite.setTextureRect(this->idleAnimation[counterIdle]);
			if (this->sprite.getScale().x < 0) {
				this->sprite.setScale(sf::Vector2f(float(scale), float(scale)));
			}
		}
	}
}

void Player::Draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(sprite);
}
