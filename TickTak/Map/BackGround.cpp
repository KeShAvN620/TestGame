//Background.cpp
#include "BackGround.h"
#include"../GameObject.h"

BackGround::BackGround(const float pathWidthPositionScale , const float pathHeightPositionScale , const int i =-2 ):
    isCollidingWithPlayer(false), pathSize(GameMagicNumbers::pathSize,GameMagicNumbers::pathSize),
    pathPosition(GameMagicNumbers::windowMaxWidth * pathWidthPositionScale,
        GameMagicNumbers::windowMaxHeight * pathHeightPositionScale), font(gameObject.utility.GetFont()),
    collosionText("false") , I(i) , skipCollisionCheckLeft(false), skipCollisionCheckRight(false), skipCollisionCheckTop(false),
    skipCollisionCheckBottom(false) {
    this->backgoundcollisionText.setFont(font);
    this->backGroundPath.setSize(pathSize);
    this->backGroundPath.setPosition(pathPosition);
    this->backGroundPath.setFillColor(sf::Color::Cyan);
}

void BackGround::Load() {
    this->backgoundcollisionText.setPosition(sf::Vector2f(GameMagicNumbers::zero,GameMagicNumbers::zero + 15*I));
    this->backgoundcollisionText.setCharacterSize(15);
 
}

void BackGround::Update(){
    CollisonDetection();
}

void BackGround::CollisonDetection(){
    sf::Vector2f playerCoordinate = gameObject.player->GetPlayerSprite().getPosition();
    this->isCollidingWithPlayer = gameObject.collision.PathPlayerCollidionDetection(gameObject.player->GetPlayerCollisionBox(), backGroundPath, gameObject.player->GetPlayerSprite(), skipCollisionCheckLeft, skipCollisionCheckRight, skipCollisionCheckTop, skipCollisionCheckBottom);
    this->collosionText = this->isCollidingWithPlayer == true ? " True" : "False";
   // this->backgoundcollisionText.setString("Collision = " + this->collosionText + "  " +"; Player Coordinate = " + std::to_string(int(gameObject.player->GetPlayerSprite().getPosition().x)) + " " + std::to_string(int(gameObject.player->GetPlayerSprite().getPosition().y)));
}

void BackGround::Draw(std::shared_ptr<sf::RenderWindow>& window) {
    window->draw(this->backGroundPath);
    window->draw(this->backgoundcollisionText);
}
