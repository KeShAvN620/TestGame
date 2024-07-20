//collision.cpp
#include"Collision.h"
#include"../GameObject.h"
#include"../Map/BackGround.h"

Collision::Collision() : bounds1(), bounds2(), position1(0,0), position2(0,0), tolerance(4.0f), overlapLeft(0.0f), overlapRight(0.0f), overlapTop(0.0f), overlapBottom(0.0f),
fromLeft(false), fromRight(false), fromTop(false), fromBottom(false),isGravityAffecting(false){}

void Collision::CollisionReseter(){
    overlapLeft = 0; overlapRight = 0; overlapTop = 0; overlapBottom = 0;
    fromLeft = false; fromRight = false; fromTop = false; fromBottom = false;
    position1.x = 0;position1.y = 0;
    position2.x = 0;position2.y = 0;
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

void Collision::PathPlayerCollidionDetection(const sf::RectangleShape& sprite1, const sf::RectangleShape& sprite2, sf::Sprite& sprite3, bool& boxLeft, bool& boxRight, bool& boxTop, bool& boxBottom) {
    bounds1 = sprite1.getGlobalBounds();
    bounds2 = sprite2.getGlobalBounds();
    if (bounds1.intersects(bounds2)) {
        BoundFinder();
        BoolFinder();
        if (fromTop && !boxTop) {
            sprite3.setPosition(sprite3.getPosition().x, bounds2.top +GameMagicNumbers::oneAndHalf - bounds1.height / 2);
            gameObject.player->IsJumping() = false;
        }
        else if (fromBottom && !boxBottom ) {
            sprite3.setPosition(sprite3.getPosition().x, bounds2.top + GameMagicNumbers::oneAndHalf  + bounds2.height + bounds1.height / 2);
            gameObject.player->IsGravityBoost() = false;
        }
        else if (fromLeft && !boxLeft) {
            sprite3.setPosition(bounds2.left - bounds1.width / 2, sprite3.getPosition().y);
        }
        else if (fromRight&& !boxRight) {
            sprite3.setPosition(bounds2.left + bounds2.width + bounds1.width / 2 + GameMagicNumbers::oneAndHalf, sprite3.getPosition().y);
        }
    }
    CollisionReseter();
}


void Collision::PreliminarySearch(std::vector<std::shared_ptr<BackGround>>& level1) {
    for (unsigned int i = 0; i < level1.size(); i++) {
        bounds1 = level1[i]->GetPathSprite().getGlobalBounds(); ExpandBound(bounds1);
        position1 = level1[i]->GetPathSprite().getPosition();  //std::cout << "Bounds3 (Object " << i << "): " << bounds1.left << ", " << bounds1.top << ", "<< bounds1.width << ", "<< bounds1.height << std::endl;
        for (unsigned int j = 0; j < level1.size(); j++) {
            if (i == j) continue;
            bounds2 = level1[j]->GetPathSprite().getGlobalBounds(); ExpandBound(bounds2);//std::cout << "Bounds3 (Object " << i << "): " << bounds2.left << ", " << bounds2.top << ", "<< bounds2.width << ", "<< bounds2.height << std::endl;
            position2 = level1[j]->GetPathSprite().getPosition();
            if (bounds1.intersects(bounds2) && (abs(position1.x - position2.x) <= tolerance || abs(position1.y - position2.y) <= tolerance) ) {
                //std::cout << "Intersection detected between object " << i << " and object " << j << std::endl;
                //std::cout << position1.x << " " << position1.y << " " << position2.x << " " << position2.y << std::endl;
                BoundFinder();
                BoolFinder();
                if (fromLeft) {                    //std::cout << "Lp" << std::endl;
                    level1[i]->skipCollisionCheckRight = true;
                    level1[j]->skipCollisionCheckLeft = true;
                }
                if (fromRight) {                    //std::cout << "Rp" << std::endl
                    level1[i]->skipCollisionCheckLeft = true;
                    level1[j]->skipCollisionCheckRight = true;
                }
                if (fromTop) {                        //std::cout << "Tp" << std::endl;
                    level1[i]->skipCollisionCheckBottom = true;
                    level1[j]->skipCollisionCheckTop = true;
                }
                if (fromBottom) {                    //std::cout << "Bp" << std::endl;
                    level1[i]->skipCollisionCheckTop = true;
                    level1[j]->skipCollisionCheckBottom = true;
                }
            }
        }
        CollisionReseter();
    }
}





bool Collision::PlayerOnGround(sf::Sprite& sprite, std::vector<std::shared_ptr<BackGround>>& level) {
    this->isGravityAffecting = false;
    position1 = sprite.getPosition();
    bounds1 = sprite.getGlobalBounds();
    for (unsigned int i = 0; i < level.size(); i++) {
        position2 = level[i]->GetPathSprite().getPosition();
        bounds2 = level[i]->GetPathSprite().getGlobalBounds();
        if (bounds1.intersects(bounds2) && !gameObject.utility.MinimumDistanceCollisionUpdate(position1, position2)) {
            BoundFinder();
            if (overlapTop < overlapBottom && overlapTop < overlapLeft && overlapTop < overlapRight) {
                isGravityAffecting = true;
                break;
            }
         
        }
    }
    CollisionReseter();
    return isGravityAffecting;
}

void Collision::BoundFinder(){
    overlapLeft = bounds1.left + bounds1.width - bounds2.left;
    overlapRight = bounds2.left + bounds2.width - bounds1.left;
    overlapTop = bounds1.top + bounds1.height - bounds2.top;
    overlapBottom = bounds2.top + bounds2.height - bounds1.top;
}

void Collision::BoolFinder(){
    fromLeft = (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom);
    fromRight = (overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom);
    fromTop = (overlapTop < overlapBottom && overlapTop < overlapLeft && overlapTop < overlapRight);
    fromBottom = (overlapBottom < overlapTop && overlapBottom < overlapLeft && overlapBottom < overlapRight);
}

void Collision::ExpandBound(sf::FloatRect& bound){
    bound.left -= 2;
    bound.top -= 2;
    bound.width += 4;
    bound.height += 4;
}
