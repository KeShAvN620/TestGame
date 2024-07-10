#include "Runner.h"

Runner::Runner()
	: windowMinWidth(0), windowMinHeight(0), windowMaxWidth(800), windowMaxHeight(600),
	window(std::make_shared<sf::RenderWindow>(sf::VideoMode(windowMaxWidth, windowMaxHeight), "SFML works!")),
	event(),backGroundPath(windowMinWidth, windowMaxWidth, windowMinHeight, windowMaxHeight), deltaTime(0){
	window->setFramerateLimit(60);
}



void Runner::SfmlEvent()
{
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}	
}

void Runner::Load()
{
	backGroundPath.Load();
	player.Load();
	Update();
}

void Runner::Update()
{
	while (window->isOpen()) {
	SfmlEvent();
	Deltatime();
	player.Update(deltaTime);
	Draw();
	}
}

void Runner::Draw()
{
	window->clear();
	player.Draw(window);
	backGroundPath.Draw(window);

	window->display();
}

inline void Runner::Deltatime()
{
	this->deltaTime = clock.restart().asSeconds();
}

