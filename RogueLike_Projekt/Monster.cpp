#include "Monster.h"

void monster::Update(float deltaTime, sf::Clock &fire_delay_clock, sf::Texture* arrow, std::vector<Bullet>& bulletVec, hero player)
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
		sf::Vector2f moveDir = -getDirVec(player);
		sf::Vector2f moveDirNorm = { moveDir.x / (float)sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2)), moveDir.y / (float)sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2)) };
		body.move({ moveDirNorm.x * speed * deltaTime, moveDirNorm.y * speed * deltaTime });
	}
	animation.Update(0, deltaTime, true);
	body.setTextureRect(animation.uvRect);
}
sf::Vector2f monster::getDirVec(hero player)
{
	return this->GetPosition() - player.GetPosition();
}
float monster::getDirDeg(sf::Vector2f DirVec)
{
	return std::atan2f(DirVec.y, DirVec.x) * 180 / PI - 90.0f;
}