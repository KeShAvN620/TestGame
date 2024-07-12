#include "Physic.h"

Physic::Physic():gravity(0,GameMagicNumbers::gravity), velocityOfGravity(0,0){}

sf::Vector2f Physic::AffectGravity(const sf::RectangleShape collisionBox, const sf::RectangleShape& path, const float& deltaTime) {
	velocityOfGravity = gravity * deltaTime;
	if (collisionBox.getGlobalBounds().intersects(path.getGlobalBounds())) {
		velocityOfGravity.y -= GameMagicNumbers::errorManagement;
		return velocityOfGravity;
	}
	return velocityOfGravity;
}