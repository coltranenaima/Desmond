#include "Player.h"

Player::Player()
{
	playerSizeX = 20.f;
	playerSizeY = 20.f;
	cameraChase = .05f;
	playerShape.setSize(sf::Vector2f(playerSizeX, playerSizeY));
	playerShape.setFillColor(sf::Color::Blue);
	playerShape.setOrigin(sf::Vector2f(playerShape.getGlobalBounds().width / 2, playerShape.getGlobalBounds().height / 2));
}

void Player::PlayerRotation(sf::RenderWindow& win, sf::RectangleShape& pO)
{
	dx = 0.f;
	dy = 0.f;
	mouse = sf::Mouse::getPosition(win);
	mouseWorld = win.mapPixelToCoords(mouse);
	dx = mouseWorld.x - pO.getPosition().x;
	dy = mouseWorld.y - pO.getPosition().y;
	rotation = (atan2(dy, dx)) * 180 / PI;
	pO.setRotation(rotation);
}

void Player::PlayerCameraChase(sf::RectangleShape& pO, sf::View& gameView, float& cameraChaseTime, float& deltaCd)
{

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (cameraChaseTime > deltaCd)
		{
			if (gameView.getCenter().x < pO.getPosition().x)
			{
				gameView.move(Player::cameraChase, 0.f);
			}
			if (gameView.getCenter().x > pO.getPosition().x)
			{
				gameView.move(-Player::cameraChase, 0.f);
			}
			if (gameView.getCenter().y < pO.getPosition().y)
			{
				gameView.move(.0f, Player::cameraChase);
			}
			if (gameView.getCenter().y > pO.getPosition().y)
			{
				gameView.move(.0f, -Player::cameraChase);
			}
		}
	}
}