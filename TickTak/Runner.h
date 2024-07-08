#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include<memory>
#include"Player.h"
class Runner
{
	std::shared_ptr<sf::RenderWindow> window;
	sf::Event event;
	sf::Clock clock;
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

