#include "Bullet.h"

Bullet::Bullet(sf::Color bulletColor)
{
	bulletSizeX = 5.f;
	bulletSizeY = 5.f;
	bulletShape.setSize(sf::Vector2f(bulletSizeX, bulletSizeY));
	bulletShape.setOrigin(sf::Vector2f(bulletShape.getGlobalBounds().width / 2.f, bulletShape.getGlobalBounds().height / 2.f));
	bulletShape.setFillColor(bulletColor);
}

float Bullet::BulletAnglePlayer(sf::RenderWindow& win, sf::RectangleShape& bS)
{
	dx = 0.f;
	dy = 0.f;
	mouse = sf::Mouse::getPosition(win);
	mouseWorld = win.mapPixelToCoords(mouse);
	dx = mouseWorld.x - bS.getPosition().x;
	dy = mouseWorld.y - bS.getPosition().y;
	return rotationPlayer = atan2(dy, dx);
}

float Bullet::BulletAngleEnemy(sf::RenderWindow& win, sf::RectangleShape& bS, Player& pO)
{
	dx = 0.f;
	dy = 0.f;
	dx = pO.playerShape.getPosition().x - bS.getPosition().x;
	dy = pO.playerShape.getPosition().y - bS.getPosition().y;
	return rotationEnemy = atan2(dy, dx);
}