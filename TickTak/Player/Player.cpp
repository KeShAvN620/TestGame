//Player.cpp
#include "Player.h"
#include"../GameObject.h"

Player::Player():
	playerId(GameMagicNumbers::playerId) ,deltaTime(0.0f), speed(GameMagicNumbers::playerSpeed), playerSpeed(0.0f, 0.0f), gravity(0,GameMagicNumbers::gravity),
	counterGravity(0,GameMagicNumbers::gravityCounter) , window(gameObject.runProgram.GetWindow()) , playerToMouseDistance(0), maxShootingDistance(80){

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


	this->playerPositionText.setFont(gameObject.utility.GetFont());
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(this->playerAnimation[GameMagicNumbers::zero]);
	
}
void Player::StructInit() {
	aS.animationSize = aSP.frequencyX;
	aSP.idle = 0 * aSP.frequencyX;
	aSP.slide = aSP.idle + (aSP.frequencyX*2)/3;
	aSP.run = 1 * aSP.frequencyX;
	aSP.jump = 2 * aSP.frequencyX;
	aSP.jumpFirsthalf = aSP.jump ;
	aSP.jumpSecondhalf = aSP.jump + aSP.frequencyX / 3;
	aSP.attack1 = 3 * aSP.frequencyX;
}



void Player::Load() {
	ImportantLoad();
	CollisionLoad();
	PositionTxtLoader();
}


void Player::Update( const float& deltaTime){
	ProjectileLoad();
	this->deltaTime = deltaTime;
	AnimationHandle();
	InputHandle();
	GravityAffect();   
	// just reset player position to top if player falls down of path
	if (sprite.getPosition().y >= GameMagicNumbers::windowMaxHeight)
	{ sprite.setPosition(sf::Vector2f(sprite.getPosition().x, 0)); }
	PositionTxtUpdate(); 
	// for projectile
	ProjectielUpdate();

}

void Player::Draw(std::shared_ptr<sf::RenderWindow>& window) {
	window->draw(this->sprite);
	window->draw(this->playerCollisionBox);
	window->draw(this->playerPositionText);
	ProjectileDraw();
}



//---------------------------------------load part-------------------------------------


void Player::ImportantLoad(){// important need to be in this same order
	//player
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->sprite.setScale(sf::Vector2f(GameMagicNumbers::playerScale, GameMagicNumbers::playerScale));
	//collisionbox
	this->playerCollisionBox.setSize(sf::Vector2f(GameMagicNumbers::collisionBoxSizeX, GameMagicNumbers::collisionBoxSizeY));
	this->playerCollisionBox.setOrigin(this->playerCollisionBox.getGlobalBounds().width / 2, this->playerCollisionBox.getGlobalBounds().height / 2);

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
	ShiftAnimation();
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
	if (!b.isDodging &&( sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) && b.canDodge) {
		b.isDodging = true;
		b.isDodgeBoost = true;
		b.canDodge = false;
		gT.dodgeTimer = GameMagicNumbers::zero;
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
	SetScaleForPlayer();
	if (b.isJumping) {return;}
		aT.animationTime += this->deltaTime;
		if (aT.animationTime >= aT.animationRate) {
			aT.animationTime -= aT.animationRate;
			auto& counter = (b.isMovingLeft ? c.counterLeft : c.counterRight);
			auto& size = (b.isMovingLeft || b.isMovingRight || b.isGravityAffecting) && !b.isDodgeBoost ? aSP.run : aSP.idle;
			auto& animationSize = (b.isMovingLeft || b.isMovingRight || b.isGravityAffecting) && !b.isDodgeBoost ? aS.animationSize : aS.idleSize;
			gameObject.utility.UpdateAnimation(sprite, playerAnimation, counter, size, animationSize);
		}
}

void Player::SetScaleForPlayer() {
	if (b.isMovingLeft != b.isMovingRight) {
		sprite.setScale((b.isMovingLeft ? -GameMagicNumbers::playerScale : GameMagicNumbers::playerScale), GameMagicNumbers::playerScale);
	}
	else if (!b.isJumping) {
		this->playerToMouseDistance = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)).x - this->sprite.getPosition().x;
		sprite.setScale((this->playerToMouseDistance >= 0 ? GameMagicNumbers::playerScale : -GameMagicNumbers::playerScale), GameMagicNumbers::playerScale);
	}
}

void Player::ShiftAnimation(){
	if (b.isDodgeBoost) {
		gameObject.utility.UpdateAnimation(sprite, playerAnimation, c.counterSlide, aSP.slide, aS.jumpAndSlide);
	}
}






void Player::JumpAnimation() {
	if (this->b.isJumping) {
		aT.jumpAnimationTime += this->deltaTime;
		if (aT.jumpAnimationTime >= aT.animationRate) {
			aT.jumpAnimationTime -= aT.animationRate;
			gameObject.utility.UpdateAnimation(sprite, playerAnimation,(b.isJumpBoost ? c.counterJumpFirst : c.counterJumpSecond),
				(b.isJumpBoost ? aSP.jumpFirsthalf : aSP.jumpSecondhalf), aS.jumpAndSlide);
		}
	}
}





//------------------------------- for projectile ---------------------


void Player::ProjectileLoad(){
	if (gT.fireRate >= gT.fireTime) { b.isFiring = false; }
	if (b.isFiring) {return; }
	gT.fireTime += this->deltaTime;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && gT.fireRate <= gT.fireTime) {
		b.isFiring = true;
		gT.fireTime = 0; 
		sf::Vector2f shootingPosition;
		this->playerToMouseDistance = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)).x - this->sprite.getPosition().x;

		if (b.isMovingLeft && this->playerToMouseDistance < 0) {
        shootingPosition.x = this->sprite.getPosition().x - this->sprite.getGlobalBounds().width / 2 - GameMagicNumbers::one;
		shootingPosition.y = this->sprite.getPosition().y;
		}
		else if (b.isMovingRight && this->playerToMouseDistance > 0) {
			shootingPosition.x = this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2 + GameMagicNumbers::one;
			shootingPosition.y = this->sprite.getPosition().y;
		}
		else if (!b.isMovingLeft && !b.isMovingRight){
			shootingPosition.x = this->sprite.getPosition().x +
				(playerToMouseDistance >= 0 ? (this->sprite.getGlobalBounds().width / + GameMagicNumbers::one) :
					-(this->sprite.getGlobalBounds().width / 2 + GameMagicNumbers::one));
			shootingPosition.y = this->sprite.getPosition().y;
		}
		else { return; }
		projectile.push_back(std::make_unique<AuraSlice>(this->playerId, shootingPosition, this->maxShootingDistance));
	}
}

void Player::ProjectielUpdate(){
	for (unsigned int i = 0; i < projectile.size(); i++) {
		projectile[i]->Update(deltaTime);
	}
}

void Player::ProjectileDraw() {
	for (unsigned int i = 0; i < this->projectile.size(); i++) {
		projectile[i]->Draw();
	}
}
