#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include<memory>
#include"Player.h"
#include "BackGround.h"

class Runner
{
	
	float windowMinWidth , windowMinHeight , windowMaxWidth, windowMaxHeight;
	std::shared_ptr<sf::RenderWindow> window;
	sf::Event event;
	sf::Clock clock;
	

	BackGround backGroundPath;
	Player player;
private:
	float deltaTime;

public:
	Runner();

public:
	void SfmlEvent();
	void Load();
	void Update();
	void Draw();

public:
	inline void Deltatime();
};

