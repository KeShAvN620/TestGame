//Runner.cpp
#include "Runner.h"

Runner::Runner()
	:window(std::make_shared<sf::RenderWindow>(sf::VideoMode(static_cast<int>(GameMagicNumbers::windowMaxWidth),static_cast<int>(GameMagicNumbers::windowMaxHeight)), "SFML works!")),
	event(),deltaTime(0.0f){
	window->setFramerateLimit(GameMagicNumbers::maxFrameRate);
}

void Runner::SfmlEvent(){
	while (window->pollEvent(event)){
		if (event.type == sf::Event::Closed)
			window->close();
	}	
}

void Runner::Load(){
	gameObject.backGroundPath->Load();
	gameObject.player->Load();
	Update();
}

void Runner::Update(){
	while (window->isOpen()) {
	SfmlEvent();
	Deltatime();
	gameObject.backGroundPath->Update();
	gameObject.player->Update(deltaTime);
	Draw();
	}
}

void Runner::Draw(){
	window->clear();
	gameObject.player->Draw(window);
	gameObject.backGroundPath->Draw(window);

	window->display();
}

inline void Runner::Deltatime(){
	this->deltaTime = clock.restart().asSeconds();
}

