//GameObject.h
#pragma once
#include<iostream>
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
	std::shared_ptr<BackGround> backGroundPath = std::make_shared<BackGround>(GameMagicNumbers::windowMinWidth, GameMagicNumbers::windowMaxWidth, GameMagicNumbers::windowMinHeight, GameMagicNumbers::windowMaxHeight);
}; 
extern GameObject gameObject;
