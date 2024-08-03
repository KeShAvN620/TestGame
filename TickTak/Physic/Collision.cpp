//collision.cpp
#include"Collision.h"
#include"../GameObject.h"
#include"../Map/BackGround.h"

Collision::Collision() : bounds1(), bounds2(), position1(0,0), position2(0,0), tolerance(6.0f), overlapLeft(0.0f), overlapRight(0.0f), overlapTop(0.0f), overlapBottom(0.0f),
fromLeft(false), fromRight(false), fromTop(false), fromBottom(false),isGravityAffecting(false){}

void Collision::CollisionReseter(){
    overlapLeft = 0; overlapRight = 0; overlapTop = 0; overlapBottom = 0;
    fromLeft = false; fromRight = false; fromTop = false; fromBottom = false;
    position1.x = 0;position1.y = 0;
    position2.x = 0;position2.y = 0;
}

void Collision::UpdateAnimation(sf::Sprite& animationSprite, 
    unsigned int& animationCounter, std::vector<sf::IntRect>& animationFrame) {
    if (!animationFrame.empty()) {
        animationCounter = (animationCounter + 1) % animationFrame.size();
        animationSprite.setTextureRect(animationFrame[animationCounter]);
    }
    else {
        std::cout << "unable to load frames " << std::endl;
        return;
    }
}

void Collision::PathPlayerCollidionDetection(const sf::RectangleShape& sprite1,
    const sf::RectangleShape& sprite2, sf::Sprite& sprite3, bool& boxLeft,
    bool& boxRight, bool& boxTop, bool& boxBottom) {
    bounds1 = sprite1.getGlobalBounds();
    bounds2 = sprite2.getGlobalBounds();
    if (bounds1.intersects(bounds2)) {
        BoundFinder();
        BoolFinder();
        if (fromTop && !boxTop) {
            sprite3.setPosition(sprite3.getPosition().x, bounds2.top - bounds1.height / 2);
            gameObject.player->IsJumping() = false;
        }
        else if (fromBottom && !boxBottom ) {
            sprite3.setPosition(sprite3.getPosition().x, bounds2.top  + bounds2.height + bounds1.height / 2);
            gameObject.player->IsGravityBoost() = false;
        }
        else if (fromLeft && !boxLeft) {
            sprite3.setPosition(bounds2.left - bounds1.width / 2 - GMnumber::oneAndHalf, sprite3.getPosition().y);
        }
        else if (fromRight&& !boxRight) {
            sprite3.setPosition(bounds2.left + bounds2.width + bounds1.width/2 + GMnumber::oneAndHalf, sprite3.getPosition().y);
        }
    }
    CollisionReseter();
}


void Collision::PreliminarySearch(std::vector<std::shared_ptr<BackGround>>& level1
    , std::vector<bool>& left, std::vector<bool>& right, std::vector<bool>& top, std::vector<bool>& bottom
    , std::vector<bool>& alreadydone) {
    for (unsigned int i = 0; i < level1.size(); i++) {
        if (level1[i]->c.DetectionAlreadyDone) { continue; }
        this->bounds1 = level1[i]->GetPathSprite().getGlobalBounds();
        this->position1 = level1[i]->GetPathSprite().getPosition();  //std::cout << "Bounds3 (Object " << i << "): " << bounds1.left << ", " << bounds1.top << ", "<< bounds1.width << ", "<< bounds1.height << std::endl;
        for (unsigned int j = 0; j < level1.size(); j++) {
            this->position2 = level1[j]->GetPathSprite().getPosition();
            if (i == j || !(abs(position1.x - position2.x) <= tolerance || abs(position1.y - position2.y) <= tolerance)) continue;
            this->bounds2 = level1[j]->GetPathSprite().getGlobalBounds();//std::cout << "Bounds3 (Object " << i << "): " << bounds2.left << ", " << bounds2.top << ", "<< bounds2.width << ", "<< bounds2.height << std::endl;
            ExpandBound(bounds1);
            ExpandBound(bounds2);
            if (this->bounds1.intersects(this->bounds2)) {
                BoundFinder();
                BoolFinder();
                if (this->fromLeft) {
                    level1[i]->c.skipLeft = true;
                    left[i] = true;
                }
                if (this->fromRight) {
                    level1[i]->c.skipRight = true;
                    right[i] = true;
                }
                if (this->fromTop) { 
                    level1[i]->c.skipTop = true; 
                    top[i] = true;
                }
                if (this->fromBottom) { 
                    level1[i]->c.skipBottom = true;
                    bottom[i] = true;
                }
            }
        }
        alreadydone[i] = true;
        level1[i]->c.DetectionAlreadyDone = true;
        CollisionReseter();
    }
}

