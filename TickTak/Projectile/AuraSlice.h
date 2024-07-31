#pragma once
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include<cmath>
#include"../Map/Background.h"
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
	sf::Vector2f maxDistance;
	bool isCreated;
	bool isDestroyedWhenHitWithPath;
	bool isDestroyedWhenOutOfReach;
	unsigned int counter;
	float angle;
public:
	AuraSlice(const unsigned int entityId, const sf::Vector2f startingPosition, const unsigned int maxDistanceTravel);
	inline bool& IsOutOfReach() { return isDestroyedWhenOutOfReach; }
	inline bool& IsCollidedWithPath() { return isDestroyedWhenHitWithPath; }

public:
	void Load();
	void Update(float& deltaTime);
	void Draw();

private:
	void CriticalLoad();
	void CollisionBoxLoad();
	void DirectionFinder();
	inline void AngleFinderAndLoader();

	void Movement(const float& deltaTime);
	void DestoryWhenOutOfRange();
public:
	void  DestoryWhenHitThePath(std::vector<std::shared_ptr<BackGround>>& other);

};