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


Utiluty::Utiluty(){
	if (!font.loadFromFile("Assets/Fonts/arial.ttf")) {
		std::cerr << "Error loading font\n";
		return;
	}
}

sf::Font Utiluty::GetFont()
{
	return font;
}



