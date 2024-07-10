//GameObject.h
#pragma once
#include<iostream>
#include<memory>
#include"Player.h"
#include"BackGround.h"

struct GameObject
{
	//std::shared_ptr<Runner> runner = std::make_shared<Runner>();
	std::shared_ptr<Player> player = std::make_shared<Player>();
}; 
extern GameObject gameObject;
