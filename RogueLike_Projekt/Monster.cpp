#include "Monster.h"
#include <iostream>
sf::Vector2f monster::getDirVec(hero player)
{
	return this->GetPosition() - player.GetPosition();
}

float monster::getDirDeg(sf::Vector2f DirVec)
{
	return std::atan2f(DirVec.y, DirVec.x) * 180 / PI - 90.0f;
}

void monster::Update(float deltaTime, sf::Texture* arrow, std::vector<Bullet>& bulletVec, std::vector<monster>& monsterVec, hero player, int& skeleton_count, int& dead_skeleton)
{
	if (fire_delay_clock.getElapsedTime().asSeconds() >= fire_rate && shooting == true)
	{
		sf::Vector2f shottingDir = getDirVec(player);
		Bullet newBullet({ 8,8 }, body.getPosition(), shot_speed, damage, -shottingDir, arrow, getDirDeg(shottingDir));
		bulletVec.push_back(newBullet);
		fire_delay_clock.restart();
	}
	if (speed > 0.0f)
	{
		if (memSpeed >= 170.0f)
		{
			if (jump_clock.getElapsedTime().asSeconds() >= 2.5f)
			{
				std::cout << "weszlo" << std::endl;
				jump_clock.restart();
				speed = memSpeed;
				row = 1;
				sf::Vector2f moveDir = -getDirVec(player);
				if (abs(getDirVec(player).x) > 100.0f || abs(getDirVec(player).y) > 100.0f)
				{
					std::cout << "losowo" << std::endl;
					float vecX = -50.0f + rand() / (RAND_MAX / 50.0f);
					float vecY = -50.0f + rand() / (RAND_MAX / 50.0f);
					//std::cout << "X" << vecX << std::endl << "Y" << vecY << std::endl;
					moveDir = { vecX, vecY };
					sf::Vector2f moveDirNorm = { moveDir.x / (float)sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2)), moveDir.y / (float)sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2)) };
					body.move({ moveDirNorm.x * speed * deltaTime, moveDirNorm.y * speed * deltaTime });
					std::cout << speed;
					//std::cout << "X" << moveDirNorm.x << std::endl << "Y" << moveDirNorm.y << std::endl;
					//chuj wie dlaczego pajaki sie nie ruszaja, speed jest, wektory tez git dzialaja, ani do gracza ani losowo nie chce kurwa chodzic
				}
				else
				{
					std::cout << "do gracza" << std::endl;
					sf::Vector2f moveDirNorm = { moveDir.x / (float)sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2)), moveDir.y / (float)sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2)) };
					body.move({ moveDirNorm.x * speed * deltaTime, moveDirNorm.y * speed * deltaTime });
					std::cout << "X" << moveDirNorm.x << std::endl << "Y" << moveDirNorm.y << std::endl;
				}
			}
			else if(jump_clock.getElapsedTime().asSeconds()>=0.9f)
			{
				row = 0;
				speed = 0.01;	//musi byc tyle, bo jak 0 to juz tutaj nie wejdzie wgl a przy tej wartosci w sumie i tak stoi w miejscu
			}
			
		}
		else
		{
			sf::Vector2f moveDir = -getDirVec(player);
			sf::Vector2f moveDirNorm = { moveDir.x / (float)sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2)), moveDir.y / (float)sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2)) };
			body.move({ moveDirNorm.x * speed * deltaTime, moveDirNorm.y * speed * deltaTime });
		}
	}
	if (getDirVec(player).x < 0) {
		faceRight = true;
	}
	else {
		faceRight = false;
	}
	if (this->resurection == true && this->health <= 0.0f)
	{
		if (this->dead == false)
		{
			dead_skeleton++;
			dead = true;
			animation_clock.restart();
			row = 1;
			speed = 0.0f;
		}
		if (skeleton_count == monsterVec.size() && dead_skeleton == monsterVec.size())
		{
			skeleton_count = 0;
			monsterVec.clear();
			monsterVec = std::vector<monster>();
		}	
	}
	if (animation_clock.getElapsedTime().asSeconds() >= 10.0f && this->dead == true) {

		speed = memSpeed;
		health = memHealth;
		row = 0;
		dead = false;
		dead_skeleton--;
	}
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}
