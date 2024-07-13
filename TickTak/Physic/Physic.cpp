#include "Physic.h"

Physic::Physic():gravity(0,GameMagicNumbers::gravity), velocityOfGravity(0,0) , overlapLeft(0), overlapRight(0), overlapTop(0), overlapBottom(0) 
, fromTop(false){}

sf::Vector2f Physic::AffectGravity(const sf::RectangleShape collisionBox, const sf::RectangleShape& path, const float& deltaTime) {
	velocityOfGravity = gravity * deltaTime;
    bounds1 = collisionBox.getGlobalBounds();
    bounds2 = path.getGlobalBounds();
    if (bounds1.intersects(bounds2)) {
        overlapLeft = bounds1.left + bounds1.width - bounds2.left;
        overlapRight = bounds2.left + bounds2.width - bounds1.left;
        overlapTop = bounds1.top + bounds1.height - bounds2.top;
        overlapBottom = bounds2.top + bounds2.height - bounds1.top;

        fromTop = (overlapTop < overlapBottom && overlapTop < overlapLeft && overlapTop < overlapRight);
        if (fromTop) { 
            velocityOfGravity.y = GameMagicNumbers::errorManagement;
            return velocityOfGravity; 
        }
    }
    return velocityOfGravity;
}