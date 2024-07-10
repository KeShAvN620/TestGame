//Background.cpp
#include "BackGround.h"
#include"GameObject.h"

BackGround::BackGround(const float& windowMinWidth, const float& windowMaxWidth, const float& windowMinHeight, const float& windowMaxHeight)
    :isCollidingWithPlayer(false), pathSize((windowMaxWidth - windowMinWidth) / Dimension.pathWidthSizeScale,
        (windowMaxHeight - windowMinHeight) / Dimension.pathHeightSizeScale),
    pathPosition(windowMaxWidth - (windowMaxWidth / Dimension.pathWidthPositionScale),
        windowMaxHeight - (windowMaxHeight / Dimension.pathHeightPositionScale)), font(gameObject.font.GetFont()),
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
    CollisonDetection();
}

void BackGround::CollisonDetection(){
    sf::Vector2f playerCoordinate = gameObject.player->GetPlayerSprite().getPosition();
    this->isCollidingWithPlayer = gameObject.utility.PathPlayerCollidionDetection(gameObject.player->GetPlayerSprite(), backGroundPath , pathSize);
    this->collosionText = this->isCollidingWithPlayer == true ? " True" : "False";
      this->backgoundcollisionText.setString("Collision Happening with path = " + this->collosionText + "  " +"; Player Coordinate = " + std::to_string(playerCoordinate.x) + " " + std::to_string(playerCoordinate.y));
}

void BackGround::Draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(this->backGroundPath);
    window->draw(this->backgoundcollisionText);
}