void Collision::PreliminarySearch(std::vector<std::shared_ptr<BackGround>>& level1, Map1::PathData& VS){
    for (unsigned int i = 0; i < level1.size(); i++) {
        if (level1[i]->c.DetectionAlreadyDone) { continue; }
        this->bounds1 = level1[i]->GetPathSprite().getGlobalBounds();
        this->position1 = level1[i]->GetPathSprite().getPosition();  //std::cout << "Bounds3 (Object " << i << "): " << bounds1.left << ", " << bounds1.top << ", "<< bounds1.width << ", "<< bounds1.height << std::endl;
        for (unsigned int j = 0; j < level1.size(); j++) {
            this->position2 = level1[j]->GetPathSprite().getPosition();
            if (i == j || !(abs(position1.x - position2.x) <= tolerance || abs(position1.y - position2.y) <= tolerance)) continue;
            this->bounds2 = level1[j]->GetPathSprite().getGlobalBounds();//std::cout << "Bounds3 (Object " << i << "): " << bounds2.left << ", " << bounds2.top << ", "<< bounds2.width << ", "<< bounds2.height << std::endl;
            ExpandBound(bounds1);
            ExpandBound(bounds2);
            if (this->bounds1.intersects(this->bounds2)) {
                BoundFinder();
                BoolFinder();
                if (this->fromLeft) {
                    level1[i]->c.skipLeft = true;
                    VS.skipLeft[i] = true;
                }
                if (this->fromRight) {
                    level1[i]->c.skipRight = true;
                    VS.skipRight[i] = true;
                }
                if (this->fromTop) {
                    level1[i]->c.skipTop = true;
                    VS.skipTop[i] = true;
                }
                if (this->fromBottom) {
                    level1[i]->c.skipBottom = true;
                    VS.skipBottom[i] = true;
                }
            }
        }
        VS.alreadySkipCalculated[i] = true;
        level1[i]->c.DetectionAlreadyDone = true;
        CollisionReseter();
    }
}

//
//void Collision::PreliminarySerachV2(std::vector<std::shared_ptr<BackGround>>& level, const unsigned int i) {
//    std::cout << " i = " << i << std::endl;
//    this->position1 = level[i]->GetPathSprite().getPosition();
//    this->bounds1 = level[i]->GetPathSprite().getGlobalBounds(); ExpandBound(bounds1);
//    for (int j = 0; j <= i; j++) {
//        std::cout <<" j ." << j << std::endl;
//        this->position2 = level[j]->GetPathSprite().getPosition();
//        if (i == j || !(abs(position1.x - position2.x) <= tolerance || abs(position1.y - position2.y) <= tolerance)) continue;
//        this->bounds2 = level[j]->GetPathSprite().getGlobalBounds();
//        ExpandBound(bounds2);
//        if (this->bounds1.intersects(this->bounds2)) {
//            overlapLeft = abs(bounds1.left - (bounds2.left + bounds2.width));
//            overlapRight = abs((bounds1.left + bounds1.width) - bounds2.left);
//            overlapTop = abs(bounds1.top - (bounds2.top + bounds2.height));
//            overlapBottom = abs((bounds1.top + bounds1.height) - bounds2.top);
//      /*      std::cout << "Overlap Left: " << overlapLeft << "\n";
//            std::cout << "Overlap Right: " << overlapRight << "\n";
//            std::cout << "Overlap Top: " << overlapTop << "\n";
//            std::cout << "Overlap Bottom: " << overlapBottom << "\n";*/
//
//            fromLeft = (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom);
//            //std::cout << "From Left: " << fromLeft << "\n";
//            fromRight = (overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom);
//            //std::cout << "From Right: " << fromRight << "\n";
//            fromTop = (overlapTop < overlapBottom && overlapTop < overlapLeft && overlapTop < overlapRight);
//           // std::cout << "From Top: " << fromTop << "\n";
//            fromBottom = (overlapBottom < overlapTop && overlapBottom < overlapLeft && overlapBottom < overlapRight);
//           // std::cout << "From Bottom: " << fromBottom << "\n";
//
//            if (this->fromLeft) {
//                level[i]->c.skipLeft = true;
//                level[j]->c.skipRight = true;
//                //std::cout << " L . " << level[j]->c.skipRight << " " << level[i]->c.skipLeft << std::endl;
//            }
//            if (this->fromRight) {
//                level[i]->c.skipRight = true;
//                level[j]->c.skipLeft = true;
//               // std::cout << " R . " << level[i]->c.skipRight << " " << level[j]->c.skipLeft << std::endl;
//            }
//            if (this->fromTop) {
//                level[i]->c.skipTop = true;
//                level[j]->c.skipBottom = true;
//            }
//            if (this->fromBottom) {
//                level[i]->c.skipBottom = true;
//                level[j]->c.skipTop = true;
//            }
//        }
//    level[j]->c.DetectionAlreadyDone = true;
//    }
//    CollisionReseter();
//}


//bool Collision::PlayerOnGround(sf::Sprite& sprite, std::vector<std::shared_ptr<BackGround>>& level) {
//    this->isGravityAffecting = false;
//    position1 = sprite.getPosition();
//    bounds1 = sprite.getGlobalBounds();
//    for (unsigned int i = 0; i < level.size(); i++) {
//        position2 = level[i]->GetPathSprite().getPosition();
//        bounds2 = level[i]->GetPathSprite().getGlobalBounds();
//        if (bounds1.intersects(bounds2) && !gameObject.utility.MinimumDistanceCollisionUpdate(position1, position2)) {
//            BoundFinder();
//            if (overlapTop < overlapBottom && overlapTop < overlapLeft && overlapTop < overlapRight) {
//                isGravityAffecting = true;
//                gameObject.player->CanDodging() = true;
//                break;
//            }
//         
//        }
//    }
//    CollisionReseter();
//    return isGravityAffecting;
//}

void Collision::BoundFinder() {
    overlapLeft = bounds1.left + bounds1.width - bounds2.left;
    overlapRight = bounds2.left + bounds2.width - bounds1.left;
    overlapTop = bounds1.top + bounds1.height - bounds2.top;
    overlapBottom = bounds2.top + bounds2.height - bounds1.top;
}

void Collision::BoolFinder() {
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
