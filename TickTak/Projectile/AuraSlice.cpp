#include "AuraSlice.h"
#include"../GameObject.h"

AuraSlice::AuraSlice(const unsigned int entityId, const sf::Vector2f startingPosition, const unsigned int maxDistanceTravel):
	entityId(entityId) , shootingPosition(startingPosition) , maxDistance(maxDistanceTravel) ,
	isCreated(false) , window(gameObject.runProgram.GetWindow()) , speed(GameMagicNumbers::projectileSpeed, GameMagicNumbers::projectileSpeed),
counter(0) , angle(0) {
	texture = gameObject.utility.GetBulletTexture();
	for (unsigned int x = 0; x < texture.getSize().x / GameMagicNumbers::sliceSize; x++) {
		slicePositionInFile.push_back(sf::IntRect(x, 0, GameMagicNumbers::sliceSize, GameMagicNumbers::sliceSize));
	}
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(slicePositionInFile[0]);
	Load();
}

void AuraSlice::Load(){
	CriticalLoad();
	CollisionBoxLoad();
	DirectionFinder();
	AngleFinderAndLoader();
}

void AuraSlice::Update(float& deltaTime) {
	this->sprite.move(sf::Vector2f(this->direction.x * this->speed.x * deltaTime , 
		this->direction.y * this->speed.y * deltaTime));
	this->collisionBox.setPosition(this->sprite.getPosition());


}

void AuraSlice::Draw(){
	this->window->draw(sprite);
	this->window->draw(collisionBox);
}


void AuraSlice::CriticalLoad() {
	// must me in this exact order
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(GameMagicNumbers::projectileScale, GameMagicNumbers::projectileScale);

	this->collisionBox.setSize(sf::Vector2f(GameMagicNumbers::sliceCollisionSize * GameMagicNumbers::projectileScale, GameMagicNumbers::sliceCollisionSize * GameMagicNumbers::projectileScale));
    this->collisionBox.setOrigin(this->collisionBox.getGlobalBounds().width/2 , this->collisionBox.getGlobalBounds().height/ 2);

	this->sprite.setPosition(shootingPosition);
	this->collisionBox.setPosition(this->sprite.getPosition());
}

void AuraSlice::CollisionBoxLoad(){
	this->collisionBox.setFillColor(sf::Color::Transparent);
	this->collisionBox.setOutlineThickness(GameMagicNumbers::collisionBoxThickness);
	this->collisionBox.setOutlineColor(sf::Color::Blue);
	this->collisionBox.setScale(GameMagicNumbers::collisionBoxThickness, GameMagicNumbers::collisionBoxThickness);
}


void AuraSlice::DirectionFinder(){
	this->position = this->window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	this->direction = this->position - shootingPosition;
	this->direction = gameObject.utility.NormalizedVectors(direction);
}

inline void AuraSlice::AngleFinderAndLoader(){
	angle = std::atan2(direction.y, direction.x) * GameMagicNumbers::oneEightyDegree / GameMagicNumbers::PI;
	sprite.setRotation(angle);
}
