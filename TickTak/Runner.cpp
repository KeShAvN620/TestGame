#include "Runner.h"

Runner::Runner() : window(std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "SFML works!")),
					deltaTime(0) {
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

	window->display();
}

inline void Runner::Deltatime()
{
	this->deltaTime = clock.restart().asSeconds();
}

