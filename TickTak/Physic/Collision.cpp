#include"Collision.h"

Collision::Collision() : bounds1(), bounds2(), overlapLeft(0.0f), overlapRight(0.0f), overlapTop(0.0f), overlapBottom(0.0f),
fromLeft(false), fromRight(false), fromTop(false), fromBottom(false)
{}

void Collision::UpdateAnimation(sf::Sprite& animationSprite, unsigned int& animationCounter, std::vector<sf::IntRect>& animationFrame) {
    if (!animationFrame.empty()) {
        animationCounter = (animationCounter + 1) % animationFrame.size();
        animationSprite.setTextureRect(animationFrame[animationCounter]);
    }
    else {
        std::cout << "unable to load frames " << std::endl;
        return;
    }
}

bool Collision::PathPlayerCollidionDetection(const sf::RectangleShape& sprite1, const sf::RectangleShape& sprite2, sf::Sprite& sprite3) {
    // Get bounding boxes of the sprites
    bounds1 = sprite1.getGlobalBounds();
    bounds2 = sprite2.getGlobalBounds();

    if (bounds1.intersects(bounds2)) {
        overlapLeft = bounds1.left + bounds1.width - bounds2.left;
        overlapRight = bounds2.left + bounds2.width - bounds1.left;
        overlapTop = bounds1.top + bounds1.height - bounds2.top;
        overlapBottom = bounds2.top + bounds2.height - bounds1.top;

        // Determine the side of the collision based on the smallest overlap
        fromLeft = (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom);
        fromRight = (overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom);
        fromTop = (overlapTop < overlapBottom && overlapTop < overlapLeft && overlapTop < overlapRight);
        fromBottom = (overlapBottom < overlapTop && overlapBottom < overlapLeft && overlapBottom < overlapRight);

        // Resolve collision based on the side
        if (fromLeft) {
            sprite3.setPosition(bounds2.left - bounds1.width / 2 - GameMagicNumbers::errorManagement , sprite3.getPosition().y);
        }
        else if (fromRight) {
            sprite3.setPosition(bounds2.left + bounds2.width + bounds1.width / 2 + GameMagicNumbers::errorManagement, sprite3.getPosition().y);
        }
        else if (fromTop) {
            sprite3.setPosition(sprite3.getPosition().x, bounds2.top + GameMagicNumbers::errorManagement - bounds1.height / 2);
        }
        else if (fromBottom) {
            sprite3.setPosition(sprite3.getPosition().x, bounds2.top + GameMagicNumbers::errorManagement + bounds2.height + bounds1.height / 2 );
        }

        return true;
    }
    return false;
}


