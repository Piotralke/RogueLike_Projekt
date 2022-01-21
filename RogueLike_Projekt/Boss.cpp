#include"Boss.h"
#include <iostream>
/** \brief  Funkcja aktualizująca pozycje bossów oraz określająca ich specjalne umiejętności
 *
 * Główna funkcja dla naszych bossów, w niej są sprecyzowane unikalne zachowania dla każdego bossa
 * @param deltaTime Zmienna określająca ile czasu minęło pomiędzy klatkami gry (umożliwia ona płynniejsze działanie gry, ponieważ niezależnie od wykorzystanie zasobów komputera gra nie powinna przyspieszać, ani zwalniać)
 * @param bulletVec Wskaźnik na vector naboi potworów
 * @param monsterVec Wskaźnik na vector potworów
 * @param player Wysłana cała nasza główna postać
 * @param ghostTexture Wskaźnik na teksture ducha
 * @param objectVec Wskaźnik na vector obiektów
 * @param wallVec Wskaźnik na vector ścian pokoju
 */

void boss::Update(float deltaTime, std::vector<Bullet>& bulletVec, std::vector<monster>& monsterVec, hero player, sf::Texture* ghostTexture, sf::Texture* demonTexture, std::vector<Object>& objectVec, std::vector<sf::RectangleShape>& wallVec)
{
	if (getDirVec(player).x < 0) {
		faceRight = true;
	}
	else {
		faceRight = false;
	}
	if (fire_delay_clock.getElapsedTime().asSeconds() >= fire_rate && shooting == true && can_shot == true)
	{
		sf::Vector2f shottingDir = getDirVec(player);
		Bullet newBullet(bullet_size, body.getPosition(), shot_speed, damage, -shottingDir, arrow, getDirDeg(shottingDir)-90);
		bulletVec.push_back(newBullet);
		if (triple_shot == true)
		{
			sf::Vector2f test1 = { 15.0f,2.0f };
			Bullet newBullet1(bullet_size, { body.getPosition().x, body.getPosition().y + 10 }, shot_speed, damage, -shottingDir + test1, arrow, getDirDeg(shottingDir)-90);
			Bullet newBullet2(bullet_size, { body.getPosition().x, body.getPosition().y - 10 }, shot_speed, damage, -shottingDir - test1, arrow, getDirDeg(shottingDir)-90);
			bulletVec.push_back(newBullet1);
			bulletVec.push_back(newBullet2);
		}
		fire_delay_clock.restart();
	}
	if (speed > 0.0f && !special_movement)
	{
		sf::Vector2f moveDir = -getDirVec(player);
		sf::Vector2f moveDirNorm = { moveDir.x / (float)sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2)), moveDir.y / (float)sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2)) };
		body.move({ moveDirNorm.x * speed * deltaTime, moveDirNorm.y * speed * deltaTime });
	}
	else if (special_movement && shooting == true )
	{
		if (abs((float)sqrt(pow(-getDirVec(player).x, 2) + pow(-getDirVec(player).y, 2)) < 150.0f ))
		{
			can_shot = false;
			speed = memSpeed;
			sf::Vector2f moveDir = getDirVec(player);
			sf::Vector2f moveDirNorm = { moveDir.x / (float)sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2)), moveDir.y / (float)sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2)) };
			body.move({ moveDirNorm.x * speed * deltaTime, moveDirNorm.y * speed * deltaTime });
			if (!spawn)
			{
				row = 1;
				if (faceRight == true)
					faceRight = false;
				else
					faceRight = true;
			}
				
		}
		else
		{
			row = 0;
			can_shot = true;
			speed = 0;
		}
	}
	else if (memSpeed == 80.0f && spawn == true)
	{
		if (80>= body.getPosition().x || body.getPosition().x >= 620 || 80 >= body.getPosition().y || body.getPosition().y >= 320 )
		{
			std::cout << "dupa" << std::endl;
			running = true;
			speed = memSpeed;
			row = 0;
			randomDir.x = (rand() % 21 - 10) / 10;
			randomDir.y = (rand() % 21 - 10) / 10;
		}
		if ((abs(getDirVec(player).x) <= 5.0f && running == true) || (abs(getDirVec(player).y) <= 5.0f && running == true))
		{
			std::cout << "jebac figursona" << std::endl;
			randomDir = -getDirVec(player);
			randomDir = { randomDir.x / (float)sqrt(pow(randomDir.x, 2) + pow(randomDir.y, 2)), randomDir.y / (float)sqrt(pow(randomDir.x, 2) + pow(randomDir.y, 2)) };
			speed = 250.0f;
			running = false;
		}
		if (running == false)
		{
			row = 1;
		}
		body.move({ randomDir.x * speed * deltaTime, randomDir.y * speed * deltaTime });
	}
	if (spawn_delay_clock.getElapsedTime().asSeconds() >= 15.0f && spawn == true)
	{
		if (shooting == true)
		{
			monster ghost(ghostTexture, sf::Vector2u(4, 1), 0.1f, 75.0f, 1.5f, 150.0f, 30.0f, 4.0f, { 12.0f,17.0f }, { body.getPosition().x ,body.getPosition().y }, false, true, false, NULL, { 0,0 });
			monster ghost1(ghostTexture, sf::Vector2u(4, 1), 0.1f, 75.0f, 1.5f, 150.0f, 30.0f, 4.0f, { 12.0f,17.0f }, { body.getPosition().x ,body.getPosition().y }, false, true, false, NULL, { 0,0 });
			monsterVec.push_back(ghost);
			monsterVec.push_back(ghost1);
			spawn_delay_clock.restart();
			animation_clock.restart();
			row = 1;
		}
		else
		{
			monster demon(demonTexture, sf::Vector2u(4, 1), 0.1f, 110.0f, 0.0f, 0.0f, 10.0f, 6.0f, { 14.0f,22.0f }, { body.getPosition().x ,body.getPosition().y }, false, false, false, NULL, { 0,0 });
			monster demon1(demonTexture, sf::Vector2u(4, 1), 0.1f, 110.0f, 0.0f, 0.0f, 10.0f, 6.0f, { 14.0f,22.0f }, { body.getPosition().x ,body.getPosition().y }, false, false, false, NULL, { 0,0 });
			monsterVec.push_back(demon);
			monsterVec.push_back(demon1);
			spawn_delay_clock.restart();
			animation_clock.restart();
			row = 2;
		}
	}
	if(animation_clock.getElapsedTime().asSeconds()>=0.5f && spawn == true) {
		row = 0;
	}
	
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}