//GameObject.h
#pragma once
#include<iomanip>
#include"Player/Player.h"
#include"Map/BackGround.h"
#include"Resources/Utility.h"
#include"Physic/Collision.h"
#include <SFML/Graphics.hpp>
#include"Physic/Physic.h"
#include "Map/Map1.h"
#include"Runner.h"

struct GameObject
{
	Runner runProgram;
	Utility utility;
	Collision collision;
	Physic physic;
	std::shared_ptr<Player> player = std::make_shared<Player>();
	std::shared_ptr<Map1> map1 = std::make_shared<Map1>();

	}; 
extern GameObject gameObject;
    