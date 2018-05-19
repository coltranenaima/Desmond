#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
#include <cmath>
#include <random>

class Enemy
{
public:
	float enemySizeX, enemySizeY, dx, dy, rotation, movement, enemyAngleReturn;
	const float PI = 3.14159265f;
	sf::RectangleShape enemyShape;
	void enemyRotation(sf::RectangleShape& eO, sf::RectangleShape& pO);
	float enemyMovement(sf::RectangleShape& eO, sf::RectangleShape& pO);
	void Enemy::loadEnemies(int numberOfEnemies, std::vector<Enemy>& eV, Enemy& eO, Player& pO);
	sf::RectangleShape enemyNode(int randmin, int randmax, float allNodeOffset, Player& pO);
	float nodeCollision(std::vector<Enemy>& eO, sf::RectangleShape& eNO, std::vector<bool>& x, std::vector<bool>& prevX, int i, float& eA);
	Enemy();
};