//Player.cpp
#include "Player.h"
#include"../GameObject.h"

Player::Player()
	: deltaTime(0.0f), speed(150.0f), playerSpeed(0.0f, 0.0f), gravity(0,GameMagicNumbers::gravity),
	counterGravity(0,GameMagicNumbers::gravityCounter) {  

	this->texture = gameObject.utility.GetPlayerTexture();
	aSP.frequencyX = texture.getSize().x / GameMagicNumbers::spriteSize;
	aSP.frequencyY = texture.getSize().y / GameMagicNumbers::spriteSize;

	for (unsigned int y = 0 ; y < aSP.frequencyY; y++) {
		for (unsigned int x = 0; x < aSP.frequencyX; x++) {
			textureId.push_back(x + aSP.frequencyX * y);
			playerAnimation.push_back(sf::IntRect(x * GameMagicNumbers::spriteSize, y * GameMagicNumbers::spriteSize,
				GameMagicNumbers::spriteSize, GameMagicNumbers::spriteSize));
		}
	}
	StructInit();
	//std::cout << "X size = " << aS.animationSize << std::endl;
	//for (int i = 0 ; i < textureId.size() ; i++ ){ std::cout << textureId[i] << std::endl; }
	this->playerPositionText.setFont(gameObject.utility.GetFont());
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(this->playerAnimation[GameMagicNumbers::zero]);
	
}
void Player::StructInit() {
	aS.animationSize = aSP.frequencyX;
	aSP.idle = 0 * aSP.frequencyX;
	aSP.run = 1 * aSP.frequencyX;
	aSP.jump = 2 * aSP.frequencyX;
	aSP.jumpFirsthalf = aSP.jump ;
	aSP.jumpSecondhalf = aSP.jump + aSP.frequencyX / 2;
	aSP.attack1 = 3 * aSP.frequencyX;
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
	GravityAffect();   // just reset player position to top if player falls down of path
	if (sprite.getPosition().y >= GameMagicNumbers::windowMaxHeight) { sprite.setPosition(sf::Vector2f(sprite.getPosition().x, 0)); }
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
			+(b.isGravityAffecting ? this->gravity : sf::Vector2f(GameMagicNumbers::zero, GameMagicNumbers::one))));
	this->playerCollisionBox.setPosition(sprite.getPosition());
	this->playerSpeed = sf::Vector2f(GameMagicNumbers::zero, GameMagicNumbers::zero);
}


void Player::InputHandle(){
	InputJump();
	InputShift();
	InputMovement();
}
void Player::AnimationHandle() {
	JumpAnimation();
	MovementAnimation();
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
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
	//	this->playerSpeed.y = -this->speed;                      //// needed for debugging

	//}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
	//	this->playerSpeed.y = this->speed;
	//}
}

void Player::InputJump() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !this->b.isJumping) {
		b.isJumping = true;
		b.isJumpBoost = true;
		sprite.setTextureRect(playerAnimation[aSP.jumpFirsthalf]); // just to set animation of jump fast
		gT.jumpBoostTimer = GameMagicNumbers::zero;
		c.counterJumpFirst = GameMagicNumbers::zero;
		c.counterJumpSecond = GameMagicNumbers::zero;
	}
	if (b.isJumpBoost) {
		gT.jumpBoostTimer += this->deltaTime;
		this->playerSpeed.y = (gT.jumpBoostTimer <= gT.jumpBoostRate) ? -counterGravity.y : GameMagicNumbers::zero;
		this->b.isJumpBoost = (gT.jumpBoostTimer <= gT.jumpBoostRate);
	}
}
void Player::InputShift() {
	if (!b.isDodging && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		b.isDodging = true;
		b.isDodgeBoost = true;
		gT.dodgeTimer = 0;
		gT.dodgeBoostTimer = GameMagicNumbers::zero;

	}
	if (b.isDodging) {
		gT.dodgeBoostTimer += this->deltaTime;
		gT.dodgeTimer += this->deltaTime;
		if (b.isMovingLeft != b.isMovingRight && gT.dodgeBoostTimer <= gT.dodgeBoostRate) {
			sprite.setPosition(sprite.getPosition() +
				sf::Vector2f((b.isMovingLeft ? -GameMagicNumbers::dodgepixel : GameMagicNumbers::dodgepixel), 0));
		}
		b.isDodgeBoost = (gT.dodgeBoostTimer < gT.dodgeBoostRate);
		b.isDodging = (gT.dodgeTimer < gT.dodgeRate);

	}
}




void Player::MovementAnimation() {
	if (!b.isJumping) {
		aT.animationTime += this->deltaTime;
		if (aT.animationTime >= aT.animationRate) {
			aT.animationTime -= aT.animationRate;
			if (b.isMovingLeft || b.isMovingRight || b.isGravityAffecting) {
				auto& counter = this->b.isMovingLeft ? c.counterLeft : c.counterRight;
				gameObject.utility.UpdateAnimation(this->sprite, this->playerAnimation, counter , aSP.run , aS.animationSize);
			}
			else {gameObject.utility.UpdateAnimation(this->sprite, this->playerAnimation, c.counterIdle, aSP.idle , aS.idleSize);}
		}
	}
	float desiredScale = b.isMovingLeft ? -GameMagicNumbers::playerScale : GameMagicNumbers::playerScale;
	sprite.setScale(desiredScale, GameMagicNumbers::playerScale);
}






void Player::JumpAnimation() {
	if (this->b.isJumping) {
		aT.jumpAnimationTime += this->deltaTime;
		if (aT.jumpAnimationTime >= aT.animationRate) {
			aT.jumpAnimationTime -= aT.animationRate;
			gameObject.utility.UpdateAnimation(sprite, playerAnimation,(b.isJumpBoost ? c.counterJumpFirst : c.counterJumpSecond),
				(b.isJumpBoost ? aSP.jumpFirsthalf : aSP.jumpSecondhalf), aS.jumpAnimationSize);
		}
	}
}



