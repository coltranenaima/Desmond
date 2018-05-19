#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Bullet
{
public:
	float bulletSizeX, bulletSizeY, dx, dy, rotationPlayer, rotationEnemy;
	const float PI = 3.14159265f;
	sf::Vector2i mouse;
	sf::Vector2f mouseWorld;
	sf::RectangleShape bulletShape;
	float Bullet::BulletAnglePlayer(sf::RenderWindow& win, sf::RectangleShape& bS);
	float Bullet::BulletAngleEnemy(sf::RenderWindow& win, sf::RectangleShape& bS, Player& pO);
	Bullet(sf::Color bulletColor);
};