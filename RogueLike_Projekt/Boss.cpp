#include"Boss.h"

/** \brief Funkcja aktualizuj�ca pozycje boss�w oraz okre�laj�ca ich specjalne umiej�tno�ci
 *
 * G��wna funkcja dla naszych boss�w, w niej s� sprecyzowane unikalne zachowania dla ka�dego bossa
 * @param deltaTime Zmienna okre�laj�ca ile czasu min�o pomi�dzy klatkami gry (umo�liwia ona p�ynniejsze dzia�anie gry, poniewa� niezale�nie od wykorzystanie zasob�w komputera gra nie powinna przyspiesza�, ani zwalnia�)
 * @param bulletVec Wska�nik na vector naboi potwor�w
 * @param monsterVec Wska�nik na vector potwor�w
 * @param player Wys�ana ca�a nasza g��wna posta�
 * @param ghostTexture Wska�nik na teksture ducha
 */

void boss::Update(float deltaTime, std::vector<Bullet>& bulletVec, std::vector<monster>& monsterVec, hero player, sf::Texture* ghostTexture, sf::Texture* demonTexture)
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
	else if (special_movement )
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
	if (spawn_delay_clock.getElapsedTime().asSeconds() >= 15.0f && spawn == true)
	{
		if (shooting == true)
		{
			monster ghost(ghostTexture, sf::Vector2u(4, 1), 0.1f, 75.0f, 1.5f, 150.0f, 30.0f, 4.0f, { 12.0f,17.0f }, { body.getPosition().x - 25,body.getPosition().y }, false, true, false, NULL, { 0,0 });
			monster ghost1(ghostTexture, sf::Vector2u(4, 1), 0.1f, 75.0f, 1.5f, 150.0f, 30.0f, 4.0f, { 12.0f,17.0f }, { body.getPosition().x + 25,body.getPosition().y }, false, true, false, NULL, { 0,0 });
			monsterVec.push_back(ghost);
			monsterVec.push_back(ghost1);
			spawn_delay_clock.restart();
			animation_clock.restart();
			row = 1;
		}
		else
		{
			monster demon(demonTexture, sf::Vector2u(4, 1), 0.1f, 110.0f, 0.0f, 0.0f, 10.0f, 6.0f, { 14.0f,22.0f }, { body.getPosition().x - 25,body.getPosition().y }, false, false, false, NULL, { 0,0 });
			monster demon1(demonTexture, sf::Vector2u(4, 1), 0.1f, 110.0f, 0.0f, 0.0f, 10.0f, 6.0f, { 14.0f,22.0f }, { body.getPosition().x + 25,body.getPosition().y }, false, false, false, NULL, { 0,0 });
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
	if (memSpeed == 80.0f && spawn == true)
	{
		if (abs(getDirVec(player).x) <= 5.0f || abs(getDirVec(player).y) <= 5.0f)
		{
			speed = 200.0f;
		}
	}
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}