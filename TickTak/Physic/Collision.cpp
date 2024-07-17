//collision.cpp
#include"Collision.h"
#include"../GameObject.h"
#include"../Map/BackGround.h"

Collision::Collision() : bounds1(), bounds2(), overlapLeft(0.0f), overlapRight(0.0f), overlapTop(0.0f), overlapBottom(0.0f),
fromLeft(false), fromRight(false), fromTop(false), fromBottom(false),left(false),right(false),top(false),bottom(false)
{}

void Collision::CollisionReseter(){
    fromLeft = false; fromRight = false; fromTop = false; fromBottom = false;
}

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

bool Collision::PathPlayerCollidionDetection(const sf::RectangleShape& sprite1, const sf::RectangleShape& sprite2, sf::Sprite& sprite3, bool& boxLeft, bool& boxRight, bool& boxTop, bool& boxBottom) {
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
        if (fromTop && !boxTop) {
            sprite3.setPosition(sprite3.getPosition().x, bounds2.top + GameMagicNumbers::errorManagement - bounds1.height / 2);
            gameObject.player->IsJumping() = false;
        }
        else if (fromBottom && !boxBottom) {
            sprite3.setPosition(sprite3.getPosition().x, bounds2.top + GameMagicNumbers::errorManagement + bounds2.height + bounds1.height / 2);
            gameObject.player->IsGravityBoost() = false;
        }
        else if (fromLeft && !boxLeft) {
            sprite3.setPosition(bounds2.left - bounds1.width / 2, sprite3.getPosition().y);
        }
        else if (fromRight && !boxRight) {
            sprite3.setPosition(bounds2.left + bounds2.width + bounds1.width / 2 + GameMagicNumbers::errorManagement, sprite3.getPosition().y);
        }
        return true;
    }
    return false;
}

void Collision::PreliminarySearch(std::vector<std::shared_ptr<BackGround>>& level1)
{
    const float tolerance = 1.0f; // Small tolerance to handle floating-point inaccuracies

    for (unsigned int i = 0; i < level1.size(); ++i) {
        sf::FloatRect bounds1 = level1[i]->GetPathSprite().getGlobalBounds();
        for (unsigned int j = 0; j < level1.size(); ++j) {
            if (i == j) continue;

            sf::FloatRect bounds2 = level1[j]->GetPathSprite().getGlobalBounds();

            overlapLeft = bounds1.left + bounds1.width - bounds2.left;
            overlapRight = bounds2.left + bounds2.width - bounds1.left;
            overlapTop = bounds1.top + bounds1.height - bounds2.top;
            overlapBottom = bounds2.top + bounds2.height - bounds1.top;

            left    =  (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom);
            right   = (overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom);
            top     = (overlapTop < overlapBottom && overlapTop < overlapLeft && overlapTop < overlapRight);
            bottom  = (overlapBottom < overlapTop && overlapBottom < overlapLeft && overlapBottom < overlapRight);

            if (left) {
                level1[i]->skipCollisionCheckRight = true;
                level1[j]->skipCollisionCheckLeft = true;
            }
            if (right) {
                level1[i]->skipCollisionCheckLeft = true;
                level1[j]->skipCollisionCheckRight = true;
            }
            if (top ) {
                level1[i]->skipCollisionCheckBottom = true;
                level1[j]->skipCollisionCheckTop = true;
            }
            if (bottom) {
                level1[i]->skipCollisionCheckTop = true;
                level1[j]->skipCollisionCheckBottom = true;
            }
        }
    }
}




