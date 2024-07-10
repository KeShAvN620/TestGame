//Runner.h
#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include<memory>
#include"Utility.h"
#include"GameObject.h"

class Runner
{
	std::shared_ptr<sf::RenderWindow> window;
	sf::Event event;
	sf::Clock clock;
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

