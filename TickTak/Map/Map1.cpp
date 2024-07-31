#include "Map1.h"
#include "../Resources/Utility.h"
#include "../GameObject.h"


Map1::Map1():playerPosition(0,0), pathPosition(0,0){
   gameObject.fileRescource.ReadMapData(pathdatas);
    for (unsigned int i = GMnumber::zero; i < pathdatas.xPosition.size(); i++) {
        this->level1.push_back(
            std::make_shared<BackGround>(
                GetProperScaleX(pathdatas.xPosition[i]),
                GetProperScaleY(pathdatas.yPosition[i]),
                pathdatas.colorCode[i],
                bool(pathdatas.skipLeft[i]),
                bool(pathdatas.skipRight[i]),
                bool(pathdatas.skipTop[i]),
                bool(pathdatas.skipBottom[i]),
                bool(pathdatas.alreadySkipCalculated[i])
            )
        );

    } 
}

void Map1::Load() { 
    for (auto& background : this->level1) {
        background->Load();
    }
    gameObject.collision.PreliminarySearch(this->level1);
    VectorsOverWrite();
    gameObject.fileRescource.WriteMapData(this->pathdatas);
}

void Map1::Update() {
    gameObject.player->IsGravityAffecting() = !gameObject.collision.PlayerOnGround(gameObject.player->GetPlayerSprite(), level1);
    this->playerPosition = gameObject.player->GetPlayerSprite().getPosition();
    for (unsigned int i = GMnumber::zero; i < level1.size(); i++) {
        this->pathPosition = level1[i]->GetPathSprite().getPosition();
        if (gameObject.utility.UpdateAndDrawEnabler(playerPosition, pathPosition)) {continue;}
        //std::cout << gameObject.utility.UpdateAndDrawEnabler(playerPosition, pathPosition) <<" " << std::setw(4)<< i << std::endl;
        this->level1[i]->Update();
    }
}

void Map1::Draw(std::shared_ptr<sf::RenderWindow>& window) {
    this->playerPosition = gameObject.player->GetPlayerSprite().getPosition();
    for (unsigned int i = GMnumber::zero; i < level1.size(); i++) {
        this->pathPosition = level1[i]->GetPathSprite().getPosition();
        if (gameObject.utility.UpdateAndDrawEnabler(playerPosition,pathPosition)){continue;}
        //std::cout << gameObject.utility.UpdateAndDrawEnabler(playerPosition, pathPosition) << " " << std::setw(4) << i << std::endl;
        level1[i]->Draw(window);
    }
}

void Map1::VectorsOverWrite(){
    for (unsigned int i = GMnumber::zero; i < pathdatas.xPosition.size(); i++) {
        pathdatas.skipLeft[i] = this->level1[i]->c.skipLeft;
        pathdatas.skipRight[i] = this->level1[i]->c.skipRight;
        pathdatas.skipTop[i] = this->level1[i]->c.skipTop;
        pathdatas.skipBottom[i] = this->level1[i]->c.skipBottom;
        pathdatas.alreadySkipCalculated[i] = this->level1[i]->c.DetectionAlreadyDone;
    }

}

inline float Map1::GetProperScaleX(const float xPosition) {
    return (xPosition) * GMnumber::windowMaxWidth / (GMnumber::baseWidth * GMnumber::baseWidth);
}

inline float Map1::GetProperScaleY(const float yPosition) {
    return (yPosition) * GMnumber::windowMaxHeight / (GMnumber::baseHeight * GMnumber::baseHeight);
}































//gameObject.player->IsGravityAffecting() = !gameObject.collision.PlayerOnGround(gameObject.player->GetPlayerSprite(), level1);
//float xpos = 66.0f, ypos = 400.0; unsigned int ccode;
//bool left = false, right = false, top = false, bottom = false, alreadydone = false;
//       ccode = i % (gameObject.utility.colors.size() - 3);
//pathdatas.xPosition.push_back(xpos * i);
//pathdatas.yPosition.push_back(ypos);
//pathdatas.colorCode.push_back(ccode);
//pathdatas.skipLeft.push_back(left);
//pathdatas.skipRight.push_back(right);
//pathdatas.skipTop.push_back(top);
//pathdatas.skipBottom.push_back(bottom);
//pathdatas.alreadySkipCalculated.push_back(alreadydone);