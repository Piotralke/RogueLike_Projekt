#include"Boss.h"
void boss::Update(float deltaTime, sf::Texture* arrow, std::vector<Bullet>& bulletVec, std::vector<monster>& monsterVec, hero player, sf::Texture* ghostTexture)
{
	if (fire_delay_clock.getElapsedTime().asSeconds() >= fire_rate && shooting == true)
	{
		sf::Vector2f shottingDir = getDirVec(player);
		Bullet newBullet({ 8,8 }, body.getPosition(), shot_speed, damage, -shottingDir, arrow, getDirDeg(shottingDir));
		Bullet newBullet1({ 8,8 }, body.getPosition(), shot_speed, damage, { -shottingDir.x*(float)cos(30) - shottingDir.y * (float)sin(30),-shottingDir.x * (float)sin(30) - shottingDir.y * (float)cos(30) }, arrow, getDirDeg(shottingDir));
		Bullet newBullet2({ 8,8 }, body.getPosition(), shot_speed, damage, { -shottingDir.x * (float)cos(330) - shottingDir.y * (float)sin(330),-shottingDir.x * (float)sin(330) - shottingDir.y * (float)cos(330) }, arrow, getDirDeg(shottingDir));
		bulletVec.push_back(newBullet);
		bulletVec.push_back(newBullet1);
		bulletVec.push_back(newBullet2);
		fire_delay_clock.restart();
	}
	if (speed > 0.0f)
	{
		sf::Vector2f moveDir = -getDirVec(player);
		sf::Vector2f moveDirNorm = { moveDir.x / (float)sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2)), moveDir.y / (float)sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2)) };
		body.move({ moveDirNorm.x * speed * deltaTime, moveDirNorm.y * speed * deltaTime });
	}
	if (spawn_delay_clock.getElapsedTime().asSeconds() >= 15.0f)
	{
		monster ghost(ghostTexture, sf::Vector2u(4, 1), 0.1f, 75.0f, 1.5f, 150.0f, 30.0f, 4.0f, { 12.0f,17.0f }, { body.getPosition().x - 25,body.getPosition().y }, false, true);
		monster ghost1(ghostTexture, sf::Vector2u(4, 1), 0.1f, 75.0f, 1.5f, 150.0f, 30.0f, 4.0f, { 12.0f,17.0f }, { body.getPosition().x + 25,body.getPosition().y }, false, true);
		monsterVec.push_back(ghost);
		monsterVec.push_back(ghost1);
		spawn_delay_clock.restart();
	}
	animation.Update(0, deltaTime, true);
	body.setTextureRect(animation.uvRect);
}