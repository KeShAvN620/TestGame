//Background.cpp
#include "BackGround.h"
#include"../GameObject.h"

BackGround::BackGround(const float& windowMinWidth, const float& windowMaxWidth, const float& windowMinHeight, const float& windowMaxHeight)
    :isCollidingWithPlayer(false), pathSize((windowMaxWidth - windowMinWidth) / GameMagicNumbers::pathWidthSizeScale,
        (windowMaxHeight - windowMinHeight) / GameMagicNumbers::pathHeightSizeScale),
    pathPosition(windowMaxWidth - (windowMaxWidth / GameMagicNumbers::pathWidthPositionScale),
        windowMaxHeight - (windowMaxHeight / GameMagicNumbers::pathHeightPositionScale)), font(gameObject.utility.GetFont()),
    collosionText("false"){
    this->backgoundcollisionText.setFont(font);
}

void BackGround::Load() {
    this->backGroundPath.setSize(pathSize);
    this->backGroundPath.setPosition(pathPosition);
    this->backGroundPath.setFillColor(sf::Color::Cyan); 

    this->backgoundcollisionText.setPosition(sf::Vector2f(50,50));
    this->backgoundcollisionText.setCharacterSize(15);
 
}

void BackGround::Update(){
    CollisionOfJump();
    CollisonDetection();
}

void BackGround::CollisonDetection(){
    sf::Vector2f playerCoordinate = gameObject.player->GetPlayerSprite().getPosition();
    this->isCollidingWithPlayer = gameObject.collision.PathPlayerCollidionDetection(gameObject.player->GetPlayerCollisionBox(), backGroundPath, gameObject.player->GetPlayerSprite());
    this->collosionText = this->isCollidingWithPlayer == true ? " True" : "False";
    this->backgoundcollisionText.setString("Collision Happening with path = " + this->collosionText + "  " +"; Player Coordinate = " + std::to_string(int(playerCoordinate.x)) + " " + std::to_string(int(playerCoordinate.y)));
}

void BackGround::CollisionOfJump() {
    if (gameObject.player->IsJumping()) {
        if (gameObject.player->GetPlayerCollisionBox().getGlobalBounds().intersects(backGroundPath.getGlobalBounds())) {
            gameObject.player->IsJumping() = false;
        }
    }
}

void BackGround::Draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(this->backGroundPath);
    window->draw(this->backgoundcollisionText);
}
