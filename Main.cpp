#include "Bullet.h"
#include "Enemy.h"
#include "Levels.h"
#include <iostream>

int main()
{
#pragma region

	float
		delta, deltaCd, cameraChaseTime, 
		bulletTime, bulletCd, bulletSpeed, bulletAngle, bulletCleanTime,
		bulletTimeEnemy, bulletCdEnemy, bulletSpeedEnemy, bulletAngleEnemy, bulletCleanTimeEnemy,
		enemySpeed, enemyAngle,
		wKeyVelocity, aKeyVelocity, sKeyVelocity, dKeyVelocity,
		wKeyAccel, aKeyAccel, sKeyAccel, dKeyAccel, posAccelChange, negAccelChange, accelMax,
		wKeyPressTime, aKeyPressTime, sKeyPressTime, dKeyPressTime;
	float& cCT = cameraChaseTime;
	float& dCd = deltaCd;
	float& eA = enemyAngle;
	bool node0, node1, node2, node3, node4;
	bool& n0 = node0;
	bool& n1 = node1;
	bool& n2 = node2;
	bool& n3 = node3;
	bool& n4 = node4;
	int numberOfEnemies;
	sf::View gameView, miniView;
	sf::View& gV = gameView;
	sf::Event event;
	sf::Clock gameClock, wKeyPressClock, aKeyPressClock, sKeyPressClock, dKeyPressClock, bulletClock, cameraChaseClock, bulletCleanUp, bulletClockEnemy, bulletCleanUpEnemy;
	sf::Vector2i mouse;
	sf::Vector2f mouseWorld;
	sf::RectangleShape enemyNodeOne, enemyNodeTwo, enemyNodeThree, enemyNodeFour;
	sf::RectangleShape& eNO = enemyNodeOne;
	sf::RectangleShape& eNT = enemyNodeTwo;
	sf::RectangleShape& eNTR = enemyNodeThree;
	sf::RectangleShape& eNF = enemyNodeFour;
	Player playerOne;
	Player& pO = playerOne;
	Bullet playerBullet(sf::Color::Red);
	Bullet& pB = playerBullet;
	Enemy enemyOne;
	Enemy& eO = enemyOne;
	Bullet enemyBullet(sf::Color::Green);
	Bullet& eB = enemyBullet;
	std::vector<sf::RectangleShape> bulletVector, bulletVectorEnemy;
	std::vector<float> bulletAngleVector, bulletTimeFVector, bulletAngleVectorEnemy, bulletTimeFVectorEnemy, bulletTimeEnemies;
	std::vector<sf::Clock> bulletTimeVector, bulletTimeVectorEnemy, bulletTimeCVectorEnemy;
	std::vector<Enemy> enemies;
	std::vector<Enemy>& eV = enemies;
	std::vector<bool> nodesZero, nodesOne, nodesTwo, nodesThree, nodesFour;
	std::vector<bool>& nZ = nodesZero;
	std::vector<bool>& nO = nodesOne;
	std::vector<bool>& nT = nodesTwo;
	std::vector<bool>& nTR = nodesThree;
	std::vector<bool>& nF = nodesFour;

	//initialize
	delta = .0f;
	wKeyVelocity = .0f;
	aKeyVelocity = .0f;
	sKeyVelocity = .0f;
	dKeyVelocity = .0f;
	wKeyAccel = .0f;
	aKeyAccel = .0f;
	sKeyAccel = .0f;
	dKeyAccel = .0f;
	wKeyPressTime = .0f;
	aKeyPressTime = .0f;
	sKeyPressTime = .0f;
	dKeyPressTime = .0f;
	bulletAngle = .0f;
	bulletAngleEnemy = .0f;
	cameraChaseTime = .0f;
	bulletTime = .0f;
	bulletCleanTime = .0f;
	bulletTimeEnemy = .0f;
	bulletCleanTimeEnemy = .0f;
	numberOfEnemies = 0;
	node0 = true;
	node1 = false;
	node2 = false;
	node3 = false;
	node4 = false;

	//gameplay variables
	deltaCd = .25f;
	bulletCd = .8f;
	bulletCdEnemy = 2.0f;
	bulletSpeed = 1000.f;
	bulletSpeedEnemy = 100.f;
	enemySpeed = 400.f;
	posAccelChange = 2.0f;
	negAccelChange = .1f;
	accelMax = 500.0f;
	numberOfEnemies = 5;

#pragma endregion

	//create window...view...set player
	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Game", sf::Style::Fullscreen);
	//sf::RenderWindow window(sf::VideoMode(800,600), "Game");
	sf::RenderWindow& win = window;
	gameView.setSize(sf::Vector2f((float)sf::VideoMode::getDesktopMode().width, (float)sf::VideoMode::getDesktopMode().height));
	playerOne.playerShape.setPosition(gameView.getCenter().x, gameView.getCenter().y);

	//load background
	sf::Texture backGroundLayerOne;
	backGroundLayerOne.loadFromFile("space.png");
	backGroundLayerOne.setRepeated(true);
	sf::Sprite backGroundLayerOneSprite;
	backGroundLayerOneSprite.setTexture(backGroundLayerOne);
	backGroundLayerOneSprite.setTextureRect(sf::IntRect(0, 0, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
	backGroundLayerOneSprite.setOrigin(backGroundLayerOneSprite.getGlobalBounds().width / 2.f, backGroundLayerOneSprite.getGlobalBounds().height / 2.f);
	backGroundLayerOneSprite.setPosition(gameView.getCenter().x, gameView.getCenter().y);

	//enemy pathing nodes & load enemies (includes loading nodes)
	//TODO:(move to levels)
	enemyNodeOne = enemyOne.enemyNode(100, 1500, 750, pO);
	enemyNodeTwo = enemyOne.enemyNode(100, 1500, 750, pO);
	enemyNodeThree = enemyOne.enemyNode(100, 1500, 750, pO);
	enemyNodeFour = enemyOne.enemyNode(100, 1500, 750, pO);

	//TODO: make more flexible
	//ex: level 1 = 5 enemies
	enemyOne.loadEnemies(numberOfEnemies, eV, eO, pO);
	for (int i = 0; i < numberOfEnemies; i++)
	{
		nodesZero.push_back(node0);
		nodesOne.push_back(node1);
		nodesTwo.push_back(node2);
		nodesThree.push_back(node3);
		nodesFour.push_back(node4);
		bulletTimeEnemy = bulletClockEnemy.restart().asSeconds();
		bulletTimeVectorEnemy.push_back(bulletClockEnemy);
		bulletTimeEnemies.push_back(bulletTimeEnemy);
	}
	
	//window loop 
	//TODO: Create game loop
	while (win.isOpen())
	{
		//begin gameclock
		delta = gameClock.restart().asSeconds();

		//draw back layers first
		window.clear();
		window.setView(gameView);
		window.draw(backGroundLayerOneSprite);

		//rotate player based on mouse position
		playerOne.PlayerRotation(win, pO.playerShape);

		//enemies
		//TODO: incorporate into levels.cpp
		for(unsigned int i = 0; i < enemies.size(); i++)
		{
			enemies[i].enemyRotation(eV[i].enemyShape, pO.playerShape);
			enemyAngle = enemies[i].nodeCollision(eV, eNO, nO, nZ, i, eA);
			enemyAngle = enemies[i].nodeCollision(eV, eNT, nT, nO, i, eA);
			enemyAngle = enemies[i].nodeCollision(eV, eNTR, nTR, nT, i, eA);
			enemyAngle = enemies[i].nodeCollision(eV, eNF, nF, nTR, i, eA);
			if (nodesFour[i] == true)
			{
				//reset
				nodesOne[i] = false;
				nodesTwo[i] = false;
				nodesThree[i] = false;
				nodesFour[i] = false;
			}
			enemies[i].enemyShape.move(cos(enemyAngle) * enemySpeed * delta, sin(enemyAngle) * enemySpeed * delta);
			window.draw(enemies[i].enemyShape);
			
			bulletTimeEnemies[i] = bulletTimeVectorEnemy[i].getElapsedTime().asSeconds();
			if (bulletTimeEnemies[i] > bulletCdEnemy)
			{
				bulletTimeEnemies[i] = bulletTimeVectorEnemy[i].restart().asSeconds();
				bulletCleanTimeEnemy = bulletCleanUpEnemy.restart().asSeconds();
				bulletTimeFVectorEnemy.push_back(bulletCleanTimeEnemy);
				bulletTimeCVectorEnemy.push_back(bulletCleanUpEnemy);
				enemyBullet.bulletShape.setPosition(sf::Vector2f(enemies[i].enemyShape.getPosition().x, enemies[i].enemyShape.getPosition().y));
				bulletAngleEnemy = enemyBullet.BulletAngleEnemy(win, eB.bulletShape, pO);
				bulletVectorEnemy.push_back(enemyBullet.bulletShape);
				bulletAngleVectorEnemy.push_back(bulletAngleEnemy);
			}
			
			for (unsigned int i = 0; i < bulletVectorEnemy.size(); i++)
			{
				bulletVectorEnemy[i].move(cos(bulletAngleVectorEnemy[i]) * bulletSpeedEnemy * delta, sin(bulletAngleVectorEnemy[i]) * bulletSpeedEnemy * delta);
				bulletTimeFVectorEnemy[i] = bulletTimeCVectorEnemy[i].getElapsedTime().asSeconds();
				window.draw(bulletVectorEnemy[i]);
			}

			for (unsigned int i = 0; i < bulletVectorEnemy.size(); i++)
			{
				if (bulletTimeFVectorEnemy[i] > 5.0f)
				{
					bulletVectorEnemy.erase(bulletVectorEnemy.begin());
					bulletTimeCVectorEnemy.erase(bulletTimeCVectorEnemy.begin());
					bulletAngleVectorEnemy.erase(bulletAngleVectorEnemy.begin());
				}
			}
		}

		//Keypress
			//movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			wKeyPressTime = wKeyPressClock.restart().asSeconds();
			cameraChaseTime = cameraChaseClock.restart().asSeconds();
			if (wKeyAccel < accelMax)
			{
				wKeyAccel += posAccelChange;
			}
			wKeyVelocity = wKeyAccel * delta;
			gameView.move(.0f, -wKeyVelocity);
			playerOne.playerShape.move(.0f, -wKeyVelocity);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			aKeyPressTime = aKeyPressClock.restart().asSeconds();
			cameraChaseTime = cameraChaseClock.restart().asSeconds();
			if (aKeyAccel < accelMax)
			{
				aKeyAccel += posAccelChange;
			}
			aKeyVelocity = aKeyAccel * delta;
			gameView.move(-aKeyVelocity, .0f);
			playerOne.playerShape.move(-aKeyVelocity, 0.f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			sKeyPressTime = sKeyPressClock.restart().asSeconds();
			cameraChaseTime = cameraChaseClock.restart().asSeconds();
			if (sKeyAccel < accelMax)
			{
				sKeyAccel += posAccelChange;
			}
			sKeyVelocity = sKeyAccel * delta;
			gameView.move(0.f, sKeyVelocity);
			playerOne.playerShape.move(0.f, sKeyVelocity);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			dKeyPressTime = dKeyPressClock.restart().asSeconds();
			cameraChaseTime = cameraChaseClock.restart().asSeconds();
			if (dKeyAccel < accelMax)
			{
				dKeyAccel += posAccelChange;
			}
			dKeyVelocity = dKeyAccel * delta;
			gameView.move(dKeyVelocity, 0.f);
			playerOne.playerShape.move(dKeyVelocity, 0.f);
		}

			//player bullets
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bulletTime > bulletCd)
		{
			bulletTime = bulletClock.restart().asSeconds();
			bulletCleanTime = bulletCleanUp.restart().asSeconds();
			bulletTimeFVector.push_back(bulletCleanTime);
			bulletTimeVector.push_back(bulletCleanUp);
			playerBullet.bulletShape.setPosition(sf::Vector2f(playerOne.playerShape.getPosition().x, playerOne.playerShape.getPosition().y));
			bulletAngle = playerBullet.BulletAnglePlayer(win, pB.bulletShape);
			bulletVector.push_back(playerBullet.bulletShape);
			bulletAngleVector.push_back(bulletAngle);
		}		

		for (unsigned int i = 0; i < bulletVector.size(); i++)
		{
			bulletVector[i].move(cos(bulletAngleVector[i]) * bulletSpeed * delta, sin(bulletAngleVector[i]) * bulletSpeed * delta);
			bulletTimeFVector[i] = bulletTimeVector[i].getElapsedTime().asSeconds();
			window.draw(bulletVector[i]);
		}
		
		//Key Release
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			playerOne.playerShape.move(.0f, -wKeyVelocity);
			gameView.move(.0f, -wKeyVelocity);
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			playerOne.playerShape.move(-aKeyVelocity, .0f);
			gameView.move(-aKeyVelocity, .0f);
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			playerOne.playerShape.move(.0f, sKeyVelocity);
			gameView.move(.0f, sKeyVelocity);
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			playerOne.playerShape.move(dKeyVelocity, .0f);
			gameView.move(dKeyVelocity, .0f);
		}

		//Camera
		playerOne.PlayerCameraChase(pO.playerShape, gV, cCT, dCd);

		//Update timers & velocity
		wKeyPressTime = wKeyPressClock.getElapsedTime().asSeconds();
		aKeyPressTime = aKeyPressClock.getElapsedTime().asSeconds();
		sKeyPressTime = sKeyPressClock.getElapsedTime().asSeconds();
		dKeyPressTime = dKeyPressClock.getElapsedTime().asSeconds();
		cameraChaseTime = cameraChaseClock.getElapsedTime().asSeconds();
		bulletTime = bulletClock.getElapsedTime().asSeconds();
		wKeyVelocity = wKeyAccel * delta;
		aKeyVelocity = aKeyAccel * delta;
		sKeyVelocity = sKeyAccel * delta;
		dKeyVelocity = dKeyAccel * delta;

		//Key release decrease velocity
		if ((wKeyVelocity > .0f) && (wKeyPressTime > deltaCd))
		{
			wKeyAccel -= negAccelChange;
			if (wKeyAccel < 0.f)
			{
				wKeyAccel = 0.f;
			}
		}

		if ((aKeyVelocity > .0f) && (aKeyPressTime > deltaCd))
		{
			aKeyAccel -= negAccelChange;
			if (aKeyAccel < 0.f)
			{
				aKeyAccel = 0.f;
			}
		}

		if ((sKeyVelocity > .0f) && (sKeyPressTime > deltaCd))
		{
			sKeyAccel -= negAccelChange;
			if (sKeyAccel < 0.f)
			{
				sKeyAccel = 0.f;
			}
		}

		if ((dKeyVelocity > .0f) && (dKeyPressTime > deltaCd))
		{
			dKeyAccel -= negAccelChange;
			if (dKeyAccel < 0.f)
			{
				dKeyAccel = 0.f;
			}
		}

		//player bullet cleanup
		for (unsigned int i = 0; i < bulletVector.size(); i++)
		{
			if (bulletTimeFVector[i] > 5.0f)
			{
				bulletVector.erase(bulletVector.begin());
				bulletTimeVector.erase(bulletTimeVector.begin());
				bulletTimeFVector.erase(bulletTimeFVector.begin());
				bulletAngleVector.erase(bulletAngleVector.begin());
			}
		}

		//background scrolling
		backGroundLayerOneSprite.setPosition(playerOne.playerShape.getPosition().x, playerOne.playerShape.getPosition().y);
		backGroundLayerOneSprite.setTextureRect(sf::IntRect((int)playerOne.playerShape.getPosition().x*1, (int)playerOne.playerShape.getPosition().y*1, 1920, 1080));

		//check for window close
		while (win.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				win.close();
		}
		
		//final draw layer
		window.draw(pO.playerShape);
		window.display();
	}
}