#include "Monster.h"

void monster::move(hero player)
{
	// potrzebny pathpfind algorithm
}
void monster::Update(float deltaTime, sf::Clock &fire_delay_clock, sf::Texture* arrow, std::vector<Bullet>& bulletVec, hero player)
{
	if (fire_delay_clock.getElapsedTime().asSeconds() >= fire_rate)
	{
		sf::Vector2f temp = getDirVec(player);
		Bullet newBullet({ 8,8 }, body.getPosition(), shot_speed, 1.0f, -temp, arrow, getDirDeg(temp)-90.0f);
		bulletVec.push_back(newBullet);
		fire_delay_clock.restart();
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
	return std::atan2f(DirVec.y, DirVec.x) * 180 / PI;
}