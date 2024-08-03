//Background.cpp
#include "BackGround.h"
#include"../GameObject.h"
BackGround::BackGround(float xPosSacle, float yPosSacle, unsigned int colorCode , bool left, bool right, bool top, bool bottom, bool done):

    pathSize(GMnumber::pathSize, GMnumber::pathSize),
    pathPosition(GMnumber::windowMaxWidth* xPosSacle, GMnumber::windowMaxHeight* yPosSacle),
    pathColor(gameObject.utility.colors[colorCode]), playerPosition(0, 0) {
    c.DetectionAlreadyDone = done;
    c.skipLeft = left;
    c.skipRight = right;
    c.skipTop = top;
    c.skipBottom = bottom;
    Load();
}


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
    gameObject.collision.PathPlayerCollidionDetection(gameObject.player->GetPlayerCollisionBox(), this->backGroundPath, gameObject.player->GetPlayerSprite()
        , c.skipLeft, c.skipRight, c.skipTop, c.skipBottom);
  }
}

void BackGround::Draw(std::shared_ptr<sf::RenderWindow>& window) {
    window->draw(this->backGroundPath);
}

