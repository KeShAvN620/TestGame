//utility.cpp
#include"Utility.h"

Utility::Utility(): dx(0) , dy(0), distanceSquared(0) , minimumDistanceSquared(0) , length(0){
	if (!font.loadFromFile("Assets/Fonts/arial.ttf")) {
		std::cerr << "Error loading font\n";
		return;
	}
	if (!playerTexture.loadFromFile("Assets/Adventure/PlayerSprite.png")) {
		std::cerr << "Error loading playerSprite\n";
	}
	LoadBullet();
	ColorLoader();
}

void Utility::ColorLoader(){
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

void Utility::LoadBullet(){
	if (!bulletTexture.loadFromFile("Assets/Bullets/Bullets.png")) {
		std::cerr << "Error loading BulletSprite\n";
	}
}

void Utility::UpdateAnimation(sf::Sprite& aSprite, std::vector<sf::IntRect>& aFrame, unsigned int& aCounter, const unsigned int& aStart, const unsigned int& aSize) {
	if (!aFrame.empty()) {
		aCounter = (aCounter + 1) % aSize;
		aSprite.setTextureRect(aFrame[aStart + aCounter]);
	}
	else {
		std::cout << "unable to load frames " << std::endl;
		return;
	}
}

bool Utility::UpdateAndDrawEnabler(const sf::Vector2f& playerPosition, const sf::Vector2f& pathPosition) {
    dx = playerPosition.x - pathPosition.x;
    dy = playerPosition.y - pathPosition.y;
	bool withinX = std::abs(dx) > GameMagicNumbers::minimumUpdateDistanceX;
	bool withinY = std::abs(dy) > GameMagicNumbers::minimumUpdateDistanceY;
	return withinX && withinY;
}

bool Utility::MinimumDistanceCollisionUpdate(const sf::Vector2f& position1, const sf::Vector2f& position2){
	dx = position1.x - position2.x;
	dy = position1.y - position2.y;
	distanceSquared = dx * dx + dy * dy;
	minimumDistanceSquared = GameMagicNumbers::minimumDistance * GameMagicNumbers::minimumDistance;
	return distanceSquared > minimumDistanceSquared;
}

sf::Vector2f Utility::NormalizedVectors(sf::Vector2f& vector){
	length = sqrt(vector.x * vector.x + vector.y * vector.y);
	if (length == 0) {
		return vector;
	}
	else {
	vector = vector / length;
	return vector;
	}
}









