#include "Map1.h"
#include "../Resources/Utility.h"
#include "../GameObject.h"


Map1::Map1():playerPosition(0,0), pathPosition(0,0){
    for (unsigned int i = GameMagicNumbers::zero; i < GameMagicNumbers::vectorSize; i++) {
        level1.push_back(std::make_shared<BackGround>((i) * GetProperScaleX(66.0f),GetProperScaleY(400.0), (i % (gameObject.utility.colors.size() - 3))));  /*- (i*(1.0/25))*/
    } 
  
}

void Map1::Load() { 
    for (auto& background : level1) {
        background->Load();
    }
    gameObject.collision.PreliminarySearch(level1);
}

void Map1::Update() {
    gameObject.player->IsGravityAffecting() = !gameObject.collision.PlayerOnGround(gameObject.player->GetPlayerSprite(), level1);
    playerPosition = gameObject.player->GetPlayerSprite().getPosition();
    for (unsigned int i = GameMagicNumbers::zero; i < level1.size(); i++) {
        pathPosition = level1[i]->GetPathSprite().getPosition();

        if (gameObject.utility.UpdateAndDrawEnabler(playerPosition, pathPosition)) {continue;}
        //std::cout << gameObject.utility.UpdateAndDrawEnabler(playerPosition, pathPosition) <<" " << std::setw(4)<< i << std::endl;
        level1[i]->Update();
    }
}

void Map1::Draw(std::shared_ptr<sf::RenderWindow>& window) {
    playerPosition = gameObject.player->GetPlayerSprite().getPosition();
    for (unsigned int i = GameMagicNumbers::zero; i < level1.size(); i++) {
        pathPosition = level1[i]->GetPathSprite().getPosition();
        if (gameObject.utility.UpdateAndDrawEnabler(playerPosition,pathPosition)){continue;}
        //std::cout << gameObject.utility.UpdateAndDrawEnabler(playerPosition, pathPosition) << " " << std::setw(4) << i << std::endl;
        level1[i]->Draw(window);
    }
}

inline float Map1::GetProperScaleX(const float xPosition) {
    return (xPosition) * GameMagicNumbers::windowMaxWidth / (GameMagicNumbers::baseWidth * GameMagicNumbers::baseWidth);
}

inline float Map1::GetProperScaleY(const float yPosition) {
    return (yPosition) * GameMagicNumbers::windowMaxHeight / (GameMagicNumbers::baseHeight * GameMagicNumbers::baseHeight);
}































//gameObject.player->IsGravityAffecting() = !gameObject.collision.PlayerOnGround(gameObject.player->GetPlayerSprite(), level1);