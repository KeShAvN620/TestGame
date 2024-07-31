#include "AuraSlice.h"
#include"../GameObject.h"


AuraSlice::AuraSlice(const unsigned int entityId, const sf::Vector2f startingPosition, const unsigned int maxDistanceTravel):
	entityId(entityId) , shootingPosition(startingPosition) , maxDistance(float(maxDistanceTravel),float(maxDistanceTravel)),
	isCreated(false) , window(gameObject.runProgram.GetWindow()) , speed(GMnumber::projectileSpeed, GMnumber::projectileSpeed),
counter(0) , angle(0) , isDestroyedWhenHitWithPath(false) , isDestroyedWhenOutOfReach(false){
	texture = gameObject.utility.GetBulletTexture();
	for (unsigned int x = 0; x < texture.getSize().x / GMnumber::sliceSize; x++) {
		slicePositionInFile.push_back(sf::IntRect(x, 0,int(GMnumber::sliceSize), int(GMnumber::sliceSize)));
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
	Movement(deltaTime);
	DestoryWhenOutOfRange();
}

void AuraSlice::Draw(){
	this->window->draw(sprite);
	this->window->draw(collisionBox);
}


void AuraSlice::CriticalLoad() {
	// must me in this exact order
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(GMnumber::projectileScale, GMnumber::projectileScale);

	this->collisionBox.setSize(sf::Vector2f(GMnumber::sliceCollisionSize * GMnumber::projectileScale, GMnumber::sliceCollisionSize * GMnumber::projectileScale));
    this->collisionBox.setOrigin(this->collisionBox.getGlobalBounds().width/2 , this->collisionBox.getGlobalBounds().height/ 2);

	this->sprite.setPosition(shootingPosition);
	this->collisionBox.setPosition(this->sprite.getPosition());
}

void AuraSlice::CollisionBoxLoad(){
	this->collisionBox.setFillColor(sf::Color::Transparent);
	this->collisionBox.setOutlineThickness(GMnumber::collisionBoxThickness);
	this->collisionBox.setOutlineColor(sf::Color::Transparent);
	this->collisionBox.setScale(GMnumber::collisionBoxThickness, GMnumber::collisionBoxThickness);
}


void AuraSlice::DirectionFinder(){
	this->position = this->window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	this->direction = this->position - shootingPosition;
	this->direction = gameObject.utility.NormalizedVectors(direction);
}

inline void AuraSlice::AngleFinderAndLoader(){
	angle = std::atan2(direction.y, direction.x) * GMnumber::oneEightyDegree / GMnumber::PI;
	sprite.setRotation(angle);
}

void AuraSlice::Movement(const float& deltaTime){
	this->sprite.move(sf::Vector2f(this->direction.x * this->speed.x * deltaTime,
		this->direction.y * this->speed.y * deltaTime));
	this->collisionBox.setPosition(this->sprite.getPosition());
}

void AuraSlice::DestoryWhenOutOfRange() {
	if ((this->maxDistance.x * this->maxDistance.x + this->maxDistance.y * this->maxDistance.y)
		< ((this->collisionBox.getPosition().x - this->shootingPosition.x) * (this->collisionBox.getPosition().x - this->shootingPosition.x)
			+ (this->collisionBox.getPosition().y - this->shootingPosition.y) * (this->collisionBox.getPosition().y - this->shootingPosition.y)))
	{this->isDestroyedWhenOutOfReach = true;}
	else{ this->isDestroyedWhenOutOfReach = false; }
}

void  AuraSlice::DestoryWhenHitThePath(std::vector<std::shared_ptr<BackGround>>&other){
	for (int i = 0; i < other.size(); i++) {
		if (gameObject.utility.MinimumDistanceCollisionUpdate(sprite.getPosition(), other[i]->GetPathSprite().getPosition())) 
		{continue;}
		sf::FloatRect tBound = other[i]->GetPathSprite().getGlobalBounds();
		if (collisionBox.getGlobalBounds().intersects(tBound)) {
			this->isDestroyedWhenHitWithPath = true;
			std::cout << isDestroyedWhenHitWithPath << std::endl;
			break;
		}
		this->isDestroyedWhenHitWithPath = false;
	}
}
