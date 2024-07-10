//Runner.cpp
#include "Runner.h"

Runner::Runner()
	:window(std::make_shared<sf::RenderWindow>(sf::VideoMode(static_cast<int>(GameMagicNumbers::windowMaxWidth),static_cast<int>(GameMagicNumbers::windowMaxHeight)), "SFML works!")),
	event(),backGroundPath(GameMagicNumbers::windowMinWidth, GameMagicNumbers::windowMaxWidth, GameMagicNumbers::windowMinHeight, GameMagicNumbers::windowMaxHeight),
	deltaTime(0.0f){
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
	gameObject.player->Load();
	Update();
}

void Runner::Update()
{
	while (window->isOpen()) {
	SfmlEvent();
	Deltatime();
	gameObject.player->Update(deltaTime);
	Draw();
	}
}

void Runner::Draw()
{
	window->clear();
	gameObject.player->Draw(window);
	backGroundPath.Draw(window);

	window->display();
}

inline void Runner::Deltatime()
{
	this->deltaTime = clock.restart().asSeconds();
}

