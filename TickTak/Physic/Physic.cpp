//physic.cpp
#include "Physic.h"

Physic::Physic(): overlapLeft(0), overlapRight(0), overlapTop(0), overlapBottom(0) 
, fromTop(false){}

//void Physic::PreliminarySearch(std::vector<std::shared_ptr<BackGround>>* level){
//	std::vector<std::shared_ptr<BackGround>>bb = *level;
//	for (int i = 0; i < level->size(); i++) {
//		bounds1 = bb[i]->GetPathSprite().getGlobalBounds();
//		std::cout << bounds1.top << std::endl;
//	}
//}
//
