#include"Utility.h"


Utiluty::Utiluty() : bounds1(), bounds2(), overlapLeft(0.0f), overlapRight(0.0f), overlapTop(0.0f), overlapBottom(0.0f),
        fromLeft(false), fromRight(false), fromTop(false), fromBottom(false)
{}

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


bool Utiluty::PathPlayerCollidionDetection(sf::Sprite& sprite1, const sf::RectangleShape& sprite2, const sf::Vector2f& sprite2Size) {
    // Get bounding boxes of the sprites
    bounds1 = sprite1.getGlobalBounds();
    bounds2 = sprite2.getGlobalBounds();
    if (bounds1.intersects(bounds2)) {
        overlapLeft = bounds1.left + bounds1.width - bounds2.left;
        overlapRight = bounds2.left + bounds2.width - bounds1.left;
        overlapTop = bounds1.top + bounds1.height - bounds2.top;
        overlapBottom = bounds2.top + bounds2.height - bounds1.top;

        // Determine the side of the collision based on the smallest overlap
        fromLeft = (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom);
        fromRight = (overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom);
        fromTop = (overlapTop < overlapBottom && overlapTop < overlapLeft && overlapTop < overlapRight);
        fromBottom = (overlapBottom < overlapTop && overlapBottom < overlapLeft && overlapBottom < overlapRight);

        // Resolve collision based on the side
        if (fromLeft) {
            sprite1.setPosition(bounds2.left - bounds1.width, sprite1.getPosition().y);
        }
        else if (fromRight) {
            sprite1.setPosition(bounds2.left + bounds2.width, sprite1.getPosition().y);
        }
        else if (fromTop) {
            sprite1.setPosition(sprite1.getPosition().x, bounds2.top - bounds1.height);
        }
        else if (fromBottom) {
            sprite1.setPosition(sprite1.getPosition().x, bounds2.top + bounds2.height);
        }
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



