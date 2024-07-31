//Runner.cpp
#include "Runner.h"
#include"GameObject.h"

Runner::Runner():window(std::make_shared<sf::RenderWindow>(sf::VideoMode(static_cast<int>(GMnumber::windowMaxWidth),
	static_cast<int>(GMnumber::windowMaxHeight)), "SFML works!")),
	viewCamera(sf::FloatRect(int(GMnumber::zero), int(GMnumber::zero), int(window->getSize().x), int(window->getSize().y)))
	,event(), deltaTime(0.0f) , playerPosition(0,0){
	window->setFramerateLimit(GMnumber::maxFrameRate);
}

void Runner::SfmlEvent(){
	while (window->pollEvent(event)){
		if (event.type == sf::Event::Closed)
			window->close();
	}	
}

void Runner::Load(){
	gameObject.map1->Load();
	gameObject.player->Load();
	Update();

}

void Runner::Update(){
	while (window->isOpen()) {
	SfmlEvent();
	Deltatime();
	gameObject.map1->Update();
	gameObject.player->Update(deltaTime);
	UpdateCamera();
	Draw();
	}
}

void Runner::Draw(){
	window->clear();
	gameObject.player->Draw(window);
	gameObject.map1->Draw(window);
	window->display();
}

void Runner::UpdateCamera(){
	playerPosition = gameObject.player->GetPlayerSprite().getPosition();

	viewCamera.setCenter((playerPosition.x - GMnumber::windowMaxWidth / 2 > 0)? playerPosition.x : GMnumber::windowMaxWidth / 2,
		GMnumber::windowMaxHeight / 2);
	window->setView(viewCamera);
}

inline void Runner::Deltatime(){
	this->deltaTime = clock.restart().asSeconds();
}

