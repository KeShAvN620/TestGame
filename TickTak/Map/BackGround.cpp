//Background.cpp
#include "BackGround.h"
#include"../GameObject.h"

BackGround::BackGround(const float pathWidthPositionScale, const float pathHeightPositionScale):
    isCollidingWithPlayer(false), pathSize(GameMagicNumbers::pathSize,GameMagicNumbers::pathSize),
    pathPosition(GameMagicNumbers::windowMaxWidth - (GameMagicNumbers::windowMaxWidth * pathWidthPositionScale),
        GameMagicNumbers::windowMaxHeight - (GameMagicNumbers::windowMaxHeight * pathHeightPositionScale)), font(gameObject.utility.GetFont()),
    collosionText("false"){
    this->backgoundcollisionText.setFont(font);
    this->backGroundPath.setSize(pathSize);
    this->backGroundPath.setPosition(pathPosition);
    this->backGroundPath.setFillColor(sf::Color::Cyan);
    this->backGroundPath.setOutlineThickness(GameMagicNumbers::one);
    this->backGroundPath.setOutlineColor(sf::Color::Yellow);
}

void BackGround::Load() {
    this->backgoundcollisionText.setPosition(sf::Vector2f(50,50));
    this->backgoundcollisionText.setCharacterSize(15);
 
}

void BackGround::Update(){
    CollisonDetection();
}

void BackGround::CollisonDetection(){
    sf::Vector2f playerCoordinate = gameObject.player->GetPlayerSprite().getPosition();
    this->isCollidingWithPlayer = gameObject.collision.PathPlayerCollidionDetection(gameObject.player->GetPlayerCollisionBox(), backGroundPath, gameObject.player->GetPlayerSprite());
    this->collosionText = this->isCollidingWithPlayer == true ? " True" : "False";
    this->backgoundcollisionText.setString("Collision = " + this->collosionText + "  " +"; Player Coordinate = " + std::to_string(int(playerCoordinate.x)) + " " + std::to_string(int(playerCoordinate.y)));
}

void BackGround::Draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(this->backGroundPath);
    window->draw(this->backgoundcollisionText);
}
