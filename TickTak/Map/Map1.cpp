#include "Map1.h"
#include "../Resources/Utility.h"
#include "../GameObject.h"


Map1::Map1() {
    for (unsigned int i = 0; i < GameMagicNumbers::vectorSize; i++) {
        level1.push_back(std::make_shared<BackGround>((i+1) * GetProperScaleX(64.0f),GetProperScaleY(400) - i*(1.0f/25), -1 * i));
    }
    gameObject.collision.PreliminarySearch(level1);
}

void Map1::Load() {
    for (auto& background : level1) {
        background->Load();
    }
}

void Map1::Update() {
    for (auto& background : level1) {
        background->Update();
    }
}

void Map1::Draw(std::shared_ptr<sf::RenderWindow>& window) {
    gameObject.player->IsGravityAffecting() = !gameObject.collision.PlayerOnGround(gameObject.player->GetPlayerSprite(), level1);
    for (auto& background : level1) {
        background->Draw(window);
    }
}

inline float Map1::GetProperScaleX(const float xPosition) {
    return xPosition * GameMagicNumbers::windowMaxWidth / (GameMagicNumbers::baseWidth * GameMagicNumbers::baseWidth);
}

inline float Map1::GetProperScaleY(const float yPosition) {
    return yPosition * GameMagicNumbers::windowMaxHeight / (GameMagicNumbers::baseHeight * GameMagicNumbers::baseHeight);
}































//gameObject.player->IsGravityAffecting() = !gameObject.collision.PlayerOnGround(gameObject.player->GetPlayerSprite(), level1);