#include"Utility.h"


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


bool Utiluty::AABBCollisionDetection(const sf::Sprite& sprite1, const sf::RectangleShape& sprite2){
	if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds())) {
		return true;
	}
	return false;
}






Font::Font(){
	if (!font.loadFromFile("Assets/Fonts/arial.ttf")) {
		std::cerr << "Error loading font\n";
		return;
	}
}

sf::Font Font::GetFont()
{
	return font;
}



