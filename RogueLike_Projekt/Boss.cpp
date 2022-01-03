#include"Boss.h"
void boss::Update(float deltaTime, sf::Texture* arrow, std::vector<Bullet>& bulletVec, std::vector<monster>& monsterVec, hero player, sf::Texture* ghostTexture)
{
	if (getDirVec(player).x < 0) {
		faceRight = true;
	}
	else {
		faceRight = false;
	}
	if (fire_delay_clock.getElapsedTime().asSeconds() >= fire_rate && shooting == true)
	{
		sf::Vector2f shottingDir = getDirVec(player), test1 = {15.0f,2.0f}, test2 = { 2.0f,15.0f };
		Bullet newBullet({ 10,10 }, body.getPosition(), shot_speed, damage, -shottingDir, arrow, getDirDeg(shottingDir));
		Bullet newBullet1({ 10,10 }, { body.getPosition().x, body.getPosition().y+10}, shot_speed, damage, -shottingDir + test1, arrow, getDirDeg(shottingDir));
		Bullet newBullet2({ 10,10 }, { body.getPosition().x, body.getPosition().y-10}, shot_speed, damage, -shottingDir - test1, arrow, getDirDeg(shottingDir));
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
		monster ghost(ghostTexture, sf::Vector2u(4, 1), 0.1f, 75.0f, 1.5f, 150.0f, 30.0f, 4.0f, { 12.0f,17.0f }, { body.getPosition().x - 25,body.getPosition().y }, false, true, false);
		monster ghost1(ghostTexture, sf::Vector2u(4, 1), 0.1f, 75.0f, 1.5f, 150.0f, 30.0f, 4.0f, { 12.0f,17.0f }, { body.getPosition().x + 25,body.getPosition().y }, false, true, false);
		monsterVec.push_back(ghost);
		monsterVec.push_back(ghost1);
		spawn_delay_clock.restart();
		animation_clock.restart();
		row = 1;
	}
	if(animation_clock.getElapsedTime().asSeconds()>=0.5f) {
		row = 0;
	}
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}