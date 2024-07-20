//Player.cpp
#include "Player.h"
#include"../GameObject.h"

Player::Player()
	: deltaTime(0.0f), speed(150.0f), playerSpeed(0.0f, 0.0f), gravity(0,GameMagicNumbers::gravity),
	counterGravity(0,GameMagicNumbers::gravityCounter) {  
	if (!texture.loadFromFile("Assets/Adventure/newSpriteplayer.png")) { 
		std::cout << "failed to load player texture " << std::endl;
	}   

	for (unsigned int i = 0; i < GameMagicNumbers::idleFrame; i++) {
		this->idleAnimation.push_back(sf::IntRect(i * GameMagicNumbers::spriteSize,
			GameMagicNumbers::zero, GameMagicNumbers::spriteSize, GameMagicNumbers::spriteSize));
	}
	for (unsigned int i = 0; i < GameMagicNumbers::runFrame; i++) {
		this->runAnimation.push_back(sf::IntRect(i * GameMagicNumbers::spriteSize,
			GameMagicNumbers::spriteSize, GameMagicNumbers::spriteSize, GameMagicNumbers::spriteSize));
	}
	for (unsigned int i = 0; i < GameMagicNumbers::runFrame; i++) {
		this->jumpAnimation.push_back(sf::IntRect(i * GameMagicNumbers::spriteSize,
			2 * GameMagicNumbers::spriteSize, GameMagicNumbers::spriteSize, GameMagicNumbers::spriteSize));

		playerPositionText.setFont(gameObject.utility.GetFont());
	}
	this->playerPositionText.setFont(gameObject.utility.GetFont());
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(this->idleAnimation[GameMagicNumbers::zero]);
}



void Player::Load() {
	ImportantLoad();
	CollisionLoad();
	PositionTxtLoader();
}


void Player::Update( const float& deltaTime){
	this->deltaTime = deltaTime;
	AnimationHandle();
	InputHandle();
	ReInitializer();
	GravityAffect();   
	PositionTxtUpdate();
}

void Player::Draw(std::shared_ptr<sf::RenderWindow> window) {
	window->draw(this->sprite);
	window->draw(this->playerCollisionBox);
	window->draw(this->playerPositionText);
}
 

//---------------------------------------load part-------------------------------------


void Player::ImportantLoad(){// important need to be in this same order
	this->playerCollisionBox.setSize(sf::Vector2f(GameMagicNumbers::collisionBoxSizeX, GameMagicNumbers::collisionBoxSizeY));
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->playerCollisionBox.setOrigin(this->playerCollisionBox.getGlobalBounds().width / 2, this->playerCollisionBox.getGlobalBounds().height / 2);
	this->sprite.setScale(sf::Vector2f(GameMagicNumbers::playerScale, GameMagicNumbers::playerScale));
	this->sprite.setPosition(sf::Vector2f(200.f, 200.f)); // Random starting point, todo: change it to GameMagicNumbers
}

void Player::PositionTxtLoader(){
	this->playerPositionText.setCharacterSize(10);
	this->playerPositionText.setPosition(GameMagicNumbers::zero, GameMagicNumbers::zero);
}

void Player::PositionTxtUpdate(){
	this->playerPositionText.setPosition(this->sprite.getPosition().x - GameMagicNumbers::windowMaxWidth / 2, GameMagicNumbers::zero);
	this->playerPositionText.setString("position " + std::to_string(int(sprite.getPosition().x))
		+ " " + std::to_string(int(sprite.getPosition().y)));
}

void Player::CollisionLoad(){
	this->playerCollisionBox.setPosition(sprite.getPosition());
	this->playerCollisionBox.setOutlineThickness(GameMagicNumbers::collisionBoxThickness);
	this->playerCollisionBox.setOutlineColor(sf::Color::Red);
	this->playerCollisionBox.setFillColor(sf::Color::Transparent);
}



//--------------------------------------- update part-------------------------------------
void Player::GravityAffect() {
	this->sprite.setPosition(sprite.getPosition() + this->deltaTime*(this->playerSpeed 
			+(b.isGravityAffecting ? this->gravity : sf::Vector2f(GameMagicNumbers::one, GameMagicNumbers::one))));
	this->playerCollisionBox.setPosition(sprite.getPosition());
	this->playerSpeed = sf::Vector2f(GameMagicNumbers::zero, GameMagicNumbers::zero);
}
void Player::ReInitializer(){
	// just to make player start from top if player fall down to abbys
	if (sprite.getPosition().y >= GameMagicNumbers::windowMaxHeight) {
		sprite.setPosition(sf::Vector2f(sprite.getPosition().x , 0));
	}
}


void Player::InputHandle(){
	InputMovement();
	InputJump();
}
void Player::AnimationHandle() {
	AnimationMovement();
	JumpAnimation();
}

void Player::InputMovement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->playerSpeed.x = -this->speed;
		b.isMovingRight = false;
		b.isMovingLeft = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->playerSpeed.x = this->speed;
		b.isMovingRight = true;
		b.isMovingLeft = false;
	}
	else {
		b.isMovingRight = false;
		b.isMovingLeft = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->playerSpeed.y = -this->speed;   // needed for debugging

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->playerSpeed.y = this->speed;
	}
}
void Player::AnimationMovement() {
	if (!b.isJumping) {
		a.animationTime += this->deltaTime;
		if (a.animationTime >= a.animationSpeed) {
			a.animationTime -= a.animationSpeed;
			if (this->b.isMovingLeft || this->b.isMovingRight || this->b.isGravityAffecting) {
				auto& counter = this->b.isMovingLeft ? c.counterLeft : c.counterRight;
				gameObject.utility.UpdateAnimation(this->sprite, counter, this->runAnimation);
			}
			else {
				gameObject.utility.UpdateAnimation(this->sprite, c.counterIdle, this->idleAnimation);
			}
		}
	}
	float desiredScale = this->b.isMovingLeft ? -GameMagicNumbers::playerScale : GameMagicNumbers::playerScale;
	sprite.setScale(desiredScale, GameMagicNumbers::playerScale);
}



void Player::InputJump() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !this->b.isJumping) {
		this->b.isJumping = true;
		this->b.isJumpBoost = true;
		a.jumpTime = GameMagicNumbers::zero;
		c.jumpAnimationcounter = GameMagicNumbers::zero;
	}
	if (b.isJumpBoost) {
		a.jumpTime += this->deltaTime;
		this->playerSpeed.y = (a.jumpTime <= a.jumpRate) ? -counterGravity.y : GameMagicNumbers::zero;
		this->b.isJumpBoost = (a.jumpTime <= a.jumpRate);
	}
}


void Player::JumpAnimation() {
	if (this->b.isJumping) {
		a.jumpAnimationTime += this->deltaTime;
		if (a.jumpAnimationTime >= a.jumpAnimationRate) {
			a.jumpAnimationTime -= a.jumpAnimationRate;
			c.jumpAnimationcounter = (c.jumpAnimationcounter + 1) % (jumpAnimation.size() / 2);
			sprite.setTextureRect(jumpAnimation[this->b.isJumpBoost ? c.jumpAnimationcounter : 3 + c.jumpAnimationcounter]);
		}
	}
}


