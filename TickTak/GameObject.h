//GameObject.h
#pragma once
#include<iostream>
#include<vector>
#include<memory>
#include"Player/Player.h"
#include"Map/BackGround.h"
#include"Resources/Utility.h"
#include"Physic/Collision.h"
#include <SFML/Graphics.hpp>
#include"Physic/Physic.h"

struct GameObject
{
	Utiluty utility;
	Collision collision;
	Physic physic;
	std::shared_ptr<Player> player = std::make_shared<Player>();
	std::shared_ptr<BackGround> backGroundPath = std::make_shared<BackGround>(GameMagicNumbers::pathWidthPositionScale , GameMagicNumbers::pathHeightPositionScale);
	std::shared_ptr<BackGround> backGroundPath1 = std::make_shared<BackGround>( 0.8973f,1/3.0f);
}; 
extern GameObject gameObject;
