#pragma once
#include "SFML/Graphics.hpp"
#include <cmath>

class Player
{
public:
	float playerSizeX, playerSizeY, dx, dy, rotation, cameraChase;
	const float PI = 3.14159265f;
	sf::Vector2i mouse;
	sf::Vector2f mouseWorld;
	sf::RectangleShape playerShape;
	void PlayerRotation(sf::RenderWindow& win, sf::RectangleShape& pO);
	void PlayerCameraChase(sf::RectangleShape& pO, sf::View& gameView, float& cameraChaseTime, float& deltaCd);
	Player();
};