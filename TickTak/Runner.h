//Runner.h
#pragma once
#include<SFML/Graphics.hpp>
#include<memory>
#include<vector>

class Runner
{
	std::shared_ptr<sf::RenderWindow> window;
	sf::View viewCamera;
	sf::Event event;
	sf::Clock clock;
private:
	float deltaTime;
	sf::Vector2f playerPosition;
public:
	Runner();
public:
	std::shared_ptr<sf::RenderWindow>& GetWindow() { return window; }
public:
	void SfmlEvent();
	void Load();
	void Update();
	void Draw();
private:
	void UpdateCamera();
public:
	inline void Deltatime();
};

