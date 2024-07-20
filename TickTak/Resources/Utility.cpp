//utility.cpp
#include"Utility.h"

Utiluty::Utiluty() {
	if (!font.loadFromFile("Assets/Fonts/arial.ttf")) {
		std::cerr << "Error loading font\n";
		return;
	}
	colors = {
	  sf::Color::White,
	  sf::Color::Red,
	  sf::Color::Green,
	  sf::Color::Blue,
	  sf::Color::Yellow,
	  sf::Color::Magenta,
	  sf::Color::Cyan,
	  sf::Color(150,75,0,150),
	  sf::Color::Black,
	  sf::Color::Transparent,
	  sf::Color(0, 0, 0, 0) //transparent black
	};
}

void Utiluty::UpdateAnimation(sf::Sprite& animationSprite, unsigned int& animationCounter, std::vector<sf::IntRect>& animationFrame) {
	if (!animationFrame.empty()) {
		animationCounter = (animationCounter + 1) % animationFrame.size();
		animationSprite.setTextureRect(animationFrame[animationCounter]);
	}
	else {
		std::cout << "unable to load frames " << std::endl;
		return;
	}
}

bool Utiluty::UpdateAndDrawEnabler(sf::Vector2f& playerPosition, sf::Vector2f& pathPosition){
	return abs(playerPosition.x - pathPosition.x) >= GameMagicNumbers::minimumUpdateDistanceX &&
		abs(playerPosition.y - pathPosition.y) >= GameMagicNumbers::minimumUpdateDistanceY;
}

bool Utiluty::MinimumDistanceCollisionUpdate(sf::Vector2f& position1, sf::Vector2f position2){
	return abs(position1.x - position2.x) >= GameMagicNumbers::minimumDistance &&
		abs(position1.y - position2.y) >= GameMagicNumbers::minimumDistance;
}









