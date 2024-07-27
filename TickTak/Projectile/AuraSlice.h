#pragma once
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include<cmath>
class AuraSlice
{
private:
	std::shared_ptr<sf::RenderWindow>& window;
	sf::Texture texture;
	sf::Sprite sprite;
	std::vector<sf::IntRect> slicePositionInFile;
	sf::RectangleShape collisionBox;
	sf::Vector2f position;
	sf::Vector2f direction;
    sf::Vector2f speed;


private:
	unsigned int entityId;
	sf::Vector2f shootingPosition;
	unsigned int maxDistance;
	bool isCreated;
	unsigned int counter;
	float angle;
public:
	AuraSlice(const unsigned int entityId, const sf::Vector2f startingPosition , const unsigned int maxDistanceTravel);

public:
	void Load();
	void Update(float& deltaTime);
	void Draw();
	

private:
	void CriticalLoad();
	void CollisionBoxLoad();
	void DirectionFinder();
	inline void AngleFinderAndLoader();
};

