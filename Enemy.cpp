#include "Enemy.h"

Enemy::Enemy()
{
	enemySizeX = 20.f;
	enemySizeY = 20.f;
	enemyShape.setSize(sf::Vector2f(enemySizeX, enemySizeY));
	enemyShape.setFillColor(sf::Color::Yellow);
	enemyShape.setOrigin(sf::Vector2f(enemyShape.getGlobalBounds().width / 2, enemyShape.getGlobalBounds().height / 2));
}

void Enemy::enemyRotation(sf::RectangleShape& eO, sf::RectangleShape& pO)
{
	dx = 0.f;
	dy = 0.f;
	dx = pO.getPosition().x - eO.getPosition().x;
	dy = pO.getPosition().y - eO.getPosition().y;
	rotation = (atan2(dy, dx)) * 180 / PI;
	eO.setRotation(rotation);
}

float Enemy::enemyMovement(sf::RectangleShape& eO, sf::RectangleShape& pO)
{
	dx = 0.f;
	dy = 0.f;
	dx = pO.getPosition().x - eO.getPosition().x;
	dy = pO.getPosition().y - eO.getPosition().y;
	return movement = atan2(dy, dx);
}

void Enemy::loadEnemies(int numberOfEnemies, std::vector<Enemy>& eV, Enemy& eO, Player& pO)
{	
	//ensure randomness
	srand((unsigned int)time(NULL));

	//load enemies 
	for (int i = 0; i < numberOfEnemies; i++)
	{
		int randx = rand() % 600;
		int randy = rand() % 600;
		eO.enemyShape.setPosition(sf::Vector2f(pO.playerShape.getPosition().x + (randx - 500), pO.playerShape.getPosition().y + (randy - 500)));
		eV.push_back(eO);
	}
}

sf::RectangleShape Enemy::enemyNode(int randmin, int randmax, float allNodeOffset, Player& pO)
{
	int randx = rand() % randmax + randmin;
	int randy = rand() % randmax + randmin;
	float nodeOneOffsetx = (float)randx;
	float nodeOneOffsety = (float)randy;
	sf::RectangleShape enemyNodeShape;
	enemyNodeShape.setSize(sf::Vector2f(5.0f, 5.0f));
	enemyNodeShape.setPosition(pO.playerShape.getPosition().x + (nodeOneOffsetx - allNodeOffset), pO.playerShape.getPosition().y + (nodeOneOffsety - allNodeOffset));
	return enemyNodeShape;

}

float Enemy::nodeCollision(std::vector<Enemy>& eO, sf::RectangleShape& eNO, std::vector<bool>& x, std::vector<bool>& prevX, int i, float& eA)
{
	float enemyAngle = 0.f;
	if (x[i] == false && prevX[i] == true)
	{
		if (eO[i].enemyShape.getGlobalBounds().intersects(eNO.getGlobalBounds()))
		{
			x[i] = true;
		}
		return enemyAngle = eO[i].enemyMovement(eO[i].enemyShape, eNO);
	}
	return eA;
	
}