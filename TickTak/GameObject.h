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
#include "Map/Map1.h"

struct GameObject
{
	Utiluty utility;
	Collision collision;
	Physic physic;
	std::shared_ptr<Player> player = std::make_shared<Player>();
	std::shared_ptr<Map1> map1 = std::make_shared<Map1>();
	}; 
extern GameObject gameObject;
    