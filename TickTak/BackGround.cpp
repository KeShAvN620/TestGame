//Background.cpp
#include "BackGround.h"
#include"GameObject.h"

BackGround::BackGround(const float& windowMinWidth, const float& windowMaxWidth, const float& windowMinHeight, const float& windowMaxHeight)
    : pathSize((windowMaxWidth - windowMinWidth) / Dimension.pathWidthSizeScale,
        (windowMaxHeight - windowMinHeight) / Dimension.pathHeightSizeScale),
    pathPosition(windowMaxWidth - (windowMaxWidth / Dimension.pathWidthPositionScale),
        windowMaxHeight - (windowMaxHeight / Dimension.pathHeightPositionScale)) {
}

void BackGround::Load() {
    this->backGroundPath.setSize(pathSize);
    this->backGroundPath.setPosition(pathPosition);
    this->backGroundPath.setFillColor(sf::Color::Cyan);
}

void BackGround::Draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(backGroundPath);
}
