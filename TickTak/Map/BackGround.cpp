//Background.cpp
#include "BackGround.h"
#include"../GameObject.h"

BackGround::BackGround(const float wPositionScale, const float hPositionScale, unsigned int colorcode) :
    pathSize(GameMagicNumbers::pathSize, GameMagicNumbers::pathSize),
    pathPosition(GameMagicNumbers::windowMaxWidth* wPositionScale, GameMagicNumbers::windowMaxHeight* hPositionScale),
    pathColor(gameObject.utility.colors[colorcode]), playerPosition(0, 0), skipCollisionCheckLeft(false), skipCollisionCheckRight(false),
    skipCollisionCheckTop(false), skipCollisionCheckBottom(false) {}


void BackGround::Load() {
    this->backGroundPath.setSize(pathSize);
    this->backGroundPath.setPosition(pathPosition);
    this->backGroundPath.setFillColor(pathColor);
}

void BackGround::Update(){
    CollisonDetection();
}

void BackGround::CollisonDetection() {
    this->playerPosition = gameObject.player->GetPlayerSprite().getPosition();
  if (!gameObject.utility.MinimumDistanceCollisionUpdate(playerPosition, pathPosition)) {
      //std::cout << gameObject.utility.MinimumDistanceCollisionUpdate(playerPosition, pathPosition) << std::endl;
    gameObject.collision.PathPlayerCollidionDetection(gameObject.player->GetPlayerCollisionBox(), this->backGroundPath, gameObject.player->GetPlayerSprite(), this->skipCollisionCheckLeft, this->skipCollisionCheckRight, this->skipCollisionCheckTop, this->skipCollisionCheckBottom);
  }
}

void BackGround::Draw(std::shared_ptr<sf::RenderWindow>& window) {
    window->draw(this->backGroundPath);
}

