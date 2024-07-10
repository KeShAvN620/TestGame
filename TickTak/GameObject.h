//GameObject.h
#pragma once
#include<iostream>
#include<memory>
#include"Player.h"
#include"BackGround.h"
#include"Utility.h"

struct GameObject
{
	Font font;
	Utiluty utility;
	std::shared_ptr<Player> player = std::make_shared<Player>();
	std::shared_ptr<BackGround> backGroundPath = std::make_shared<BackGround>(GameMagicNumbers::windowMinWidth, GameMagicNumbers::windowMaxWidth, GameMagicNumbers::windowMinHeight, GameMagicNumbers::windowMaxHeight);
}; 
extern GameObject gameObject;
